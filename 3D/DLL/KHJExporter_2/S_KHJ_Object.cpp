#include "S_KHJ_Object.h"

void S_KHJ_Object::GetMaterial()
{
	for (int iMtl = 0; iMtl < m_pMtlList.size(); iMtl++)
	{
		Mtl* pSrcMtl = m_pMtlList[iMtl];

		SMtl AddMtl;
		TSTR className;
		pSrcMtl->GetClassName(className);
		AddMtl.strName = FixupName(pSrcMtl->GetName());
		AddMtl.strClassName = FixupName(className);
		AddMtl.iNumSubMtl = pSrcMtl->NumSubMtls();
		AddMtl.iIndex = iMtl;

		if (pSrcMtl->NumSubMtls() > 0)
		{
			for (int iSubMtrl = 0; iSubMtrl < pSrcMtl->NumSubMtls(); iSubMtrl++)
			{
				Mtl* subMtl = pSrcMtl->GetSubMtl(iSubMtrl);

				SMtl AddSubMtl;
				AddSubMtl.iIndex = iSubMtrl;
				AddSubMtl.iNumSubMtl = subMtl->NumSubMtls();
				AddSubMtl.strName = FixupName(subMtl->GetName());

				TSTR className;
				subMtl->GetClassName(className);
				AddSubMtl.strClassName = FixupName(className);

				if (subMtl->NumSubMtls() > 0)
				{
					MessageBox(0, _T("다중 서브 매터리얼"), _T("Fatal error"), MB_OK);
				}
				if (subMtl)
				{
					GetTexture(&AddSubMtl, subMtl);
				}
				AddMtl.SubMaterial.push_back(AddSubMtl);
			}
		}
		else
		{
			GetTexture(&AddMtl, pSrcMtl);
		}
		m_Material.push_back(AddMtl);
	}
}

void  S_KHJ_Object::GetTexture(SMtl* DestMtrl, Mtl* pSrcMtl)
{
	for (int iSubMap = 0; iSubMap < pSrcMtl->NumSubTexmaps(); iSubMap++)
	{
		Texmap* tex = pSrcMtl->GetSubTexmap(iSubMap);
		if (tex)
		{
			if (pSrcMtl->ClassID() == Class_ID(DMTL_CLASS_ID, 0))
			{
				StdMat* std = (StdMat*)pSrcMtl;
				if (!std->MapEnabled(iSubMap))
					continue;
			}

			STexMap TexMap;
			TexMap.iType = iSubMap;

			if (tex->ClassID() == Class_ID(BMTEX_CLASS_ID, 0x00))
			{
				TSTR mapName = ((BitmapTex*)tex)->GetMapName();
				TSTR 
			}
		}
	}
}

S_KHJ_Object::S_KHJ_Object()
{
}


S_KHJ_Object::~S_KHJ_Object()
{
}
