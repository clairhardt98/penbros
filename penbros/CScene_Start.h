#pragma once
#include "CScene.h"

class CTexture;
class CScene_Start :
    public CScene
{
private:
    CTexture* m_pBGTex;

private:
    Vector2D m_vPlayerSpawnPos;

public:
    virtual void Update()override;
    virtual void Render(HDC _dc)override;
    virtual void Enter()override;
    virtual void Exit()override;

private:
    virtual void RevivePlayer()override;
    void InstantiatePlayer();
public:
    CScene_Start();
    ~CScene_Start();
};

