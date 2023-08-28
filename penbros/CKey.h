#pragma once
#include "CObject.h"
class CPlayer;
class CKey :
    public CObject
{
public:
    CPlayer*    m_pPlayer;
    bool        m_bIsCaptured;
    int         m_iDir;
    CObject*    m_pCurPlate;
    Vector2D    m_vPrevPos;

public:
    virtual void Update()override;
    virtual void Render(HDC _dc)override;
public:
    virtual void OnCollisionEnter(CCollider* _pOther)override;
    virtual void OnCollision(CCollider* _pOther)override;
public:
    void SetCaptured(bool _b) { m_bIsCaptured = _b; }
    void BeThrown(CObject* _pObj, int _Dir);
private:
    void UpdateAnim();
public:
    CLONE(CKey);
    CKey();
    ~CKey();
};

