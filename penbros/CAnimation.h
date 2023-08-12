#pragma once
class CAnimator;
class CTexture;
//�� ������ ���� ����ü
struct tAnimFrm
{
	Vector2D	vLT;	//�� ��� ��ġ
	Vector2D	vSlice;	//�ڸ� ����
	Vector2D	vOffset;//������
	float		fDuration;
};

class CAnimation
{

private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;
	vector<tAnimFrm>	m_vecFrm; // ��� ������ ����
	UINT				m_iCurFrm;// ���� ������
	float				m_fAccTime;

	bool				m_bFinish; // �ִϸ��̼��� �������� üũ

public:
	const wstring& GetName() { return m_strName; }
	bool IsFinish() { return m_bFinish; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.0f;
	}

	tAnimFrm& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; }
	int GetMaxFrame() { return m_vecFrm.size(); }
private:
	void SetName(const wstring& _strName) { m_strName = _strName; }
public:
	void Update();
	void Render(HDC _dc);
	void Create(const wstring& _strName, CTexture* _pTex, Vector2D _vLT, Vector2D _vSliceSize, Vector2D _vStep, float _fDuration, UINT _iFrameCount);

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};
