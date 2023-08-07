#pragma once
#include "CObject.h"

class CTexture;

class CPlayer :
    public CObject
{

private:
    CTexture* m_pTex;//텍스쳐는 본인의 render함수를 갖는다
public:
    virtual void Update()override;
    virtual void Render(HDC _dc)override;

public:
    CPlayer();
    ~CPlayer();
};

