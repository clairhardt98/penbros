#pragma once

class CPlayer;

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
	vector<tEvent> m_vecEvent;
	vector<CObject*> m_vecDead;//삭제 예정 오브젝트들
	
private:
	CPlayer* m_pPlayer;

public:
	void SetPlayer(CPlayer* _pPlayer) { m_pPlayer = _pPlayer; }
public:
	void Update();

public:
	void Execute(const tEvent& _eve);

public:
	void AddEvent(const tEvent& _eve) { m_vecEvent.push_back(_eve); }

};

