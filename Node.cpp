#include "StdAfx.h"
#include "Node.h"

NameGenerator Node::msNameGenerator("Unnamed_");

Node::Node()
	:mParent(0),
	mNeedParentUpdate(false),
	mNeedChildUpdate(false),
	mParentNotified(false),
	mQueuedForUpdate(false),
	mOrientation(Quaternion::IDENTITY),
	mPosition(Vector3::ZERO),
	mScale(Vector3::UNIT_SCALE),
	mInheritOrientation(true),
	mInheritScale(true),
	mDerivedOrientation(Quaternion::IDENTITY),
	mDerivedPosition(Vector3::ZERO),
	mDerivedScale(Vector3::UNIT_SCALE)
//	mInitialPosition(Vector3::ZERO),
//	mInitialOrientation(Quaternion::IDENTITY),
//	mInitialScale(Vector3::UNIT_SCALE),
//	mCachedTransformOutOfDate(true),
//	mListener(0),
//	mDebug(0)
{
	// Generate a name
	mName = msNameGenerator.generate();

	needUpdate();

}

Node::Node(const std::string& name)
	:
	mParent(0),
	mNeedParentUpdate(false),
	mNeedChildUpdate(false),
	mParentNotified(false),
	mQueuedForUpdate(false),
	mName(name),
	mOrientation(Quaternion::IDENTITY),
	mPosition(Vector3::ZERO),
	mScale(Vector3::UNIT_SCALE),
	mInheritOrientation(true),
	mInheritScale(true),
	mDerivedOrientation(Quaternion::IDENTITY),
	mDerivedPosition(Vector3::ZERO),
	mDerivedScale(Vector3::UNIT_SCALE)
	//mInitialPosition(Vector3::ZERO),
	//mInitialOrientation(Quaternion::IDENTITY),
	//mInitialScale(Vector3::UNIT_SCALE),
	//mCachedTransformOutOfDate(true),
	//mListener(0),
	//mDebug(0)

{

	needUpdate();

}

Node::~Node()
{
	
	removeAllChildren();
	if (mParent)
		mParent->removeChild(this);

	/*if (mQueuedForUpdate)
	{
		// Erase from queued updates
		QueuedUpdates::iterator it =
			std::find(msQueuedUpdates.begin(), msQueuedUpdates.end(), this);
		assert(it != msQueuedUpdates.end());
		if (it != msQueuedUpdates.end())
		{
			// Optimised algorithm to erase an element from unordered vector.
			*it = msQueuedUpdates.back();
			msQueuedUpdates.pop_back();
		}
	}*/

}
void Node::setParent(Node* parent)
{
	bool different = (parent != mParent);

	mParent = parent;
	// Request update from parent
	mParentNotified = false;
	needUpdate();
}

const Matrix4& Node::_getFullTransform(void) const
{
	if (mCachedTransformOutOfDate)
	{
#if OGRE_NODE_INHERIT_TRANSFORM
		Ogre::Matrix4 tr;
		tr.makeTransform(mPosition, mScale, mOrientation);

		if (mParent == NULL)
		{
			mCachedTransform = tr;
		}
		else if (mInheritOrientation && mInheritScale) // everything is inherited
		{
			mCachedTransform = mParent->_getFullTransform() * tr;
		}
		else if (!mInheritOrientation && !mInheritScale) // only position is inherited
		{
			mCachedTransform = tr;
			mCachedTransform.setTrans(tr.getTrans() + mParent->_getFullTransform().getTrans());
		}
		else // shear is inherited together with orientation, controlled by mInheritOrientation
		{
			const Ogre::Matrix4& parentTr = mParent->_getFullTransform();
			Ogre::Vector3 parentScale(
				parentTr.transformDirectionAffine(Vector3::UNIT_X).length(),
				parentTr.transformDirectionAffine(Vector3::UNIT_Y).length(),
				parentTr.transformDirectionAffine(Vector3::UNIT_Z).length());

			assert(mInheritOrientation ^ mInheritScale);
			mCachedTransform = (mInheritOrientation ? Matrix4::getScale(1.0f / parentScale)  * parentTr : Matrix4::getScale(parentScale)) * tr;
		}
#else
		// Use derived values
		mCachedTransform.makeTransform(
			_getDerivedPosition(),
			_getDerivedScale(),
			_getDerivedOrientation());
#endif
		mCachedTransformOutOfDate = false;
	}
	return mCachedTransform;
}

void Node::_update(bool updateChildren, bool parentHasChanged)
{
	// always clear information about parent notification
	mParentNotified = false;

	// See if we should process everyone
	if (mNeedParentUpdate || parentHasChanged)
	{
		// Update transforms from parent
		_updateFromParent();
	}

	if (updateChildren)
	{
		if (mNeedChildUpdate || parentHasChanged)
		{
			ChildNodeMap::iterator it, itend;
			itend = mChildren.end();
			for (it = mChildren.begin(); it != itend; ++it)
			{
				Node* child = it->second;
				child->_update(true, true);
			}
		}
		else
		{
			// Just update selected children
			ChildUpdateSet::iterator it, itend;
			itend = mChildrenToUpdate.end();
			for (it = mChildrenToUpdate.begin(); it != itend; ++it)
			{
				Node* child = *it;
				child->_update(true, false);
			}

		}

		mChildrenToUpdate.clear();
		mNeedChildUpdate = false;
	}
}

void Node::_updateFromParent() const
{
	updateFromParentImpl();
}

void Node::updateFromParentImpl(void) const
{
	mCachedTransformOutOfDate = true;

	if (mParent)
	{
#if OGRE_NODE_INHERIT_TRANSFORM
		// Decompose full transform to position, orientation and scale, shear is lost here.
		_getFullTransform().decomposition(mDerivedPosition, mDerivedScale, mDerivedOrientation);
#else
		// Update orientation
		const Quaternion& parentOrientation = mParent->_getDerivedOrientation();
		if (mInheritOrientation)
		{
			// Combine orientation with that of parent
			mDerivedOrientation = parentOrientation * mOrientation;
		}
		else
		{
			// No inheritance
			mDerivedOrientation = mOrientation;
		}

		// Update scale
		const Vector3& parentScale = mParent->_getDerivedScale();
		if (mInheritScale)
		{
			// Scale own position by parent scale, NB just combine
			// as equivalent axes, no shearing
			mDerivedScale = parentScale * mScale;
		}
		else
		{
			// No inheritance
			mDerivedScale = mScale;
		}

		// Change position vector based on parent's orientation & scale
		mDerivedPosition = parentOrientation * (parentScale * mPosition);

		// Add altered position vector to parents
		mDerivedPosition += mParent->_getDerivedPosition();
#endif
	}
	else
	{
		// Root node, no parent
		mDerivedOrientation = mOrientation;
		mDerivedPosition = mPosition;
		mDerivedScale = mScale;
	}

	mNeedParentUpdate = false;

}

//-----------------------------------------------------------------------
Node* Node::createChild(const Vector3& inTranslate, const Quaternion& inRotate)
{
	Node* newNode = createChildImpl();
	newNode->setPosition(inTranslate);
	newNode->setOrientation(inRotate);
	this->addChild(newNode);

	return newNode;
}
//-----------------------------------------------------------------------
Node* Node::createChild(const std::string& name, const Vector3& inTranslate, const Quaternion& inRotate)
{
	Node* newNode = createChildImpl(name);
	newNode->setPosition(inTranslate);
	newNode->setOrientation(inRotate);
	this->addChild(newNode);

	return newNode;
}
//-----------------------------------------------------------------------
void Node::addChild(Node* child)
{
	if (child->mParent)
	{
		/*OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS,
			"Node '" + child->getName() + "' already was a child of '" +
			child->mParent->getName() + "'.",
			"Node::addChild");*/
	}

	mChildren.insert(ChildNodeMap::value_type(child->getName(), child));
	child->setParent(this);

}
//-----------------------------------------------------------------------
Node* Node::getChild(unsigned short index) const
{
	if (index < mChildren.size())
	{
		ChildNodeMap::const_iterator i = mChildren.begin();
		while (index--) ++i;
		return i->second;
	}
	else
		return NULL;
}
//-----------------------------------------------------------------------
Node* Node::removeChild(unsigned short index)
{
	if (index < mChildren.size())
	{
		ChildNodeMap::iterator i = mChildren.begin();
		while (index--) ++i;
		Node* ret = i->second;
		// cancel any pending update
		cancelUpdate(ret);

		mChildren.erase(i);
		ret->setParent(NULL);
		return ret;
	}
	else
	{
	/*	OGRE_EXCEPT(
			Exception::ERR_INVALIDPARAMS,
			"Child index out of bounds.",
			"Node::getChild");*/
	}
	return 0;
}
//-----------------------------------------------------------------------
Node* Node::removeChild(Node* child)
{
	if (child)
	{
		ChildNodeMap::iterator i = mChildren.find(child->getName());
		// ensure it's our child
		if (i != mChildren.end() && i->second == child)
		{
			// cancel any pending update
			cancelUpdate(child);

			mChildren.erase(i);
			child->setParent(NULL);
		}
	}
	return child;
}

//-----------------------------------------------------------------------
void Node::setOrientation(const Quaternion & q)
{
	//OgreAssertDbg(!q.isNaN(), "Invalid orientation supplied as parameter");
	mOrientation = q;
	mOrientation.normalise();
	needUpdate();
}
//-----------------------------------------------------------------------
void Node::setOrientation(Real w, Real x, Real y, Real z)
{
	setOrientation(Quaternion(w, x, y, z));
}
//-----------------------------------------------------------------------
void Node::resetOrientation(void)
{
	mOrientation = Quaternion::IDENTITY;
	needUpdate();
}

//-----------------------------------------------------------------------
void Node::setPosition(const Vector3& pos)
{
	assert(!pos.isNaN() && "Invalid vector supplied as parameter");
	mPosition = pos;
	needUpdate();
}


//-----------------------------------------------------------------------
void Node::setPosition(Real x, Real y, Real z)
{
	Vector3 v(x, y, z);
	setPosition(v);
}

//-----------------------------------------------------------------------
Matrix3 Node::getLocalAxes(void) const
{
	Vector3 axisX = Vector3::UNIT_X;
	Vector3 axisY = Vector3::UNIT_Y;
	Vector3 axisZ = Vector3::UNIT_Z;

	axisX = mOrientation * axisX;
	axisY = mOrientation * axisY;
	axisZ = mOrientation * axisZ;

	return Matrix3(axisX.x, axisY.x, axisZ.x,
		axisX.y, axisY.y, axisZ.y,
		axisX.z, axisY.z, axisZ.z);
}

//-----------------------------------------------------------------------
void Node::translate(const Vector3& d, TransformSpace relativeTo)
{
	switch (relativeTo)
	{
	case TS_LOCAL:
		// position is relative to parent so transform downwards
		mPosition += mOrientation * d;
		break;
	case TS_WORLD:
		// position is relative to parent so transform upwards
		if (mParent)
		{
			mPosition += mParent->convertWorldToLocalDirection(d, true);
		}
		else
		{
			mPosition += d;
		}
		break;
	case TS_PARENT:
		mPosition += d;
		break;
	}
	needUpdate();

}
//-----------------------------------------------------------------------
void Node::translate(Real x, Real y, Real z, TransformSpace relativeTo)
{
	Vector3 v(x, y, z);
	translate(v, relativeTo);
}
//-----------------------------------------------------------------------
void Node::translate(const Matrix3& axes, const Vector3& move, TransformSpace relativeTo)
{
	Vector3 derived = axes * move;
	translate(derived, relativeTo);
}
//-----------------------------------------------------------------------
void Node::translate(const Matrix3& axes, Real x, Real y, Real z, TransformSpace relativeTo)
{
	Vector3 d(x, y, z);
	translate(axes, d, relativeTo);
}
//-----------------------------------------------------------------------
void Node::roll(const Radian& angle, TransformSpace relativeTo)
{
	rotate(Vector3::UNIT_Z, angle, relativeTo);
}
//-----------------------------------------------------------------------
void Node::pitch(const Radian& angle, TransformSpace relativeTo)
{
	rotate(Vector3::UNIT_X, angle, relativeTo);
}
//-----------------------------------------------------------------------
void Node::yaw(const Radian& angle, TransformSpace relativeTo)
{
	rotate(Vector3::UNIT_Y, angle, relativeTo);

}
//-----------------------------------------------------------------------
void Node::rotate(const Vector3& axis, const Radian& angle, TransformSpace relativeTo)
{
	Quaternion q;
	q.FromAngleAxis(angle, axis);
	rotate(q, relativeTo);
}

//-----------------------------------------------------------------------
void Node::rotate(const Quaternion& q, TransformSpace relativeTo)
{
	switch (relativeTo)
	{
	case TS_PARENT:
		// Rotations are normally relative to local axes, transform up
		mOrientation = q * mOrientation;
		break;
	case TS_WORLD:
		// Rotations are normally relative to local axes, transform up
		mOrientation = mOrientation * _getDerivedOrientation().Inverse() * q * _getDerivedOrientation();
		break;
	case TS_LOCAL:
		// Note the order of the mult, i.e. q comes after
		mOrientation = mOrientation * q;
		break;
	}

	// Normalise quaternion to avoid drift
	mOrientation.normalise();

	needUpdate();
}
//-----------------------------------------------------------------------
void Node::_setDerivedPosition(const Vector3& pos)
{
	//find where the node would end up in parent's local space
	if (mParent)
		setPosition(mParent->convertWorldToLocalPosition(pos));
}
//-----------------------------------------------------------------------
void Node::_setDerivedOrientation(const Quaternion& q)
{
	//find where the node would end up in parent's local space
	if (mParent)
		setOrientation(mParent->convertWorldToLocalOrientation(q));
}

//-----------------------------------------------------------------------
const Quaternion & Node::_getDerivedOrientation(void) const
{
	if (mNeedParentUpdate)
	{
		_updateFromParent();
	}
	return mDerivedOrientation;
}
//-----------------------------------------------------------------------
const Vector3 & Node::_getDerivedPosition(void) const
{
	if (mNeedParentUpdate)
	{
		_updateFromParent();
	}
	return mDerivedPosition;
}
//-----------------------------------------------------------------------
const Vector3 & Node::_getDerivedScale(void) const
{
	if (mNeedParentUpdate)
	{
		_updateFromParent();
	}
	return mDerivedScale;
}
//-----------------------------------------------------------------------
Vector3 Node::convertWorldToLocalPosition(const Vector3 &worldPos)
{
	if (mNeedParentUpdate)
	{
		_updateFromParent();
	}
#if OGRE_NODE_INHERIT_TRANSFORM
	return _getFullTransform().inverseAffine().transformAffine(worldPos);
#else
	return mDerivedOrientation.Inverse() * (worldPos - mDerivedPosition) / mDerivedScale;
#endif
}
//-----------------------------------------------------------------------
Vector3 Node::convertLocalToWorldPosition(const Vector3 &localPos)
{
	if (mNeedParentUpdate)
	{
		_updateFromParent();
	}
	return _getFullTransform().transformAffine(localPos);
}
//-----------------------------------------------------------------------
Vector3 Node::convertWorldToLocalDirection(const Vector3 &worldDir, bool useScale)
{
	if (mNeedParentUpdate)
	{
		_updateFromParent();
	}

	return useScale ?
#if OGRE_NODE_INHERIT_TRANSFORM
		_getFullTransform().inverseAffine().transformDirectionAffine(worldDir) :
		mDerivedOrientation.Inverse() * worldDir;
#else
		mDerivedOrientation.Inverse() * worldDir / mDerivedScale :
	mDerivedOrientation.Inverse() * worldDir;
#endif
}
//-----------------------------------------------------------------------
Vector3 Node::convertLocalToWorldDirection(const Vector3 &localDir, bool useScale)
{
	if (mNeedParentUpdate)
	{
		_updateFromParent();
	}
	return useScale ?
		_getFullTransform().transformDirectionAffine(localDir) :
		mDerivedOrientation * localDir;
}
//-----------------------------------------------------------------------
Quaternion Node::convertWorldToLocalOrientation(const Quaternion &worldOrientation)
{
	if (mNeedParentUpdate)
	{
		_updateFromParent();
	}
	return mDerivedOrientation.Inverse() * worldOrientation;
}
//-----------------------------------------------------------------------
Quaternion Node::convertLocalToWorldOrientation(const Quaternion &localOrientation)
{
	if (mNeedParentUpdate)
	{
		_updateFromParent();
	}
	return mDerivedOrientation * localOrientation;

}
//-----------------------------------------------------------------------
void Node::removeAllChildren(void)
{
	ChildNodeMap::iterator i, iend;
	iend = mChildren.end();
	for (i = mChildren.begin(); i != iend; ++i)
	{
		i->second->setParent(0);
	}
	mChildren.clear();
	mChildrenToUpdate.clear();
}
//-----------------------------------------------------------------------
void Node::setScale(const Vector3& inScale)
{
	assert(!inScale.isNaN() && "Invalid vector supplied as parameter");
	mScale = inScale;
	needUpdate();
}
//-----------------------------------------------------------------------
void Node::setScale(Real x, Real y, Real z)
{
	setScale(Vector3(x, y, z));
}

//-----------------------------------------------------------------------
void Node::setInheritOrientation(bool inherit)
{
	mInheritOrientation = inherit;
	needUpdate();
}
//-----------------------------------------------------------------------
void Node::setInheritScale(bool inherit)
{
	mInheritScale = inherit;
	needUpdate();
}
//-----------------------------------------------------------------------
void Node::scale(const Vector3& inScale)
{
	mScale = mScale * inScale;
	needUpdate();

}
//-----------------------------------------------------------------------
void Node::scale(Real x, Real y, Real z)
{
	mScale.x *= x;
	mScale.y *= y;
	mScale.z *= z;
	needUpdate();

}

Node* Node::getChild(const std::string& name) const
{
	ChildNodeMap::const_iterator i = mChildren.find(name);

	if (i == mChildren.end())
	{
		/*OGRE_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "Child node named " + name +
			" does not exist.", "Node::getChild");*/
	}
	return i->second;

}
//-----------------------------------------------------------------------
Node* Node::removeChild(const std::string& name)
{
	ChildNodeMap::iterator i = mChildren.find(name);

	if (i == mChildren.end())
	{
		/*OGRE_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "Child node named " + name +
			" does not exist.", "Node::removeChild");*/
	}

	Node* ret = i->second;
	// Cancel any pending update
	cancelUpdate(ret);

	mChildren.erase(i);
	ret->setParent(NULL);

	return ret;


}
/*
//-----------------------------------------------------------------------
Node::ChildNodeIterator Node::getChildIterator(void)
{
	return ChildNodeIterator(mChildren.begin(), mChildren.end());
}
//-----------------------------------------------------------------------
Node::ConstChildNodeIterator Node::getChildIterator(void) const
{
	return ConstChildNodeIterator(mChildren.begin(), mChildren.end());
}
//-----------------------------------------------------------------------
Real Node::getSquaredViewDepth(const Camera* cam) const
{
	Vector3 diff = _getDerivedPosition() - cam->getDerivedPosition();

	// NB use squared length rather than real depth to avoid square root
	return diff.squaredLength();
}*/
//-----------------------------------------------------------------------
void Node::needUpdate(bool forceParentUpdate)
{

	mNeedParentUpdate = true;
	mNeedChildUpdate = true;
	mCachedTransformOutOfDate = true;

	// Make sure we're not root and parent hasn't been notified before
	if (mParent && (!mParentNotified || forceParentUpdate))
	{
		mParent->requestUpdate(this, forceParentUpdate);
		mParentNotified = true;
	}

	// all children will be updated
	mChildrenToUpdate.clear();
}
//-----------------------------------------------------------------------
void Node::requestUpdate(Node* child, bool forceParentUpdate)
{
	// If we're already going to update everything this doesn't matter
	if (mNeedChildUpdate)
	{
		return;
	}

	mChildrenToUpdate.insert(child);
	// Request selective update of me, if we didn't do it before
	if (mParent && (!mParentNotified || forceParentUpdate))
	{
		mParent->requestUpdate(this, forceParentUpdate);
		mParentNotified = true;
	}

}
//-----------------------------------------------------------------------
void Node::cancelUpdate(Node* child)
{
	mChildrenToUpdate.erase(child);

	// Propagate this up if we're done
	if (mChildrenToUpdate.empty() && mParent && !mNeedChildUpdate)
	{
		mParent->cancelUpdate(this);
		mParentNotified = false;
	}
}
/*
//-----------------------------------------------------------------------
void Node::queueNeedUpdate(Node* n)
{
	// Don't queue the node more than once
	if (!n->mQueuedForUpdate)
	{
		n->mQueuedForUpdate = true;
		msQueuedUpdates.push_back(n);
	}
}
//-----------------------------------------------------------------------
void Node::processQueuedUpdates(void)
{
	for (QueuedUpdates::iterator i = msQueuedUpdates.begin();
		i != msQueuedUpdates.end(); ++i)
	{
		// Update, and force parent update since chances are we've ended
		// up with some mixed state in there due to re-entrancy
		Node* n = *i;
		n->mQueuedForUpdate = false;
		n->needUpdate(true);
	}
	msQueuedUpdates.clear();
}*/