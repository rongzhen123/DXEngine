#pragma once
#include "stdafx.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "Mesh.h"
#include "Matrix4.h"
#include "AxisAlignedBox.h"
#include "Sphere.h"
#include "SceneManager.h"
class SceneNode;
class Node;
class Entity 
{
protected:
	Mesh* mesh;
	bool mInitialised;
	std::string mName;
	/// Last parent transform.
	Matrix4 mLastParentXform;
	/// Bounding box that 'contains' all the mesh of each child entity.
	mutable AxisAlignedBox mFullBoundingBox;  // note: this exists only so that getBoundingBox() can return an AAB by reference
	SceneManager* mManager;
	/// node to which this object is attached
	Node* mParentNode;
	//bool mParentIsTagPoint;
	bool mVisible;
	/// Upper distance to still render
	Real mUpperDistance;
	Real mSquaredUpperDistance;
	/// Hidden because of distance?
	bool mBeyondFarDistance;
	/// Cached world AABB of this object
	mutable AxisAlignedBox mWorldAABB;
	// Cached world bounding sphere
	mutable Sphere mWorldBoundingSphere;
	/// World space AABB of this object's dark cap
	mutable AxisAlignedBox mWorldDarkCapBounds;
public:
	Entity();
	Entity(const std::string& name,const Mesh* mesh);
	~Entity();
	void _notifyAttached(Node* parent, bool isTagPoint = false);
	SceneNode* getParentSceneNode(void) const;
	Node* getParentNode(void) const;
	std::string getName() const { return mName; };
	const Mesh* getMesh(void) const;
	Entity* clone(const std::string& newName) const;
	const AxisAlignedBox& getBoundingBox(void) const;
	Real getBoundingRadius(void) const;
	const Matrix4& _getParentNodeFullTransform(void) const;
	const AxisAlignedBox& getWorldBoundingBox(bool derive = false) const;
	const Sphere& getWorldBoundingSphere(bool derive = false) const;
	virtual bool isAttached(void) const;
	virtual void detachFromParent(void);
	virtual bool isInScene(void) const;
	 void setVisible(bool visible);
	 bool getVisible(void) const;
	 bool isVisible(void) const;
	 virtual void setRenderingDistance(Real dist) {
		 mUpperDistance = dist;
		 mSquaredUpperDistance = mUpperDistance * mUpperDistance;
	 }

	 /** Gets the distance at which batches are no longer rendered. */
	 virtual Real getRenderingDistance(void) const { return mUpperDistance; }

};