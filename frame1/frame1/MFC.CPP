#include "my.h"
extern CMyWinApp theApp;

static char szCObject[] = "CObject";
struct CRuntimeClass CObject::classCObject = 
{
	szCObject, sizeof(CObject), 0xffff, NULL, NULL, NULL
};
static AFX_CLASSINIT _init_CObject(&CObject::classCObject);
CRuntimeClass* CRuntimeClass::pFirstClass = NULL;

AFX_CLASSINIT::AFX_CLASSINIT(CRuntimeClass* pNewClass)
{
	pNewClass->m_pNextClass = CRuntimeClass::pFirstClass;
	CRuntimeClass::pFirstClass = pNewClass;
}

CObject* CRuntimeClass::CreateObject()
{
	if (NULL == m_pfnCreateObject)
	{
		TRACE1("Error: Trying to create object which is not "
			"DECLARE_DYNCREATE \\NOR DECLARE_SERIAL: %hs.\n",
			m_lpszClassName);
		return NULL;
	}
	CObject* pObject = NULL;
	pObject = (*m_pfnCreateObject)();
	return pObject;
}

CRuntimeClass* PASCAL CRuntimeClass::Load()
{
	char szClassName[64] = {0};
	CRuntimeClass* pClass = NULL;
	cout << "enter a class name... ";
	cin >> szClassName;
	for (pClass = pFirstClass; pClass != NULL; pClass = pClass->m_pNextClass)
	{
		if (0 == strcmp(szClassName, pClass->m_lpszClassName))
		{
			return pClass;
		}
	}
	TRACE1("Error: Class not found: %s \n", szClassName);
	return NULL;
}

CRuntimeClass* CObject::GetRuntimeClass() const
{
	return &CObject::classCObject;
}
BOOL CObject::IsKindOf(const CRuntimeClass* pClass)const
{
	CRuntimeClass* pClassThis = GetRuntimeClass();
	while(NULL != pClassThis)
	{
		if (pClassThis == pClass)
		{
			return TRUE;
		}
		pClassThis = pClassThis->m_pBaseClass;
	}
	return FALSE;
}

BOOL CWnd::Create()
{
	return TRUE;
}

BOOL CWnd::CreateEx()
{
	PreCreateWindow();
	return TRUE;
}

BOOL CWnd::PreCreateWindow()
{
	return TRUE;
}

BOOL CFrameWnd::Create()
{
	CreateEx();
	return TRUE;
}

BOOL CFrameWnd::PreCreateWindow()
{
	return TRUE;
}

//list的next 来自IMPLEMENT_DYNAMIC的执行顺序

IMPLEMENT_DYNAMIC(CCmdTarget, CObject)
IMPLEMENT_DYNAMIC(CWinThread,CCmdTarget)
IMPLEMENT_DYNAMIC(CWinApp,CWinThread)
IMPLEMENT_DYNCREATE(CWnd,CCmdTarget)
IMPLEMENT_DYNCREATE(CFrameWnd,CWnd)
IMPLEMENT_DYNAMIC(CDocument,CCmdTarget)
IMPLEMENT_DYNAMIC(CView,CWnd)
IMPLEMENT_DYNCREATE(CMyFrameWnd,CFrameWnd)
IMPLEMENT_DYNCREATE(CMyDoc,CDocument)
IMPLEMENT_DYNCREATE(CMyView,CView)


CWinApp* AfxGetApp()
{
	return theApp.m_pCurrentWinApp;
}

AFX_MSGMAP* CCmdTarget::GetMessageMap() const
{
	return &CCmdTarget::messageMap;
}

AFX_MSGMAP CCmdTarget::messageMap = {
	NULL,
&CCmdTarget::_messageEntries[0]
};

AFX_MSGMAP_ENTRY CCmdTarget::_messageEntries[] = {
	{0,0, CCmdTargetid, 0, AfxSig_end, 0}
};

BEGIN_MESSAGE_MAP(CWnd, CCmdTarget)
ON_COMMAND(CWndid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CFrameWnd, CWnd)
ON_COMMAND(CFrameWndid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CDocument, CCmdTarget)
ON_COMMAND(CDocumentid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CView, CWnd)
ON_COMMAND(CViewid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CWinApp, CCmdTarget)
ON_COMMAND(CWinAppid, 0)
END_MESSAGE_MAP()