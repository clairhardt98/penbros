#include "pch.h"
#include "CAnimator.h"
#include "CAnimation.h"

CAnimator::CAnimator()
	:m_pCurAnim(nullptr)
	,m_pOwner(nullptr)
	,m_bRepeat(false)
{
}

CAnimator::~CAnimator()
{
	//관리하던 애니메이션을 전부 제거해야 함
	Safe_Delete_Map(m_mapAnim);
}

//void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pTex, Vector2D _vLT, Vector2D _vSliceSize, 
//								Vector2D _vStep, float _fDuration, UINT _iFrameCount)
//{
//	CAnimation* pAnim = FindAnimation(_strName);
//	assert(nullptr == pAnim);
//
//	pAnim = new CAnimation;
//	pAnim->SetName(_strName);
//	pAnim->m_pAnimator = this;
//
//	//애니메이션 생성
//	pAnim->Create(_strName,  _pTex, _vLT, _vSliceSize, _vStep, _fDuration, _iFrameCount);
//	m_mapAnim.insert(make_pair(_strName, pAnim));
//}
void CAnimator::CreateAnimation(bool LR, const wstring& _strName, CTexture* _pTex,
	int _n, int _m, int _i, int _j, Vector2D _vSliceSize, float _fDuration, UINT _iFrameCount)
{
	CAnimation* pAnim = FindAnimation(_strName);
	assert(nullptr == pAnim);

	pAnim = new CAnimation;
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;

	//애니메이션 생성
	pAnim->Create(LR, _strName, _pTex, _n,_m,_i,_j, _vSliceSize, _fDuration, _iFrameCount);
	m_mapAnim.insert(make_pair(_strName, pAnim));
}
CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);
	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;

}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
}

void CAnimator::FinalUpdate()
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->Update();
		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			//반복재생-> 애니메이션을 초기상태로 돌려놔야 함
			m_pCurAnim->SetFrame(0);
		}
	}
}

void CAnimator::Render(HDC _dc)
{
	if (nullptr != m_pCurAnim)
		m_pCurAnim->Render(_dc);
}

