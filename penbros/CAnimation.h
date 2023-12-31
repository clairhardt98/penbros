#pragma once
class CAnimator;
class CTexture;
//각 프레임 정보 구조체
struct tAnimFrm
{
	Vector2D	vLT;	//좌 상단 위치
	Vector2D	vSlice;	//자를 영역
	Vector2D	vOffset;//오프셋
	float		fDuration;
};

class CAnimation
{

private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;
	vector<tAnimFrm>	m_vecFrm; // 모든 프레임 정보
	UINT				m_iCurFrm;// 현재 프레임
	float				m_fAccTime;

	bool				m_bFinish; // 애니메이션이 끝났음을 체크
	int					m_iEventFrm;

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
	void SetEventFrame(int _i) { m_iEventFrm = _i; }

private:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	//어떤 프레임에 이벤트를 발생시킬 건지 정해준다
public:
	void Update();
	void Render(HDC _dc);
	//void Create(const wstring& _strName, CTexture* _pTex, Vector2D _vLT, Vector2D _vSliceSize, Vector2D _vStep, float _fDuration, UINT _iFrameCount);
	void Create(bool LR, const wstring& _strName, CTexture* _pTex, int _n, int _m, int _i, int _j, Vector2D _vsliceSize, float _fDuration, UINT _iFrameCount);
public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};
