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

CScene_Start::CScene_Start()
	:m_bUseForce(false)
{
	//이미지 로드하고, 애들 그려주기 전에 먼저 배경 그리면되겠네
	CResMgr::GetInst()->LoadTexture(L"Background0", L"Image\\Background0.bmp");
	m_pBGTex = CResMgr::GetInst()->FindTexture(L"Background0");
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Update()
{
	//부모의 코드 그대로 사용
	CScene::Update();
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	if (KEY_HOLD(KEY::LSHIFT))
	{
		m_bUseForce = true;
		CreateForce();
	}
	else
	{
		m_bUseForce = false;
	}
}

void CScene_Start::Render(HDC _dc)
{
	BitBlt(_dc, 0, 0, 800, 600, m_pBGTex->GetDC(), 0, 0, SRCCOPY);
	CScene::Render(_dc);
}

void CScene_Start::Enter()
{
	//player 추가
	CObject* pObj = new CPlayer;

	pObj->SetName(L"Player");
	pObj->SetPos(Vector2D(100.0f, 400.0f));
	pObj->SetScale(Vector2D(100.0f, 100.0f));

	AddObject(pObj, GROUP_TYPE::PLAYER);

	
	


	

	//플랫폼 배치
	
	CObject* pGround = new CPlatform;
	pGround->SetPos(Vector2D(400.0f, 500.0f));
	pGround->SetScale(Vector2D(800.0f, 60.0f));
	pGround->SetName(L"Platform0");
	AddObject(pGround, GROUP_TYPE::PLATFORM);

	CObject* pGround1 = new CPlatform;
	pGround1->SetPos(Vector2D(150.0f, 350.0f));
	pGround1->SetScale(Vector2D(300.0f, 30.0f));
	pGround->SetName(L"Platform1");
	AddObject(pGround1, GROUP_TYPE::PLATFORM);

	CObject* pGround2 = new CPlatform;
	pGround2->SetPos(Vector2D(650.0f, 350.0f));
	pGround2->SetScale(Vector2D(300.0f, 30.0f));
	pGround->SetName(L"Platform2");
	AddObject(pGround2, GROUP_TYPE::PLATFORM);

	//회전판 배치
	CObject* pSpinPlate = new CSpinPlate;
	pSpinPlate->SetPos(Vector2D(400.0f, 350.0f));
	pSpinPlate->SetScale(Vector2D(200.0f, 30.0f));
	pGround->SetName(L"SpinPlatform0");
	AddObject(pSpinPlate, GROUP_TYPE::PLATFORM);
	
	//충돌 지정
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::BOMB, GROUP_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::EXPLOSION, GROUP_TYPE::PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::EXPLOSION, GROUP_TYPE::MONSTER);
	Start();
}

void CScene_Start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetInst()->Reset();
	//충돌 그룹 해제
}

void CScene_Start::CreateForce()
{

}

