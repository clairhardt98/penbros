#pragma once

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
public:
	void Update();

public:
	void Excute(const tEvent& _eve);

public:
	void AddEvent(const tEvent& _eve){m_vecEvent.push_back(_eve);}

};

