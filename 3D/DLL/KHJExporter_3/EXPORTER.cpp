#include "Header.h"
#include "S_Writer.h"
#define KHJEXP_CLASS_ID Class_ID(0x79537139, 0x5c066d4f)

class KHJExporter : public SceneExport
{
public:
	KHJExporter();
	~KHJExporter();
public:
	int ExtCount();
	const TCHAR* Ext(int n);
	const TCHAR* LongDesc();
	const TCHAR* ShortDesc();
	const TCHAR* AuthorName();
	const TCHAR* CopyrightMessage();
	const TCHAR* OtherMessage1();
	const TCHAR* OtherMessage2();
	unsigned int Version();
	void ShowAbout(HWND hWnd);

	BOOL SupportsOptions(int ext, DWORD options);
	int DoExport(const TCHAR* name, ExpInterface* ei, Interface *i, BOOL suppressPrompts = FALSE, DWORD options = 0);
};

class KHJExporterClassDesc : public ClassDesc2
{
public:
	virtual int IsPublic() { return TRUE; }
	virtual void* Create(BOOL) { return new KHJExporter(); }
	virtual const TCHAR* ClassName() { return _T("KHJExporter100"); }
	virtual SClass_ID SuperClassID() { return SCENE_EXPORT_CLASS_ID; }
	virtual Class_ID ClassID() { return KHJEXP_CLASS_ID; }
	virtual const TCHAR* Category() { return _T("KHJExporter"); }

	virtual const TCHAR* InternalName() { return _T("KHJExporterClassDesc"); }
	virtual HINSTANCE Hinstance() { return hInstance; }
};

ClassDesc2* GetExportDesc()
{
	static KHJExporterClassDesc KHJExportDesc;
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
	return 1;
}

const TCHAR* KHJExporter::Ext(int n)
{
	return _T("KHJ");
}
const TCHAR* KHJExporter::LongDesc()
{
	return _T("KHJ EXPOTER 2.0");
}

const TCHAR* KHJExporter::ShortDesc()
{
	return _T("KHJExpoter");
}

const TCHAR* KHJExporter::AuthorName()
{
	return _T("PROKVIP");
}

const TCHAR* KHJExporter::CopyrightMessage()
{
	return _T("");
}

const TCHAR* KHJExporter::OtherMessage1()
{
	return _T("");
}
const TCHAR* KHJExporter::OtherMessage2()
{
	return _T("");
}

unsigned int KHJExporter::Version()
{
	return 100;
}

void KHJExporter::ShowAbout(HWND)
{

}

BOOL KHJExporter::SupportsOptions(int, DWORD)
{
	return TRUE;
}

int KHJExporter::DoExport(const TCHAR* name, ExpInterface* ei, Interface* i, BOOL suppressPrompts, DWORD options)
{
	I_Writer.Initialize(i);
	I_Writer.KHJExport();
	return TRUE;
}