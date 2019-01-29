#pragma once
#include "TTemplate.h"
#include "S_Character.h"
#include "TParser.h"


class SCharacterLoader : public TParser
{
public:
	BOOL GetDataFromSkinMeshString(const TCHAR* pString, VOID* pData0, VOID* pData1);
public:
	SCharacterLoader() {};
	~SCharacterLoader() {};
};
class S_CharMgr : public TTemplateMap<S_Character>, public TSingleton<S_CharMgr>
{
private:
	friend class TSingleton<S_CharMgr>;
public:
	SCharacterLoader m_Parser;
public:
	int Create(ID3D11Device* pd3dDevice,
		ID3D11DeviceContext* plmmediateContext,
		const TCHAR* strFileName,
		const TCHAR* strShaderName,
		int iMatrixIndex = -1);
	bool Load(ID3D11Device* pd3dDevice,
		ID3D11DeviceContext* plmmediateContext,
		const TCHAR* strFileName);

public:
	S_CharMgr();
	virtual ~S_CharMgr();
};
#define I_CharMgr S_CharMgr::GetInstance()
