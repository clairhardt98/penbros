#include "pch.h"
#include "CScene_Start.h"
#include "CKeyMgr.h"


CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Update()
{
	CScene::Update();
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::START);
	}
}

void CScene_Start::Render(HDC _dc)
{
}

void CScene_Start::Enter()
{
}

void CScene_Start::Exit()
{
}
