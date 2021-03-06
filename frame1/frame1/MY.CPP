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
BEGIN_MESSAGE_MAP(CMyWinApp,CWinApp)
ON_COMMAND(CMyWinAppid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CMyFrameWnd,CFrameWnd)
ON_COMMAND(CMyFrameWndid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CMyDoc,CDocument)
ON_COMMAND(CMyDocid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CMyView,CView)
ON_COMMAND(CMyViewid, 0)
END_MESSAGE_MAP()

void printlpEntries(AFX_MSGMAP_ENTRY* lpEntry)
{
	struct 
	{
		int classid;
		char* classname;
	}classinfo[] = {
		CCmdTargetid, "CCmdTarget",
		CWinThreadid, "CWinThread",
		CWinAppid,  "CWinApp",
		CMyWinAppid,  "CMyWinApp",
		CWndid,       "CWnd",
		CFrameWndid,   "CFrameWnd",
		CMyFrameWndid, "CMyFrameWnd",
		CViewid,       "CView",
		CMyViewid,       "CMyView",
		CDocumentid,    "CDocument",
		CMyDocid,       "CMyDoc",
		0,              "    "
	};
	for (int i = 0; classinfo[i].classid != 0; ++i)
	{
		if (classinfo[i].classid == lpEntry->nID)
		{
			cout << lpEntry->nID << "   ";
			cout << classinfo[i].classname << endl;
			break;
		}
	}
}

void MsgMapPrinting(AFX_MSGMAP* pMessageMap)
{
	for (; pMessageMap != NULL; pMessageMap = pMessageMap->pBaseMessageMap)
	{
		AFX_MSGMAP_ENTRY* lpEntry = pMessageMap->lpEntries;
		printlpEntries(lpEntry);
	}
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
	CWinApp* pApp = AfxGetApp();
	pApp->InitApplication();
	pApp->InitInstance();
	pApp->Run();
	CMyDoc* pMyDoc = new CMyDoc;
	CMyView* pMyView = new CMyView;
	CFrameWnd* pMyFrame = (CFrameWnd*)pApp->m_pMainWnd;

	pMyFrame->m_pViewActive = pMyView;
	pMyView->m_pDocument = pMyDoc;
	cout << endl << "pMyFrame received a WM_CREATE, routing path: " << endl;
	AfxWndProc(0, WM_CREATE, 0, 0, pMyFrame);

	cout << endl << "pMyView received a WM_PAINT, routing path: " << endl;
	AfxWndProc(0, WM_PAINT, 0, 0, pMyView);
	cout << endl << "pMyView received a WM_COMMAND, routing path: " << endl;
	AfxWndProc(0, WM_COMMAND, 0, 0, pMyView);
	cout << endl << "pMyFrame received a WM_COMMAND, routing path: " << endl;
	AfxWndProc(0, WM_COMMAND, 0, 0, pMyFrame);
	//AFX_MSGMAP* pMessageMap = pMyView->GetMessageMap();
	//cout << endl << "CMyView Message Map : " << endl;
	//MsgMapPrinting(pMessageMap);
	//pMessageMap = pMyDoc->GetMessageMap();
	//cout << endl << "CMyDoc Message Map : " << endl;
	//MsgMapPrinting(pMessageMap);
	//pMessageMap = pMyFrame->GetMessageMap();
	//cout << endl << "CMyFrameWnd Message Map : " << endl;
	//MsgMapPrinting(pMessageMap);
	//pMessageMap = pApp->GetMessageMap();
	//cout << endl << "CMyWinApp Message Map : " << endl;
	//MsgMapPrinting(pMessageMap);

}
