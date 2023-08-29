#pragma once
#include "CMonster.h"

enum class CRAB_STATE
{
	START,
	IDLE,
	ATTACK,
	DIE
};
class CCrab 
	: public CMonster
{
private:
	int			m_iDir;
	float		m_fDetectionDist;
	CRAB_STATE  m_ePrevState;
	CRAB_STATE	m_eCurState;
	bool		m_bIsAttacking;

public:
	void SetDirection(int _i) { m_iDir = _i; }
	
private:
	void UpdateAnim();
	void UpdateState();
	bool CanAttack();
	void Fire();
public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render(HDC _dc)override;
public:
	virtual void OnCollisionEnter(CCollider* _pOther)override;
	virtual void Hit()override;
	virtual void OnAnimEvent()override;
public:
	CLONE(CCrab);
	CCrab();
	~CCrab();

};

