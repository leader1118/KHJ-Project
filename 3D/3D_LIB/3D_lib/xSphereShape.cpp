#include "xShape.h"
HRESULT xSphereShape::LoadVertexShader(T_STR  szName) {
	HRESULT hr = S_OK;
	m_dxObj.m_pVertexShader.Attach(
		DX::LoadVertexShaderFile(m_pd3dDevice,
			szName.c_str(),
			m_dxObj.m_pVSBlob.GetAddressOf(), "VS_NoMatrix"));
	return hr;
}
HRESULT xSphereShape::LoadGeometryShader(T_STR  szName)
{
	return xShape::LoadGeometryShader(szName);
}
xSphereShape::xSphereShape()
{

}

xSphereShape::~xSphereShape()
{

}