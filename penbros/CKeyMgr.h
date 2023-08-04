#pragma once

//������ ����ȭ
//���� ������ ������ ���� Ű�� ���� ������ �̺�Ʈ�� ��������.

//Ű �Է� �̺�Ʈ ó��
//tap, hold, away...



enum class KEY_STATE
{
	NONE,//������ �ʰ�, �������� ������ ���� ����
	TAP,//�� ���� ����
	HOLD,//������ �ִ� ����
	AWAY,//�� �� ����
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,
	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LAST,
};

struct tKeyInfo
{
	KEY_STATE	eState;	// Ű�� ���°�
	bool		bPrev;	// ���� �����ӿ��� ���ȴ��� ����
};
class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	std::vector<tKeyInfo> m_vecKey;
public:
	void Init();
	void Update();
public:
	KEY_STATE GetKeyState(KEY _eKey)
	{
		return m_vecKey[(int)_eKey].eState;
	}
};

