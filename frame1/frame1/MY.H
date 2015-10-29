#include <iostream>
#include   "MFC.H" 

class CMyWinApp : public CWinApp
{
public:
	CMyWinApp::CMyWinApp (){   cout  <<  "CMyWinApp Constructor  \n";  }
	CMyWinApp::~CMyWinApp (){    cout  <<  "CMyWinApp Destructor  \n ";   }
} ;

class CMyFrameWnd: public CFrameWnd
{
public: 
	CMyFrameWnd::CMyFrameWnd (){   cout <<  "CMyFrameWnd  Constructor  \n ";   }
	CMyFrameWnd::~CMyFrameWnd (){   cout  <<  "CMyFrameWnd  Destructor  \n" ;      }
} ;



