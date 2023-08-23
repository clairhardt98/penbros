#pragma once

class CObject;

class CCollider
{
private:
	static UINT g_iNextID;
	CObject*	m_pOwner;
	Vector2D	m_vOffsetPos;	//오프셋
	Vector2D	m_vFinalPos;	//최종 위치
	Vector2D	m_vScale;		//충돌체의 크기

	UINT		m_iID;
	int			m_iCol;

public:
	void SetOffsetPos(Vector2D _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vector2D _vScale) { m_vScale = _vScale; }

	Vector2D GetOffsetPos() { return m_vOffsetPos;}
	Vector2D GetScale() { return m_vScale; }

	Vector2D GetFinalPos() { return m_vFinalPos; }

	CObject* GetObj() { return m_pOwner; }

	int GetICol() { return m_iCol; }

	UINT GetID() { return m_iID; }

public:
	void FinalUpdate();
	void Render(HDC _dc);

public:
	void OnCollision(CCollider* _pOther);//충돌중인 경우 호출되는 함수
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

	CCollider& operator = (CCollider& origin) = delete;

public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();
	friend class CObject;
};

