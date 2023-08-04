#pragma once

//���� ���� -> ������Ÿ�����θ� ����� �� ����
class CObject;

class CScene
{
private:
	std::vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];// ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	std::wstring			m_strName; // scene �̸�

public:
	void SetName(const std::wstring& _strName) { m_strName = _strName; }
	const std::wstring& GetName() { return m_strName; }

	virtual void Enter() = 0;//�������̽�, �ش� ���� ���� �� ȣ��
	virtual void Exit() = 0;//�ش� ������ Ż�� �� ȣ��

	void Update();
	void Render(HDC _dc);

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		//inline ó���� ���ؼ� ȣ�� ������� �߻� x
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}
public:
	CScene();
	virtual ~CScene();
};

