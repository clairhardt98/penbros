#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);
private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END];
	CScene* m_pCurScene;

public:
	void Init();
	void Update();
	void Render(HDC _dc);
public:
	CScene* GetCurScene() { return m_pCurScene; }
private:
	//ChangeScene은 이벤트 매니저만 호출할 수 있게 함
	void ChangeScene(SCENE_TYPE _eNext);
	friend class CEventMgr;
};

