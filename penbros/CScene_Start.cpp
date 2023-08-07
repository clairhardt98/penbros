#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{
	//player �߰�
	CObject* pObj = new CPlayer;

	pObj->SetPos(Vector2D(640.0f, 384.0f));
	pObj->SetScale(Vector2D(100.0f, 100.0f));

	AddObject(pObj, GROUP_TYPE::PLAYER);

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
		pMonsterObj->SetPos(Vector2D((fMoveDist + fObjScale / 2.0f) +(float)i * fTerm,50.0f));
		pMonsterObj->SetCenterPos(Vector2D(pMonsterObj->GetPos()));
		pMonsterObj->SetMaxDistance(fMoveDist);
		pMonsterObj->SetScale(Vector2D(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}
	//�浹 ����
	// player�׷�� Monster �׷찣�� �浹 üũ
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
}

void CScene_Start::Exit()
{
	CCollisionMgr::GetInst()->Reset();
	//�浹 �׷� ����
}

