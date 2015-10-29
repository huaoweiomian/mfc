#include <iostream>
#define FALSE 0
#define TRUE 1

using std::cout;

typedef int BOOL;

class CObject
{
public:
	CObject::CObject() {cout<<"CObject Constructor \n";}
	CObject::~CObject() {cout<<"CObject Destructor \n";}
};

class CCmdTarget:public CObject
{

public:
	CCmdTarget::CCmdTarget () {cout<<"CCmdTarget Constructor \n"; }
	CCmdTarget::~CCmdTarget () {cout<<"CCmdTarget Destructor \n"; }
};

class CWinThread:public CCmdTarget
{
public:
	CWinThread::CWinThread(){ cout<<"CCWdinThread Constructor \n";}
	CWinThread::~CWinThread(){ cout<<"CCWdinThread Destructor \n";}
};

class CWinApp: public CWinThread
{
public:
	CWinApp* m_pCurrentWinApp;

public:
	CWinApp() { m_pCurrentWinApp = this;
	cout << "CWinApp Constructor \n"; } 
	~CWinApp() { cout << "CWinApp Destructor \n";}
	virtual BOOL InitApplication(){cout<<"CWinApp InitApplication!\n";}
	virtual BOOL InitInstance(){cout<<"CWinApp InitInstance!\n";}
	virtual BOOL Run(){cout<<"CWinApp Run\n";}
};

class CDocument:public CCmdTarget
{
public:
CDocument::CDocument() { cout << "CDocument Constructor \n"; }
CDocument::~CDocument(){ cout << "CDocument Destructor \n"; }
} ;

class CWnd : public CCmdTarget
{
public:
CWnd::CWnd(){ cout << "CWnd Construct or \n"; }
CWnd::~CWnd(){ cout << "CWind Destructor \n"; }
virtual BOOL CreateEx(){cout<<"CFrameWnd CreateEx\n";
PreCreateWindow();return TRUE;}
virtual BOOL PreCreateWindow(){ cout << "CWind PreCreateWindow \n"; return TRUE;}
};

class CFrameWnd : public CWnd
{
public:
	CFrameWnd(){cout << "CFrameWnd Constructor \n"; }
	~CFrameWnd(){ cout  <<  "CFrameWnd Destructor  \n ";    }
	virtual BOOL Create(){cout<<"CFrameWnd Create\n";
	CreateEx();return TRUE;}
} ;



class CView : public  CWnd
{
public:
CView::CView() {   cout<< "CView Constructor  \n";  }
CView::~CView(){   cout<< "CView  Destructor  \n ";   }
} ;

//    global   function 
CWinApp* AfxGetApp () ;










