#pragma once
class CObject;
class CRigidBody
{
private:
	CObject*	m_pOwner;

	Vector2D	m_vForce;		// 크기, 방향
	Vector2D	m_vAccel;		// 가속도
	Vector2D	m_vGravity;

	Vector2D	m_vVelocity;	// 속도
	Vector2D	m_vMaxVelocity;	// 최대 속력
	float		m_fMass;		// 질량

	float		m_fFricCoeff;	// 마찰계수

	bool		m_bIsGrounded;	// 땅 위에 있는지
	bool		m_bIsGravityOn;	// 중력이 적용되는지 여부

	//가속도 * DT -> 누적시키면 속도가 증가함

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

