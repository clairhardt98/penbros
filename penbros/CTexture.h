#pragma once
#include "CRes.h"
class CTexture :
    public CRes
{
private:
    HDC         m_dc;
    HBITMAP     m_hBit;
    BITMAP      m_bitInfo;

public:
    void Load(const wstring& _strFilePath);

    UINT Width() { return m_bitInfo.bmWidth; }
    UINT Height() { return m_bitInfo.bmHeight; }

    HDC GetDC() { return m_dc; }
private://텍스쳐를 아무나 생성하지 못하게 막아버림
    CTexture();
    ~CTexture();

    friend class CResMgr;//리소스매니저만 가능
};

