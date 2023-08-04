#include "pch.h"
#include "CPlayer.h"

#include "CSceneMgr.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

void CPlayer::Update()
{
	Vector2D vPos = GetPos();
	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.0f * fDT;
	}
	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.0f * fDT;
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.0f * fDT;
	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.0f * fDT;
	}

	SetPos(vPos);
}
