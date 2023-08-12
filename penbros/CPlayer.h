#pragma once
#include "CObject.h"

class CTexture;

class CPlayer :
    public CObject
{

public:
    virtual void Update()override;
    virtual void Render(HDC _dc)override;

public:
    void CreateMissile();
    CLONE(CPlayer);
public:
    CPlayer();
    //플레이어의 복사생성자는 직접 구현할 필요없음 왜? -> 텍스쳐는 하나만 돌려쓰기 때문에 따로 deepcopy할 이유 없음
    ~CPlayer();
};

