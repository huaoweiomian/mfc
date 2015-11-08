#include <iostream>
#define PASCAL _stdcall
#define FALSE 0
#define TRUE 1
#pragma once
using std::cout;

typedef int BOOL;
typedef char* LPSTR;
#define UINT int
#define LPCSTR LPSTR

class CObject;
struct CRuntimeClass
{
	//attributes
	LPCSTR m_lpszClassName;
	int m_nObjectSize;
	UINT m_wSchema;
	CObject* (PASCAL*m_pfnCreateObject)();
	CRuntimeClass* m_pBaseClass;

	//CRuntimeClass objects linked together in simple list
	static CRuntimeClass* pFirstClass;//start of class list
	CRuntimeClass* m_pNextClass;//linked list of registered classes
};

struct AFX_CLASSINIT
{
	AFX_CLASSINIT(CRuntimeClass* pNewClass);
};

#define RUN_CLASS(class_name) \
		(&class_name::class##class_name)

#define DECLARE_DYNAMIC(class_name) \
public: \
		static CRuntimeClass class##class_name; \
		virtual CRuntimeClass* GetRuntimeClass() const;

#define _IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew)\
		static char _lpsz##class_name[] = #class_name; \
		CRuntimeClass class_name::class##class_name = { \
			lpsz##class_name, sizeof(class_name), wSchema, pfnNew, \
					RUNTIME_CLASS(base_class_name), NULL}; \
		static AFX_CLASSINIT _init_##class_name(&class_name::class##class_name); \
		CRuntimeClass* class_name::GetRuntimeClass() const \
			{return &class_name::class##class_name;} \

#define IMPLEMENT_DYNAMIC(class_name, base_class_name) \
	_IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, NULL)



class CObject
{
public:
	CObject::CObject() {}
	CObject::~CObject() {}
	virtual CRuntimeClass* GetRuntimeClass() const;
public:
	static CRuntimeClass classCObject;
};

class CCmdTarget:public CObject
{
	DECLARE_DYNAMIC(CCmdTarget)

public:
	CCmdTarget::CCmdTarget () {}
	CCmdTarget::~CCmdTarget () {}
};

class CWinThread:public CCmdTarget
{
	DECLARE_DYNAMIC(CCmdTarget)

public:
	CWinThread::CWinThread(){}
	CWinThread::~CWinThread(){}
	virtual BOOL InitInstance(){cout<<"CWinThread::InitInstance!\n";return TRUE;}
	virtual int Run(){cout<<"CWinThread::Run\n";return 1;}
};

class CWnd;
class CWinApp: public CWinThread
{
public:
	CWinApp* m_pCurrentWinApp;
	CWnd* m_pMainWnd;
public:
	CWinApp() { m_pCurrentWinApp = this;} 
	~CWinApp() {}
	virtual BOOL InitApplication(){cout<<"CWinApp::InitApplication\n";return TRUE;}
	virtual BOOL InitInstance(){cout<<"CWinApp::InitInstance\n";return TRUE;}
	virtual int Run(){cout<<"CWinApp::Run\n";return CWinThread::Run();}

};

class CDocument:public CCmdTarget
{
public:
CDocument::CDocument() {}
CDocument::~CDocument(){}
} ;

class CWnd : public CCmdTarget
{
public:
	CWnd::CWnd(){}
	CWnd::~CWnd(){}
	virtual BOOL Create();
	BOOL CreateEx();
	virtual BOOL PreCreateWindow();
};

class CFrameWnd : public CWnd
{
public:
	CFrameWnd(){}
	~CFrameWnd(){}
	BOOL Create();
	virtual BOOL PreCreateWindow();
} ;



class CView : public  CWnd
{
public:
CView::CView() {}
CView::~CView(){}
} ;

//    global   function 
CWinApp* AfxGetApp () ;










