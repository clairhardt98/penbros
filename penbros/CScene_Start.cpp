#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
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


CScene_Start::CScene_Start()
	:m_vPlayerSpawnPos(Vector2D(100.0f, 400.0f))
	, m_fRemainingTime(100)
	, m_bIsGhostOn(false)
	, m_bIsPhaseChanged(false)
	,m_bCleared(false)
	,m_fAfterClearTime(0.f)
	,m_bGameOvered(false)
	,m_eCurState(SCENE_STATE::PLAY)
{
	//�̹��� �ε��ϰ�, �ֵ� �׷��ֱ� ���� ���� ��� �׸���ǰڳ�
	CResMgr::GetInst()->LoadTexture(L"Background0", L"Image\\Background0.bmp");
	m_pBGTex = CResMgr::GetInst()->FindTexture(L"Background0");
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Update()
{
	//�θ��� �ڵ� �״�� ���
	UpdateState();
	CScene::Update();
	if (KEY_TAP(KEY::ENTER))
	{
		CPlayer::AddCredit();
	}

	switch (m_eCurState)
	{
	case SCENE_STATE::ENTER:
		break;
	case SCENE_STATE::PLAY:
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
		//������ �ٲ� �� �� ���� ����
		if (!m_bIsPhaseChanged && !CSceneMgr::GetInst()->GetCurScene()->IsMonsterRemaining())
		{
			GenerateNewMonsters();
			m_bIsPhaseChanged = true;
		}

		break;
	case SCENE_STATE::GAMEOVER:
		if (KEY_TAP(KEY::G))
		{
			ContinueGame();
			
		}
		//���������� �ٽ� �÷��̽�����Ʈ�� ����
		//���ӿ��� UI ���
		break;
	case SCENE_STATE::CLEAR:
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
	
	//�ð��� �پ���
	
	
	
}

void CScene_Start::Render(HDC _dc)
{
	//���
	BitBlt(_dc, 0, 0, 800, 600, m_pBGTex->GetDC(), 0, 0, SRCCOPY);
	CScene::Render(_dc);
}

void CScene_Start::Enter()
{
	m_fRemainingTime = 100.f;
	m_bIsGhostOn = false;
	m_bIsPhaseChanged = false;
	m_bCleared = false;
	m_fAfterClearTime = 0.f;
	m_eCurState = SCENE_STATE::PLAY;
	//player �߰�
	InstantiatePlayer();
	//�÷��̾��� stageCnt ++
	CPlayer::GoNextStage();
	//Bat
	CObject* pBat = new CBat;
	pBat->SetName(L"Monster");
	pBat->SetPos(Vector2D(400.0f, 440.0f));
	pBat->SetScale(Vector2D(40.0f, 40.0f));
	AddObject(pBat, GROUP_TYPE::MONSTER);

	CObject* pBat1 = new CBat;
	pBat1->SetName(L"Monster");
	pBat1->SetPos(Vector2D(600.0f, 260.0f));
	pBat1->SetScale(Vector2D(40.0f, 40.0f));
	AddObject(pBat1, GROUP_TYPE::MONSTER);

	CObject* pBat2 = new CBat;
	pBat2->SetName(L"Monster");
	pBat2->SetPos(Vector2D(200.0f, 260.0f));
	pBat2->SetScale(Vector2D(40.0f, 40.0f));
	CBat* temp = (CBat*)pBat2;
	temp->SetDirection(1);
	AddObject(pBat2, GROUP_TYPE::MONSTER);


	//crab

	CObject* pCrab0 = new CCrab;
	pCrab0->SetName(L"Monster");
	pCrab0->SetPos(Vector2D(75.0f, 280.f));
	pCrab0->SetScale(Vector2D(40.0f, 40.0f));
	CCrab* tempCrab = (CCrab*)pCrab0;
	tempCrab->SetDirection(1);
	AddObject(pCrab0, GROUP_TYPE::MONSTER);

	

	//�÷��� ��ġ
	CObject* pGround0 = new CPlatform;
	pGround0->SetPos(Vector2D(400.0f, 490.0f));
	pGround0->SetScale(Vector2D(800.0f, 38.0f));
	pGround0->SetName(L"BottomWall");
	AddObject(pGround0, GROUP_TYPE::PLATFORM);

	CObject* pGround1 = new CPlatform;
	pGround1->SetPos(Vector2D(400.0f, 350.0f));
	pGround1->SetScale(Vector2D(200.0f, 30.0f));
	pGround1->SetName(L"Platform");
	AddObject(pGround1, GROUP_TYPE::PLATFORM);

	CObject* pGround2 = new CPlatform;
	pGround2->SetPos(Vector2D(75.0f, 350.0f));
	pGround2->SetScale(Vector2D(150.f, 30.0f));
	pGround2->SetName(L"Platform");
	AddObject(pGround2, GROUP_TYPE::PLATFORM);

	CObject* pGround3 = new CPlatform;
	pGround3->SetPos(Vector2D(725.0f, 350.0f));
	pGround3->SetScale(Vector2D(150.f, 30.0f));
	pGround3->SetName(L"Platform");
	AddObject(pGround3, GROUP_TYPE::PLATFORM);

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

	//ȸ���� ��ġ
	CObject* pSpinPlate0 = new CSpinPlate;
	pSpinPlate0->SetPos(Vector2D(225.0f, 350.0f));
	pSpinPlate0->SetScale(Vector2D(150.0f, 30.0f));
	pSpinPlate0->SetName(L"SpinPlatform");
	AddObject(pSpinPlate0, GROUP_TYPE::PLATFORM);

	CObject* pSpinPlate1 = new CSpinPlate;
	pSpinPlate1->SetPos(Vector2D(575.0f, 350.0f));
	pSpinPlate1->SetScale(Vector2D(150.0f, 30.0f));
	pSpinPlate1->SetName(L"SpinPlatform");
	AddObject(pSpinPlate1, GROUP_TYPE::PLATFORM);

	

	//UI
	CObject* pUI = new CUI;
	pUI->SetName(L"UI");
	AddObject(pUI, GROUP_TYPE::UI);
	
	//�浹 ����
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


	Start();
}

void CScene_Start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetInst()->Reset();
	//�浹 �׷� ����
}

void CScene_Start::GenerateNewMonsters()
{
	//���� �� ��ȯ
	CObject* pEgg0 = new CMonsterEgg;
	pEgg0->SetName(L"MonsterEgg");
	pEgg0->SetPos(Vector2D(200.0f, 0.f));
	pEgg0->SetScale(Vector2D(40.0f, 40.0f));
	CMonsterEgg* tempEgg = (CMonsterEgg*)pEgg0;
	tempEgg->SetMonsterType(L"Bat");
	tempEgg->SetTargetDir(1);
	tempEgg->SetTargetPos(Vector2D(200.0f, 280.0f));
	AddObject(pEgg0, GROUP_TYPE::MONSTEREGG);

	CObject* pEgg1 = new CMonsterEgg;
	pEgg1->SetName(L"MonsterEgg");
	pEgg1->SetPos(Vector2D(600.0f, 0.f));
	pEgg1->SetScale(Vector2D(40.0f, 40.0f));
	tempEgg = (CMonsterEgg*)pEgg1;
	tempEgg->SetMonsterType(L"Bat");
	tempEgg->SetTargetDir(-1);
	tempEgg->SetTargetPos(Vector2D(600.0f, 280.0f));
	AddObject(pEgg1, GROUP_TYPE::MONSTEREGG);
	//Ű ��ȯ
	CObject* pKey = new CKey;
	pKey->SetPos(Vector2D(400.0f, 440.0f));
	pKey->SetScale(Vector2D(40.0f, 40.0f));
	pKey->SetName(L"Key");
	AddObject(pKey, GROUP_TYPE::KEY);
	//�ڹ��� ��ȯ
	CObject* pLock = new CLock;
	pLock->SetPos(Vector2D(400.0f, 300.0f));
	pLock->SetScale(Vector2D(50.0f, 50.0f));
	pLock->SetName(L"Lock");
	AddObject(pLock, GROUP_TYPE::LOCK);
}

void CScene_Start::MoveToNextStage()
{
	ChangeScene(SCENE_TYPE::TOOL);
}


void CScene_Start::UpdateState()
{
		
}

void CScene_Start::RevivePlayer()
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
			//Ghost �Լ����� ������� �ִϸ��̼� �����ϰ� ������� �ϴ� ���� �����ϸ� �ǰٴ�
			DeleteObject(GetGhost());
		}
	}
}

void CScene_Start::SetCleared(bool _b)
{
	m_bCleared = true;
	if (m_bCleared)
	{
		printf("StageCleared!\n");
		//�����ϴ� ��� ���鿡 ���� Hit�Լ� ȣ��
		ClearEnemy();
		//�÷��̾��� �¸� �ִϸ��̼� ����
		CPlayer* temp = (CPlayer*)GetPlayer();
		temp->OnStageCleared();
		//Ghost�� On  ���¶�� Ghost ��ü delete
		if (m_bIsGhostOn)
		{
			DeleteObject(GetGhost());
		}
		//Cool�̹�������
		CUI* pUI = (CUI*)GetUI();
		pUI->SetCleared(true);
		m_eCurState = SCENE_STATE::CLEAR;
	}
}

void CScene_Start::SetGameOvered(bool _b)
{
	m_bGameOvered = _b;
	CUI* pUI = (CUI*)GetUI();
	pUI->SetGameOvered(true);
	m_eCurState = SCENE_STATE::GAMEOVER;
}

void CScene_Start::InstantiatePlayer()
{
	CObject* pObj = new CPlayer;

	pObj->SetName(L"Player");
	pObj->SetPos(m_vPlayerSpawnPos);
	pObj->SetScale(Vector2D(100.0f, 100.0f));

	AddObject(pObj, GROUP_TYPE::PLAYER);
}

void CScene_Start::SpawnGhost()
{
	CObject* pObj = new CGhost;

	pObj->SetName(L"Ghost");
	pObj->SetPos(Vector2D(CCore::GetInst()->GetResolution())/2.f);
	pObj->SetScale(Vector2D(40.0f, 40.0f));

	AddObject(pObj, GROUP_TYPE::GHOST);
}

void CScene_Start::ContinueGame()
{
	if (0 == CPlayer::GetCredit())return;
	CPlayer::ReduceCredit();
	CPlayer::SetHP(3);
	CUI* pUI = (CUI*)GetUI();
	pUI->SetGameOvered(false);
	RevivePlayer();

	m_eCurState = SCENE_STATE::PLAY;
}
