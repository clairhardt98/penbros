#pragma once
#include "CMonster.h"

class CSound;
enum class RAT_STATE
{
	START,
	IDLE,
	WAIT,
	ATTACK,
	DIE
};

class CRat
	:public CMonster
{
public:
	CSound* m_pHitSound;
	int			m_iDir;
	int			m_iPrevDir;
	float		m_fDetectionDist;
	RAT_STATE	m_ePrevState;
	RAT_STATE	m_eCurState;
	bool		m_bIsAttacking;
public:
	void SetDirection(int _i) {m_iPrevDir =  m_iDir = _i; }
private:
	void ChangeDirection();
	void Move();
	void UpdateAnim();
	void UpdateState();
	bool CanAttack();
public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render(HDC _dc)override;
	virtual void Hit() override;
public:
	virtual void OnCollisionEnter(CCollider* _pOther)override;
public:
	CLONE(CRat);
	CRat();
	~CRat();
};

