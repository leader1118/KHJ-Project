#include "S_AnimObj.h"

void S_AnimObj::GetAnimKeys(INode* pNode, SMesh* pMesh)
{
	BOOL bPosAnim;
	BOOL bRotAnim;
	BOOL bScaleAnim;

	m_iDeltatick = m_Scene.iTickPerFrame;

	if (CheckForAnimation(pNode, bPosAnim, bRotAnim, bScaleAnim))
	{
		if (bPosAnim)
		{
			DumpPosSample(pNode, pMesh);
		}
		if (bRotAnim)
		{
			DumpRotSample(pNode, pMesh);
		}
		if (bScaleAnim)
		{
			DumpScaleSample(pNode, pMesh);
		}
	}

	Control* visCont = pNode->GetVisController();
	if (visCont)
	{
		DumpFloatKeys(visCont, pMesh);
	}
}
bool S_AnimObj::GetDecompAffine(TimeValue t, INode* pNode, AffineParts* ap, Point3* rotAxis, float* rotAngle)
{
	Matrix3 tm = pNode->GetNodeTM(t)*Inverse(pNode->GetParentTM(t));
	decomp_affine(tm, ap);

	Point3 vRotAxis;
	float fRotAngle;
	if (rotAngle != NULL && rotAngle != NULL)
	{
		AngAxisFromQ(ap->q, rotAngle, *rotAxis);
	}
	return true;
}

BOOL S_AnimObj::CheckForAnimation(INode* pNode, BOOL& bPos, BOOL& bRot, BOOL& bScale)
{
	AffineParts ap;
	Point3 firstPos, firstRotAxis, firstScaleFactor;
	float firstRotAngle;

	GetDecompAffine(m_Interval.Start(), pNode, &ap, &firstRotAxis, &firstRotAngle);

	firstPos = ap.t;
	firstScaleFactor = ap.k;

	TimeValue start = m_Interval.Start() + GetTicksPerFrame();
	TimeValue end = m_Interval.End();

	bPos = bRot = bScale = FALSE;

	float rotAngle;
	Point3 rotAxis;

	for (TimeValue t = start; t <= end; t += m_iDeltatick)
	{
		GetDecompAffine(t, pNode, &ap, &rotAxis, &rotAngle);

		if (!bPos)
		{
			if (!EqualPoint3(ap.t, firstPos))
			{
				bPos = TRUE;
			}
		}
		if (!bRot)
		{

			if (fabs(rotAngle - firstRotAngle) > ALMOST_ZERO)
			{
				bRot = TRUE;
			}
			else if (!EqualPoint3(rotAxis, firstRotAxis))
			{
				bRot = TRUE;
			}
		}
		if (!bScale)
		{
			if (!EqualPoint3(ap.k, firstScaleFactor))
			{
				bScale = TRUE;
			}
		}
		if (bPos && bRot && bScale)break;
	}
	return bPos || bRot || bScale;
}
void S_AnimObj::DumpPosSample(INode* pNode, SMesh* pMesh)
{
	TimeValue start = m_Interval.Start();
	TimeValue end = m_Interval.End();
	AffineParts ap;

	for (TimeValue t = start; t <= end; t += m_iDeltatick)
	{
		GetDecompAffine(t, pNode, &ap);

		SAnimTrack pAnim;
		pAnim.iTick = t;
		pAnim.vValue.x = ap.t.x;
		pAnim.vValue.y = ap.t.z;
		pAnim.vValue.z = ap.t.y;
		pMesh->m_PosTrack.push_back(pAnim);
	}
}

void S_AnimObj::DumpRotSample(INode* pNode, SMesh* pMesh)
{
	TimeValue start = m_Interval.Start();
	TimeValue end = m_Interval.End();
	AffineParts ap;

	for (TimeValue t = start; t <= end; t += m_iDeltatick)
	{
		GetDecompAffine(t, pNode, &ap);

		SAnimTrack pAnim;
		pAnim.iTick = t;
		pAnim.qValue.x = ap.q.x;
		pAnim.qValue.y = ap.q.z;
		pAnim.qValue.z = ap.q.y;
		pAnim.qValue.w = ap.q.w;
		pMesh->m_RotTrack.push_back(pAnim);
	}
}

void S_AnimObj::DumpScaleSample(INode* pNode, SMesh* pMesh)
{
	TimeValue start = m_Interval.Start();
	TimeValue end = m_Interval.End();
	AffineParts ap;
	
	for (TimeValue t = start; t <= end; t += m_iDeltatick)
	{
		GetDecompAffine(t, pNode, &ap);

		SAnimTrack Anim;
		Anim.iTick = t;
		Anim.vValue.x = ap.k.x;
		Anim.vValue.y = ap.k.z;
		Anim.vValue.z = ap.k.y;

		Anim.qValue.x = ap.u.x;
		Anim.qValue.y = ap.u.z;
		Anim.qValue.z = ap.u.y;
		Anim.qValue.w = ap.u.w;
		pMesh->m_SclTrack.push_back(Anim);
	}
}

void S_AnimObj::DumpFloatKeys(Control* cont, SMesh* pMesh)
{
	if (!cont)		return;
	int i;
	IKeyControl *ikc = NULL;
	ikc = GetKeyControlInterface(cont);

	SAnimTrack Anim;


	if (ikc && cont->ClassID() == Class_ID(TCBINTERP_FLOAT_CLASS_ID, 0))
	{
		for (i = 0; i < ikc->GetNumKeys(); i++)
		{
			ITCBFloatKey key;
			ikc->GetKey(i, &key);
			Anim.iTick = key.time;
			Anim.vValue.x = key.val;
			pMesh->m_VisTrack.push_back(Anim);
		}
	}
	
	else if (ikc && cont->ClassID() == Class_ID(HYBRIDINTERP_FLOAT_CLASS_ID, 0)) {
		for (i = 0; i < ikc->GetNumKeys(); i++) {
			IBezFloatKey key;
			ikc->GetKey(i, &key);
			Anim.iTick = key.time;
			Anim.vValue.x = key.val;
			pMesh->m_VisTrack.push_back(Anim);

		}
	}
	else if (ikc && cont->ClassID() == Class_ID(LININTERP_FLOAT_CLASS_ID, 0)) {
		for (i = 0; i < ikc->GetNumKeys(); i++)
		{
			ILinFloatKey key;
			ikc->GetKey(i, &key);
			Anim.iTick = key.time;
			Anim.vValue.x = key.val;
			pMesh->m_VisTrack.push_back(Anim);
		}
	}
	else
	{
		TSTR name;
		cont->GetClassName(name);

		
		if (cont->IsAnimated()) {
			
			Interval range;
			
			Interval animRange = m_p3dsMax->GetAnimRange();
			TimeValue t = cont->GetTimeRange(TIMERANGE_ALL).Start();
			float value;

			 
			while (animRange.InInterval(t))
			{
				
				range = FOREVER;
				cont->GetValue(t, &value, range);

				
				t = range.Start();

				Anim.iTick = t;
				Anim.vValue.x = value;
				pMesh->m_VisTrack.push_back(Anim);

				if (range.End() > cont->GetTimeRange(TIMERANGE_ALL).End())
				{
					break;
				}
				else
				{
					
					t = (range.End() / GetTicksPerFrame()) * GetTicksPerFrame();
				}
			}
		}
	}
}
S_AnimObj::S_AnimObj()
{
}


S_AnimObj::~S_AnimObj()
{
}
