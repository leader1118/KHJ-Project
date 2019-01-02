// DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다


#define KHJ_EXPORT_CLASS_ID Class_ID(0x55533089, 0x59c62028)

#include "Header.h"
#include "S_KHJ_Writer.h"
#include "S_KHJ_SkinExp.h"

class KHJMaxExporter : public UtilityObj
{
public:
	HWND hPanel;
	IUtil *iu;
	Interface *ip;
	// Constructor/Destructor
	KHJMaxExporter();
	virtual ~KHJMaxExporter();

	virtual void DeleteThis() {}

	virtual void BeginEditParams(Interface *ip, IUtil *iu);
	virtual void EndEditParams(Interface *ip, IUtil *iu);

	virtual void Init(HWND hWnd);
	virtual void Destroy(HWND hWnd);

	void SelectionSetChanged(Interface *ip, IUtil *iu);

	// Singleton access
	static KHJMaxExporter* GetInstance()
	{
		static KHJMaxExporter theKHJUtilExp;
		return &theKHJUtilExp;
	}

private:

	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

class KHJUtilExpClassDesc : public ClassDesc2
{
public:
	virtual int IsPublic() { return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) { return KHJMaxExporter::GetInstance(); }
	virtual const TCHAR* ClassName() { return _T("KHJMaxExporter"); }
	virtual SClass_ID SuperClassID(){ return UTILITY_CLASS_ID; }
	virtual Class_ID ClassID() { return KHJ_EXPORT_CLASS_ID; }
	virtual const TCHAR* Category() { return _T("KHJMaxExporter"); }
	virtual const TCHAR* InternalName() { return _T("KHJMaxExporter"); }
	virtual HINSTANCE HInstance() { return hInstance; }
};

ClassDesc2* GetExportDesc()
{
	static KHJUtilExpClassDesc KHJUtilExpDesc;
	return &KHJUtilExpDesc;
}

KHJMaxExporter::KHJMaxExporter()
	: hPanel(nullptr)
	, iu(nullptr)
{

}

KHJMaxExporter::~KHJMaxExporter()
{

}

void KHJMaxExporter::BeginEditParams(Interface* ip, IUtil* iu)
{
	this->iu = iu;
	this->ip = ip;
	hPanel = ip->AddRollupPage(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), DlgProc, _T("Parameters"), 0);
}

void KHJMaxExporter::EndEditParams(Interface* ip, IUtil*)
{
	this->iu = NULL;
	this->ip = NULL;
	this->iu = nullptr;

	ip->DeleteRollupPage(hPanel);
	hPanel = nullptr;
}

void KHJMaxExporter::Init(HWND hWnd)
{
	if (I_SkinExp.Init() == false)return;
	if (I_Writer.Initialize(ip) == false)return;

	if (I_Writer.m_MatrixMap.Count() > 0)
	{
		EnableWindow(GetDlgItem(KHJMaxExporter::GetInstance()->hPanel, IDC_SKINEXP), true);
		EnableWindow(GetDlgItem(KHJMaxExporter::GetInstance()->hPanel, IDC_MATRIXEXP), true);
		EnableWindow(GetDlgItem(KHJMaxExporter::GetInstance()->hPanel, IDC_OBJEXPORT), true);
		EnableWindow(GetDlgItem(KHJMaxExporter::GetInstance()->hPanel, IDC_UPDATE), false);
	}
	else
	{
		EnableWindow(GetDlgItem(KHJMaxExporter::GetInstance()->hPanel, IDC_SKINEXP), false);
		EnableWindow(GetDlgItem(KHJMaxExporter::GetInstance()->hPanel, IDC_MATRIXEXP), false);
		EnableWindow(GetDlgItem(KHJMaxExporter::GetInstance()->hPanel, IDC_OBJEXPORT), false);
		EnableWindow(GetDlgItem(KHJMaxExporter::GetInstance()->hPanel, IDC_UPDATE), true);
	}
	//SendMessage(theKHJUtilExp::GetInstance()->hPanel, BM_SETCHECK, BST_CHECKED, 0);
	//CheckDlgButton(KHJMaxExporter.hPanel, IDC_BINDPOSE, TRUE );
	//EnableWindow(GetDlgItem(theKHJUtilExp::GetInstance()->hPanel, IDC_BINDPOSE), false);
}

void KHJMaxExporter::Destroy(HWND hWnd)
{
	I_SkinExp.Release();
	I_Writer.Release();
}

void KHJMaxExporter::SelectionSetChanged(Interface* ip, IUtil* iu)
{
	if (ip->GetSelNodeCount() <= 0)
	{
		return;
	}
	if (I_Writer.Initialize(ip) == false)
	{
		return;
	}
	I_SkinExp.Release();

	for (int iSelectObj = 0; iSelectObj < ip->GetSelNodeCount(); iSelectObj++)
	{
		I_SkinExp.GetNodeInfo(ip->GetSelNode(iSelectObj), ip->GetTime());
	}
	if (I_Writer.m_MatrixMap.Count() > 0)
	{
		EnableWindow(GetDlgItem(KHJMaxExporter::GetInstance()->hPanel, IDC_MATRIXEXP), true);
		if (ip->GetSelNodeCount() > 0)
		{
			EnableWindow(GetDlgItem(KHJMaxExporter::GetInstance()->hPanel, IDC_SKINEXP), true);
		}
		else
		{
			EnableWindow(GetDlgItem(KHJMaxExporter::GetInstance()->hPanel, IDC_SKINEXP), false);
		}
	}
	else
	{
		EnableWindow(GetDlgItem(KHJMaxExporter::GetInstance()->hPanel, IDC_MATRIXEXP), false);
	}
}

INT_PTR CALLBACK KHJMaxExporter::DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		KHJMaxExporter::GetInstance()->Init(hWnd);
		break;
	case WM_DESTROY:
		KHJMaxExporter::GetInstance()->Destroy(hWnd);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_OBJEXPORT:
		{
			I_Writer.Initialize(KHJMaxExporter::GetInstance()->ip);
			I_Writer.KHJExport();
		}break;
		case IDC_SKINEXP:
		{
			I_Writer.SetBindPose(true);
			I_Writer.Initialize(KHJMaxExporter::GetInstance()->ip);
			I_SkinExp.m_Scene = I_Writer.m_Scene;
			I_SkinExp.skmExport();
		}break;
		case IDC_MATRIXEXP:
		{
			I_Writer.Initialize(KHJMaxExporter::GetInstance()->ip);
			I_Writer.SetBindPose(true);
			I_Writer.matExport();
		}break;
		}break;

	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MOUSEMOVE:
		GetCOREInterface()->RollupMouseMessage(hWnd, msg, wParam, lParam);
		break;
	default:
		return 0;
	}
	return 1;
}