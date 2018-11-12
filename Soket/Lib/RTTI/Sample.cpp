#include <iostream>
#include <typeinfo.h>
#include <vector>
#include <queue> // 큐는 재정의 해서 쓰느게 좋다
// RTTI RUN TIME TYPE INFORMATION

#define STRING(S)	#S  //  # 스트링화 연산자
#define LINK(i,j)	i##j // ## 연결 연산자


#define DECLARE_CLASSNAME static char IpszClassName[] // 스태틱 함수
#define IMPLEMENT_CLASSNAME(S) char S##::IpszClassName[] = (#S); // 스태틱 초기화 
#define RUNTIME_CLASS(S) &S::class##S; // 어떤놈의 주소를 연결할꺼다.

#define DECLARE_DYNAMIC(S) static CRuntimeClass class##S;
#define DECLARE_DYN_CREATE(S) static CObject* CreateObject();
#define IMPLEMENT_DYN_CREATE(S) static CObject* CreateObject() {return new S;};
#define IMPLEMENT_DYNMIC(S) CRuntimeClass S::class##S = {#S,sizeof(S),S::CreateObject };
// &(CMyClass::classCMyClass);

class CObject; // 전방선언

struct CRuntimeClass
{
	char m_ipszClassName[21];
	int m_iObjectSize;
	CObject* (*pfnCreateObject)(); // 함수 포인터
	CObject* CreateObject()
	{
		return (*pfnCreateObject)(); // CMyClass를 호출하고 있네
	}
};

// 동적 클래스 생성
 // MFC 기반

class CObject
{
public:
	static CRuntimeClass classCObject; // CRuntimeClass를 들고 있는거다
	DECLARE_CLASSNAME; // CObject에 대한 CMyclass 이다
	virtual char* GetClassName() const
	{
		return NULL;
	}
	virtual ~CObject() {}
	static CObject* CreateObject();
protected: // 생성자를 막은건 파생해서만 사용가능
	CObject() {}
};
IMPLEMENT_CLASSNAME(CObject);
CObject* CObject::CreateObject()
{
	return NULL;
}
IMPLEMENT_DYNMIC(CObject);
//CRuntimeClass CObject::classCObject = { "CObject" ,sizeof(CObject),NULL }; // 외부에서 초기화 32번줄

class TsessionMgr // 라이브러리 안에 있는거다
{
public:
	std::queue<CObject*>m_StaticQueue;
	std::vector<CObject*>m_userlist;
	void Create(CRuntimeClass* pRTC)
	{
		for (int iQueue = 0; iQueue < 1000; iQueue++) // 1000개의 CMyClass가 들어가 있는거다 // 정적화
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
	
		//m_userlist.push_back(newSession); itor 사용해라
		m_StaticQueue.push(pSession);
	}
};
TsessionMgr g_SessionMgr;

// --------------------------벽-------------------------------- 이 있다 
// 매크로로 사용하면 정말 편하다.
class CMyClass : public CObject
{
public:
	DECLARE_CLASSNAME;
	DECLARE_DYNAMIC(CMyClass);
	//static CRuntimeClass classCMyClass;
	DECLARE_DYN_CREATE(CMyClass);
	//static CObject* CreateObject(); // 함수 포인터

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
	std::cout << LINK(m_sz, Value) << std::endl; // 잘 이용하면 조건을 잘걸어서 변수를 사용할 수 있다
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
////핵심!!!
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
////이 위는 라이브러리에 있는 클래스
////----------------------------------------------------------------------------------//
////이 아래는 프로그램 코드
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