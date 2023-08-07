#include "pch.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"

CResMgr::CResMgr()
{

}
CResMgr::~CResMgr()
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.begin();
	for (; iter != m_mapTex.end(); ++iter)
	{
		delete iter->second;
	}
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelatviePath)
{
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex)
	{
		// 이미 있는 텍스쳐라면 그대로 반환
		return pTex;
	}

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelatviePath;

	pTex = new CTexture;
	pTex->Load(strFilePath);

	//리소스 객체가 키와 상대경로를 알게 하기
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelatviePath);

	//map 자료구조를 활용하기 때문에 중복된 키의 리소스는 들어가지 않음
	m_mapTex.insert(make_pair(_strKey, pTex));
	return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	//map에서 탐색
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);
	//없으면 nullptr 반환

	if (iter == m_mapTex.end())
	{
		return nullptr;
	}
	
	//키값으로 리소스 찾아서 반환하는 함수
	return iter->second;
}
