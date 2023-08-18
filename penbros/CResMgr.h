#pragma once

class CRes;
class CTexture;
class CImage;

class CResMgr
{
	SINGLE(CResMgr);
private:
	map<wstring, CRes*> m_mapTex;
	map<wstring, CRes*> m_mapImg;
public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelatviePath);
	CTexture* FindTexture(const wstring& _strKey);
	CImage* LoadImg(const wstring& _strKey, const wstring& _strRelativePath);
	CImage* FindImg(const wstring& _strKey);
};

