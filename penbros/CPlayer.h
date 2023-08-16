#pragma once
#include "CObject.h"

class CTexture;

enum class PLAYER_STATUS
{
    IDLE,
    WALK,
    SLIDE,
    HOLDING,
    JUMP,
    HOLDINGJUMP,
    DEAD
};
class CPlayer :
    public CObject
{
private:
    int           m_iDir;
    int           m_iPrevDir;
    PLAYER_STATUS m_eCurState;
    PLAYER_STATUS m_ePrevState;

    bool		m_bIsSliding;
    bool        m_bIsSetBomb;
public:
    virtual void Update()override;
    virtual void Render(HDC _dc)override;

public:
    void CreateMissile();
    void UpdateState();
    void UpdateMove();
    void UpdateAnim();//현재 상태에 대한 애니메이션 재생
    CLONE(CPlayer);
public:
    void Slide();
    void SetBomb();
public:
    CPlayer();
    //플레이어의 복사생성자는 직접 구현할 필요없음 왜? -> 텍스쳐는 하나만 돌려쓰기 때문에 따로 deepcopy할 이유 없음
    ~CPlayer();
};

