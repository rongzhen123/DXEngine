#ifndef MANUAL_MESH_H
#define	MANUAL_MESH_H
#include "Mesh.h"
#include "Renderable.h"
class ManualMesh :public Mesh
{
public:
	ManualMesh();
	~ManualMesh();

	bool Init(ID3D11Device * d3d11device);
	/*void Init(ID3D11Device* device, GeometryGenerator::MeshData& meshdata, ID3DX11Effect* meffect, ID3DX11EffectTechnique* mtech,
		ID3D11InputLayout* minputlayout, ID3DX11EffectMatrixVariable* meffectworldviewproj, ID3D11RasterizerState* mrs,
		ID3D11BlendState* mbs);*/
	bool Load(std::string filename);
	void Update(float dttime);
	void Render(ID3D11DeviceContext*& md3dImmediateContext);

	void _updateBoundsFromVertexBuffers(bool pad = false);
	void _calcBoundsFromVertexBuffer(AxisAlignedBox& outAABB, Real& outRadius, bool updateOnly = false);

	Renderable* renderobject;

};

#endif