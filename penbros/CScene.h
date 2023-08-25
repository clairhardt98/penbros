#pragma once

//전방 선언 -> 포인터타입으로만 사용할 수 있음
class CObject;

class CScene
{
private:
	vector<CObject*>		m_arrObj[(UINT)GROUP_TYPE::END];// 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	wstring					m_strName; // scene 이름

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	virtual void Enter() = 0;//인터페이스, 해당 씬에 진입 시 호출
	virtual void Exit() = 0;//해당 씬에서 탈출 시 호출
	virtual void Start();
	virtual void Update();
	void FinalUpdate();
	virtual void Render(HDC _dc);

public:
	virtual void RevivePlayer() {}
	virtual int GetRemainingTime() { return 0; }
	CObject* GetPlayer() 
	{ 
		if (!m_arrObj[(UINT)GROUP_TYPE::PLAYER].empty())
			return m_arrObj[(UINT)GROUP_TYPE::PLAYER].front();
		else
			return nullptr;
	}
	CObject* GetGhost()
	{
		if (!m_arrObj[(UINT)GROUP_TYPE::GHOST].empty())
			return m_arrObj[(UINT)GROUP_TYPE::GHOST].front();
		else
			return nullptr;
	}
public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		//inline 처리를 통해서 호출 오버헤드 발생 x
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eLeft) { return m_arrObj[(UINT)_eLeft]; }
	void DeleteGroup(GROUP_TYPE _eTarget);
	//씬의 모든 오브젝트 전부 삭제
	void DeleteAll();
public:
	CScene();
	virtual ~CScene();
};

