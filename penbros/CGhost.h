#pragma once
#include "CObject.h"

class CObject;
class CGhost :
    public CObject
{
private:
	CObject* m_pTarget;
	float m_fSpeed;
	int m_iDir;
private:
	void Trace(Vector2D _vTarget);
public:
	void UpdateAnim();
public:
	virtual void Update() override;
	virtual void Render(HDC _dc)override;
public:
	virtual void OnCollisionEnter(CCollider* _pOther)override;
public:
	CLONE(CGhost);
	CGhost();
	~CGhost();
};

