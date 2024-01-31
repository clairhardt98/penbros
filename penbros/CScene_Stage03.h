#pragma once
#include "CScene.h"

class CPlayer;
class CSound;
class CTexture;
enum class STAGE3_STATE
{
    ENTER,
    PLAY,
    GAMEOVER,
    CLEAR
};
class CScene_Stage03 :
    public CScene
{
private:
    STAGE3_STATE    m_eCurState;
    CTexture*       m_pBGTex;
    CSound*         m_pBGSound;
    float           m_fRemainingTime;
    bool            m_bIsGhostOn;
    bool            m_bIsPhaseChanged;
    bool            m_bCleared;
    bool            m_bGameOvered;
    float           m_fAfterClearTime;
private:
    Vector2D        m_vPlayerSpawnPos;

public:
    virtual int GetRemainingTime() { return (int)m_fRemainingTime; }

public:
    virtual void Update()override;
    virtual void Render(HDC _dc)override;
    virtual void Enter()override;
    virtual void Exit()override;
public:
    void GenerateNewMonsters();
    void MoveToNextStage();
private:
    void UpdateState();
    virtual void RevivePlayer()override;
    virtual void SetCleared(bool _b)override;
    virtual void SetGameOvered(bool _b)override;
    void InstantiatePlayer();
    void SpawnGhost();
    void ContinueGame();
public:
    CScene_Stage03();
    ~CScene_Stage03();
};

