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
    void UpdateAnim();//���� ���¿� ���� �ִϸ��̼� ���
    CLONE(CPlayer);
public:
    void Slide();
    void SetBomb();
public:
    CPlayer();
    //�÷��̾��� ��������ڴ� ���� ������ �ʿ���� ��? -> �ؽ��Ĵ� �ϳ��� �������� ������ ���� deepcopy�� ���� ����
    ~CPlayer();
};

