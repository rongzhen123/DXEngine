#pragma once
#include "stdafx.h"

#include "Matrix4.h"
#include "Quaternion.h"
#include "NameGenerator.h"
class Node
{
public:
	enum TransformSpace
	{
		TS_LOCAL,
		TS_PARENT,
		TS_WORLD
	};
	typedef std::map<std::string, Node*> ChildNodeMap;
	Node* mParent;
	ChildNodeMap mChildren;
	typedef std::set<Node*> ChildUpdateSet;
	ChildUpdateSet mChildrenToUpdate;
	mutable bool mNeedParentUpdate;
	bool mNeedChildUpdate;
	bool mParentNotified;
	bool mQueuedForUpdate;
	std::string mName;
	/// Incremented count for next name extension
	static NameGenerator msNameGenerator;

	Quaternion mOrientation;
	Vector3 mPosition;
	Vector3 mScale;
	bool mInheritOrientation;
	bool mInheritScale;
	
	virtual void setParent(Node* parent);

	mutable Quaternion mDerivedOrientation;
	mutable Vector3 mDerivedPosition;
	mutable Vector3 mDerivedScale;
	void _updateFromParent() const;
	virtual void updateFromParentImpl() const;
	virtual Node* createChildImpl() = 0;
	virtual Node* createChildImpl(const std::string& name) = 0;

	/// Cached derived transform as a 4x4 matrix
	mutable Matrix4 mCachedTransform;
	mutable bool mCachedTransformOutOfDate;

	Node();
	Node(const std::string& name);
	virtual ~Node();
	const std::string& getName() const { return mName; }
	Node* getParent() const { return mParent; }
	const Quaternion& getOrientation() const { return mOrientation; }
	void setOrientation(const Quaternion& q);
	void setOrientation(Real w, Real x, Real y, Real z);

	void resetOrientation(void);

	void setPosition(const Vector3& pos);
	void setPosition(Real x, Real y, Real z);
	const Vector3& getPosition() const { return mPosition; }
	void setScale(const Vector3& scale);
	void setScale(Real x,Real y,Real z);
	const Vector3& getScale() const { return mScale; }
	void setInheritOrientation(bool inherit);
	bool getInheritOrientation() const { return mInheritOrientation; }
	void setInheritScale(bool inherit);
	bool getInheritScale() const { return mInheritScale; };
	void scale(const Vector3& scale);
	void scale(Real x,Real y,Real z);
	void translate(const Vector3& d,TransformSpace relativeTo = TS_PARENT);
	void translate(Real x,Real y,Real z,TransformSpace relativeTo = TS_PARENT);
	void translate(const Matrix3& axes,const Vector3& move,TransformSpace relativeTo = TS_PARENT);
	void translate(const Matrix3& axes, Real x, Real y, Real z, TransformSpace relativeTo = TS_PARENT);

	virtual void roll(const Radian& angle, TransformSpace relativeTo = TS_LOCAL);
	virtual void pitch(const Radian& angle, TransformSpace relativeTo = TS_LOCAL);
	virtual void yaw(const Radian& angle, TransformSpace relativeTo = TS_LOCAL);
	void rotate(const Vector3& axis, const Radian& angle, TransformSpace relativeTo = TS_LOCAL);
	void rotate(const Quaternion& q, TransformSpace relativeTo = TS_LOCAL);
	Matrix3 getLocalAxes(void) const;
	virtual Node* createChild(const Vector3& translate = Vector3::ZERO,	const Quaternion& rotate = Quaternion::IDENTITY);
	virtual Node* createChild(const std::string& name, const Vector3& translate = Vector3::ZERO, const Quaternion& rotate = Quaternion::IDENTITY);
	void addChild(Node* child);
	uint16 numChildren(void) const { return static_cast< uint16 >(mChildren.size()); }
	Node* getChild(unsigned short index) const;
	Node* getChild(const std::string& name) const;
	virtual Node* removeChild(unsigned short index);
	virtual Node* removeChild(Node* child);
	virtual Node* removeChild(const std::string& name);
	virtual void removeAllChildren(void);
	void _setDerivedPosition(const Vector3& pos);
	void _setDerivedOrientation(const Quaternion& q);
	const Quaternion & _getDerivedOrientation(void) const;
	const Vector3 & _getDerivedPosition(void) const;
	const Vector3 & _getDerivedScale(void) const;
	const Matrix4& _getFullTransform(void) const;
	virtual void _update(bool updateChildren, bool parentHasChanged);
	Vector3 convertWorldToLocalPosition(const Vector3 &worldPos);
	Vector3 convertLocalToWorldPosition(const Vector3 &localPos);
	Vector3 convertWorldToLocalDirection(const Vector3 &worldDir, bool useScale);
	Vector3 convertLocalToWorldDirection(const Vector3 &localDir, bool useScale);
	Quaternion convertWorldToLocalOrientation(const Quaternion &worldOrientation);
	Quaternion convertLocalToWorldOrientation(const Quaternion &localOrientation);
//	Real getSquaredViewDepth(const Camera* cam) const;
	virtual void needUpdate(bool forceParentUpdate = false);
	void requestUpdate(Node* child, bool forceParentUpdate = false);
	void cancelUpdate(Node* child);
};
