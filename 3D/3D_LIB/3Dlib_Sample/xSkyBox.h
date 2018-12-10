#pragma once
#include "xShape.h"
#define MAX_SKYBOX_TEXTURE	6
class xSkyBox : public xBoxShape
{
	ComPtr<ID3D11ShaderResourceView>	m_pTexSRV[MAX_SKYBOX_TEXTURE];
public:
	bool	Create(ID3D11Device* pDevice,	T_STR  szShaderName, T_STR  szTextureName);
	bool	Render(ID3D11DeviceContext* pContext);
	bool	Release();
	HRESULT LoadTexture(T_STR  szName);
public:
	xSkyBox();
	virtual ~xSkyBox();
};

