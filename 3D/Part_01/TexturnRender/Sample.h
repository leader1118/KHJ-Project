#pragma once
#include "xModelView.h"
#include "xCore.h"
#include <memory>

const UINT g_iTextureRTSize = 1024;

class Sample : public xCore
{
public:
	shared_ptr<xModelView>			m_pMainCamera;
	shared_ptr<xPlaneShape>			m_pPlane;
	shared_ptr<xBoxShape>			m_pBox;
	shared_ptr<xPlaneShape>			m_pMinimap;
	shared_ptr<xPlaneShape>			m_pScreen;
	D3D11_VIEWPORT					m_MinimapViewPort;
public:


};