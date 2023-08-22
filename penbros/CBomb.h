#pragma once
#include "CObject.h"

enum class BOMB_MODE
{
    NORMAL,
    RED,
    GREEN,
    BLUE
};

class CBomb :
    public CObject
{
private:
    const float m_fExplosionInterval = 40.0f;

private:
    float m_fExplosionTime;
    BOMB_MODE m_eBMod;
    int m_iDir;

    CObject* m_pCurPlate;

public:
    void SetBombMode(BOMB_MODE _bm) { m_eBMod = _bm; }

public:
    virtual void Update()override;
    virtual void Render(HDC _dc)override;

public:
    virtual void OnCollisionEnter(CCollider* _pOther)override;
    virtual void OnCollision(CCollider* _pOther)override;
    virtual void OnCollisionExit(CCollider* _pOther)override;

public:
    void Explode();
    void BeThrown(CObject* _pObj, int _Dir);
    void CreateExplosion(Vector2D _vPos);

public:
    CLONE(CBomb);
    CBomb();
    CBomb(BOMB_MODE _bm, int _dir);
    ~CBomb();
};

