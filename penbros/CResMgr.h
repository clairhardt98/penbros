#pragma once

class CRes;
class CTexture;
class CImage;
class CSound;

class CResMgr
{
	SINGLE(CResMgr);
private:
	map<wstring, CRes*> m_mapTex;
	map<wstring, CRes*> m_mapImg;
	map<wstring, CRes*> m_mapSound;
public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelatviePath);
	CTexture* FindTexture(const wstring& _strKey);
	CImage* LoadImg(const wstring& _strKey, const wstring& _strRelativePath);
	CImage* FindImg(const wstring& _strKey);
	CSound* LoadSound(const wstring& _strKey, const wstring& _strRelativePath);
	CSound* FindSound(const wstring& _strKey);
};

