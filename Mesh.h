#pragma once
#ifndef MESH_H
#define	MESH_H
#include <string>
#include <d3dx11.h>
#include "d3dx11Effect.h"
#include <xnamath.h>
#include <dxerr.h>
#include "D3DCompiler.h"
#include <cassert>
#include <ctime>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include "ogldev_math_3d.h"
#include "util.h"
#include "AxisAlignedBox.h"

class Mesh
{
public:
	virtual bool Init(ID3D11Device * d3d11device) = 0;
	virtual bool Load(std::string filename) = 0;
	virtual void Update(float dttime) = 0;
	virtual void Render(ID3D11DeviceContext*& md3dImmediateContext) = 0;
	/** Get the axis-aligned bounding box for this mesh.*/
	const AxisAlignedBox& getBounds(void) const;
	/** Gets the radius of the bounding sphere surrounding this mesh. */
	Real getBoundingSphereRadius(void) const;
	/** Gets the radius used to inflate the bounding box around the bones. */
	void _setBounds(const AxisAlignedBox& bounds, bool pad = true);
	void _setBoundingSphereRadius(Real radius);

	virtual void _updateBoundsFromVertexBuffers(bool pad = false) = 0;
	virtual void _calcBoundsFromVertexBuffer(AxisAlignedBox& outAABB, Real& outRadius, bool updateOnly = false) = 0;

	/// Local bounding box volume.
	AxisAlignedBox mAABB;
	/// Local bounding sphere radius (centered on object).
	Real mBoundRadius;
	/// Largest bounding radius of any bone in the skeleton (centered on each bone, only considering verts weighted to the bone)
//	Real mBoneBoundingRadius;

};

#endif