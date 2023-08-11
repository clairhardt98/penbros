#pragma once
#include "CObject.h"

class CTexture;

class CPlayer :
    public CObject
{

private:
    CTexture* m_pTex;//�ؽ��Ĵ� ������ render�Լ��� ���´�
public:
    virtual void Update()override;
    virtual void Render(HDC _dc)override;

public:
    void CreateMissile();
    CLONE(CPlayer);
public:
    CPlayer();
    //�÷��̾��� ��������ڴ� ���� ������ �ʿ���� ��? -> �ؽ��Ĵ� �ϳ��� �������� ������ ���� deepcopy�� ���� ����
    ~CPlayer();
};

