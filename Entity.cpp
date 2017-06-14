#include "StdAfx.h"
#include "Entity.h"
#include "SceneNode.h"
Entity::Entity()
{
}
Entity::Entity(const std::string & name, const Mesh * mesh)
{

}
Entity::~Entity()
{
	if (!mInitialised)
		return;
	mInitialised = false;
}

void Entity::_notifyAttached(Node * parent, bool isTagPoint)
{
	assert(!mParentNode || !parent);

	bool different = (parent != mParentNode);

	mParentNode = parent;
	//mParentIsTagPoint = isTagPoint;

	// Mark light list being dirty, simply decrease
	// counter by one for minimise overhead
	//--mLightListUpdated;
}
Node* Entity::getParentNode(void) const
{
	return mParentNode;
}

const Mesh * Entity::getMesh(void) const
{
	return mesh;
}
Entity * Entity::clone(const std::string & newName) const
{
	/*if (!mManager)
	{
		OGRE_EXCEPT(Exception::ERR_ITEM_NOT_FOUND,
			"Cannot clone an Entity that wasn't created through a "
			"SceneManager", "Entity::clone");
	}
	Entity* newEnt = mManager->createEntity(newName, getMesh()->getName());

	if (mInitialised)
	{
		// Copy material settings
		SubEntityList::const_iterator i;
		unsigned int n = 0;
		for (i = mSubEntityList.begin(); i != mSubEntityList.end(); ++i, ++n)
		{
			newEnt->getSubEntity(n)->setMaterialName((*i)->getMaterialName());
		}
		if (mAnimationState)
		{
			OGRE_DELETE newEnt->mAnimationState;
			newEnt->mAnimationState = OGRE_NEW AnimationStateSet(*mAnimationState);
		}
	}

	return newEnt;*/
	return nullptr;
}
//-----------------------------------------------------------------------
SceneNode* Entity::getParentSceneNode(void) const
{
	/*if (mParentIsTagPoint)
	{
		TagPoint* tp = static_cast<TagPoint*>(mParentNode);
		return tp->getParentEntity()->getParentSceneNode();
	}
	else
	{*/
		return static_cast<SceneNode*>(mParentNode);
	//}
}
//-----------------------------------------------------------------------
bool Entity::isAttached(void) const
{
	return (mParentNode != 0);

}
//---------------------------------------------------------------------
void Entity::detachFromParent(void)
{
	if (isAttached())
	{
		/*if (mParentIsTagPoint)
		{
			TagPoint* tp = static_cast<TagPoint*>(mParentNode);
			tp->getParentEntity()->detachObjectFromBone(this);
		}
		else
		{*/
			SceneNode* sn = static_cast<SceneNode*>(mParentNode);
			sn->detachObject(this);
		//}
	}
}
//-----------------------------------------------------------------------
bool Entity::isInScene(void) const
{
	if (mParentNode != 0)
	{
		SceneNode* sn = static_cast<SceneNode*>(mParentNode);
		return sn->isInSceneGraph();
	}
	else
	{
		return false;
	}
}

const AxisAlignedBox & Entity::getBoundingBox(void) const
{
	// Get from Mesh
	mFullBoundingBox = mesh->getBounds();
	return mFullBoundingBox;
}

Real Entity::getBoundingRadius(void) const
{
	return mesh->getBoundingSphereRadius();
}

const Matrix4& Entity::_getParentNodeFullTransform(void) const
{
	if (mParentNode)
	{
		// object attached to a sceneNode
		return mParentNode->_getFullTransform();
	}
	// fallback
	return Matrix4::IDENTITY;
}
//-----------------------------------------------------------------------
const AxisAlignedBox& Entity::getWorldBoundingBox(bool derive) const
{
	if (derive)
	{
		mWorldAABB = this->getBoundingBox();
		mWorldAABB.transformAffine(_getParentNodeFullTransform());
	}

	return mWorldAABB;

}
//-----------------------------------------------------------------------
const Sphere& Entity::getWorldBoundingSphere(bool derive) const
{
	if (derive)
	{
		const Vector3& scl = mParentNode->_getDerivedScale();
		Real factor = max(max(scl.x, scl.y), scl.z);
		mWorldBoundingSphere.setRadius(getBoundingRadius() * factor);
		mWorldBoundingSphere.setCenter(mParentNode->_getDerivedPosition());
	}
	return mWorldBoundingSphere;
}
void Entity::setVisible(bool visible)
{
	mVisible = visible;
}
//-----------------------------------------------------------------------
bool Entity::getVisible(void) const
{
	return mVisible;
}
//-----------------------------------------------------------------------
bool Entity::isVisible(void) const
{
	if (!mVisible || mBeyondFarDistance /*|| mRenderingDisabled*/)
		return false;

//	SceneManager* sm = Root::getSingleton()._getCurrentSceneManager();
	//if (sm && !(getVisibilityFlags() & sm->_getCombinedVisibilityMask()))
	//	return false;

	return true;
}