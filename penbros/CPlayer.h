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
    CPlayer();
    ~CPlayer();
};

