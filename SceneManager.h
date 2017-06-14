#pragma once
#include "stdafx.h"

#include "Plane.h"
#include "Quaternion.h"
#include "NameGenerator.h"
#include "SceneNode.h"
#include "Entity.h"
#include "Effects.h"
struct  VisibleObjectsBoundsInfo
{
	/// The axis-aligned bounds of the visible objects
	AxisAlignedBox aabb;
	/// The axis-aligned bounds of the visible shadow receiver objects
	AxisAlignedBox receiverAabb;
	/// The closest a visible object is to the camera
	Real minDistance;
	/// The farthest a visible objects is from the camera
	Real maxDistance;
	/// The closest a object in the frustum regardless of visibility / shadow caster flags
	Real minDistanceInFrustum;
	/// The farthest object in the frustum regardless of visibility / shadow caster flags
	Real maxDistanceInFrustum;

	VisibleObjectsBoundsInfo();
	void reset();

	/*void merge(const AxisAlignedBox& boxBounds, const Sphere& sphereBounds,
	const Camera* cam, bool receiver = true);
	void mergeNonRenderedButInFrustum(const AxisAlignedBox& boxBounds,
	const Sphere& sphereBounds, const Camera* cam);*/
};

class  SceneManager
{
public:
	ID3D11Device* md3dDevice;
	ID3D11DeviceContext* md3dImmediateContext;
	IDXGISwapChain* mSwapChain;
	struct SkyDomeGenParameters
	{
		Real skyDomeCurvature;
		Real skyDomeTiling;
		Real skyDomeDistance;
		int skyDomeXSegments;
		int skyDomeYSegments;
		int skyDomeYSegments_keep;
	};
	struct SkyPlaneGenParameters
	{
		Real skyPlaneScale;
		Real skyPlaneTiling;
		Real skyPlaneBow;
		int skyPlaneXSegments;
		int skyPlaneYSegments;
	};
	struct SkyBoxGenParameters
	{
		Real skyBoxDistance;
	};
public:

	SceneManager(const std::string& instanceName, ID3D11Device* Device,ID3D11DeviceContext* ImmediateContext,IDXGISwapChain* SwapChain);
	virtual ~SceneManager();
	static int m_NumberPlaneCreated;
	static int m_NumberBoxCreated;
	static int m_NumberSphereCreated;
	static int m_NumberCylinderCreated;
	static int m_NumberStaticMeshCreated;
	static int m_NumberSkinnedMeshCreated;
	static int m_NumberNodeCreated;

	virtual SceneNode* createSceneNode(void);
	virtual SceneNode* createSceneNode(const std::string& name);
	virtual void destroySceneNode(SceneNode* sn);
	virtual void destroySceneNode(const std::string& name);
	virtual SceneNode* getRootSceneNode(void);
	virtual SceneNode* getSceneNode(const std::string& name) const;
	virtual bool hasSceneNode(const std::string& name) const;
	//virtual Entity* createEntity(const std::string& entityName, const std::string& meshName, const std::string& groupName = ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME);
	//virtual Entity* createEntity(const std::string& entityName, const Renderable& pMesh);
	virtual Entity* createEntity(const std::string& entityName, const std::string& meshName);
	virtual Entity* createEntityPlane(const std::string& entityName, const ManualMeshParameter& parameter,float width,float depth,float m,float n);
	virtual Entity* createEntityPlane(const ManualMeshParameter& parameter, float width, float depth, float m, float n);
	virtual Entity* createEntitySphere(const std::string& entityName, const ManualMeshParameter& parameter, float sphere_radius, int sphere_slice_count, int sphere_stack_count);
	virtual Entity* createEntityBox(const std::string& entityName, const ManualMeshParameter& parameter, float width,float height,float depth);
	virtual Entity* createEntityCylinder(const std::string& entityName, const ManualMeshParameter& parameter, float cylinder_top_radius, float cylinder_bottom_radius, int cylinder_slice_count, int cylinder_stack_count);
	virtual SceneNode* createSceneNodeImpl(void);
	virtual SceneNode* createSceneNodeImpl(const std::string& name);
	virtual void clearScene(void);

protected:

	std::string mName;
	typedef std::map<std::string, SceneNode*> SceneNodeList;
	std::map<std::string, Mesh*> MeshMaps;//存放模型名和加载后的资源
	std::map<std::string, Mesh*> mRenderQueue;//存放要渲染的renderable
	std::map<std::string, Entity*> mEntityMaps;//存放场景中已添加的Entity

	SceneNodeList mSceneNodes;
	SceneNode* mSceneRoot;

	// Sky params
	// Sky plane
	Entity* mSkyPlaneEntity;
	Entity* mSkyDomeEntity[5];
	Entity* mSkyBoxObj;

	SceneNode* mSkyPlaneNode;
	SceneNode* mSkyDomeNode;
	SceneNode* mSkyBoxNode;

	// Sky plane
	bool mSkyPlaneEnabled;
	uint8 mSkyPlaneRenderQueue;
	Plane mSkyPlane;
	SkyPlaneGenParameters mSkyPlaneGenParameters;
	// Sky box
	bool mSkyBoxEnabled;
	uint8 mSkyBoxRenderQueue;
	Quaternion mSkyBoxOrientation;
	SkyBoxGenParameters mSkyBoxGenParameters;
	// Sky dome
	bool mSkyDomeEnabled;
	uint8 mSkyDomeRenderQueue;
	Quaternion mSkyDomeOrientation;
	SkyDomeGenParameters mSkyDomeGenParameters;
};