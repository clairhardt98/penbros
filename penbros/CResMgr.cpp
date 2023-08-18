#include "pch.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CImage.h"

CResMgr::CResMgr()
{

}
CResMgr::~CResMgr()
{
	Safe_Delete_Map(m_mapTex);
	Safe_Delete_Map(m_mapImg);
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex)
	{
		// 이미 있는 텍스쳐라면 그대로 반환
		return pTex;
	}

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture;
	pTex->Load(strFilePath);

	//리소스 객체가 키와 상대경로를 알게 하기
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	//map 자료구조를 활용하기 때문에 중복된 키의 리소스는 들어가지 않음
	m_mapTex.insert(make_pair(_strKey, pTex));
	return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	//map에서 탐색
	map<wstring, CRes*>::iterator iter = m_mapTex.find(_strKey);
	//없으면 nullptr 반환

	if (iter == m_mapTex.end())
	{
		return nullptr;
	}
	
	//키값으로 리소스 찾아서 반환하는 함수
	return (CTexture*)iter->second;
}

CImage* CResMgr::LoadImg(const wstring& _strKey, const wstring& _strRelativePath)
{
	CImage* pImg = FindImg(_strKey);
	if (nullptr != pImg)
	{
		// 이미 있는 텍스쳐라면 그대로 반환
		return pImg;
	}
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pImg = new CImage;
	pImg->Load(strFilePath);

	//리소스 객체가 키와 상대경로를 알게 하기
	pImg->SetKey(_strKey);
	pImg->SetRelativePath(_strRelativePath);

	//map 자료구조를 활용하기 때문에 중복된 키의 리소스는 들어가지 않음
	m_mapImg.insert(make_pair(_strKey, pImg));
	return pImg;
}

CImage* CResMgr::FindImg(const wstring& _strKey)
{
	map<wstring, CRes*>::iterator iter = m_mapImg.find(_strKey);
	//없으면 nullptr 반환

	if (iter == m_mapImg.end())
	{
		return nullptr;
	}

	//키값으로 리소스 찾아서 반환하는 함수
	return (CImage*)iter->second;
}

