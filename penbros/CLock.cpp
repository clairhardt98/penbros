#include "pch.h"
#include "CLock.h"
#include "CCollider.h"
#include "CPlayer.h"
#include "CEventMgr.h"
CLock::CLock()
{
	CreateCollider();
	GetCollider()->SetScale(Vector2D(50.0f,50.0f));

	//CreateAnimator();
}

CLock::~CLock()
{
}

void CLock::Update()
{
}

void CLock::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();
	if (L"Player" == pObj->GetName())
	{
		CPlayer* pPlayer = (CPlayer*)pObj;
		if (!pPlayer->HasKey())return;
		//printf("Stage Clear!\n");
		tEvent eve = {};
		eve.eEven = EVENT_TYPE::STAGE_CLEAR;
		CEventMgr::GetInst()->AddEvent(eve);
	}
}




