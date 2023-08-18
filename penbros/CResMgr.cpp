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
		// �̹� �ִ� �ؽ��Ķ�� �״�� ��ȯ
		return pTex;
	}

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture;
	pTex->Load(strFilePath);

	//���ҽ� ��ü�� Ű�� ����θ� �˰� �ϱ�
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

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

CImage* CResMgr::LoadImg(const wstring& _strKey, const wstring& _strRelativePath)
{
	CImage* pImg = FindImg(_strKey);
	if (nullptr != pImg)
	{
		// �̹� �ִ� �ؽ��Ķ�� �״�� ��ȯ
		return pImg;
	}
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pImg = new CImage;
	pImg->Load(strFilePath);

	//���ҽ� ��ü�� Ű�� ����θ� �˰� �ϱ�
	pImg->SetKey(_strKey);
	pImg->SetRelativePath(_strRelativePath);

	//map �ڷᱸ���� Ȱ���ϱ� ������ �ߺ��� Ű�� ���ҽ��� ���� ����
	m_mapImg.insert(make_pair(_strKey, pImg));
	return pImg;
}

CImage* CResMgr::FindImg(const wstring& _strKey)
{
	map<wstring, CRes*>::iterator iter = m_mapImg.find(_strKey);
	//������ nullptr ��ȯ

	if (iter == m_mapImg.end())
	{
		return nullptr;
	}

	//Ű������ ���ҽ� ã�Ƽ� ��ȯ�ϴ� �Լ�
	return (CImage*)iter->second;
}

