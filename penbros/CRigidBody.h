#pragma once
class CObject;
class CRigidBody
{
private:
	CObject*	m_pOwner;

	Vector2D	m_vForce;		// ũ��, ����
	Vector2D	m_vAccel;		// ���ӵ�
	Vector2D	m_vGravity;

	Vector2D	m_vVelocity;	// �ӵ�
	Vector2D	m_vMaxVelocity;	// �ִ� �ӷ�
	float		m_fMass;		// ����

	float		m_fFricCoeff;	// �������

	bool		m_bIsGrounded;	// �� ���� �ִ���
	bool		m_bIsGravityOn;	// �߷��� ����Ǵ��� ����

	//���ӵ� * DT -> ������Ű�� �ӵ��� ������

public:
	void FinalUpdate();

public:
	void AddForce(Vector2D _vF){m_vForce += _vF;}
	void SetMass(float _fMass) { m_fMass = _fMass; }
	float GetMass() { return m_fMass; }
	float GetSpeed() { return m_vVelocity.mag(); }
	void SetVelocity(Vector2D _v) { m_vVelocity = _v; }
	void AddVelocity(Vector2D _v) { m_vVelocity += _v; }
	void SetMaxVelocity(Vector2D _v) { m_vMaxVelocity = _v; }
	void SetGravityScale(Vector2D _v) { m_vGravity = _v; }
	void ResetAccel() { m_vAccel = Vector2D(0.f, 0.f); }
	void SetFricCoeff(float _f) { m_fFricCoeff = _f; }
public:

	void UpdateGravity();
	void EnableGravity(bool _b) { m_bIsGravityOn = _b; }
	void SetGrounded(bool _b)
	{ 
		m_bIsGrounded = _b;
		if(m_bIsGrounded)
		{
			m_vVelocity = Vector2D(m_vVelocity.x, 0.f);
			ResetAccel();
		}
	}
	bool IsGrounded() { return m_bIsGrounded; }
public:
	void Move();

public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

