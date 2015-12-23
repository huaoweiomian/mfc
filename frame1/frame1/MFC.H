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
	CObject* CreateObject();
	static CRuntimeClass* PASCAL Load();
	//CRuntimeClass objects linked together in simple list
	static CRuntimeClass* pFirstClass;//start of class list
	CRuntimeClass* m_pNextClass;//linked list of registered classes
};

struct AFX_CLASSINIT
{
	AFX_CLASSINIT(CRuntimeClass* pNewClass);
};

#define RUNTIME_CLASS(class_name) \
		(&class_name::class##class_name)

#define DECLARE_DYNAMIC(class_name) \
public: \
		static CRuntimeClass class##class_name; \
		virtual CRuntimeClass* GetRuntimeClass() const;

#define _IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew)\
		static char _lpsz##class_name[] = #class_name; \
		CRuntimeClass class_name::class##class_name = { \
			_lpsz##class_name, sizeof(class_name), wSchema, pfnNew, \
					RUNTIME_CLASS(base_class_name), NULL}; \
		static AFX_CLASSINIT _init_##class_name(&class_name::class##class_name); \
		CRuntimeClass* class_name::GetRuntimeClass() const \
			{return &class_name::class##class_name;} 

#define IMPLEMENT_DYNAMIC(class_name, base_class_name) \
	_IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, NULL)


#define DECLARE_DYNCREATE(class_name) \
	DECLARE_DYNAMIC(class_name) \
	static CObject* PASCAL CreateObject();

#define IMPLEMENT_DYNCREATE(class_name, base_class_name) \
	CObject* PASCAL class_name::CreateObject() \
			{ return new class_name;} \
	_IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, \
			class_name::CreateObject)

class CObject
{
public:
	CObject::CObject() {}
	CObject::~CObject() {}
	virtual CRuntimeClass* GetRuntimeClass() const;
public:
	BOOL IsKindOf(const CRuntimeClass*)const;
	static CRuntimeClass classCObject;
};

class CCmdTarget:public CObject
{
	DECLARE_DYNCREATE(CCmdTarget)

public:
	CCmdTarget::CCmdTarget () {}
	CCmdTarget::~CCmdTarget () {}
};

class CWinThread:public CCmdTarget
{
	DECLARE_DYNCREATE(CWinThread)

public:
	CWinThread::CWinThread(){}
	CWinThread::~CWinThread(){}
	virtual BOOL InitInstance(){return TRUE;}
	virtual int Run(){return 1;}
};

class CWnd;
class CWinApp: public CWinThread
{
	DECLARE_DYNCREATE(CWinApp)

public:
	CWinApp* m_pCurrentWinApp;
	CWnd* m_pMainWnd;
public:
	CWinApp() { m_pCurrentWinApp = this;} 
	~CWinApp() {}
	virtual BOOL InitApplication(){return TRUE;}
	virtual BOOL InitInstance(){return TRUE;}
	virtual int Run(){return CWinThread::Run();}

};

class CDocument:public CCmdTarget
{
	DECLARE_DYNCREATE(CDocument)

public:
CDocument::CDocument() {}
CDocument::~CDocument(){}
} ;

class CWnd : public CCmdTarget
{
	DECLARE_DYNCREATE(CWnd)

public:
	CWnd::CWnd(){}
	CWnd::~CWnd(){}
	virtual BOOL Create();
	BOOL CreateEx();
	virtual BOOL PreCreateWindow();
};

class CFrameWnd : public CWnd
{
	DECLARE_DYNCREATE(CFrameWnd)

public:
	CFrameWnd(){}
	~CFrameWnd(){}
	BOOL Create();
	virtual BOOL PreCreateWindow();
} ;



class CView : public  CWnd
{
	DECLARE_DYNCREATE(CView)

public:
CView::CView() {}
CView::~CView(){}
} ;

//    global   function 
CWinApp* AfxGetApp () ;










