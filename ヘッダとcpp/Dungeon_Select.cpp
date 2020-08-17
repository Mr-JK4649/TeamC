#include "Dungeon.h"

void GameSSelect(int width, int height) {
	SetFontSize(40);
	DrawFormatString(200, height / 2, 0xffffff, "ƒ_ƒ“ƒWƒ‡ƒ“%d", d_sys.Dungeon_Num + 1);
	SetFontSize(16);

	if (inp.f_up) {
		if (--d_sys.Dungeon_Num < 0) d_sys.Dungeon_Num = 2;
	}

	if (inp.f_down) {
		if (++d_sys.Dungeon_Num > 2) d_sys.Dungeon_Num = 0;
	}

	if(inp.space)
		g_GameState = GAME_DUNGEON;

	if (inp.cancel)
		g_GameState = GAME_BASE;
}