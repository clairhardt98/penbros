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


CPlayer::CPlayer()
	:m_eCurState(PLAYER_STATUS::IDLE)
	, m_ePrevState(PLAYER_STATUS::IDLE)
	, m_iPrevDir(1)
	, m_iDir(1)
	,m_bIsSetBomb(false)
	,m_bIsSliding(false)
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2D(0.0f, 0.0f));
	GetCollider()->SetScale(Vector2D(25.0f, 25.0f));

	CreateRigidBody();
	GetRigidBody()->EnableGravity(true);

	CTexture* pTexRight = CResMgr::GetInst()->LoadTexture(L"PlayerTexRight", L"Image\\Golem.bmp");
	CTexture* pTexLeft = CResMgr::GetInst()->LoadTexture(L"PlayerTexLeft", L"Image\\Golem_Left.bmp");

	CreateAnimator();
	CAnimator* pAnimator = GetAnimator();
	pAnimator->CreateAnimation(true, L"GOLEM_IDLE_RIGHT", pTexRight, 9, 10, 0, 0, Vector2D(128.0f, 128.0f), 0.1f, 4);
	pAnimator->CreateAnimation(false, L"GOLEM_IDLE_LEFT", pTexLeft, 9, 10, 0, 0, Vector2D(128.0f, 128.0f), 0.1f, 4);
	pAnimator->CreateAnimation(true, L"GOLEM_MOVE_RIGHT", pTexRight, 9, 10, 1, 6, Vector2D(128.0f, 128.0f), 0.1f, 4);
	pAnimator->CreateAnimation(false, L"GOLEM_MOVE_LEFT", pTexLeft, 9, 10, 1, 6, Vector2D(128.0f, 128.0f), 0.1f, 4);
	pAnimator->CreateAnimation(true, L"GOLEM_ATTACK_RIGHT", pTexRight, 9, 10, 2, 0, Vector2D(128.0f, 128.0f), 0.1f, 12);
	pAnimator->CreateAnimation(false, L"GOLEM_ATTACK_LEFT", pTexLeft, 9, 10, 2, 0, Vector2D(128.0f, 128.0f), 0.1f, 12);

	CAnimation* pAniIdleRight = pAnimator->FindAnimation(L"GOLEM_IDLE_RIGHT");
	CAnimation* pAniIdleLeft = pAnimator->FindAnimation(L"GOLEM_IDLE_LEFT");
	CAnimation* pAniMoveRight = pAnimator->FindAnimation(L"GOLEM_MOVE_RIGHT");
	CAnimation* pAniMoveLeft = pAnimator->FindAnimation(L"GOLEM_MOVE_LEFT");
	CAnimation* pAniAttackRight = pAnimator->FindAnimation(L"GOLEM_ATTACK_RIGHT");
	CAnimation* pAniAttackLeft = pAnimator->FindAnimation(L"GOLEM_ATTACK_LEFT");


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

	pAnimator->Play(L"GOLEM_IDLE_RIGHT", true);
}

CPlayer::~CPlayer()
{

}
void CPlayer::Update()
{
	UpdateMove();
	UpdateState();
	UpdateAnim();

	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;
}

void CPlayer::Render(HDC _dc)
{
	//본인이 보유하고 있는 애니메이션 정보
	ComponentRender(_dc);
}

void CPlayer::CreateMissile()
{
	Vector2D vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.0f;

	CMissile* pMissile = new CMissile;

	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vector2D(25.0f, 25.0f));
	pMissile->SetDir(Vector2D(0.0f, -1.0f));

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}

void CPlayer::UpdateState()
{
	//상태 관리

	//방향 전환
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
	if (KEY_TAP(KEY::SPACE)&&GetRigidBody()->IsGrounded())
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
	CRigidBody* pRb = GetRigidBody();

	//키 입력시 힘 가해서 이동
	
	if (m_bIsSliding) return;
	
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
	if (KEY_TAP(KEY::SPACE)&&GetRigidBody()->IsGrounded())
	{
		GetRigidBody()->AddVelocity(Vector2D(0.0f, -300.0f));

	}
	if (KEY_HOLD(KEY::DOWN) && KEY_TAP(KEY::SPACE) && GetRigidBody()->IsGrounded())
	{
		Slide();
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
		break;
	}
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

}

