#include "pch.h"
#include "CKeyMgr.h"
#include "CCore.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,//LEFT,
	VK_RIGHT,//RIGHT,
	VK_UP,//UP,
	VK_DOWN,//DOWN,
	'Q','W','E','R','T','Y','U','I','O','P',
	'A','S','D','F','G','Z','X','C','V','B',
	
	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,
};

CKeyMgr::CKeyMgr()
{

}
CKeyMgr::~CKeyMgr()
{

}
void CKeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::Update()
{
	//������ ��Ŀ�� �˾Ƴ���
	//HWND hMainhWnd = CCore::GetInst()->GetMainHwnd();
	HWND hWnd = GetFocus();


	//�����찡 ��Ŀ������ ��
	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrev)
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					//������ �������� �ʾ���
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrev = true;
			}
			else
			{
				//������ Ű�� �� ��������
				if (m_vecKey[i].bPrev)
				{
					//������ �����־���
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					//�������� �ȴ����־���.
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrev = false;
			}
		}
	}

	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrev = false;
			if (KEY_STATE::TAP == m_vecKey[i].eState||KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
	
}