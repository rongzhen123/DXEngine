#include "StdAfx.h"
#include "SceneManager.h"
#include "GeometryGenerator.h"
#include "ManualMesh.h"
VisibleObjectsBoundsInfo::VisibleObjectsBoundsInfo()
{
	reset();
}
void VisibleObjectsBoundsInfo::reset()
{
	aabb.setNull();
	receiverAabb.setNull();
	minDistance = minDistanceInFrustum = std::numeric_limits<Real>::infinity();
	maxDistance = maxDistanceInFrustum = 0;
}
/*//---------------------------------------------------------------------
void VisibleObjectsBoundsInfo::merge(const AxisAlignedBox& boxBounds, const Sphere& sphereBounds,
	const Camera* cam, bool receiver)
{
	aabb.merge(boxBounds);
	if (receiver)
		receiverAabb.merge(boxBounds);
	// use view matrix to determine distance, works with custom view matrices
	Vector3 vsSpherePos = cam->getViewMatrix(true) * sphereBounds.getCenter();
	Real camDistToCenter = vsSpherePos.length();
	minDistance = std::min(minDistance, std::max((Real)0, camDistToCenter - sphereBounds.getRadius()));
	maxDistance = std::max(maxDistance, camDistToCenter + sphereBounds.getRadius());
	minDistanceInFrustum = std::min(minDistanceInFrustum, std::max((Real)0, camDistToCenter - sphereBounds.getRadius()));
	maxDistanceInFrustum = std::max(maxDistanceInFrustum, camDistToCenter + sphereBounds.getRadius());
}*/
int SceneManager::m_NumberPlaneCreated = 0;
int SceneManager::m_NumberBoxCreated = 0;
int SceneManager::m_NumberSphereCreated = 0;
int SceneManager::m_NumberCylinderCreated = 0;
int SceneManager::m_NumberStaticMeshCreated = 0;
int SceneManager::m_NumberSkinnedMeshCreated = 0;
int SceneManager::m_NumberNodeCreated = 0;

SceneManager::SceneManager(const std::string& name, ID3D11Device* Device, ID3D11DeviceContext* ImmediateContext, 
	IDXGISwapChain* SwapChain) :
	mName(name),
	md3dDevice(Device),
	md3dImmediateContext(ImmediateContext),
	mSwapChain(SwapChain),
	mSceneRoot(0),
	mSkyPlaneEntity(0),
	mSkyBoxObj(0),
	mSkyPlaneNode(0),
	mSkyDomeNode(0),
	mSkyBoxNode(0),
	mSkyPlaneEnabled(false),
	mSkyBoxEnabled(false),
	mSkyDomeEnabled(false)
{
	// init sky
	for (size_t i = 0; i < 5; ++i)
	{
		mSkyDomeEntity[i] = 0;
	}
}
//-----------------------------------------------------------------------
SceneManager::~SceneManager()
{
	clearScene();
	delete mSceneRoot;
}

void SceneManager::clearScene(void)
{
	// Clear root node of all children
	getRootSceneNode()->removeAllChildren();
	getRootSceneNode()->detachAllObjects();
	// Delete all SceneNodes, except root that is
	for (SceneNodeList::iterator i = mSceneNodes.begin();
		i != mSceneNodes.end(); ++i)
	{
		delete i->second;
	}
	mSceneNodes.clear();
	// Remove sky nodes since they've been deleted
	mSkyBoxNode = mSkyPlaneNode = mSkyDomeNode = 0;
	mSkyBoxEnabled = mSkyPlaneEnabled = mSkyDomeEnabled = false;
	// Clear render queue, empty completely
	//if (mRenderQueue)
	//	mRenderQueue->clear(true);
}
Entity * SceneManager::createEntity(const std::string & entityName, const std::string & meshName)
{
	return nullptr;
}

Entity * SceneManager::createEntityPlane(const std::string & entityName, const ManualMeshParameter& parameter, float width, float depth, float m, float n)
{
	GeometryGenerator geoGen;
	GeometryGenerator::MeshData plane;

	geoGen.CreateGrid(width, depth, m, n, plane);
	ManualMesh *plane_mesh = new ManualMesh();
	ManualMesh_Texture* mesh1 = new ManualMesh_Texture(ManualMeshType_Plane);
	mesh1->mPos = XMFLOAT3(parameter.position_x, parameter.position_y, parameter.position_z);
	mesh1->mScale = XMFLOAT3(parameter.scale_x, parameter.scale_y, parameter.scale_z);
	mesh1->mRotation = XMFLOAT3(parameter.rotation_x, parameter.rotation_y, parameter.rotation_z);
	mesh1->mColor = XMFLOAT4(parameter.color_r / 255.0, parameter.color_g / 255.0, parameter.color_b / 255.0, parameter.color_a / 255.0);
	mesh1->mDiffuseMap = Effects::mDiffuseMap_PosTex;
	ID3D11ShaderResourceView* m_TextureSRV;
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(md3dDevice, parameter.texture_filename.c_str(), 0, 0, &m_TextureSRV, 0);
	mesh1->m_TextureSRV = m_TextureSRV;
	mesh1->Init(md3dDevice, plane, Effects::mEffectPosTex, Effects::mEffectTechPosTex, Effects::mInputLayout_PosTex,
		Effects::mEffectWorldViewProj_PosTex, Effects::mRS, Effects::TransparentBS);
	
	plane_mesh->renderobject = mesh1;
	Entity* plane_entity = new Entity(entityName, plane_mesh);
	m_NumberPlaneCreated++;
	return nullptr;
}

Entity * SceneManager::createEntityPlane(const ManualMeshParameter & parameter, float width, float depth, float m, float n)
{
	GeometryGenerator geoGen;
	GeometryGenerator::MeshData plane;
	std::stringstream name;
	name << "Entity_Plane_" << m_NumberPlaneCreated;
	geoGen.CreateGrid(width, depth, m, n, plane);
	ManualMesh *plane_mesh = new ManualMesh();
	ManualMesh_Texture* mesh1 = new ManualMesh_Texture(ManualMeshType_Plane);
	mesh1->mPos = XMFLOAT3(parameter.position_x, parameter.position_y, parameter.position_z);
	mesh1->mScale = XMFLOAT3(parameter.scale_x, parameter.scale_y, parameter.scale_z);
	mesh1->mRotation = XMFLOAT3(parameter.rotation_x, parameter.rotation_y, parameter.rotation_z);
	mesh1->mColor = XMFLOAT4(parameter.color_r / 255.0, parameter.color_g / 255.0, parameter.color_b / 255.0, parameter.color_a / 255.0);
	mesh1->mDiffuseMap = Effects::mDiffuseMap_PosTex;
	ID3D11ShaderResourceView* m_TextureSRV;
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(md3dDevice, parameter.texture_filename.c_str(), 0, 0, &m_TextureSRV, 0);
	mesh1->m_TextureSRV = m_TextureSRV;
	mesh1->Init(md3dDevice, plane, Effects::mEffectPosTex, Effects::mEffectTechPosTex, Effects::mInputLayout_PosTex,
		Effects::mEffectWorldViewProj_PosTex, Effects::mRS, Effects::TransparentBS);

	plane_mesh->renderobject = mesh1;
	Entity* plane_entity = new Entity(name.str(), plane_mesh);
	m_NumberPlaneCreated++;
	return plane_entity;
}

Entity * SceneManager::createEntitySphere(const std::string & entityName, const ManualMeshParameter& parameter, float sphere_radius, int sphere_slice_count, int sphere_stack_count)
{
	return nullptr;
}

Entity * SceneManager::createEntityBox(const std::string & entityName, const ManualMeshParameter& parameter, float width, float height, float depth)
{
	return nullptr;
}

Entity * SceneManager::createEntityCylinder(const std::string & entityName, const ManualMeshParameter& parameter, float cylinder_top_radius, float cylinder_bottom_radius, int cylinder_slice_count, int cylinder_stack_count)
{
	return nullptr;
}

//-----------------------------------------------------------------------
SceneNode* SceneManager::createSceneNodeImpl(void)
{
	return new SceneNode(this);
}
//-----------------------------------------------------------------------
SceneNode* SceneManager::createSceneNodeImpl(const std::string& name)
{
	return new SceneNode(this, name);
}//-----------------------------------------------------------------------
SceneNode* SceneManager::createSceneNode(void)
{
	SceneNode* sn = createSceneNodeImpl();
	assert(mSceneNodes.find(sn->getName()) == mSceneNodes.end());
	mSceneNodes[sn->getName()] = sn;
	return sn;
}
//-----------------------------------------------------------------------
SceneNode* SceneManager::createSceneNode(const std::string& name)
{
	// Check name not used
	if (mSceneNodes.find(name) != mSceneNodes.end())
	{
		/*OGRE_EXCEPT(
			Exception::ERR_DUPLICATE_ITEM,
			"A scene node with the name " + name + " already exists",
			"SceneManager::createSceneNode");*/
	}

	SceneNode* sn = createSceneNodeImpl(name);
	mSceneNodes[sn->getName()] = sn;
	return sn;
}
//-----------------------------------------------------------------------
void SceneManager::destroySceneNode(const std::string& name)
{
	SceneNodeList::iterator i = mSceneNodes.find(name);

	if (i == mSceneNodes.end())
	{
		/*OGRE_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "SceneNode '" + name + "' not found.",
			"SceneManager::destroySceneNode");*/
	}

	// Find any scene nodes which are tracking this node, and turn them off
	/*AutoTrackingSceneNodes::iterator ai, aiend;
	aiend = mAutoTrackingSceneNodes.end();
	for (ai = mAutoTrackingSceneNodes.begin(); ai != aiend; )
	{
		// Pre-increment incase we delete
		//AutoTrackingSceneNodes::iterator curri = ai++;
		SceneNode* n = *curri;
		// Tracking this node
		if (n->getAutoTrackTarget() == i->second)
		{
			// turn off, this will notify SceneManager to remove
			n->setAutoTracking(false);
		}
		// node is itself a tracker
		else if (n == i->second)
		{
			mAutoTrackingSceneNodes.erase(curri);
		}
	}
	*/
	// detach from parent (don't do this in destructor since bulk destruction
	// behaves differently)
	Node* parentNode = i->second->getParent();
	if (parentNode)
	{
		parentNode->removeChild(i->second);
	}
	delete i->second;
	mSceneNodes.erase(i);
}
//---------------------------------------------------------------------
void SceneManager::destroySceneNode(SceneNode* sn)
{
	if (!sn)
		/*OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "Cannot destroy a null SceneNode.", "SceneManager::destroySceneNode");*/

	destroySceneNode(sn->getName());
}
//-----------------------------------------------------------------------
SceneNode* SceneManager::getRootSceneNode(void)
{
	if (!mSceneRoot)
	{
		// Create root scene node
		mSceneRoot = createSceneNodeImpl("Ogre/SceneRoot");
		mSceneRoot->_notifyRootNode();
	}

	return mSceneRoot;
}
//-----------------------------------------------------------------------
SceneNode* SceneManager::getSceneNode(const std::string& name) const
{
	SceneNodeList::const_iterator i = mSceneNodes.find(name);

	if (i == mSceneNodes.end())
	{
		/*OGRE_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "SceneNode '" + name + "' not found.",
			"SceneManager::getSceneNode");*/
	}

	return i->second;

}
//-----------------------------------------------------------------------
bool SceneManager::hasSceneNode(const std::string& name) const
{
	return (mSceneNodes.find(name) != mSceneNodes.end());
}
