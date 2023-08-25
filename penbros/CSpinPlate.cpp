#include "pch.h"
#include "CSpinPlate.h"
#include "CCollider.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CEventMgr.h"
#include "CImage.h"
#include "CKeyMgr.h"
#include "CRigidBody.h"
#include "CResMgr.h"
#include "CCore.h"
#include "CTimeMgr.h"

CSpinPlate::CSpinPlate()
	:m_bIsSpinning(false)
	,m_bSpinClockwise(1)
{
	pImg = CResMgr::GetInst()->LoadImg(L"SpinningPlateImg", L"Image\\SpinningPlate.bmp");
	CreateGraphics();
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
		pPlayer->GetRigidBody()->SetGrounded(true);
		if (pPlayer->GetCurState() != PLAYER_STATUS::JUMP || pPlayer->GetPos().y<GetPos().y)
			return;
		m_bIsSpinning = true;
		pPlayer->SetImgInverted(true);
		//pPlayer->GetGdiPlusImage()->Invert(pPlayer->GetPos());
		//이벤트 생성
		tEvent eve = { };
		eve.eEven = EVENT_TYPE::SPIN_START;
		eve.lParam = (DWORD_PTR)this;
		m_bSpinClockwise = eve.wParam = (pOtherObj->GetPos().x > GetPos().x) ? -1 : 1;//true는 시계, false는 반시계
		CEventMgr::GetInst()->AddEvent(eve);
	}
	
	CPlatform::OnCollisionEnter(_pOther);
}

void CSpinPlate::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		CPlayer* pPlayer = (CPlayer*)pOtherObj;
		if (KEY_TAP(KEY::DOWN) && pPlayer->GetPos().y<GetPos().y) // 위에서 누를 때
		{
			m_bIsSpinning = true;
			pPlayer->SetImgInverted(false);
			pPlayer->SetSticked(true);

			tEvent eve = { };
			eve.eEven = EVENT_TYPE::SPIN_START;
			eve.lParam = (DWORD_PTR)this;
			m_bSpinClockwise = eve.wParam = (pOtherObj->GetPos().x > GetPos().x) ? 1 : -1;//true는 시계, false는 반시계
			CEventMgr::GetInst()->AddEvent(eve);
			//여기서 폭탄 날리는 이벤트 만들어야지

			eve.eEven = EVENT_TYPE::THROW_BOMB;
			//wParam, lParam은 그대로 써도 되겠네
			CEventMgr::GetInst()->AddEvent(eve);

		}
		if (KEY_TAP(KEY::UP) && pPlayer->IsSticked())// 아래에서 올라갈 때 -> 폭탄 날릴 구조가 안되지 않나?
		{
			m_bIsSpinning = true;
			pPlayer->SetImgInverted(true);
			pPlayer->SetSticked(false);
			//pPlayer->GetGdiPlusImage()->Invert(pPlayer->GetPos());
			//이벤트 생성
			tEvent eve = { };
			eve.eEven = EVENT_TYPE::SPIN_START;
			eve.lParam = (DWORD_PTR)this;
			m_bSpinClockwise = eve.wParam = (pOtherObj->GetPos().x > GetPos().x) ? -1 : 1;//true는 시계, false는 반시계
			CEventMgr::GetInst()->AddEvent(eve);
		}
	}
	CPlatform::OnCollision(_pOther);
	//CPlatform::OnCollision(_pOther);
	//플레이어가 닿아있던 중에 아래 방향키를 눌렀을 때 
}

void CSpinPlate::Update()
{
	if (m_bIsSpinning)
	{
		RotateImage();
	}
}

void CSpinPlate::Render(HDC _dc)
{
	DrawImage();
}


void CSpinPlate::DrawImage()
{
	using namespace Gdiplus;
	Vector2D vPos = GetPos();
	Graphics* pGr = GetGraphics();
	
	int w = pImg->Width();
	int h = pImg->Height();

	pGr->DrawImage(pImg->GetImagePtr(), Rect((int)vPos.x - w / 2, (int)vPos.y - h / 2 , w, h),
		0, 0, w, h, UnitPixel, pImg->GetImgAttr());
}

void CSpinPlate::RotateImage()
{
	if (pImg->Rotate(GetGraphics(), GetPos(), (float)m_bSpinClockwise * 300.f * fDT))
		m_bIsSpinning = false;
}
