#include "MY.H"
 CMyWinApp theApp;

 BOOL CMyWinApp::InitInstance()
 {
	 m_pMainWnd = new CMyFrameWnd;
	 return TRUE;
 }
CMyFrameWnd::CMyFrameWnd ()
{
	Create();
}

void PrintAllClasses()
{
	CRuntimeClass* pClass;
	for (pClass = CRuntimeClass::pFirstClass; pClass != NULL;
		pClass = pClass->m_pNextClass)
	{
		cout<<pClass->m_lpszClassName<<"\n";
		cout<<pClass->m_nObjectSize<<"\n";
		cout<<pClass->m_wSchema<<"\n";
	}
}

void main()
{
	//CWinApp* pApp = AfxGetApp();
	//pApp->InitApplication();
	//pApp->InitInstance();
	//pApp->Run();

	//PrintAllClasses();
	CRuntimeClass* pClassRef = NULL;
	CObject* pOb = NULL;
	while(1)
	{
		if ((pClassRef = CRuntimeClass::Load()) == NULL)
		{
			break;
		}
		pOb = pClassRef->CreateObject();
		if(NULL != pOb)
			pOb->SayHello();
	}
}
