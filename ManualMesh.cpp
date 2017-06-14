#include "stdafx.h"
#include "ManualMesh.h"

ManualMesh::ManualMesh()
{
	renderobject = NULL;
}

ManualMesh::~ManualMesh()
{

}

bool ManualMesh::Init(ID3D11Device * d3d11device)
{
	return true;
}
/*
void ManualMesh::Init(ID3D11Device * device, GeometryGenerator::MeshData & meshdata, ID3DX11Effect * meffect, ID3DX11EffectTechnique * mtech, ID3D11InputLayout * minputlayout, ID3DX11EffectMatrixVariable * meffectworldviewproj, ID3D11RasterizerState * mrs, ID3D11BlendState * mbs)
{
	renderobject->Init(device, meshdata, meffect, mtech, minputlayout, meffectworldviewproj, mrs, mbs);
}*/

bool ManualMesh::Load(std::string filename)
{
	return true;
}

void ManualMesh::Update(float dttime)
{

}

void ManualMesh::Render(ID3D11DeviceContext *& md3dImmediateContext)
{

}

void ManualMesh::_updateBoundsFromVertexBuffers(bool pad)
{
}

void ManualMesh::_calcBoundsFromVertexBuffer(AxisAlignedBox & outAABB, Real & outRadius, bool updateOnly)
{
}
