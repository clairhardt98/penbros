#include "pch.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"

CResMgr::CResMgr()
{

}
CResMgr::~CResMgr()
{
	Safe_Delete_Map(m_mapTex);
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
	map<wstring, CRes*>::iterator iter = m_mapTex.find(_strKey);
	//������ nullptr ��ȯ

	if (iter == m_mapTex.end())
	{
		return nullptr;
	}
	
	//Ű������ ���ҽ� ã�Ƽ� ��ȯ�ϴ� �Լ�
	return (CTexture*)iter->second;
}
