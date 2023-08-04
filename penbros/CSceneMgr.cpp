#include "pch.h"
#include "CSceneMgr.h"
#include "CScene_Start.h"


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
	/*m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage01;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage02;*/

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
