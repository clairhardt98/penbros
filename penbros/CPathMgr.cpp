#include "pch.h"
#include "CPathMgr.h"
#include "CCore.h"

CPathMgr::CPathMgr()
	:m_szContentPath{} {}
CPathMgr::~CPathMgr() {}
void CPathMgr::Init()
{
	GetCurrentDirectory(255, m_szContentPath);

	int len = wcslen(m_szContentPath);

	for (int i = len - 1; i >= 0; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");
	//����������
	//+bin\\content\\�ٿ��ֱ�

	//SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);
}
