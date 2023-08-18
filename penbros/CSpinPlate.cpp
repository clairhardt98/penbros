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
	//플레이어가 점프하고 닿았을 때
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		CPlayer* pPlayer = (CPlayer*)pOtherObj;
		if (pPlayer->GetCurState() != PLAYER_STATUS::JUMP)
			return;
		m_bIsSpinning = true;
		pPlayer->SetImgInverted(true);
		//pPlayer->GetGdiPlusImage()->Invert(pPlayer->GetPos());
		//이벤트 생성
		tEvent eve = { };
		eve.eEven = EVENT_TYPE::SPIN_START;
		eve.lParam = (DWORD_PTR)this;
		eve.wParam = (pOtherObj->GetPos().x > GetPos().x) ? -1 : 1;//true는 시계, false는 반시계
		CEventMgr::GetInst()->AddEvent(eve);
	}
	
	CPlatform::OnCollisionEnter(_pOther);
}

void CSpinPlate::OnCollision(CCollider* _pOther)
{
	CPlatform::OnCollision(_pOther);
	//플레이어가 닿아있던 중에 아래 방향키를 눌렀을 때 
}


