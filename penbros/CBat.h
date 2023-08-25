#pragma once
#include "CMonster.h"

class CBat : 
	public CMonster
{
public:
	void SetDirection(int _i) { m_iDir = _i; }
	void ChangeDirection();
	void Move();
	void UpdateAnim();
	void SetDir(int _Dir) { m_iDir = _Dir; }
public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render(HDC _dc)override;
public:
	virtual void OnCollisionEnter(CCollider* _pOther)override;
	virtual void Hit()override;
	
public:
	CLONE(CBat);
	CBat();
	~CBat();
};

