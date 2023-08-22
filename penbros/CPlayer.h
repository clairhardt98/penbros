#pragma once
#include "CObject.h"
#include "CBomb.h"

class CTexture;
class CImage;

enum class PLAYER_STATUS
{
    IDLE,
    WALK,
    SLIDE,
    SPIN,
    HOLDING,
    JUMP,
    HOLDINGJUMP,
    DEAD
};


class CPlayer :
    public CObject
{
private:
    int             m_iDir;
    int             m_iPrevDir;
    PLAYER_STATUS   m_eCurState;
    PLAYER_STATUS   m_ePrevState;

    bool		    m_bIsSliding;
    bool            m_bCanSetBomb;

    BOMB_MODE       m_eBMod;

    //회전
    bool            m_bIsImgInverted;
    bool            m_bIsSpinning;
    bool            m_bIsSticked;
    float           m_fStickDuration;
    int             m_bSpinClockwise;
    Vector2D        m_vSpinCenter;

    CImage* pImgIdle;
    CImage* pImgIdleInvert;

public:
    virtual void Update()override;
    virtual void Render(HDC _dc)override;
public:
    PLAYER_STATUS GetCurState() { return m_eCurState; }
public:
    void UpdateState();
    void UpdateMove();
    void UpdateAnim();//현재 상태에 대한 애니메이션 재생
public:
    //gid+
    void DrawImage();
    void RotateImage();

    void SetSpinCenter(Vector2D _rotCenter) { m_vSpinCenter = _rotCenter; }
    void SetSpinClockwise(int _b) { m_bSpinClockwise = _b; }
    void SetSticked(bool _b);
    bool IsSticked() { return m_bIsSticked; }
    void SetImgInverted(bool _b) { m_bIsImgInverted = _b; }
public:
    CImage* GetGdiPlusImage(const wstring& _strImg);
public:
    void Slide();
    void SetBomb();
    void SetCanSetBomb(bool _b) { m_bCanSetBomb = _b; }
    //아이템먹으면 이벤트 발생시켜서 이 함수 호출시키자
    void SetBombMode(BOMB_MODE _bm) { m_eBMod = _bm; }
    void SetSpinning(bool _b) { m_bIsSpinning = _b; if(m_bIsSpinning) m_eCurState = PLAYER_STATUS::SPIN; }
public:
    CLONE(CPlayer);
    CPlayer();
    //플레이어의 복사생성자는 직접 구현할 필요없음 왜? -> 텍스쳐는 하나만 돌려쓰기 때문에 따로 deepcopy할 이유 없음
    ~CPlayer();
};

