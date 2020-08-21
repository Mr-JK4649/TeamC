#include "Dungeon.h"

void GameSSelect(int width, int height) {
	DrawExtendGraph(0, 0, width, height, dungeon.Dungeon_Select_img[d_sys.Dungeon_Num], TRUE);

	if (inp.f_up) {
		PlaySoundMem(se.SelectMove_SE, DX_PLAYTYPE_BACK, TRUE);
		if (++d_sys.Dungeon_Num > 2) d_sys.Dungeon_Num = 0;
	}

	if (inp.f_down) {
		PlaySoundMem(se.SelectMove_SE, DX_PLAYTYPE_BACK, TRUE);
		if (--d_sys.Dungeon_Num < 0) d_sys.Dungeon_Num = 2;
	}

	if (inp.space) {
		PlaySoundMem(se.Select_SE, DX_PLAYTYPE_BACK, TRUE);
		g_GameState = GAME_DUNGEON;
	}

	if (inp.cancel) {
		PlaySoundMem(se.Cansel_SE, DX_PLAYTYPE_BACK, TRUE);
		g_GameState = GAME_BASE;
	}

}