#include "pch.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"
#include "CTimeMgr.h"


CAnimation::CAnimation()
	:m_pAnimator(nullptr)
	,m_pTex(nullptr)
	,m_iCurFrm(0)
	,m_fAccTime(0.f)
	,m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Update()
{
	//�� �� �����ؼ� ��������� ���̻� update����
	if (m_bFinish)
		return;
	//���� �ð��� ���� �귯�� �ð�
	m_fAccTime += fDT;
	if (m_fAccTime > m_vecFrm[m_iCurFrm].fDuration)
	{
		++m_iCurFrm;
		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = -1;
			m_bFinish = true;
			m_fAccTime = 0;
			return;
		}
		//fdt�� ������ �� ��ŭ ���ܵ־� ��
		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;

	}
}

void CAnimation::Render(HDC _dc)
{
	if (m_bFinish)
		return;
	//78 230 78
	CObject* pObj = m_pAnimator->GetObj();
	Vector2D vPos = pObj->GetPos();

	vPos += m_vecFrm[m_iCurFrm].vOffset; //������Ʈ �����ǿ� offset��ŭ �߰� �̵� ��ġ

	m_vecFrm[m_iCurFrm].vOffset;
	TransparentBlt(_dc
		, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.0f)
		, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.0f)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)
		, m_pTex->GetDC()
		, (int)(m_vecFrm[m_iCurFrm].vLT.x)
		, (int)(m_vecFrm[m_iCurFrm].vLT.y)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)
		, RGB(255, 0, 255));
}

//void CAnimation::Create(const wstring& _strName, CTexture* _pTex, Vector2D _vLT, Vector2D _vSliceSize, Vector2D _vStep, float _fDuration, UINT _iFrameCount)
//{
//	m_pTex = _pTex;
//	tAnimFrm frm = {};
//
//	for (UINT i = 0; i < _iFrameCount; ++i)
//	{
//		frm.fDuration = _fDuration;
//		frm.vSlice = _vSliceSize;
//		frm.vLT = _vLT + _vStep * (int)i;
//
//		m_vecFrm.push_back(frm);
//	}
//}

void CAnimation::Create(bool LR, const wstring& _strName, CTexture* _pTex, int _n, int _m, int _i, int _j, Vector2D _vsliceSize, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;
	tAnimFrm frm = {};
	
	//n,m : ��������Ʈ�� n*m
	//LR�� true�� right, false�� left
	if (LR)
	{
		for (UINT count = 0; count < _iFrameCount; ++count)
		{
			frm.fDuration = _fDuration;
			frm.vSlice = _vsliceSize;
			frm.vLT = Vector2D(_j * _vsliceSize.x, _i * _vsliceSize.y);
			_j++;
			if (_j == _m)
			{
				_j = 0;
				_i++;
			}
			m_vecFrm.push_back(frm);
		}
	}
	else
	{
		for (UINT count = 0; count < _iFrameCount; ++count)
		{
			frm.fDuration = _fDuration;
			frm.vSlice = _vsliceSize;
			frm.vLT = Vector2D((_m-_j-1) * _vsliceSize.x, _i * _vsliceSize.y);
			_j++;
			if (_j == _m)
			{
				_j = 0;
				_i++;
			}
			m_vecFrm.push_back(frm);
		}
	}

}
