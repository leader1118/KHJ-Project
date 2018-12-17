#pragma once
#include "Header.h"
#include "S_KHJWriter.h"
#define KHJExport_CLASS_ID Class_ID(0x6fb548fb, 0x2a057187) // MAXSDK/help/gencid.exe 새로 발급받아야하는 플러그인
class S_KHJExporter : public SceneExport
{
public:
	S_KHJWriter g_Writer;
public:
	//Constructor/Destructor
	S_KHJExporter();
	~S_KHJExporter();

	int				ExtCount();					// Number of extensions supported
	const TCHAR *	Ext(int n);					// Extension #n (i.e. "3DS")
	const TCHAR *	LongDesc();					// Long ASCII description (i.e. "Autodesk 3D Studio File")
	const TCHAR *	ShortDesc();				// Short ASCII description (i.e. "3D Studio")
	const TCHAR *	AuthorName();				// ASCII Author name
	const TCHAR *	CopyrightMessage();			// ASCII Copyright message
	const TCHAR *	OtherMessage1();			// Other message #1
	const TCHAR *	OtherMessage2();			// Other message #2
	unsigned int	Version();					// Version number * 100 (i.e. v3.01 = 301)
	void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box

	BOOL SupportsOptions(int ext, DWORD options);
	int  DoExport(const TCHAR *name, ExpInterface *ei, Interface *i, BOOL suppressPrompts = FALSE, DWORD options = 0);

};

class S_KHJClassDesc :public ClassDesc2
{
public:
	virtual int IsPublic() { return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) { return new S_KHJExporter(); }
	virtual const TCHAR *	ClassName() { return _T("KHJExporter100"); }
	virtual SClass_ID SuperClassID() { return SCENE_EXPORT_CLASS_ID; }
	virtual Class_ID ClassID() { return KHJExport_CLASS_ID; }
	virtual const TCHAR* Category() { return _T("KHJExporter"); }

	virtual const TCHAR* InternalName() { return _T("S_KHJClassDesc"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() { return hInstance; }					// returns owning module handle

};
ClassDesc2* GetExportDesc()
{
	static S_KHJClassDesc theDesc;
	return &theDesc;
}
S_KHJExporter::S_KHJExporter()
{

}

S_KHJExporter::~S_KHJExporter()
{

}

int S_KHJExporter::ExtCount()
{
#pragma message(TODO("Returns the number of file name extensions supported by the plug-in."))
	return 1;
}

const TCHAR *S_KHJExporter::Ext(int /*i*/)
{
#pragma message(TODO("Return the 'i-th' file name extension (i.e. \"3DS\")."))
	return _T("KHJ");
}

const TCHAR *S_KHJExporter::LongDesc()
{
#pragma message(TODO("Return long ASCII description (i.e. \"Targa 2.0 Image File\")"))
	return _T("KHJExporter 2.0");
}

const TCHAR *S_KHJExporter::ShortDesc()
{
#pragma message(TODO("Return short ASCII description (i.e. \"Targa\")"))
	return _T("KHJExporter");
}

const TCHAR *S_KHJExporter::AuthorName()
{
#pragma message(TODO("Return ASCII Author name"))
	return _T("PROKVIP");
}

const TCHAR *S_KHJExporter::CopyrightMessage()
{
#pragma message(TODO("Return ASCII Copyright message"))
	return _T("");
}

const TCHAR *S_KHJExporter::OtherMessage1()
{
	//TODO: Return Other message #1 if any
	return _T("");
}

const TCHAR *S_KHJExporter::OtherMessage2()
{
	//TODO: Return other message #2 in any
	return _T("");
}

unsigned int S_KHJExporter::Version()
{
#pragma message(TODO("Return Version number * 100 (i.e. v3.01 = 301)"))
	return 100;
}

void S_KHJExporter::ShowAbout(HWND /*hWnd*/)
{
	// Optional
}

BOOL S_KHJExporter::SupportsOptions(int /*ext*/, DWORD /*options*/)
{
#pragma message(TODO("Decide which options to support.  Simply return true for each option supported by each Extension the exporter supports."))
	return TRUE;
}


int	S_KHJExporter::DoExport(const TCHAR *name, ExpInterface *ei, Interface *i, // Interface *i 막강한 인터페이스이다.
	BOOL suppressPrompts, DWORD options)
{
	g_Writer.Initialize(i,name);
	g_Writer.Run();
	g_Writer.Release();
	return TRUE;
}