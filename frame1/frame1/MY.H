#include <iostream>
#include   "MFC.H" 
class CMyFrameWnd: public CFrameWnd
{
public: 
	CMyFrameWnd::CMyFrameWnd (){   cout <<  "CMyFrameWnd  Constructor  \n ";   }
	CMyFrameWnd::~CMyFrameWnd (){   cout  <<  "CMyFrameWnd  Destructor  \n" ;      }
} ;

class CMyWinApp : public CWinApp
{
public:
	
	CMyWinApp ():m_pMainWnd(NULL){ cout  <<  "CMyWinApp Constructor  \n";  }
	~CMyWinApp (){    cout  <<  "CMyWinApp Destructor  \n ";   }
	virtual BOOL InitInstance(){    cout  <<  "CMyWinApp InitInstance\n ";  
	m_pMainWnd = new CMyFrameWnd;
	return TRUE;}
	CMyFrameWnd* m_pMainWnd;
} ;




