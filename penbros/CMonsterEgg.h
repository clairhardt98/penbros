#pragma once
#include "CObject.h"
class CMonsterEgg :
    public CObject
{
private:
    wstring         m_strMonsterType;
    Vector2D        m_vTargetPos;
    int             m_iTargetDir;
    bool            m_bIsArrived;

public:
    virtual void Update()override;
    virtual void Render(HDC _dc)override;

public:
    void SetTargetPos(Vector2D _vPos) { m_vTargetPos = _vPos; }
    void SetTargetDir(int _iDir) { m_iTargetDir = _iDir; }
    void SetMonsterType(const wstring& _str) { m_strMonsterType = _str; }
private:
    void SpawnMonster();
    void UpdateAnim();
public:
    CLONE(CMonsterEgg);
    CMonsterEgg();
    ~CMonsterEgg();
};

