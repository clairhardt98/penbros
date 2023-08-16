#pragma once
#include "CScene.h"

class CScene_Start :
    public CScene
{
private:
    bool m_bUseForce;

public:
    virtual void Update()override;
    virtual void Render(HDC _dc)override;
    virtual void Enter()override;
    virtual void Exit()override;
public:
    void CreateForce();
public:
    CScene_Start();
    ~CScene_Start();
};

