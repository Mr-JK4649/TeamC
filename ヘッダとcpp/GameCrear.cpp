#include "DxLib.h"
#include "Input.h"
#include "Source.h"
#include "header.h"

int background_img = 0;
int flg2 = true;
int Anim_Count2 = 0;
int Anim_Alpha2 = 0;


void DrawGameResult(int width, int height) {
	if (flg2) {
		background_img = LoadGraph("images/gamecrear.jpg");
		flg2 = false;
	}

	DrawExtendGraph(0, 0, width, height, background_img, TRUE);

	if (inp.space) {
		Anim_Count2 = 900;
	}

	if (++Anim_Count2 > 900) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Anim_Alpha2);
		DrawBox(0, 0, width, height, 0x000000, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		if (++Anim_Alpha2 > 255) {
			Anim_Alpha2 = 0;
			Anim_Count2 = 0;
			g_GameState = GAME_TITLE;
		}
	}
}