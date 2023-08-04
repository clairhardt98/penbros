#pragma once
class CObject
{
private:
	Vector2D	m_vPos;
	Vector2D	m_vScale;

public:
	void SetPos(Vector2D _vPos) { m_vPos = _vPos; }
	void SetScale(Vector2D _vScale) { m_vScale = _vScale; }

	Vector2D GetPos() { return m_vPos; }
	Vector2D GetScale() { return m_vScale; }

public:
	virtual void Update() = 0;
	virtual void Render(HDC _dc);
public:
	CObject();
	virtual ~CObject();
};

