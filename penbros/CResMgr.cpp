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
		// �̹� �ִ� �ؽ��Ķ�� �״�� ��ȯ
		return pTex;
	}

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelatviePath;

	pTex = new CTexture;
	pTex->Load(strFilePath);

	//���ҽ� ��ü�� Ű�� ����θ� �˰� �ϱ�
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelatviePath);

	//map �ڷᱸ���� Ȱ���ϱ� ������ �ߺ��� Ű�� ���ҽ��� ���� ����
	m_mapTex.insert(make_pair(_strKey, pTex));
	return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	//map���� Ž��
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);
	//������ nullptr ��ȯ

	if (iter == m_mapTex.end())
	{
		return nullptr;
	}
	
	//Ű������ ���ҽ� ã�Ƽ� ��ȯ�ϴ� �Լ�
	return iter->second;
}
