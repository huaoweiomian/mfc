#include <iostream>
#define PASCAL _stdcall
#define FALSE 0
#define TRUE 1
#define TRACE1 printf
#pragma once
using std::cout;
using std::endl;
using std::cin;

typedef int BOOL;
typedef char* LPSTR;
typedef const char* LPCSTR;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int UINT;
typedef int INT;
typedef long LONG;
typedef UINT WPARAM;
typedef LONG LPARAM;
typedef LONG LRESULT;
typedef int HWND;

#define WM_COMMAND   0x0111
#define CObjectid    0xffff
#define  CCmdTargetid  1
#define   CWinThreadid  11
#define    CWinAppid     111
#define     CMyWinAppid    1111
#define   CWndid        12
#define    CFrameWndid   121
#define     CMyFrameWndid 1211
#define    CViewid       122
#define     CMyViewid      1221
#define   CDocumentid   13
#define    CMyDocid      131




#define DECLARE_MESSAGE_MAP() \
	static AFX_MSGMAP_ENTRY _messageEntries[]; \
	static AFX_MSGMAP messageMap; \
	virtual  AFX_MSGMAP* GetMessageMap() const;

#define BEGIN_MESSAGE_MAP(theClass, baseClass) \
	AFX_MSGMAP* theClass::GetMessageMap() const \
		{ return &theClass::messageMap; } \
	AFX_MSGMAP theClass::messageMap = \
	{ &(baseClass::messageMap), \
			(AFX_MSGMAP_ENTRY*) &(theClass::_messageEntries) }; \
	AFX_MSGMAP_ENTRY theClass::_messageEntries[] = \
	{


#define END_MESSAGE_MAP() \
		{ 0, 0, 0, 0, AfxSig_end, (AFX_PMSG)0 } \
	};

#include "AFXMSG_.H"
class CCmdTarget;
typedef void (CCmdTarget::*AFX_PMSG)(void);

struct AFX_MSGMAP_ENTRY
{
	UINT nMessage;
	UINT nCode;
	UINT nID;
	UINT nLastID;
	UINT nSig;
	AFX_PMSG pfn;
};
struct AFX_MSGMAP
{
	AFX_MSGMAP* pBaseMessageMap;
	AFX_MSGMAP_ENTRY* lpEntries;
};



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
	virtual void SayHello(){cout<<"Hello CObject "<<endl;}
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
	virtual void SayHello(){cout<<"Hello CCmdTarget "<<endl;}
	virtual BOOL OnCmdMsg(UINT nID, int nCode);
	DECLARE_MESSAGE_MAP()
};

class CWinThread:public CCmdTarget
{
	DECLARE_DYNCREATE(CWinThread)

public:
	CWinThread::CWinThread(){}
	CWinThread::~CWinThread(){}
	virtual BOOL InitInstance(){return TRUE;}
	virtual void SayHello(){cout<<"Hello CWinThread "<<endl;}
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
	virtual void SayHello(){cout<<"Hello CWinApp "<<endl;}
	DECLARE_MESSAGE_MAP()
};

class CDocument:public CCmdTarget
{
	DECLARE_DYNCREATE(CDocument)

public:
CDocument::CDocument() {}
CDocument::~CDocument(){}
virtual void SayHello(){cout<<"Hello CDocument "<<endl;}
virtual BOOL OnCmdMsg(UINT nID, int nCode);

	DECLARE_MESSAGE_MAP()
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
	virtual void SayHello(){cout<<"Hello CWnd "<<endl;}
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT DefWindowProce(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};
typedef void (CCmdTarget::*AFX_PMSGW)(void);

class CFrameWnd : public CWnd
{
	DECLARE_DYNCREATE(CFrameWnd)

public:
	CView* m_pViewActive;
	CFrameWnd(){}
	~CFrameWnd(){}
	BOOL Create();
	virtual void SayHello(){cout<<"Hello CFrameWnd "<<endl;}
	CView* GetActiveView() const;
	virtual BOOL PreCreateWindow();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCmdMsg(UINT nID, int nCode);
	DECLARE_MESSAGE_MAP()
	friend CView;
} ;



class CView : public  CWnd
{
	DECLARE_DYNCREATE(CView)
public:
	CDocument* m_pDocument;
public:
CView::CView() {}
CView::~CView(){}
virtual BOOL OnCmdMsg(UINT nID, int nCode);

virtual void SayHello(){cout<<"Hello CView "<<endl;}
	DECLARE_MESSAGE_MAP()
	friend CFrameWnd;
} ;

//    global   function 
CWinApp* AfxGetApp () ;

LRESULT AfxWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam, CWnd* pWnd);
LRESULT AfxCallWndProc(CWnd* pWnd, HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);










