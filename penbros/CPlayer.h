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
    //�÷��̾��� ��������ڴ� ���� ������ �ʿ���� ��? -> �ؽ��Ĵ� �ϳ��� �������� ������ ���� deepcopy�� ���� ����
    ~CPlayer();
};

