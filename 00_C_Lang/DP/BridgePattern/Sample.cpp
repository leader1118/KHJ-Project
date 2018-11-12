//bridge는 '무엇인가를 연결한다'는 의미이다. bridge 패턴도 두 장소를 연결하는 역할을 한다.
//bridge 패턴은 기능의 클래스 계층과 구현의 클래스 계층을 연결하고,
//구현부에서 추상 계층을 분리하여 각자 독립적으로 변형할 수 있게 해준다.

#include <iostream>
#include <string>
using namespace std;
class BTree { };
class SearchEngineImp
{
public:
	virtual bool Search(string s, string idxFn) = 0;
	virtual bool Search(string s, BTree& bTree) = 0;
};
class UnixSearchEngineImp : public SearchEngineImp
{
public:
	bool Search(string s, string idxFn)
	{
		// -- Unix 환경에 맞추어 idxFn 에서 문자열 검색
		return true;
	}
	bool Search(string s, BTree& bTree)
	{
		// -- Unix 환경에 맞추어 BTree 에서 문자열 검색
		return true;
	}
};

class WindowsSearchEnginelmp : public SearchEngineImp
{
public:
	bool Search(string s, string idxFn)
	{
		//-- MS Windows 환경에 맞추어 idxFn에서 문자열 검색
		return true;
	}
	bool Search(string s, BTree& bTree)
	{
		//-- MS Windows 환경에 맞추어 BTree 에서 문자열 검색
		return true;
	}
};

class SearchEngine
{
public:
	SearchEngine() { plmp_ = 0; }
	virtual bool Search(string s) = 0;

protected:
	SearchEngineImp * GetSearchEnginelmp()
	{
		if (plmp_ == 0)
		{
#ifdef			__WIN32__
			plmp_ = new WindowsSearchEnginelmp;
#else
			plmp_ = new UnixSearchEngineImp;
#endif
		}
		return plmp_;
	}
private:
	SearchEngineImp * plmp_;
};

class WebSearchEngine : public SearchEngine
{
public:
	WebSearchEngine(string idxFn) { indexFn_ = idxFn; }
	bool Search(string s)
	{
		return GetSearchEnginelmp()->Search(s, indexFn_);
	}
private:
	string indexFn_;
};

class DBSearchEngine : public SearchEngine
{
public:
	bool Search(string s)
	{
		return GetSearchEnginelmp()->Search(s, bTree_);
	}
private:
		BTree bTree_;
};

void main()
{
	WebSearchEngine finder("inverted_file4web.idx");
	finder.Search("디자인 패턴");
}