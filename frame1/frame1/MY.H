#include <iostream>
#include   "MFC.H" 

class CMyWinApp : public CWinApp
{
public:
	
	CMyWinApp (){}
	~CMyWinApp (){}
	virtual BOOL InitInstance();
	virtual void SayHello(){cout<<"Hello CMyWinApp"<<endl;}
	DECLARE_MESSAGE_MAP()
} ;

class CMyFrameWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CMyFrameWnd)
public: 
	CMyFrameWnd ();
	~CMyFrameWnd (){}
	virtual void SayHello(){cout<<"Hello CMyFrameWnd"<<endl;}
	DECLARE_MESSAGE_MAP()
} ;

class CMyDoc : public CDocument
{
	DECLARE_DYNCREATE(CMyDoc)
public:
	CMyDoc(){}
	~CMyDoc(){}
	virtual void SayHello(){cout<<"Hello CMyDoc"<<endl;}
	DECLARE_MESSAGE_MAP()
};

class CMyView : public CView
{
	DECLARE_DYNCREATE(CMyView)
public:
	CMyView(){}
	~CMyView(){}
	virtual void SayHello(){cout<<"Hello CMyView"<<endl;}
	DECLARE_MESSAGE_MAP()
};

void PrintAllClasses();