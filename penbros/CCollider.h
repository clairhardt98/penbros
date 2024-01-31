#pragma once

class CObject;

class CCollider
{
private:
	static UINT g_iNextID;
	UINT		m_iID;
	CObject*	m_pOwner;
	Vector2D	m_vOffsetPos;	//오프셋
	Vector2D	m_vFinalPos;	//최종 위치
	Vector2D	m_vScale;		//충돌체의 크기
	Vector2D	m_vTempScale;	//비활성 처리했을 때 이전 스케일을 담아둘 변수
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
	void OnCollision(CCollider* _pOther);//충돌중인 경우 호출되는 함수
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

	CCollider& operator = (CCollider& origin) = delete; // 대입연산자 호출 금지

public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();
	friend class CObject;
};

