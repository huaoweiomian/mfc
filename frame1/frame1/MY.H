#include <iostream>
#include   "MFC.H" 
class CMyFrameWnd: public CFrameWnd
{
public: 
	CMyFrameWnd ();
	~CMyFrameWnd (){}
} ;

class CMyWinApp : public CWinApp
{
public:
	
	CMyWinApp (){}
	~CMyWinApp (){}
	virtual BOOL InitInstance();
} ;




