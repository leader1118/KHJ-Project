//#pragma once
//#include "xStd.h"
//#include "XTemplate.h"
//class xTexture
//{
//public:
//	T_STR		m_szName;
//	T_STR		m_szPath;
//public:
//	ID3D11ShaderResourceView*		m_pTextureRV;
//	ID3D11SamplerState*				m_pSamplerState;
//	D3D11_SAMPLER_DESC				m_SampleDesc;
//public:
//	HRESULT				Load(ID3D11Device* pDevice, const TCHAR* strFilePath);
//	bool				Apply(ID3D11DeviceContext* plmmediateContext);
//	bool				Release();
//	void				SetPath(const TCHAR* pPath);
//public:
//	xTexture(void);
//	virtual ~xTexture(void);
//};
//
//class XTextureMgr : public TSingleton<XTextureMgr>
//{
//private:
//	friend class TSingleton<XTextureMgr>;
//	ID3D11Device*			m_pd3dDevice;
//	ID3D11DeviceContext*	m_plmmediateContext;
//public:
//	typedef unordered_map <INT, xTexture*>		TemplateMap;
//	typedef TemplateMap::iterator				TemplateMapItor;
//	TemplateMapItor								TItor;
//	TemplateMap									TMap;
//	INT											m_iCurIndex;
//public:
//	INT		Add(ID3D11Device* pDevice, const TCHAR* pFileName);
//	INT		Add(ID3D11Device* pDevice, const TCHAR* pFileName, const TCHAR* szPath);
//	xTexture* const Getptr(INT iIndex);
//	xTexture* const Getptr(T_STR strFindName);
//	bool		Release();
//public:
//	XTextureMgr();
//	virtual ~XTextureMgr();
//};
//#define I_Texture XTextureMgr::GetInstance()
