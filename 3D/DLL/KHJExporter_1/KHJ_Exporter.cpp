// kgcaExporter.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의 합니다.

#include "Header.h"

#define KHJExporter_CLASS_ID Class_ID(0x7f1d60c8, 0x6c453ac4)

class KHJExporter : public SceneExport
{
public:
	KHJExporter();
	~KHJExporter();
public:
	int			 ExtCount();
	const TCHAR *Ext(int n);
	const TCHAR *LongDesc();
	const TCHAR *ShortDesc();
	const TCHAR *AuthorName();
	const TCHAR *CopyrightMessage();
	const TCHAR *OtherMessage1();
	const TCHAR *OtherMessage2();
	unsigned int Version();
	void		 ShowAbout(HWND hwnd);
	
public:
	BOOL SupportsOptions(int ext, DWORD options);
	int DoExport(const TCHAR *name, ExpInterface *ei, Interface*i, BOOL suppressPrompts = FALSE, DWORD options = 0);
};

class KHJExportClassDesc :public ClassDesc2
{
public:
	virtual int IsPublic() { return TRUE; }
	virtual void* Create(BOOL) { return new KHJExporter(); }
	virtual const TCHAR* ClassName() { return _T("KHJ_EXPORTER 1"); }
	virtual SClass_ID SuperClassID() { return SCENE_EXPORT_CLASS_ID; }
	virtual Class_ID ClassID() { return KHJExporter_CLASS_ID; }
	virtual const TCHAR* Category() { return _T("KHJ_EXPORTER"); }

	virtual const TCHAR* InternalName() { return _T("KHJ_EXPORT_ClassDesc"); }
	virtual HINSTANCE HInstance() { return hInstance; }
};

ClassDesc2* GetExportDesc()
{
	static KHJExportClassDesc KHJExportDesc;
	return &KHJExportDesc;
}

KHJExporter::KHJExporter()
{

}
KHJExporter::~KHJExporter()
{

}

int KHJExporter::ExtCount()
{
#pragma message(TODO("Returns the number of file name extensions supported by the plug-in"))
	return 1;
}

const TCHAR *KHJExporter::Ext(int)
{
#pragma message(TODO("Return the 'i-th' file name extension (i.e. \"3DS\")."))
	return _T("KHJ1");
}

const TCHAR* KHJExporter::LongDesc()
{
#pragma message(TODO("Return long ASCII description (i.e. \"Targa 2.0 Image File\")")))
	return _T("KHJ Exporter 1.0");
}

const TCHAR* KHJExporter::ShortDesc()
{
#pragma message(TODO("Return short ASCII description (i.e. \"Targa\")"))
	return _T("KHJExporter");
}

const TCHAR *KHJExporter::AuthorName()
{
#pragma message(TODO("Return ASCII Author name"))
	return _T("PROKVIP");
}

const TCHAR *KHJExporter::CopyrightMessage()
{
#pragma message(TODO("Return ASCII Copyright message"))
	return _T("");
}

const TCHAR *KHJExporter::OtherMessage1()
{
	//TODO: Return Other message #1 if any
	return _T("");
}

const TCHAR *KHJExporter::OtherMessage2()
{
	//TODO: Return other message #2 in any
	return _T("");
}

unsigned int KHJExporter::Version()
{
#pragma message(TODO("Return Version number * 100 (i.e. v3.01 = 301)"))
	return 100;
}

void KHJExporter::ShowAbout(HWND /*hWnd*/)
{
	// Optional
}

BOOL KHJExporter::SupportsOptions(int /*ext*/, DWORD /*options*/)
{
#pragma message(TODO("Decide which options to support.  Simply return true for each option supported by each Extension the exporter supports."))
	return TRUE;
}


int	KHJExporter::DoExport(const TCHAR *name, ExpInterface *ei, Interface *i,
	BOOL suppressPrompts, DWORD options)
{
	return FALSE;
}


