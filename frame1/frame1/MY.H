#include <iostream>
#include   "MFC.H" 

class CMyWinApp : public CWinApp
{
public:
	
	CMyWinApp (){}
	~CMyWinApp (){}
	virtual BOOL InitInstance();
} ;

class CMyFrameWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CMyFrameWnd)
public: 
	CMyFrameWnd ();
	~CMyFrameWnd (){}
} ;

class CMyDoc : public CDocument
{
	DECLARE_DYNCREATE(CMyDoc)
public:
	CMyDoc(){}
	~CMyDoc(){}
};

class CMyView : public CView
{
	DECLARE_DYNCREATE(CMyView)
public:
	CMyView(){}
	~CMyView(){}
};

void PrintAllClasses();