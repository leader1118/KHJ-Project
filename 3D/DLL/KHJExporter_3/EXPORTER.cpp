#include "Header.h"

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

	virtual
};