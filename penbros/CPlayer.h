#pragma once
#include "CObject.h"
#include "CBomb.h"

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
    bool        m_bCanSetBomb;

    BOMB_MODE   m_eBMod;
public:
    virtual void Update()override;
    virtual void Render(HDC _dc)override;

public:
    void CreateMissile();
    void UpdateState();
    void UpdateMove();
    void UpdateAnim();//���� ���¿� ���� �ִϸ��̼� ���
public:
    void Slide();
    void SetBomb();
    void SetCanSetBomb(bool _b) { m_bCanSetBomb = _b; }
    //�����۸����� �̺�Ʈ �߻����Ѽ� �� �Լ� ȣ���Ű��
    void SetBombMode(BOMB_MODE _bm) { m_eBMod = _bm; }
public:
    CLONE(CPlayer);
    CPlayer();
    //�÷��̾��� ��������ڴ� ���� ������ �ʿ���� ��? -> �ؽ��Ĵ� �ϳ��� �������� ������ ���� deepcopy�� ���� ����
    ~CPlayer();
};

