#pragma once
const float PI = 3.1415f;
#define SINGLE(type) public:\
						static type* GetInst()\
						{\
							static type mgr;\
							return &mgr;\
						}\
						private:\
							type();\
							~type();

#define fDT CTimeMgr::GetInst()->GetfDT()
#define DT CTimeMgr::GetInst()->GetDT()

#define CLONE(type) type* Clone(){return new type(*this);}

#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)

enum class GROUP_TYPE
{
	DEFAULT,
	PLATFORM,
	LOCK,
	EXPLOSION,
	PLAYER,
	BOMB,
	MONSTER,
	GHOST,
	MONSTEREGG,
	KEY,
	MONSTERPROJ,
	

	UI = 31,
	END = 32,
};

enum class SCENE_TYPE
{
	START,
	STAGE_01,
	STAGE_02,
	STAGE_03,
	ENDING,

	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	BOMB_EXPLODED,
	SPIN_START,
	SPIN_END,
	THROW_BOMB,
	PLAYER_HIT,
	EXPLOSION_HIT,
	PLAYER_REVIVE,
	PLAYER_HOLDKEY,
	STAGE_CLEAR,
	END,
};