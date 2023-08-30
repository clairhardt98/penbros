#include "pch.h"
#include "CScene_Stage03.h"
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


CScene_Stage03::CScene_Stage03()
	:m_vPlayerSpawnPos(Vector2D(100.0f, 400.0f))
	, m_fRemainingTime(100.f)
	, m_bIsGhostOn(false)
	, m_bIsPhaseChanged(false)
	, m_bCleared(false)
	, m_fAfterClearTime(0.f)
	, m_bGameOvered(false)
	, m_eCurState(STAGE3_STATE::PLAY)
{
	//이미지 로드하고, 애들 그려주기 전에 먼저 배경 그리면되겠네
	CResMgr::GetInst()->LoadTexture(L"Background2", L"Image\\Background2.bmp");
	m_pBGTex = CResMgr::GetInst()->FindTexture(L"Background2");

	m_pBGSound = CResMgr::GetInst()->LoadSound(L"Stage03BGM", L"Sound\\Stage3.wav");
}

CScene_Stage03::~CScene_Stage03()
{
}

void CScene_Stage03::Update()
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
	case STAGE3_STATE::ENTER:
		break;
	case STAGE3_STATE::PLAY:
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
	case STAGE3_STATE::GAMEOVER:
		if (KEY_TAP(KEY::G))
		{
			ContinueGame();

		}
		//동전넣으면 다시 플레이스테이트로 변경
		//게임오버 UI 출력
		break;
	case STAGE3_STATE::CLEAR:
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

void CScene_Stage03::Render(HDC _dc)
{
	//배경
	BitBlt(_dc, 0, 0, 800, 600, m_pBGTex->GetDC(), 0, 0, SRCCOPY);
	CScene::Render(_dc);
}

void CScene_Stage03::Enter()
{
	CSoundMgr::GetInst()->RegisterToBGM(m_pBGSound);
	m_pBGSound->Play(true);

	m_fRemainingTime = 100.f;
	m_bIsGhostOn = false;
	m_bIsPhaseChanged = false;
	m_bCleared = false;
	m_fAfterClearTime = 0.f;
	m_eCurState = STAGE3_STATE::PLAY;
	//player 추가
	InstantiatePlayer();
	//플레이어의 stageCnt ++
	CPlayer::GoNextStage();
	//Bat
	CObject* pBat = new CBat;
	pBat->SetName(L"Monster");
	pBat->SetPos(Vector2D(400.0f, 170.0f));
	pBat->SetScale(Vector2D(40.0f, 40.0f));
	AddObject(pBat, GROUP_TYPE::MONSTER);

	CObject* pBat1 = new CBat;
	pBat1->SetName(L"Monster");
	pBat1->SetPos(Vector2D(600.0f, 440.0f));
	pBat1->SetScale(Vector2D(40.0f, 40.0f));
	AddObject(pBat1, GROUP_TYPE::MONSTER);

	CObject* pBat2 = new CBat;
	pBat2->SetName(L"Monster");
	pBat2->SetPos(Vector2D(200.0f, 300.0f));
	pBat2->SetScale(Vector2D(40.0f, 40.0f));
	CBat* temp = (CBat*)pBat2;
	temp->SetDirection(1);
	AddObject(pBat2, GROUP_TYPE::MONSTER);



	//crab

	CObject* pCrab0 = new CCrab;
	pCrab0->SetName(L"Monster");
	pCrab0->SetPos(Vector2D(375.0f, 280.f));
	pCrab0->SetScale(Vector2D(40.0f, 40.0f));
	CCrab* tempCrab = (CCrab*)pCrab0;
	tempCrab->SetDirection(1);
	AddObject(pCrab0, GROUP_TYPE::MONSTER);

	CObject* pCrab1 = new CCrab;
	pCrab1->SetName(L"Monster");
	pCrab1->SetPos(Vector2D(725.0f, 440.f));
	pCrab1->SetScale(Vector2D(40.0f, 40.0f));
	tempCrab = (CCrab*)pCrab1;
	tempCrab->SetDirection(-1);
	AddObject(pCrab1, GROUP_TYPE::MONSTER);

	CObject* pCrab2 = new CCrab;
	pCrab2->SetName(L"Monster");
	pCrab2->SetPos(Vector2D(75.0f, 170.f));
	pCrab0->SetScale(Vector2D(40.0f, 40.0f));
	tempCrab = (CCrab*)pCrab2;
	tempCrab->SetDirection(1);
	AddObject(pCrab2, GROUP_TYPE::MONSTER);

	//Rat

	CObject* pRat0 = new CRat;
	pRat0->SetName(L"Monster");
	pRat0->SetPos(Vector2D(75.0f, 200.0f));
	pRat0->SetScale(Vector2D(40.0f, 40.0f));
	CRat* tempRat = (CRat*)pRat0;
	tempRat->SetDirection(1);
	AddObject(pRat0, GROUP_TYPE::MONSTER);

	CObject* pRat1 = new CRat;
	pRat1->SetName(L"Monster");
	pRat1->SetPos(Vector2D(300.0f, 320.0f));
	pRat1->SetScale(Vector2D(40.0f, 40.0f));
	tempRat = (CRat*)pRat1;
	tempRat->SetDirection(-1);
	AddObject(pRat1, GROUP_TYPE::MONSTER);



	//플랫폼 배치
	CObject* pGround0 = new CPlatform;
	pGround0->SetPos(Vector2D(400.0f, 490.0f));
	pGround0->SetScale(Vector2D(800.0f, 38.0f));
	pGround0->SetName(L"BottomWall");
	AddObject(pGround0, GROUP_TYPE::PLATFORM);



	CObject* pGround1 = new CPlatform;
	pGround1->SetPos(Vector2D(50.0f, 215.0f));
	pGround1->SetScale(Vector2D(100.0f, 30.0f));
	pGround1->SetName(L"Platform");
	AddObject(pGround1, GROUP_TYPE::PLATFORM);

	CObject* pGround2 = new CPlatform;
	pGround2->SetPos(Vector2D(350.0f, 215.0f));
	pGround2->SetScale(Vector2D(200.f, 30.0f));
	pGround2->SetName(L"Platform");
	AddObject(pGround2, GROUP_TYPE::PLATFORM);

	CObject* pGround3 = new CPlatform;
	pGround3->SetPos(Vector2D(550.0f, 215.0f));
	pGround3->SetScale(Vector2D(200.f, 30.0f));
	pGround3->SetName(L"Platform");
	AddObject(pGround3, GROUP_TYPE::PLATFORM);

	CObject* pGround4 = new CPlatform;
	pGround4->SetPos(Vector2D(725.0f, 215.0f));
	pGround4->SetScale(Vector2D(150.f, 30.0f));
	pGround4->SetName(L"Platform");
	AddObject(pGround4, GROUP_TYPE::PLATFORM);

	CObject* pGround5 = new CPlatform;
	pGround5->SetPos(Vector2D(75.0f, 350.0f));
	pGround5->SetScale(Vector2D(150.f, 30.0f));
	pGround5->SetName(L"Platform");
	AddObject(pGround5, GROUP_TYPE::PLATFORM);

	CObject* pGround6 = new CPlatform;
	pGround6->SetPos(Vector2D(250.0f, 350.0f));
	pGround6->SetScale(Vector2D(200.0f, 30.0f));
	pGround6->SetName(L"Platform");
	AddObject(pGround6, GROUP_TYPE::PLATFORM);

	CObject* pGround7 = new CPlatform;
	pGround7->SetPos(Vector2D(450.0f, 350.0f));
	pGround7->SetScale(Vector2D(200.f, 30.0f));
	pGround7->SetName(L"Platform");
	AddObject(pGround7, GROUP_TYPE::PLATFORM);

	CObject* pGround8 = new CPlatform;
	pGround8->SetPos(Vector2D(750.0f, 350.0f));
	pGround8->SetScale(Vector2D(100.f, 30.0f));
	pGround8->SetName(L"Platform");
	AddObject(pGround8, GROUP_TYPE::PLATFORM);


	CObject* pWall0 = new CPlatform;
	pWall0->SetPos(Vector2D(25.f, 400.0f));
	pWall0->SetScale(Vector2D(50.0f, 800.0f));
	pWall0->SetName(L"Wall");
	AddObject(pWall0, GROUP_TYPE::PLATFORM);

	CObject* pWall1 = new CPlatform;
	pWall1->SetPos(Vector2D(775.f, 400.0f));
	pWall1->SetScale(Vector2D(50.0f, 800.0f));
	pWall1->SetName(L"Wall");
	AddObject(pWall1, GROUP_TYPE::PLATFORM);

	//회전판 배치
	CObject* pSpinPlate0 = new CSpinPlate; 
	pSpinPlate0->SetPos(Vector2D(175.0f, 215.0f));
	pSpinPlate0->SetScale(Vector2D(150.0f, 30.0f));
	pSpinPlate0->SetName(L"SpinPlatform");
	AddObject(pSpinPlate0, GROUP_TYPE::PLATFORM);

	CObject* pSpinPlate1 = new CSpinPlate;
	pSpinPlate1->SetPos(Vector2D(625.0f, 350.0f));
	pSpinPlate1->SetScale(Vector2D(150.0f, 30.0f));
	pSpinPlate1->SetName(L"SpinPlatform");
	AddObject(pSpinPlate1, GROUP_TYPE::PLATFORM);


	//UI
	CObject* pUI = new CUI;
	pUI->SetName(L"UI");
	AddObject(pUI, GROUP_TYPE::UI);

	//충돌 지정
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GHOST);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::BOMB, GROUP_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::BOMB, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::EXPLOSION, GROUP_TYPE::PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::EXPLOSION, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::KEY, GROUP_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::KEY, GROUP_TYPE::PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::LOCK, GROUP_TYPE::PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTERPROJ, GROUP_TYPE::PLAYER);



	Start();
}

void CScene_Stage03::Exit()
{
	DeleteAll();
	CCollisionMgr::GetInst()->Reset();
	//충돌 그룹 해제
}

void CScene_Stage03::GenerateNewMonsters()
{
	//몬스터 알 소환
	CObject* pEgg0 = new CMonsterEgg;
	pEgg0->SetName(L"MonsterEgg");
	pEgg0->SetPos(Vector2D(550.0f, 0.f));
	pEgg0->SetScale(Vector2D(40.0f, 40.0f));
	CMonsterEgg* tempEgg = (CMonsterEgg*)pEgg0;
	tempEgg->SetMonsterType(L"Bat");
	tempEgg->SetTargetDir(1);
	tempEgg->SetTargetPos(Vector2D(550.0f, 175.0f));
	AddObject(pEgg0, GROUP_TYPE::MONSTEREGG);

	CObject* pEgg1 = new CMonsterEgg;
	pEgg1->SetName(L"MonsterEgg");
	pEgg1->SetPos(Vector2D(300.0f, 0.f));
	pEgg1->SetScale(Vector2D(40.0f, 40.0f));
	tempEgg = (CMonsterEgg*)pEgg1;
	tempEgg->SetMonsterType(L"Bat");
	tempEgg->SetTargetDir(-1);
	tempEgg->SetTargetPos(Vector2D(300.0f, 280.0f));
	AddObject(pEgg1, GROUP_TYPE::MONSTEREGG);

	CObject* pEgg2 = new CMonsterEgg;
	pEgg2->SetName(L"MonsterEgg");
	pEgg2->SetPos(Vector2D(450.0f, 0.f));
	pEgg2->SetScale(Vector2D(40.0f, 40.0f));
	tempEgg = (CMonsterEgg*)pEgg2;
	tempEgg->SetMonsterType(L"Bat");
	tempEgg->SetTargetDir(1);
	tempEgg->SetTargetPos(Vector2D(450.0f, 280.0f));
	AddObject(pEgg2, GROUP_TYPE::MONSTEREGG);

	CObject* pEgg3 = new CMonsterEgg;
	pEgg3->SetName(L"MonsterEgg");
	pEgg3->SetPos(Vector2D(600.0f, 0.f));
	pEgg3->SetScale(Vector2D(40.0f, 40.0f));
	tempEgg = (CMonsterEgg*)pEgg3;
	tempEgg->SetMonsterType(L"Crab");
	tempEgg->SetTargetDir(-1);
	tempEgg->SetTargetPos(Vector2D(600.0f, 175.0f));
	AddObject(pEgg3, GROUP_TYPE::MONSTEREGG);

	CObject* pEgg4 = new CMonsterEgg;
	pEgg4->SetName(L"MonsterEgg");
	pEgg4->SetPos(Vector2D(500.0f, 0.f));
	pEgg4->SetScale(Vector2D(40.0f, 40.0f));
	tempEgg = (CMonsterEgg*)pEgg4;
	tempEgg->SetMonsterType(L"Crab");
	tempEgg->SetTargetDir(1);
	tempEgg->SetTargetPos(Vector2D(500.0f, 450.0f));
	AddObject(pEgg4, GROUP_TYPE::MONSTEREGG);

	CObject* pEgg5 = new CMonsterEgg;
	pEgg5->SetName(L"MonsterEgg");
	pEgg5->SetPos(Vector2D(725.0f, 0.f));
	pEgg5->SetScale(Vector2D(40.0f, 40.0f));
	tempEgg = (CMonsterEgg*)pEgg5;
	tempEgg->SetMonsterType(L"Crab");
	tempEgg->SetTargetDir(-1);
	tempEgg->SetTargetPos(Vector2D(725.0f, 280.0f));
	AddObject(pEgg5, GROUP_TYPE::MONSTEREGG);

	CObject* pEgg6 = new CMonsterEgg;
	pEgg6->SetName(L"MonsterEgg");
	pEgg6->SetPos(Vector2D(75.0f, 0.f));
	pEgg6->SetScale(Vector2D(40.0f, 40.0f));
	tempEgg = (CMonsterEgg*)pEgg6;
	tempEgg->SetMonsterType(L"Crab");
	tempEgg->SetTargetDir(1);
	tempEgg->SetTargetPos(Vector2D(75.0f, 280.0f));
	AddObject(pEgg6, GROUP_TYPE::MONSTEREGG);

	CObject* pEgg7 = new CMonsterEgg;
	pEgg7->SetName(L"MonsterEgg");
	pEgg7->SetPos(Vector2D(400.0f, 0.f));
	pEgg7->SetScale(Vector2D(40.0f, 40.0f));
	tempEgg = (CMonsterEgg*)pEgg7;
	tempEgg->SetMonsterType(L"Rat");
	tempEgg->SetTargetDir(1);
	tempEgg->SetTargetPos(Vector2D(400.0f, 440.0f));
	AddObject(pEgg7, GROUP_TYPE::MONSTEREGG);

	CObject* pEgg8 = new CMonsterEgg;
	pEgg8->SetName(L"MonsterEgg");
	pEgg8->SetPos(Vector2D(300.0f, 0.f));
	pEgg8->SetScale(Vector2D(40.0f, 40.0f));
	tempEgg = (CMonsterEgg*)pEgg8;
	tempEgg->SetMonsterType(L"Rat");
	tempEgg->SetTargetDir(-1);
	tempEgg->SetTargetPos(Vector2D(300.0f, 440.0f));
	AddObject(pEgg8, GROUP_TYPE::MONSTEREGG);
	//키 소환
	CObject* pKey = new CKey;
	pKey->SetPos(Vector2D(700.0f, 175.0f));
	pKey->SetScale(Vector2D(40.0f, 40.0f));
	pKey->SetName(L"Key");
	AddObject(pKey, GROUP_TYPE::KEY);
	//자물쇠 소환
	CObject* pLock = new CLock;
	pLock->SetPos(Vector2D(75.0f, 460.0f));
	pLock->SetScale(Vector2D(64.0f, 64.0f));
	pLock->SetName(L"Lock");
	AddObject(pLock, GROUP_TYPE::LOCK);
}

void CScene_Stage03::MoveToNextStage()
{
	ChangeScene(SCENE_TYPE::ENDING);
}


void CScene_Stage03::UpdateState()
{

}

void CScene_Stage03::RevivePlayer()
{
	if (0 == CPlayer::GetHP())
	{
		SetGameOvered(true);
		printf("GameOver\n");
	}
	else
	{
		CPlayer::ReduceHP();
		InstantiatePlayer();
		if (m_bIsGhostOn)
		{
			m_fRemainingTime += 30;
			m_bIsGhostOn = false;
			//Ghost 함수에서 사라지는 애니메이션 실행하고 사라지게 하는 로직 구현하면 되겟다
			DeleteObject(GetGhost());
		}
	}
}

void CScene_Stage03::SetCleared(bool _b)
{
	m_bCleared = true;
	if (m_bCleared)
	{
		printf("StageCleared!\n");
		//존재하는 모든 적들에 대해 Hit함수 호출
		ClearEnemy();
		//플레이어의 승리 애니메이션 실행
		CPlayer* temp = (CPlayer*)GetPlayer();
		temp->OnStageCleared();
		//Ghost가 On  상태라면 Ghost 객체 delete
		if (m_bIsGhostOn)
		{
			DeleteObject(GetGhost());
		}
		//Cool이미지띄우기
		CUI* pUI = (CUI*)GetUI();
		pUI->SetCleared(true);
		m_eCurState = STAGE3_STATE::CLEAR;
	}
}

void CScene_Stage03::SetGameOvered(bool _b)
{
	m_bGameOvered = _b;
	CUI* pUI = (CUI*)GetUI();
	pUI->SetGameOvered(true);
	m_eCurState = STAGE3_STATE::GAMEOVER;
}

void CScene_Stage03::InstantiatePlayer()
{
	CObject* pObj = new CPlayer;

	pObj->SetName(L"Player");
	pObj->SetPos(m_vPlayerSpawnPos);
	pObj->SetScale(Vector2D(100.0f, 100.0f));

	AddObject(pObj, GROUP_TYPE::PLAYER);
}

void CScene_Stage03::SpawnGhost()
{
	CObject* pObj = new CGhost;

	pObj->SetName(L"Ghost");
	pObj->SetPos(Vector2D(CCore::GetInst()->GetResolution()) / 2.f);
	pObj->SetScale(Vector2D(40.0f, 40.0f));

	AddObject(pObj, GROUP_TYPE::GHOST);
}

void CScene_Stage03::ContinueGame()
{
	if (0 == CPlayer::GetCredit())return;
	CPlayer::ReduceCredit();
	CPlayer::SetHP(3);
	CUI* pUI = (CUI*)GetUI();
	pUI->SetGameOvered(false);
	RevivePlayer();

	m_eCurState = STAGE3_STATE::PLAY;
}
