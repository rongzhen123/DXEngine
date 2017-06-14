#include "stdafx.h"
#include "Renderable.h"
#include "GeometryGenerator.h"



ManualMesh_Texture::ManualMesh_Texture(ManualMeshType t) :Renderable(t, POS_TEX)
{
}

void ManualMesh_Texture::Init(ID3D11Device * device, GeometryGenerator::MeshData& meshdata,ID3DX11Effect* meffect, ID3DX11EffectTechnique* mtech,
	ID3D11InputLayout* minputlayout, ID3DX11EffectMatrixVariable* meffectworldviewproj, ID3D11RasterizerState* mrs,
	ID3D11BlendState* mbs)
{
	mEffect = meffect;
	mEffectTech = mtech;
	mInputLayout = minputlayout;
	mEffectWorldViewProj = meffectworldviewproj;
	mRS = mrs;
	mBS = mbs;
	//mDiffuseMap = mdiffusemap;

	NumIndices = meshdata.Indices.size();
	m_Vertex.resize(meshdata.Vertices.size());
	m_Indices.resize(NumIndices);
	mVertexStride = sizeof(MeshVertex_Pos_Tex);
	for (UINT i = 0; i < meshdata.Vertices.size(); ++i)
	{
		m_Vertex[i].m_pos = meshdata.Vertices[i].Position;
		//m_Vertex[i].m_pos.y = GetHillHeight(m_Vertex[i].m_pos.x, m_Vertex[i].m_pos.z);
		m_Vertex[i].m_tex = meshdata.Vertices[i].TexC;
	}
	for (UINT i = 0; i < meshdata.Indices.size(); ++i)
	{
		m_Indices[i] = meshdata.Indices[i];
	}
	HRESULT hr;
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = mVertexStride * m_Vertex.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &m_Vertex[0];
	hr = device->CreateBuffer(&vbd, &vinitData, &mVB);
	if (FAILED(hr))
	{
		return;
	}
	// Pack the indices of all the meshes into one index buffer.
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * NumIndices;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &meshdata.Indices[0];
	hr = device->CreateBuffer(&ibd, &iinitData, &mIB);
	if (FAILED(hr))
	{
		return;
	}
}

ManualMesh_Color::ManualMesh_Color(ManualMeshType t):Renderable(t, POS_COLOR)
{
}

float GetHillHeight(float x, float z) 
{
	return 0.3f*(z*sinf(0.1f*x) + x*cosf(0.1f*z));
}
void ManualMesh_Color::Init(ID3D11Device * device, GeometryGenerator::MeshData& meshdata,ID3DX11Effect* meffect, ID3DX11EffectTechnique* mtech,
	ID3D11InputLayout* minputlayout, ID3DX11EffectMatrixVariable* meffectworldviewproj, ID3D11RasterizerState* mrs,	ID3D11BlendState* mbs)
{
	mEffect = meffect;
	mEffectTech = mtech;
	mInputLayout = minputlayout;
	mEffectWorldViewProj = meffectworldviewproj;
	mRS = mrs;
	mBS = mbs;
	NumIndices = meshdata.Indices.size();
	m_Vertex.resize(meshdata.Vertices.size());
	m_Indices.resize(NumIndices);
	mVertexStride = sizeof(MeshVertex_Pos_Color);
	for (UINT i = 0; i < meshdata.Vertices.size(); ++i)
	{
		m_Vertex[i].m_pos = meshdata.Vertices[i].Position;
		//m_Vertex[i].m_pos.y = GetHillHeight(m_Vertex[i].m_pos.x, m_Vertex[i].m_pos.z);
		m_Vertex[i].m_color = mColor;
	}
	for (UINT i = 0; i < meshdata.Indices.size(); ++i)
	{
		m_Indices[i] = meshdata.Indices[i];
	}
	HRESULT hr;
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = mVertexStride * m_Vertex.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &m_Vertex[0];
	hr = device->CreateBuffer(&vbd, &vinitData, &mVB);
	if (FAILED(hr))
	{
		return;
	}
	// Pack the indices of all the meshes into one index buffer.
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * NumIndices;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &meshdata.Indices[0];
	hr = device->CreateBuffer(&ibd, &iinitData, &mIB);
	if (FAILED(hr))
	{
		return;
	}
}

Renderable::Renderable(ManualMeshType t, ManualMeshMaterialType materialtype):type(t), mMaterialType(materialtype)
{

}

const AxisAlignedBox & Renderable::getBounds(void) const
{
	// TODO: 在此处插入 return 语句
	return mAABB;
}

Real Renderable::getBoundingSphereRadius(void) const
{
	return mBoundRadius;
}

ManualMesh_Color_Texture::ManualMesh_Color_Texture(ManualMeshType t) : Renderable(t, POS_TEX_COLOR)
{

}

void ManualMesh_Color_Texture::Init(ID3D11Device * device, GeometryGenerator::MeshData & meshdata, ID3DX11Effect * meffect, ID3DX11EffectTechnique * mtech, ID3D11InputLayout * minputlayout, ID3DX11EffectMatrixVariable * meffectworldviewproj, ID3D11RasterizerState * mrs, ID3D11BlendState * mbs)
{
	mEffect = meffect;
	mEffectTech = mtech;
	mInputLayout = minputlayout;
	mEffectWorldViewProj = meffectworldviewproj;
	mRS = mrs;
	mBS = mbs;
	NumIndices = meshdata.Indices.size();
	m_Vertex.resize(meshdata.Vertices.size());
	m_Indices.resize(NumIndices);
	mVertexStride = sizeof(MeshVertex_Pos_Tex_Color);
	for (UINT i = 0; i < meshdata.Vertices.size(); ++i)
	{
		m_Vertex[i].m_pos = meshdata.Vertices[i].Position;
		//m_Vertex[i].m_pos.y = GetHillHeight(m_Vertex[i].m_pos.x, m_Vertex[i].m_pos.z);
		m_Vertex[i].m_color = mColor;
		m_Vertex[i].m_tex = meshdata.Vertices[i].TexC;
	}
	for (UINT i = 0; i < meshdata.Indices.size(); ++i)
	{
		m_Indices[i] = meshdata.Indices[i];
	}
	HRESULT hr;
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = mVertexStride * m_Vertex.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &m_Vertex[0];
	hr = device->CreateBuffer(&vbd, &vinitData, &mVB);
	if (FAILED(hr))
	{
		return;
	}
	//
	// Pack the indices of all the meshes into one index buffer.
	//

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * NumIndices;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &meshdata.Indices[0];
	hr = device->CreateBuffer(&ibd, &iinitData, &mIB);
	if (FAILED(hr))
	{
		return;
	}

}
