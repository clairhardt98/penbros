#pragma once

class CObject;

class CCollider
{
private:
	static UINT g_iNextID;
	UINT		m_iID;
	CObject*	m_pOwner;
	Vector2D	m_vOffsetPos;	//������
	Vector2D	m_vFinalPos;	//���� ��ġ
	Vector2D	m_vScale;		//�浹ü�� ũ��
	Vector2D	m_vTempScale;	//��Ȱ�� ó������ �� ���� �������� ��Ƶ� ����
	bool		m_bIsActive;
	int			m_iCol;

public:
	void SetOffsetPos(Vector2D _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vector2D _vScale) { m_vScale = _vScale; }
	Vector2D GetOffsetPos() const { return m_vOffsetPos; }
	Vector2D GetScale() const { return m_vScale; }
	Vector2D GetFinalPos() const { return m_vFinalPos; }
	CObject* GetObj() { return m_pOwner; }
	int GetICol() const { return m_iCol; }
	UINT GetID() const { return m_iID; }

public:
	void EnableCollider();
	void DisableCollider();

public:
	void FinalUpdate();
	void Render(HDC _dc);

public:
	void OnCollision(CCollider* _pOther);//�浹���� ��� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

	CCollider& operator = (CCollider& origin) = delete; // ���Կ����� ȣ�� ����

public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();
	friend class CObject;
};

