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

CScene_Start::CScene_Start()
	:m_bUseForce(false)
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Update()
{
	//�θ��� �ڵ� �״�� ���
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
	CScene::Render(_dc);
}

void CScene_Start::Enter()
{
	//player �߰�
	CObject* pObj = new CPlayer;

	pObj->SetName(L"Player");
	pObj->SetPos(Vector2D(100.0f, 400.0f));
	pObj->SetScale(Vector2D(100.0f, 100.0f));

	AddObject(pObj, GROUP_TYPE::PLAYER);

	/*CObject* pOtherPlayer = pObj->Clone();
	pOtherPlayer->SetPos(Vector2D(740.0f, 384.0f));
	AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);*/

	//monster �߰�
	int iMonsterCnt = 10;
	float fMoveDist = 25.0f;
	float fObjScale = 50.0f;

	Vector2D vResolution = CCore::GetInst()->GetResolution();

	CMonster* pMonsterObj = nullptr;

	float fTerm = (vResolution.x - ((fMoveDist + fObjScale /2.0f) * 2)) / (float)(iMonsterCnt-1);
	for (int i = 0; i < iMonsterCnt; ++i)
	{
		pMonsterObj = new CMonster;
		pMonsterObj->SetName(L"Monster");
		pMonsterObj->CreateRigidBody();
		pMonsterObj->GetRigidBody()->SetMass(1.f);

		pMonsterObj->SetPos(Vector2D((fMoveDist + fObjScale / 2.0f) +(float)i * fTerm,50.0f));
		pMonsterObj->SetCenterPos(Vector2D(pMonsterObj->GetPos()));
		pMonsterObj->SetMaxDistance(fMoveDist);
		pMonsterObj->SetScale(Vector2D(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);

		
	}

	//�÷��� ��ġ
	
	CObject* pGround = new CPlatform;
	pGround->SetPos(Vector2D(400.0f, 500.0f));
	pGround->SetScale(Vector2D(800.0f, 60.0f));
	AddObject(pGround, GROUP_TYPE::PLATFORM);
	
	//�浹 ����
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::BOMB, GROUP_TYPE::PLATFORM);
	Start();
}

void CScene_Start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetInst()->Reset();
	//�浹 �׷� ����
}

void CScene_Start::CreateForce()
{

}

