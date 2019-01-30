#include "S_CharMgr.h"
#include "TObjMgr.h"

BOOL SCharacterLoader::GetDataFromSkinMeshString(const TCHAR* pString, VOID* pData0, VOID* pData1)
{
	TCHAR szPath_0[MAX_PATH] = TEXT("");
	TCHAR szPath_1[MAX_PATH] = TEXT("");

	_fgetts(m_pBuffer, 256, m_pStream);
	_stscanf(m_pBuffer, _T("%s%s%s"), m_pString, szPath_0, szPath_1);
	if (!_tcsicmp(m_pString, pString))
	{
		_tcscpy((TCHAR*)pData0, &szPath_0[0]);
		_tcscpy((TCHAR*)pData1, &szPath_1[0]);
		return TRUE;
	}
	return FALSE;
}
int S_CharMgr::Create(ID3D11Device* pd3dDevice,
	ID3D11DeviceContext* plmmediateContext,
	const TCHAR* strFileName,
	const TCHAR* strShaderName,
	int iMatrixIndex)
{
	TCHAR szFileName[256];
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];

	if (strFileName)
	{
		_tsplitpath_s(strFileName, Drive, Dir, FName, Ext);
		Ext[4] = 0;
		_stprintf_s(szFileName, _T("%s%s"), FName, Ext);

		for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++)
		{
			S_Character *pPoint = (S_Character*)(*itor).second;
			if (!_tcsicmp(pPoint->m_szName.c_str(), szFileName))
			{
				return (*itor).first;
			}
		}
	}
	S_Character* pChild = 0;
	SAFE_NEW(pChild, S_Character);
	pChild->m_szName = szFileName;

	pChild->m_pBoneObject = (TBoneObj*)I_ObjMgr.GetPtr(iMatrixIndex);

	pChild->SetActionFrame(pChild->m_pBoneObject->m_Scene.iFirstFrame,
		pChild->m_pBoneObject->m_Scene.iLastFrame,
		iMatrixIndex);

	{
		TMap.insert(make_pair(m_iCurIndex++, pChild));
		return m_iCurIndex - 1;
	}
	return -1;

}

bool S_CharMgr::Load(ID3D11Device* pd3dDevice,
	ID3D11DeviceContext* plmmediateContext,
	const TCHAR* strFileName)
{
	const TCHAR* Sections[] = { _T("*SKIN_UPPER_BODY_COUNT"), 	_T("*SKIN_UPPER_BODY"),
							_T("*SKIN_LOWER_BODY_COUNT"),	_T("*SKIN_LOWER_BODY"),
							_T("*SKIN_ARM_COUNT"),		_T("*SKIN_ARM"),
							_T("*SKIN_HAND_COUNT"),		_T("*SKIN_HAND"),
							_T("*SKIN_FOOT_COUNT"),		_T("*SKIN_FOOT"),
							_T("*SKIN_FACE_COUNT"),		_T("*SKIN_FACE"),
							_T("*SKIN_HAIR_COUNT"),		_T("*SKIN_HAIR"),
							_T("*SKIN_WEAPON_COUNT"),	_T("*SKIN_WEAPON"),
							_T("*SKIN_DEFENSE_COUNT"),	_T("*SKIN_DEFENSE"),
							_T("*SKIN_ETCETERA_COUNT"),	_T("*SKIN_ETCETERA"), };

	int iNumSection = sizeof(Sections) / sizeof(Sections[0]);

	m_Parser.OpenStream(strFileName);
	TCHAR strCharacterName[MAX_PATH] = { 0, };
	TCHAR strMeshName[MAX_PATH] = { 0, };
	TCHAR strShaderName[MAX_PATH] = { 0, };
	TCHAR strMatrixName[MAX_PATH] = { 0, };

	int iNumCharacter = 0;

	if (m_Parser.GetDataFromFileLoop(_T("*NUMCHARACTER"), &iNumCharacter, INT_DATA))
	{
		float a, b, c;
		for (int iNum = 0; iNum < iNumCharacter; iNum++)
		{
			m_Parser.GetDataFromFileLoop(_T("*CHARACTERNAME"), strCharacterName, STRING_DATA);
			m_Parser.GetDataFromFileLoop(_T("*SHADERFILENMAE"), strShaderName, STRING_DATA);
			m_Parser.GetDataFromFileLoop(_T("*MATRIXFILENAME"), strMatrixName, STRING_DATA);

			int		iNumSkin = 0;
			S_Character* pChar = 0;
			int iCharacterIndex = -1;
			int iMatrixIndex = -1;

			if (_tcsicmp(strMatrixName, _T("null")))
			{
				iMatrixIndex = I_ObjMgr.Load(pd3dDevice, strMatrixName, _T("MatrixViewer.hlsl"));
			}

			iCharacterIndex = Create(pd3dDevice, plmmediateContext,
				strCharacterName, strShaderName,
				iMatrixIndex);

			if (iCharacterIndex < 0) continue;
			pChar = GetPtr(iCharacterIndex);

			for (int iMesh = 0; iMesh < iNumSection; iMesh += 2)
			{
				m_Parser.GetDataFromFileLoop(Sections[iMesh], &iNumSkin, INT_DATA);
				for (int iSkin = 0; iSkin < iNumSkin; iSkin++)
				{
					m_Parser.GetDataFromSkinMeshString(Sections[iMesh + 1], strMeshName, strMatrixName);
					int iModelMatrixIndex = -1;
					if (_tcsicmp(strMatrixName, _T("null")))
					{

						iModelMatrixIndex = I_ObjMgr.Load(pd3dDevice, strMatrixName, _T("MatrixViewer.hlsl"));
					}
					if (pChar)
					{
						pChar->Add(pd3dDevice, plmmediateContext,
							strMeshName, strShaderName,
							iMatrixIndex,
							iModelMatrixIndex);
					}
				}
			}
		}
	}
	m_Parser.CloseStream();
	return true;
}




S_CharMgr::S_CharMgr()
{
}


S_CharMgr::~S_CharMgr()
{
}
