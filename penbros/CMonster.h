#pragma once
#include "CObject.h"
class CMonster :
    public CObject
{
private:
    Vector2D    m_vCenterPos;
    float       m_fSpeed;
    float       m_fMaxDistance;
    int         m_iDir;

    int         m_iHP;

public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetMaxDistance(float _f) { m_fMaxDistance = _f; }
    void SetCenterPos(Vector2D _vPos) { m_vCenterPos = _vPos; }
public:
    virtual void OnCollisionEnter(CCollider* _pOther);
public:
    virtual void Update()override;

    CLONE(CMonster);

public:
    CMonster();
    ~CMonster();
};

