#include "pch.h"
#include "CScene_Stage.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"
#include "CRigidBody.h"
#include "CPlatform.h"
#include "CSpinPlate.h"
#include "CResMgr.h"
#include "CBat.h"
#include "CUI.h"
#include "CTimeMgr.h"
#include "CGhost.h"
#include "CMonsterEgg.h"
#include "CKey.h"
#include "CLock.h"
#include "CUI.h"
#include "CCrab.h"
#include "CRat.h"

void CScene_Stage::Update()
{
	//부모의 코드 그대로 사용
	UpdateState();
	CScene::Update();
	if (KEY_TAP(KEY::ENTER))
	{
		CPlayer::AddCredit();
	}

	switch (m_eCurState)
	{
	case STAGE_STATE::ENTER:
		break;
	case STAGE_STATE::PLAY:
		if (m_fRemainingTime >= 0.f)
			m_fRemainingTime -= fDT;
		else
		{
			if (!m_bIsGhostOn)
			{
				SpawnGhost();
				m_bIsGhostOn = true;
			}
		}
		//페이즈 바뀔 때 한 번만 실행
		if (!m_bIsPhaseChanged && !CSceneMgr::GetInst()->GetCurScene()->IsMonsterRemaining())
		{
			GenerateNewMonsters();
			m_bIsPhaseChanged = true;
		}

		break;
	case STAGE_STATE::GAMEOVER:
		if (KEY_TAP(KEY::G))
		{
			ContinueGame();

		}
		//동전넣으면 다시 플레이스테이트로 변경
		//게임오버 UI 출력
		break;
	case STAGE_STATE::CLEAR:
		if (m_bCleared)
		{
			m_fAfterClearTime += fDT;
			if (m_fAfterClearTime >= 2.0f)
			{
				printf("Move to Next Scene\n");
				MoveToNextStage();
			}
			return;
		}
		break;
	}

	if (KEY_TAP(KEY::I))
	{
		ClearEnemy();
	}


}

void CScene_Stage::Render(HDC _dc)
{
	BitBlt(_dc, 0, 0, 800, 600, m_pBGTex->GetDC(), 0, 0, SRCCOPY);
	CScene::Render(_dc);
}

void CScene_Stage::Enter()
{
	// !TODO : 각 씬에 맞게 자식 씬 오브젝트에서 오브젝트들을 배치합니다
}

void CScene_Stage::Exit()
{
	DeleteAll();
	CCollisionMgr::GetInst()->Reset();
	//충돌 그룹 해제
}

void CScene_Stage::GenerateNewMonsters()
{
}

void CScene_Stage::MoveToNextStage()
{
}

void CScene_Stage::UpdateState()
{
}

void CScene_Stage::RevivePlayer()
{
}

void CScene_Stage::SetCleared(bool _b)
{
}

void CScene_Stage::SetGameOvered(bool _b)
{
}

void CScene_Stage::InstantiatePlayer()
{
}

void CScene_Stage::SpawnGhost()
{
}

void CScene_Stage::ContinueGame()
{
}

CScene_Stage::CScene_Stage()
{
}

CScene_Stage::~CScene_Stage()
{
}
