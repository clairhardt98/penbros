#include "pch.h"
#include "CSceneMgr.h"
#include "CScene_Stage01.h"
#include "CScene_Stage02.h"
#include "CScene_Stage03.h"
#include "CScene_Start.h"
#include "CScene_End.h"


CSceneMgr::CSceneMgr()
	:m_arrScene{}
	,m_pCurScene(0)
{

}

CSceneMgr::~CSceneMgr()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if(nullptr!=m_arrScene[i])
			delete m_arrScene[i];
	}
}

void CSceneMgr::Init()
{
	//scene 생성
	
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage01;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_01]->SetName(L"Stage01 Scene");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage02;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_02]->SetName(L"Stage02 Scene");
	m_arrScene[(UINT)SCENE_TYPE::STAGE_03] = new CScene_Stage03;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_03]->SetName(L"Stage03 Scene");
	m_arrScene[(UINT)SCENE_TYPE::ENDING] = new CScene_End;
	m_arrScene[(UINT)SCENE_TYPE::ENDING]->SetName(L"End Scene");

	//현재 씬 지정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	//시작 씬 진입
	m_pCurScene->Enter();
}

void CSceneMgr::Update()
{
	m_pCurScene->Update();
}

void CSceneMgr::Render(HDC _dc)
{
	m_pCurScene->Render(_dc);
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	//이벤트 매니저에서 호출하는 함수
	//현재 씬 탈출
	m_pCurScene->Exit();
	//씬 포인터 변경
	m_pCurScene = m_arrScene[(UINT)_eNext];
	//변경된 씬의 enter 호출
	m_pCurScene->Enter();
}
