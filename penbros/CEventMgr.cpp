#include "pch.h"
#include "CEventMgr.h"
#include "CObject.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CPlayer.h"
#include "CSpinPlate.h"
#include "CRigidBody.h"
#include "CImage.h"
CEventMgr::CEventMgr()
	:m_pPlayer(nullptr)
{

}
CEventMgr::~CEventMgr()
{

}

void CEventMgr::Update()
{
	//���� �������� ���庤�͸� üũ�ϰ� ����
	for (size_t i = 0; i < m_vecDead.size(); i++)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();
	//�̺�Ʈ ó��
	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		//�޽����� ó���ϰ� �޽����� ���־� ��
		Execute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventMgr::Execute(const tEvent& _eve)
{
	//�̺�Ʈ Ÿ�Կ� ���� ó��
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
		//lParam : Object Addr
		//wParam : Group Type
	{
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;
		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
		//���� �̺�Ʈ�� ��ϵǸ� Ʈ���Ÿ� �÷���
		//������ ������Ʈ�� �����ϰ� �ִ� �ٸ� ������Ʈ���� ������ ���� �˰Ե�
		//�ϴ� ������ ������Ʈ�� ����ϰ�, �� ���� �����ӿ��� �������� ����
		//������Ʈ�� dead���·� ����, �� ������Ʈ���� ��Ƶд�
	{
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
		//lParam : next Scene type
		//�� �Ŵ������� �� ������ ��û
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);
		break;
	case EVENT_TYPE::BOMB_EXPLODED:
		//��ź�� ������ �÷��̾�
		m_pPlayer->SetCanSetBomb(true);
		break;
	case EVENT_TYPE::SPIN_START:
	{
		m_pPlayer->SetSpinning(true);
		//m_pPlayer->GetGdiPlusImage()->Invert(m_pPlayer->GetPos());
		//m_pPlayer->GetGdiPlusImage()->GetImagePtr()->RotateFlip(Gdiplus::Rotate180FlipX);
		
		CSpinPlate* pPlate = (CSpinPlate*)_eve.lParam;
		m_pPlayer->SetSpinCenter(pPlate->GetPos());
		m_pPlayer->SetSpinClockwise((int)_eve.wParam);
		m_pPlayer->GetRigidBody()->EnableGravity(false);
		m_pPlayer->SetName(L"PlayerSpinning");
		//m_pPlayer->DisableRigidBody();
	}
		break;
	case EVENT_TYPE::SPIN_END:
		m_pPlayer->SetSpinning(false);
		m_pPlayer->GetRigidBody()->SetVelocity(Vector2D(0.f, 0.f));
		m_pPlayer->GetRigidBody()->ResetAccel();
		m_pPlayer->GetRigidBody()->EnableGravity(true);
		m_pPlayer->SetName(L"Player");

		//m_pPlayer->EnableRigidBody();
		/*CSpinPlate* pPlate = (CSpinPlate*)_eve.lParam;
		pPlate->SetSpinning(false);*/
		break;;
	}

}


