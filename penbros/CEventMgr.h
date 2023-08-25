#pragma once

class CPlayer;
class CBomb;

struct tEvent
{
	EVENT_TYPE		eEven;
	DWORD_PTR		lParam;
	DWORD_PTR		wParam;
};
class CEventMgr
{
	SINGLE(CEventMgr);
private:
	vector<tEvent>		m_vecEvent;
	vector<CObject*>	m_vecDead;//삭제 예정 오브젝트들
	
private:
	CPlayer*		m_pPlayer;
	CBomb*			m_pBomb = nullptr;


public:
	void SetPlayer(CPlayer* _pPlayer) { m_pPlayer = _pPlayer; }
	void SetBomb(CBomb* _pBomb) { m_pBomb = _pBomb; }
public:
	void Update();

public:
	void Execute(const tEvent& _eve);

public:
	void AddEvent(const tEvent& _eve) { m_vecEvent.push_back(_eve); }

};

