#pragma once
#include "CScene.h"

class CPlayer;
class CTexture;
class CScene_Start :
    public CScene
{
private:
    CTexture* m_pBGTex;
    float     m_fRemainingTime;
    bool      m_bIsGhostOn;
private:
    Vector2D m_vPlayerSpawnPos;

public:
    virtual int GetRemainingTime() { return (int)m_fRemainingTime; }

public:
    virtual void Update()override;
    virtual void Render(HDC _dc)override;
    virtual void Enter()override;
    virtual void Exit()override;

private:
    virtual void RevivePlayer()override;
    void InstantiatePlayer();
    void SpawnGhost();
public:
    CScene_Start();
    ~CScene_Start();
};

