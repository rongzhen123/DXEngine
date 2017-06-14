#pragma once
#include "Node.h"

#include "AxisAlignedBox.h"
//#include "SceneManager.h"
// forward decl
struct VisibleObjectsBoundsInfo;
class Entity;
class SceneManager;
class SceneNode :public Node
{
public:
	typedef std::map<std::string, Entity*> ObjectMap;
protected:
	ObjectMap mObjectsByName;
	/// Pointer to a Wire Bounding Box for this Node
	//WireBoundingBox *mWireBoundingBox;
	/// Flag that determines if the bounding box of the node should be displayed
	bool mShowBoundingBox;
	bool mHideBoundingBox;

	/// SceneManager which created this node
	SceneManager* mCreator;

	/// World-Axis aligned bounding box, updated only through _update
	AxisAlignedBox mWorldAABB;

	void updateFromParentImpl(void) const;


	Node* createChildImpl(void);


	Node* createChildImpl(const std::string& name);


	void setParent(Node* parent);

	
	virtual void setInSceneGraph(bool inGraph);

	/// Whether to yaw around a fixed axis.
	bool mYawFixed;
	/// Fixed axis to yaw around
	Vector3 mYawFixedAxis;

	/// Auto tracking target
	SceneNode* mAutoTrackTarget;
	/// Tracking offset for fine tuning
	Vector3 mAutoTrackOffset;
	/// Local 'normal' direction vector
	Vector3 mAutoTrackLocalDirection;
	/// Is this node a current part of the scene graph?
	bool mIsInSceneGraph;
public:

	SceneNode(SceneManager* creator);

	SceneNode(SceneManager* creator, const std::string& name);
	~SceneNode();

	virtual void attachObject(Entity* obj);

	unsigned short numAttachedObjects(void) const;

	Entity* getAttachedObject(unsigned short index);

	Entity* getAttachedObject(const std::string& name);

	virtual Entity* detachObject(unsigned short index);

	virtual void detachObject(Entity* obj);

	
	virtual Entity* detachObject(const std::string& name);


	virtual void detachAllObjects(void);


	bool isInSceneGraph(void) const { return mIsInSceneGraph; }

	void _notifyRootNode(void) { mIsInSceneGraph = true; }

	void _update(bool updateChildren, bool parentHasChanged);

	
	virtual void _updateBounds(void);

	/*void _findVisibleObjects(Camera* cam, RenderQueue* queue,
		VisibleObjectsBoundsInfo* visibleBounds,
		bool includeChildren = true, bool displayNodes = false, bool onlyShadowCasters = false);
*/
	const AxisAlignedBox& _getWorldAABB(void) const { return mWorldAABB; }

//	SceneManager* getCreator(void) const { return mCreator; }

	void removeAndDestroyChild(const std::string& name);

	void removeAndDestroyChild(unsigned short index);

	void removeAndDestroyAllChildren(void);

	void showBoundingBox(bool bShow) { mShowBoundingBox = bShow; }

	void hideBoundingBox(bool bHide) { mHideBoundingBox = bHide; }

	bool getShowBoundingBox() const { return mShowBoundingBox; }

	virtual SceneNode* createChildSceneNode(
		const Vector3& translate = Vector3::ZERO,
		const Quaternion& rotate = Quaternion::IDENTITY);

	virtual SceneNode* createChildSceneNode(const std::string& name, const Vector3& translate = Vector3::ZERO, const Quaternion& rotate = Quaternion::IDENTITY);

	void setFixedYawAxis(bool useFixed, const Vector3& fixedAxis = Vector3::UNIT_Y);

	void yaw(const Radian& angle, TransformSpace relativeTo = TS_LOCAL);
	
	void setDirection(Real x, Real y, Real z,
		TransformSpace relativeTo = TS_LOCAL,
		const Vector3& localDirectionVector = Vector3::NEGATIVE_UNIT_Z);

	/// @overload
	void setDirection(const Vector3& vec, TransformSpace relativeTo = TS_LOCAL,
		const Vector3& localDirectionVector = Vector3::NEGATIVE_UNIT_Z);

	void lookAt(const Vector3& targetPoint, TransformSpace relativeTo,
		const Vector3& localDirectionVector = Vector3::NEGATIVE_UNIT_Z);

/*	void setAutoTracking(bool enabled, SceneNode* const target = 0,
		const Vector3& localDirectionVector = Vector3::NEGATIVE_UNIT_Z,
		const Vector3& offset = Vector3::ZERO);*/
	SceneNode* getAutoTrackTarget(void) { return mAutoTrackTarget; }
	
	const Vector3& getAutoTrackOffset(void) { return mAutoTrackOffset; }

	const Vector3& getAutoTrackLocalDirection(void) { return mAutoTrackLocalDirection; }

	void _autoTrack(void);

	SceneNode* getParentSceneNode(void) const;

	void setVisible(bool visible, bool cascade = true);
	
	void flipVisibility(bool cascade = true);
};