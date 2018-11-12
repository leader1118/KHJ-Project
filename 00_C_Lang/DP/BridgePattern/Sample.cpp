//bridge�� '�����ΰ��� �����Ѵ�'�� �ǹ��̴�. bridge ���ϵ� �� ��Ҹ� �����ϴ� ������ �Ѵ�.
//bridge ������ ����� Ŭ���� ������ ������ Ŭ���� ������ �����ϰ�,
//�����ο��� �߻� ������ �и��Ͽ� ���� ���������� ������ �� �ְ� ���ش�.

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
		// -- Unix ȯ�濡 ���߾� idxFn ���� ���ڿ� �˻�
		return true;
	}
	bool Search(string s, BTree& bTree)
	{
		// -- Unix ȯ�濡 ���߾� BTree ���� ���ڿ� �˻�
		return true;
	}
};

class WindowsSearchEnginelmp : public SearchEngineImp
{
public:
	bool Search(string s, string idxFn)
	{
		//-- MS Windows ȯ�濡 ���߾� idxFn���� ���ڿ� �˻�
		return true;
	}
	bool Search(string s, BTree& bTree)
	{
		//-- MS Windows ȯ�濡 ���߾� BTree ���� ���ڿ� �˻�
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
	finder.Search("������ ����");
}