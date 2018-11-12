#include <iostream>
#include <typeinfo.h>
#include <vector>
#include <queue> // ť�� ������ �ؼ� ������ ����
// RTTI RUN TIME TYPE INFORMATION

#define STRING(S)	#S  //  # ��Ʈ��ȭ ������
#define LINK(i,j)	i##j // ## ���� ������


#define DECLARE_CLASSNAME static char IpszClassName[] // ����ƽ �Լ�
#define IMPLEMENT_CLASSNAME(S) char S##::IpszClassName[] = (#S); // ����ƽ �ʱ�ȭ 
#define RUNTIME_CLASS(S) &S::class##S; // ����� �ּҸ� �����Ҳ���.

#define DECLARE_DYNAMIC(S) static CRuntimeClass class##S;
#define DECLARE_DYN_CREATE(S) static CObject* CreateObject();
#define IMPLEMENT_DYN_CREATE(S) static CObject* CreateObject() {return new S;};
#define IMPLEMENT_DYNMIC(S) CRuntimeClass S::class##S = {#S,sizeof(S),S::CreateObject };
// &(CMyClass::classCMyClass);

class CObject; // ���漱��

struct CRuntimeClass
{
	char m_ipszClassName[21];
	int m_iObjectSize;
	CObject* (*pfnCreateObject)(); // �Լ� ������
	CObject* CreateObject()
	{
		return (*pfnCreateObject)(); // CMyClass�� ȣ���ϰ� �ֳ�
	}
};

// ���� Ŭ���� ����
 // MFC ���

class CObject
{
public:
	static CRuntimeClass classCObject; // CRuntimeClass�� ��� �ִ°Ŵ�
	DECLARE_CLASSNAME; // CObject�� ���� CMyclass �̴�
	virtual char* GetClassName() const
	{
		return NULL;
	}
	virtual ~CObject() {}
	static CObject* CreateObject();
protected: // �����ڸ� ������ �Ļ��ؼ��� ��밡��
	CObject() {}
};
IMPLEMENT_CLASSNAME(CObject);
CObject* CObject::CreateObject()
{
	return NULL;
}
IMPLEMENT_DYNMIC(CObject);
//CRuntimeClass CObject::classCObject = { "CObject" ,sizeof(CObject),NULL }; // �ܺο��� �ʱ�ȭ 32����

class TsessionMgr // ���̺귯�� �ȿ� �ִ°Ŵ�
{
public:
	std::queue<CObject*>m_StaticQueue;
	std::vector<CObject*>m_userlist;
	void Create(CRuntimeClass* pRTC)
	{
		for (int iQueue = 0; iQueue < 1000; iQueue++) // 1000���� CMyClass�� �� �ִ°Ŵ� // ����ȭ
		{
			CObject* pObj = pRTC->CreateObject();
			m_StaticQueue.push(pObj);
		}
	}
	CObject* CreateNewSession()
	{
		CObject* newSession = (CObject*)m_StaticQueue.front();
		m_userlist.push_back(newSession);
		return newSession;
	}
	CObject* RemoveSession(CObject* pSession)
	{
	
		//m_userlist.push_back(newSession); itor ����ض�
		m_StaticQueue.push(pSession);
	}
};
TsessionMgr g_SessionMgr;

// --------------------------��-------------------------------- �� �ִ� 
// ��ũ�η� ����ϸ� ���� ���ϴ�.
class CMyClass : public CObject
{
public:
	DECLARE_CLASSNAME;
	DECLARE_DYNAMIC(CMyClass);
	//static CRuntimeClass classCMyClass;
	DECLARE_DYN_CREATE(CMyClass);
	//static CObject* CreateObject(); // �Լ� ������

	/*virtual char* GetClassName() const
	{
		return IpszClassName;
	}*/
};
IMPLEMENT_CLASSNAME(CMyClass);
IMPLEMENT_DYN_CREATE(CMyClass);
//IMPLEMENT_CLASSNAME(CMyClass);

IMPLEMENT_DYNMIC(CMyClass);
//CObject* CMyClass::CreateObject() { return new CMyClass; };
//CRuntimeClass CMyClass::classCMyClass = { "CMyClass" ,sizeof(CMyClass),CMyClass::CreateObject };

void main()
{
	//g_SessionMgr.Create(RUNTIME_CLASS(CMyClass));

	CRuntimeClass* pRTCMyClass = RUNTIME_CLASS(CMyClass);
	g_SessionMgr.Create(pRTCMyClass);

	/*CObject* p = pRTCMyClass->CreateObject(); 
	CMyClass* pChild = (CMyClass*)p;
	std::cout << pChild->IpszClassName << std::endl;
	delete p;*/


#pragma region LINK&STRING
	std::cout << STRING(kgca) << std::endl;
	char m_szValue[] = "kgcagame";
	std::cout << LINK(m_sz, Value) << std::endl; // �� �̿��ϸ� ������ �߰ɾ ������ ����� �� �ִ�
	std::cout << m_szValue << std::endl;

	int LINK(m_i, Data) = 0;
	//	int m_iData = 0;
#pragma endregion LINK&STRING

//#pragma region aaa
//	CBase	parent;
//	CChild	child;
//
//	const type_info& tBase = typeid(parent);
//	const type_info& tChild = typeid(child);
//
//	std::cout << tBase.name() << "{ }" << std::endl;
//	std::cout << typeid(parent).name() << std::endl;
//
//	std::cout << tChild.name() << std::endl;
//	std::cout << typeid(child).name() << std::endl;
//
//	std::cout << tBase.before(tChild) << std::endl;
//	std::cout << tChild.before(tBase) << std::endl;
//	std::cout << (tChild == tBase) << std::endl;
//#pragma endregion aaa
}

//
//#include <iostream>
//#include <typeinfo.h>
////#include <list>
//#include <queue>
//
//#define DECLARE_CLASSNAME static char lpszClassName[]
//#define IMPLEMENT_CLASSNAME(s) char s##::lpszClassName[] = (#s);
//
//#define DECLARE_DYNCREATE static CObject* CreateObject();
//#define IMPLEMENT_DYNCREATE(s) CObject* s::CreateObject()   {return new s;}
//
//#define DECLARE_DYNAMIC(s) static CRuntimeClass class##s;
//#define IMPLEMENT_DYNAMIC(s) CRuntimeClass s::class##s={ #s, sizeof(s), s::CreateObject }
//
//#define DECLARE_DYNCLASS_CREATE CRuntimeClass* GetRuntimeClass() const;
//#define IMPLEMENT_DYNCLASS_CREATE(s) CRuntimeClass* s::GetRuntimeClass() const{return &class##s;}
//
//#define RUNTIME_CLASS(s) &s::class##s;
//
//
//class CObject;
////�ٽ�!!!
//class CRuntimeClass
//{
//public:
//	char m_lpszClassName[21];
//	int  m_iObjectSize;
//	CObject* (*pfnCreateObject)();
//	CObject* CreateObject()
//	{
//		return (*pfnCreateObject)();
//	}
//};
//
//class CObject
//{
//public:
//	static CRuntimeClass classCObject; //DECLARE_DYNAMIC(CObject);
//	static char lpszClassName[];       //DECLARE_CLASSNAME;
//	virtual CRuntimeClass* GetRuntimeClass() const
//	{
//		return NULL;
//	}
//	virtual ~CObject() {}
//protected:
//	CObject() {}
//};
//
//char CObject::lpszClassName[] = "CObject"; //  IMPLEMENT_CLASSNAME(CObject);
//CRuntimeClass CObject::classCObject = { "CObject", sizeof(CObject), NULL };
//
//class Mgr
//{
//public:
//
//	std::queue<CObject*>  m_StaticQueue;
//	std::queue<CObject*>  m_UserQueue;
//
//	void Create(CRuntimeClass* pRTC)
//	{
//		for (int iQueue = 0; iQueue < 1000; iQueue++) {
//			CObject* pObj = pRTC->CreateObject();
//			m_StaticQueue.push(pObj);
//		}
//	}
//
//	CObject* CreateUser()
//	{
//		CObject* User = (CObject*)m_StaticQueue.front();
//		m_UserQueue.push(User);
//		return User;
//	}
//};
//
//Mgr g_mgr;
//
////�� ���� ���̺귯���� �ִ� Ŭ����
////----------------------------------------------------------------------------------//
////�� �Ʒ��� ���α׷� �ڵ�
//
//
//class CUser : public CObject
//{
//public:
//	DECLARE_CLASSNAME;        /*static char lpszClassName[];            */
//	DECLARE_DYNCREATE;        /*static CObject* CreateObject();         */
//	DECLARE_DYNCLASS_CREATE;  /*CRuntimeClass* GetRuntimeClass() const; */
//	DECLARE_DYNAMIC(CUser);     /*static CRuntimeClass classCUser;        */
//protected:
//	CUser() {}
//};
//
//IMPLEMENT_CLASSNAME(CUser);         /*char CUser::lpszClassName[] = ("CUser");                                           */
//IMPLEMENT_DYNCREATE(CUser);         /*CObject* CUser::CreateObject() { return new CUser; }                               */
//IMPLEMENT_DYNCLASS_CREATE(CUser);  /*CRuntimeClass* CUser::GetRuntimeClass() const { return &classCUser; }              */
//IMPLEMENT_DYNAMIC(CUser);         /*CRuntimeClass CUser::classCUser = { "CUser", sizeof(CUser), CUser::CreateObject }; */
//
//class test : public CObject
//{
//public:
//	DECLARE_CLASSNAME;        /*static char lpszClassName[];            */
//	DECLARE_DYNCREATE;        /*static CObject* CreateObject();         */
//	DECLARE_DYNCLASS_CREATE;  /*CRuntimeClass* GetRuntimeClass() const; */
//	DECLARE_DYNAMIC(test);     /*static CRuntimeClass classCUser;        */
//protected:
//	test() {}
//};
//
//IMPLEMENT_CLASSNAME(test);         /*char CUser::lpszClassName[] = ("CUser");                                           */
//IMPLEMENT_DYNCREATE(test);         /*CObject* CUser::CreateObject() { return new CUser; }                               */
//IMPLEMENT_DYNCLASS_CREATE(test);  /*CRuntimeClass* CUser::GetRuntimeClass() const { return &classCUser; }              */
//IMPLEMENT_DYNAMIC(test);         /*CRuntimeClass CUser::classCUser = { "CUser", sizeof(CUser), CUser::CreateObject }; */
//
//
//int main()
//{
//	CRuntimeClass* pRTCMyClass = RUNTIME_CLASS(CUser);
//	g_mgr.Create(pRTCMyClass);
//
//	//CRuntimeClass* pRTCMyClass = &CUser::classCUser; //RUNTIME_CLASS(CUser);
//	//CObject* p = pRTCMyClass->CreateObject();
//
//	g_mgr.CreateUser();
//	g_mgr.CreateUser();
//	g_mgr.CreateUser();
//
//	test* pPoint;
//	CUser* pCUser;
//
//	for (int i = 0; i < 2; i++) {
//		pPoint = (test*)(g_mgr.m_UserQueue.front());
//		std::cout << pPoint->lpszClassName << std::endl;
//		g_mgr.m_UserQueue.pop();
//		//delete (CUser*)(CUser*)(g_mgr.m_UserQueue.front());
//	}
//
//	pCUser = (CUser*)(g_mgr.m_UserQueue.front());
//	std::cout << pCUser->lpszClassName << std::endl;
//	g_mgr.m_UserQueue.pop();
//
//}