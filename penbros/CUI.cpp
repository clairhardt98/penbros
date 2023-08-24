#include "pch.h"
#include "CUI.h"
#include "CResMgr.h"
#include "CImage.h"
#include "CTexture.h"
#include "CPlayer.h"
CUI::CUI()
{
	m_pNumFont = CResMgr::GetInst()->LoadTexture(L"Font_num", L"Image\\NumberFonts.bmp");
	m_pAlphabetFont = CResMgr::GetInst()->LoadTexture(L"Font_alpha", L"Image\\AlphabetFonts.bmp");
	m_pPlayerIdle = CResMgr::GetInst()->LoadImg(L"PlayerImageIdle", L"Image\\Golem_Idle_Image.bmp");

	m_vFontSize = Vector2D(8.f, 8.f);

	CreateGraphics();
}

CUI::~CUI()
{
}

void CUI::Update()
{
	//���ھ� ó��
	//�÷��̾� ��� ���� ó��
	//�ð��� ó��
	//���� ī��Ʈ ó��

}

void CUI::Render(HDC _dc)
{
	//�»�� �÷��̾� �̹���
	DrawPlayerImage(Vector2D(30.f, 30.f));
	//�»�� �÷��̾� ��� ī��Ʈ
	RenderNum(_dc, Vector2D(20.f, 40.f), CPlayer::GetHP(), 16, 2);
	//�÷��̾� ���ھ�
	RenderNum(_dc, Vector2D(60.f, 20.f), CPlayer::GetScore(), 16, 2);
	//�߾ӻ�� Ÿ�̸�
	RenderNum(_dc, Vector2D(340.f, 10.f), 99, 25, 6);
	//�߾��ϴ� ��������
	RenderAlphabet(_dc, Vector2D(340.f, 560.0f), L"ROUND", 16, 2);
	RenderNum(_dc, Vector2D(420.f, 560.f), CPlayer::GetCurStage(), 16, 2);
	//���ϴ� ũ����
	RenderAlphabet(_dc, Vector2D(600.f, 560.f), L"CREDIT", 16, 2);
	RenderNum(_dc, Vector2D(700.0f, 560.f), CPlayer::GetCredit(), 16, 2);
}

void CUI::RenderNum(HDC _dc, Vector2D _vStartPos, int _num, int _size, int _interval)
{
	if (0 == _num)
	{
		TransparentBlt(_dc, (int)_vStartPos.x + (_size + _interval), (int)_vStartPos.y, _size, _size, m_pNumFont->GetDC(), 0, 0, 16, 16, RGB(255, 0, 255));
		return;
	}
	int temp = _num;
	int cnt = 0;
	while (temp > 0)
	{
		temp /= 10;
		cnt++;
	}
	for (int i = 0; i < cnt; i++)
	{
		int idx = _num % 10;
		_num /= 10;
		TransparentBlt(_dc, (int)_vStartPos.x + (cnt - i) * (_size + _interval), (int)_vStartPos.y, _size, _size, m_pNumFont->GetDC(), idx * 16, 0, 16, 16, RGB(255, 0, 255));
	}
}

void CUI::RenderAlphabet(HDC _dc, Vector2D _vStartPos, wstring _str, int _size, int _interval)
{
	int cnt = _str.size();
	for (int i = 0; i < cnt; i++)
	{
		int idx = (int)(_str[i] - 'A');
		TransparentBlt(_dc, (int)_vStartPos.x + i * (_size + _interval), (int)_vStartPos.y, _size, _size, m_pAlphabetFont->GetDC(), idx * 16, 0, 16, 16, RGB(255, 0, 255));
	}
}

void CUI::DrawPlayerImage(Vector2D _vStartPos)
{
	using namespace Gdiplus;
	Graphics* pGr = GetGraphics();
	int w = m_pPlayerIdle->Width();
	int h = m_pPlayerIdle->Height();
	pGr->DrawImage(m_pPlayerIdle->GetImagePtr(), Rect((int)_vStartPos.x - w / 2, (int)_vStartPos.y - h / 2, w, h),
		0, 0, w, h, UnitPixel, m_pPlayerIdle->GetImgAttr());
}

