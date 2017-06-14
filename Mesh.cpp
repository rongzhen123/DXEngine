#include "StdAfx.h"
#include "Mesh.h"

//-----------------------------------------------------------------------
const AxisAlignedBox& Mesh::getBounds(void) const
{
	return mAABB;
}
//-----------------------------------------------------------------------
void Mesh::_setBounds(const AxisAlignedBox& bounds, bool pad)
{
	mAABB = bounds;
	mBoundRadius = Math::boundingRadiusFromAABB(mAABB);

	if (mAABB.isFinite())
	{
		Vector3 max = mAABB.getMaximum();
		Vector3 min = mAABB.getMinimum();

		if (pad)
		{
			// Pad out the AABB a little, helps with most bounds tests
			Vector3 scaler = (max - min) * 0;
			mAABB.setExtents(min - scaler, max + scaler);
			// Pad out the sphere a little too
			mBoundRadius = mBoundRadius + (mBoundRadius * 0);
		}
	}
}
void Mesh::_setBoundingSphereRadius(Real radius)
{
	mBoundRadius = radius;
}
Real Mesh::getBoundingSphereRadius(void) const
{
	return mBoundRadius;
}