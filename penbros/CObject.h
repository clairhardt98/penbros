#pragma once

class CCollider;
class CAnimator;
class CRigidBody;

class CObject
{
private:
	wstring		m_strName;
	Vector2D	m_vPos;
	Vector2D	m_vScale;

	//�浹 ���
	CCollider*	m_pCollider;
	CAnimator*	m_pAnimator;
	CRigidBody* m_pRigidBody;

	//gdi+�� ����ϱ� ���� graphics ��ü
	Gdiplus::Graphics* m_pGraphics;

	bool		m_bAlive;
private:
	float		m_fRotateAmount;

public:
	void SetPos(Vector2D _vPos) { m_vPos = _vPos; }
	void SetScale(Vector2D _vScale) { m_vScale = _vScale; }

	const Vector2D GetPos() const { return m_vPos; }
	const Vector2D GetScale() const { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() const { return m_strName; }
	const bool IsDead() const { return !m_bAlive; }
	virtual void Hit() {};

private:
	void SetDead() { m_bAlive = false; }

	//�浹ü ���� �Լ�
public:

	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();
	void CreateGraphics();
	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }
	virtual void OnAnimEvent() {};
	CRigidBody* GetRigidBody() { return m_pRigidBody; }
	Gdiplus::Graphics* GetGraphics() { return m_pGraphics; }

	virtual void OnCollision(CCollider* _pOther) {};
	virtual void OnCollisionEnter(CCollider* _pOther) {};
	virtual void OnCollisionExit(CCollider* _pOther) {};
public:
	

public:
	void RotatePos(Vector2D _refVector, float _amount);

public:
	virtual void Start() {}; // Scene�� ���۵Ǳ� ������ ȣ��Ǵ� �Լ�
	virtual void Update() = 0;
	virtual void FinalUpdate() final;
	virtual void Render(HDC _dc);

	void ComponentRender(HDC _dc);

	//�ڱ� �ڽ��� �������� �ǵ����ִ� ����
	virtual CObject* Clone() = 0;
public:
	CObject();
	CObject(const CObject& _origin);//collider deep copy�� ���� ���������
	virtual ~CObject();

	friend class CEventMgr;
};

