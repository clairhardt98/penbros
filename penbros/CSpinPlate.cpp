#include "pch.h"
#include "CSpinPlate.h"
#include "CCollider.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CEventMgr.h"
#include "CImage.h"

CSpinPlate::CSpinPlate()
	:m_bIsSpinning(false)
{
}

CSpinPlate::~CSpinPlate()
{
}



void CSpinPlate::OnCollisionEnter(CCollider* _pOther)
{
	//�÷��̾ �����ϰ� ����� ��
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		CPlayer* pPlayer = (CPlayer*)pOtherObj;
		if (pPlayer->GetCurState() != PLAYER_STATUS::JUMP)
			return;
		m_bIsSpinning = true;
		pPlayer->SetImgInverted(true);
		//pPlayer->GetGdiPlusImage()->Invert(pPlayer->GetPos());
		//�̺�Ʈ ����
		tEvent eve = { };
		eve.eEven = EVENT_TYPE::SPIN_START;
		eve.lParam = (DWORD_PTR)this;
		eve.wParam = (pOtherObj->GetPos().x > GetPos().x) ? -1 : 1;//true�� �ð�, false�� �ݽð�
		CEventMgr::GetInst()->AddEvent(eve);
	}
	
	CPlatform::OnCollisionEnter(_pOther);
}

void CSpinPlate::OnCollision(CCollider* _pOther)
{
	CPlatform::OnCollision(_pOther);
	//�÷��̾ ����ִ� �߿� �Ʒ� ����Ű�� ������ �� 
}


