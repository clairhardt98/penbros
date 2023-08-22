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

    //ȸ��
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
    void UpdateAnim();//���� ���¿� ���� �ִϸ��̼� ���
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
    //�����۸����� �̺�Ʈ �߻����Ѽ� �� �Լ� ȣ���Ű��
    void SetBombMode(BOMB_MODE _bm) { m_eBMod = _bm; }
    void SetSpinning(bool _b) { m_bIsSpinning = _b; if(m_bIsSpinning) m_eCurState = PLAYER_STATUS::SPIN; }
public:
    CLONE(CPlayer);
    CPlayer();
    //�÷��̾��� ��������ڴ� ���� ������ �ʿ���� ��? -> �ؽ��Ĵ� �ϳ��� �������� ������ ���� deepcopy�� ���� ����
    ~CPlayer();
};

