#include "pch.h"
#include "CPlayer.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CMissile.h"
#include "CScene.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"
#include "CEventMgr.h"
#include "CImage.h"
#include "CCore.h"

int CPlayer::m_iHP = 2;
int CPlayer::m_iScore = 0;
int CPlayer::m_iCurStage = 0;
int CPlayer::m_iCredit = 0;

CPlayer::CPlayer()
	:m_eCurState(PLAYER_STATUS::IDLE)
	, m_ePrevState(PLAYER_STATUS::IDLE)
	, m_iPrevDir(1)
	, m_iDir(1)
	, m_bCanSetBomb(true)
	, m_bIsSliding(false)
	, m_bIsSpinning(false)
	, m_bIsImgInverted(false)
	, m_eBMod(BOMB_MODE::GREEN)
	, m_bIsSticked(false)
	, m_fStickDuration(0.f)
	, m_bIsAlive(true)
	,m_fDeathTime(0.f)
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2D(0.0f, 0.0f));
	GetCollider()->SetScale(Vector2D(25.0f, 25.0f));

	CreateRigidBody();
	GetRigidBody()->EnableGravity(true);

	CreateGraphics();

	CTexture* pTexRight = CResMgr::GetInst()->LoadTexture(L"PlayerTexRight", L"Image\\Golem.bmp");
	CTexture* pTexLeft = CResMgr::GetInst()->LoadTexture(L"PlayerTexLeft", L"Image\\Golem_Left.bmp");
	pImgIdle = CResMgr::GetInst()->LoadImg(L"PlayerImageIdle", L"Image\\Golem_Idle_Image.bmp");
	pImgIdleInvert = CResMgr::GetInst()->LoadImg(L"PlayerImageIdleInverted", L"Image\\Golem_Idle_Invert_Image.bmp");


	CreateAnimator();
	CAnimator* pAnimator = GetAnimator();
	pAnimator->CreateAnimation(true, L"GOLEM_IDLE_RIGHT", pTexRight, 9, 10, 0, 0, Vector2D(128.0f, 128.0f), 0.1f, 4);
	pAnimator->CreateAnimation(false, L"GOLEM_IDLE_LEFT", pTexLeft, 9, 10, 0, 0, Vector2D(128.0f, 128.0f), 0.1f, 4);
	pAnimator->CreateAnimation(true, L"GOLEM_MOVE_RIGHT", pTexRight, 9, 10, 1, 6, Vector2D(128.0f, 128.0f), 0.1f, 4);
	pAnimator->CreateAnimation(false, L"GOLEM_MOVE_LEFT", pTexLeft, 9, 10, 1, 6, Vector2D(128.0f, 128.0f), 0.1f, 4);
	pAnimator->CreateAnimation(true, L"GOLEM_ATTACK_RIGHT", pTexRight, 9, 10, 2, 0, Vector2D(128.0f, 128.0f), 0.1f, 12);
	pAnimator->CreateAnimation(false, L"GOLEM_ATTACK_LEFT", pTexLeft, 9, 10, 2, 0, Vector2D(128.0f, 128.0f), 0.1f, 12);
	pAnimator->CreateAnimation(true, L"GOLEM_DIE_RIGHT", pTexRight, 9, 10, 5, 3, Vector2D(128.0f, 128.0f), 0.2f, 8);
	pAnimator->CreateAnimation(false, L"GOLEM_DIE_LEFT", pTexLeft, 9, 10, 5, 3, Vector2D(128.0f, 128.0f), 0.2f, 8);

	CAnimation* pAniIdleRight = pAnimator->FindAnimation(L"GOLEM_IDLE_RIGHT");
	CAnimation* pAniIdleLeft = pAnimator->FindAnimation(L"GOLEM_IDLE_LEFT");
	CAnimation* pAniMoveRight = pAnimator->FindAnimation(L"GOLEM_MOVE_RIGHT");
	CAnimation* pAniMoveLeft = pAnimator->FindAnimation(L"GOLEM_MOVE_LEFT");
	CAnimation* pAniAttackRight = pAnimator->FindAnimation(L"GOLEM_ATTACK_RIGHT");
	CAnimation* pAniAttackLeft = pAnimator->FindAnimation(L"GOLEM_ATTACK_LEFT");
	CAnimation* pAniDieRight = pAnimator->FindAnimation(L"GOLEM_DIE_RIGHT");
	CAnimation* pAnidieLeft = pAnimator->FindAnimation(L"GOLEM_DIE_LEFT");


	//애니메이션의 오프셋 세팅
	for (int i = 0; i < pAniIdleRight->GetMaxFrame(); i++)
		pAniIdleRight->GetFrame(i).vOffset = Vector2D(0.f, -15.f);
	for (int i = 0; i < pAniIdleLeft->GetMaxFrame(); i++)
		pAniIdleLeft->GetFrame(i).vOffset = Vector2D(0.f, -15.f);
	for (int i = 0; i < pAniMoveRight->GetMaxFrame(); i++)
		pAniMoveRight->GetFrame(i).vOffset = Vector2D(0.f, -15.f);
	for (int i = 0; i < pAniMoveLeft->GetMaxFrame(); i++)
		pAniMoveLeft->GetFrame(i).vOffset = Vector2D(0.f, -15.f);
	for (int i = 0; i < pAniAttackRight->GetMaxFrame(); i++)
		pAniAttackRight->GetFrame(i).vOffset = Vector2D(0.f, -15.f);
	for (int i = 0; i < pAniAttackLeft->GetMaxFrame(); i++)
		pAniAttackLeft->GetFrame(i).vOffset = Vector2D(0.f, -15.f);
	for (int i = 0; i < pAniDieRight->GetMaxFrame(); i++)
		pAniDieRight->GetFrame(i).vOffset = Vector2D(0.f, -15.f);
	for (int i = 0; i < pAnidieLeft->GetMaxFrame(); i++)
		pAnidieLeft->GetFrame(i).vOffset = Vector2D(0.f, -15.f);

	pAnimator->Play(L"GOLEM_IDLE_RIGHT", true);

	CEventMgr::GetInst()->SetPlayer(this);
}


CPlayer::~CPlayer()
{

}

void CPlayer::Update()
{
	if (!m_bIsAlive)
	{
		m_fDeathTime += fDT;
		if (m_fDeathTime >= 2.0f)
		{
			tEvent eve = {};
			eve.eEven = EVENT_TYPE::PLAYER_REVIVE;
			DeleteObject(this);
			CEventMgr::GetInst()->AddEvent(eve);
		}
	}
	UpdateMove();
	UpdateState();
	UpdateAnim();

	if (m_bIsSticked)
	{
		m_fStickDuration += fDT;
		if (m_fStickDuration >= 2.0f)
		{
			m_bIsSticked = false;
			m_fStickDuration = 0.f;
			GetRigidBody()->EnableGravity(true);
		}
	}
	if (m_bIsSpinning)
	{
		GetAnimator()->Pause();
		RotateImage();
		RotatePos(m_vSpinCenter, (float)m_bSpinClockwise * 250.f * fDT);
	}
	else
	{
		GetAnimator()->Resume();
		GetRigidBody()->SetFricCoeff(200.f);
	}

	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;

	//printf("Player Velocity) x : %.1lf, y : %.1lf, IsSticked : %d, StickDur : %.1lf\n", GetRigidBody()->GetVelocity().x, GetRigidBody()->GetVelocity().y,IsSticked(),m_fStickDuration);
	
}

void CPlayer::Render(HDC _dc)
{
	//본인이 보유하고 있는 애니메이션 정보
	//DrawImage();

	//회전중일때만 gdi+이미지 출력
	if (m_bIsSpinning)
		DrawImage();
	else
		ComponentRender(_dc);
}



void CPlayer::UpdateState()
{
	//상태 관리

	//방향 전환
	if (!m_bIsAlive)
	{
		m_eCurState = PLAYER_STATUS::DEAD;
		return;
	}
	if (KEY_TAP(KEY::LEFT))
	{
		m_iDir = -1;
		m_eCurState = PLAYER_STATUS::WALK;
	}
	if (KEY_TAP(KEY::RIGHT))
	{
		m_iDir = 1;
		m_eCurState = PLAYER_STATUS::WALK;
	}
	if (0.f == GetRigidBody()->GetSpeed())
	{
		m_bIsSliding = false;
		GetRigidBody()->SetFricCoeff(200.0f);
		m_eCurState = PLAYER_STATUS::IDLE;
	}
	if (KEY_TAP(KEY::SPACE) && GetRigidBody()->IsGrounded())
	{
		m_eCurState = PLAYER_STATUS::JUMP;
	}
	if (KEY_HOLD(KEY::DOWN) && KEY_TAP(KEY::SPACE) && GetRigidBody()->IsGrounded())
	{
		m_eCurState = PLAYER_STATUS::SLIDE;
	}

}

void CPlayer::UpdateMove()
{
	if (!m_bIsAlive)return;
	CRigidBody* pRb = GetRigidBody();

	//키 입력시 힘 가해서 이동

	if (m_bIsSliding || m_bIsSpinning) return;

	if (KEY_HOLD(KEY::LEFT))
	{
		pRb->AddForce(Vector2D(-200.f, 0.f));
	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		pRb->AddForce(Vector2D(200.f, 0.f));
	}
	if (KEY_TAP(KEY::LEFT))
	{
		m_iDir = -1;
		//x방향 속도 초기화 시켜주자
		if (GetRigidBody()->IsGrounded())
			pRb->SetVelocity(Vector2D(-100.f, 0.f));
	}
	if (KEY_TAP(KEY::RIGHT))
	{
		m_iDir = 1;
		if (GetRigidBody()->IsGrounded())
			pRb->SetVelocity(Vector2D(100.f, 0.f));
	}
	if (KEY_TAP(KEY::SPACE) && GetRigidBody()->IsGrounded())
	{
		GetRigidBody()->AddVelocity(Vector2D(0.0f, -350.0f));

	}
	if (KEY_HOLD(KEY::DOWN) && KEY_TAP(KEY::SPACE) && GetRigidBody()->IsGrounded())
	{
		Slide();
	}
	if (KEY_TAP(KEY::Q))
	{
		SetBomb();
	}
	if (m_bIsSticked && KEY_TAP(KEY::SPACE))
	{
		m_bIsSticked = false;
		m_fStickDuration = 0.f;
		GetRigidBody()->EnableGravity(true);
		GetRigidBody()->SetVelocity(Vector2D(0.f, 200.0f));
	}
}

void CPlayer::UpdateAnim()
{
	if ((m_ePrevState == m_eCurState) && m_iDir == m_iPrevDir)
		return;

	//상태가 바뀌거나, 방향이 바뀌면 현재 상태에 맞는 애니메이션 실행
	switch (m_eCurState)
	{
	case PLAYER_STATUS::IDLE:
	{
		if (!m_bIsSliding)
		{
			if (m_iDir == -1)
				GetAnimator()->Play(L"GOLEM_IDLE_LEFT", true);
			else
				GetAnimator()->Play(L"GOLEM_IDLE_RIGHT", true);
		}
	}
	break;
	case PLAYER_STATUS::WALK:
	{
		if (!m_bIsSliding)
		{
			if (m_iDir == -1)
				GetAnimator()->Play(L"GOLEM_MOVE_LEFT", true);
			else
				GetAnimator()->Play(L"GOLEM_MOVE_RIGHT", true);
		}
	}
	break;
	case PLAYER_STATUS::SLIDE:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"GOLEM_ATTACK_LEFT", true);
		else
			GetAnimator()->Play(L"GOLEM_ATTACK_RIGHT", true);
	}
	break;
	case PLAYER_STATUS::JUMP:
		break;
	case PLAYER_STATUS::HOLDING:
		break;
	case PLAYER_STATUS::HOLDINGJUMP:
		break;
	case PLAYER_STATUS::DEAD:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"GOLEM_DIE_LEFT", false);
		else
			GetAnimator()->Play(L"GOLEM_DIE_RIGHT", false);
	}
	break;
	}
}

void CPlayer::DrawImage()
{
	using namespace Gdiplus;
	Vector2D vPos = GetPos();
	Graphics* pGr = GetGraphics();
	CImage* pImg = nullptr;

	int imgoffset;
	if (m_bIsImgInverted)
	{
		imgoffset = -1;
		pImg = pImgIdleInvert;
	}
	else
	{
		imgoffset = 1;
		pImg = pImgIdle;
	}

	int w = pImg->Width();
	int h = pImg->Height();

	pGr->DrawImage(pImg->GetImagePtr(), Rect((int)vPos.x - w / 2, (int)vPos.y - h / 2 - imgoffset * 15, w, h),
		0, 0, w, h, UnitPixel, pImg->GetImgAttr());
}

void CPlayer::SetSticked(bool _b)
{
	m_bIsSticked = _b;
	if (!m_bIsSticked)
	{
		m_fStickDuration = 0.f;
		GetRigidBody()->EnableGravity(true);
	}
}
void CPlayer::RotateImage()
{
	CImage* pImg = nullptr;
	if (m_bIsImgInverted)
		pImg = pImgIdleInvert;
	else
		pImg = pImgIdle;

	pImg->Rotate(GetGraphics(), GetPos(), (float)m_bSpinClockwise * 250.f * fDT);
}

CImage* CPlayer::GetGdiPlusImage(const wstring& _strImg)
{
	return CResMgr::GetInst()->FindImg(_strImg.c_str());
}

void CPlayer::Slide()
{
	m_bIsSliding = true;
	GetRigidBody()->ResetAccel();
	//rigidbody 마찰력 빡세게
	GetRigidBody()->SetFricCoeff(600.0f);
	GetRigidBody()->SetVelocity(Vector2D((float)m_iDir * 400.0f, 0.f));
}

void CPlayer::SetBomb()
{
	if (!m_bCanSetBomb)return;

	Vector2D vPos = GetPos();
	Vector2D vDeployPos(vPos.x + m_iDir * 30.0f, vPos.y - 20.f);

	CBomb* pBomb = new CBomb(m_eBMod, m_iDir);

	pBomb->SetName(L"Bomb");
	pBomb->SetPos(vDeployPos);
	pBomb->SetScale(Vector2D(40.0f, 40.0f));

	CreateObject(pBomb, GROUP_TYPE::BOMB);
	//생성 시킨 후 힘을 가하자
	Vector2D vDeployForce(m_iDir * 50.0f, -50.0f);
	Vector2D vDeployForceToPlayer(-m_iDir * 100.0f, 0.f);
	pBomb->GetRigidBody()->AddVelocity(vDeployForce + GetRigidBody()->GetVelocity());

	GetRigidBody()->SetVelocity(Vector2D(0.0f, 0.0f));
	GetRigidBody()->ResetAccel();
	GetRigidBody()->AddVelocity(vDeployForceToPlayer);
	m_bCanSetBomb = false;
}

void CPlayer::Hit()
{
	//사망처리
	//사망 애니메이션 재생
	//상태를 사망으로
	SetName(L"DeadPlayer");
	m_bIsAlive = false;
	GetRigidBody()->SetVelocity(Vector2D((float)-m_iDir * 200.f, -150.f));
}
