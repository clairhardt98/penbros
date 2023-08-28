#pragma once
#include "CObject.h"
#include "CBomb.h"

class CTexture;
class CImage;
class CKey;

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
    static int m_iHP;
    static int m_iScore;
    static int m_iCurStage;
    static int m_iCredit;
public:
    static int GetHP() { return m_iHP; }
    static void ReduceHP() { m_iHP--; }
    static void SetHP(int _i) { m_iHP = _i; }
    static int GetScore() { return m_iScore; }
    static void AddScore(int _i) { m_iScore += _i; }
    static int GetCurStage() { return m_iCurStage; }
    static void GoNextStage() { m_iCurStage++; }
    static int GetCredit() { return m_iCredit; }
    static void AddCredit() { m_iCredit++; }
    static void ReduceCredit() { m_iCredit--; }

private:
    bool            m_bIsAlive;
    float           m_fDeathTime;
    int             m_iDir;
    int             m_iPrevDir;
    PLAYER_STATUS   m_eCurState;
    PLAYER_STATUS   m_ePrevState;

    bool            m_bIsInVulnerable;
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

    CImage*         pImgIdle;
    CImage*         pImgIdleInvert;

    CKey*           m_pKey;
    bool            m_bIsHoldingKey;
        
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
    //gdi+
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
    int GetDir() { return m_iDir; }
    bool HasKey() { return m_bIsHoldingKey; }
    void OnStageCleared();

    virtual void Hit()override;//������Ʈ���� ������ �����Լ�
private:
    void ThrowKey();

public:
    virtual void OnCollisionEnter(CCollider* _pOther)override;
public:
    CLONE(CPlayer);
    CPlayer();
    //�÷��̾��� ��������ڴ� ���� ������ �ʿ���� ��? -> �ؽ��Ĵ� �ϳ��� �������� ������ ���� deepcopy�� ���� ����
    ~CPlayer();
};

