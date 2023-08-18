#pragma once
class CObject;
class CAnimation;
class CTexture;
class CAnimator
{
private:
	map<wstring, CAnimation*>	m_mapAnim;	//��� �ִϸ��̼�
	CAnimation*					m_pCurAnim;	//���� ������� �ִϸ��̼�
	CObject*					m_pOwner;	//�ִϸ��̼� ���� ������Ʈ
	bool						m_bRepeat;	//�ݺ���� ����

public:
	CObject* GetObj() { return m_pOwner; }
public:
	//void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vector2D _vLT, Vector2D _vSliceSize, Vector2D _vStep, float _fDuration, UINT _iFrameCount);
	void CreateAnimation(bool LR, const wstring& _strName, CTexture* _pTex, int n, int m, int i, int j, Vector2D _vsliceSize, float _fDuration, UINT _iFrameCount);
	CAnimation* FindAnimation(const wstring& _strName);
	CAnimation* GetCurAnimation() { return m_pCurAnim; }
	void Play(const wstring& _strName, bool _bRepeat);

	void Pause();
	void Resume();

	void FinalUpdate();
	void Render(HDC _dc);



public:
	CAnimator();
	~CAnimator();
	friend class CObject;
};

