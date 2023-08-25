#pragma once

//���� ���� -> ������Ÿ�����θ� ����� �� ����
class CObject;

class CScene
{
private:
	vector<CObject*>		m_arrObj[(UINT)GROUP_TYPE::END];// ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	wstring					m_strName; // scene �̸�

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	virtual void Enter() = 0;//�������̽�, �ش� ���� ���� �� ȣ��
	virtual void Exit() = 0;//�ش� ������ Ż�� �� ȣ��
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
		//inline ó���� ���ؼ� ȣ�� ������� �߻� x
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eLeft) { return m_arrObj[(UINT)_eLeft]; }
	void DeleteGroup(GROUP_TYPE _eTarget);
	//���� ��� ������Ʈ ���� ����
	void DeleteAll();
public:
	CScene();
	virtual ~CScene();
};

