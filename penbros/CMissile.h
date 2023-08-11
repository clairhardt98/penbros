#pragma once
#include "CObject.h"
class CMissile :
	public CObject
{
private:
	float			m_fTheta;
	Vector2D		m_vDir;


public:
	void SetDir(Vector2D _vDir) 
	{
		m_vDir = _vDir;
		m_vDir.normalize();
	}
public:
	virtual void Update()override;
	virtual void Render(HDC _dc)override;

public:
	virtual void OnCollisionEnter(CCollider* _pOther)override;


	CLONE(CMissile);
public:
	CMissile();
	~CMissile();

};

