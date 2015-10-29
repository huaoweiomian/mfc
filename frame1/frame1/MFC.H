#include <iostream>
using std::cout;

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
	CWinApp::CWinApp() { m_pCurrentWinApp = this;
	cout << "CWinApp Constructor \n"; } 
	CWinApp::~CWinApp() { cout << "CWinApp Destructor \n";}
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
};

class CFrameWnd : public CWnd
{
public:
	CFrameWnd::CFrameWnd(){cout << "CFrameWnd Constructor \n"; }
	CFrameWnd::~CFrameWnd(){ cout  <<  "CFrameWnd Destructor  \n ";    }
} ;



class CView : public  CWnd
{
public:
CView::CView() {   cout<< "CView Constructor  \n";  }
CView::~CView(){   cout<< "CView  Destructor  \n ";   }
} ;

//    global   function 
CWinApp* AfxGetApp () ;










