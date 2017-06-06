#ifndef Renderable__H_
#define Renderable__H_
#include <d3dx11.h>
#include "d3dx11Effect.h"
#include "GeometryGenerator.h"
#include <xnamath.h>
#include <dxerr.h>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>

enum ManualMeshType
{
	Plane = 0,
	Box,
	Cylinder,
	Sphere
};
enum ManualMeshMaterialType
{
	POS_COLOR = 0,
	POS_TEX
};

struct MeshVertex_Pos_Tex
{
	XMFLOAT3 m_pos;
	XMFLOAT2 m_tex;
	MeshVertex_Pos_Tex() { }
	MeshVertex_Pos_Tex(const XMFLOAT3& pos, const XMFLOAT2& tex)
	{
		m_pos = pos;
		m_tex = tex;
	}
};

struct MeshVertex_Pos_Color
{
	XMFLOAT3 m_pos;
	XMFLOAT4 m_color;
	MeshVertex_Pos_Color() { }
	MeshVertex_Pos_Color(const XMFLOAT3& pos, const XMFLOAT4& color)
	{
		m_pos = pos;
		m_color = color;
	}
};

class Renderable
{
public:
	Renderable(ManualMeshType t, ManualMeshMaterialType materialtype);
	ManualMeshType type;
	ManualMeshMaterialType mMaterialType;
	virtual void Init(ID3D11Device* device, GeometryGenerator::MeshData& meshdata, ID3DX11Effect* meffect, ID3DX11EffectTechnique* mtech,
		ID3D11InputLayout* minputlayout, ID3DX11EffectMatrixVariable* meffectworldviewproj, ID3D11RasterizerState* mrs,
		ID3D11BlendState* mbs) = 0;
	ID3D11Buffer* mVB;
	ID3D11Buffer* mIB;
	DXGI_FORMAT mIndexBufferFormat; // Always 16-bit
	UINT mVertexStride;
	std::vector<unsigned int> m_Indices;
	unsigned int NumIndices;
	unsigned int MaterialIndex;
	ID3DX11Effect* mEffect;
	ID3DX11EffectTechnique* mEffectTech;
	ID3D11InputLayout* mInputLayout;
	ID3DX11EffectMatrixVariable* mEffectWorldViewProj;
	ID3D11RasterizerState* mRS;
	ID3D11BlendState* mBS;
};

class ManualMesh_Texture:public Renderable
{
public:
	ManualMesh_Texture(ManualMeshType t);
	std::vector<MeshVertex_Pos_Tex> m_Vertex;
	void Init(ID3D11Device* device, GeometryGenerator::MeshData& meshdata, ID3DX11Effect* meffect, ID3DX11EffectTechnique* mtech, 
		ID3D11InputLayout* minputlayout, ID3DX11EffectMatrixVariable* meffectworldviewproj, ID3D11RasterizerState* mrs,
		ID3D11BlendState* mbs, ID3DX11EffectShaderResourceVariable* mdiffusemap);
	ID3DX11EffectShaderResourceVariable* mDiffuseMap;
};

class ManualMesh_Color :public Renderable
{
public:
	ManualMesh_Color(ManualMeshType t);
	std::vector<MeshVertex_Pos_Color> m_Vertex;
	void Init(ID3D11Device* device, GeometryGenerator::MeshData& meshdata, ID3DX11Effect* meffect, ID3DX11EffectTechnique* mtech,
		ID3D11InputLayout* minputlayout, ID3DX11EffectMatrixVariable* meffectworldviewproj, ID3D11RasterizerState* mrs,
		ID3D11BlendState* mbs);
};

#endif