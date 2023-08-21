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

	//ȸ���� ��ġ
	CObject* pSpinPlate = new CSpinPlate;
	pSpinPlate->SetPos(Vector2D(400.0f, 350.0f));
	pSpinPlate->SetScale(Vector2D(200.0f, 30.0f));
	pGround->SetName(L"SpinPlatform0");
	AddObject(pSpinPlate, GROUP_TYPE::PLATFORM);
	
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

