#include "DxLib.h"

#include "Source.h"
#include "Input.h"
#include "header.h"



void DrawGameTitle(int Width, int Height) {

	const float w = (float)Width * 4.0 / 100.0;
	const float h = (float)Height / 100.0;
	static bool Start_Anim_Flg = false;
	static int Start_Anime_Count = 0;


	/*背景の表示*/
	DrawExtendGraph(0, 0, Width, Height, title.image[title.Arrow], 1);

	/*ＢＧＭの再生*/
	if (!Start_Anim_Flg && CheckSoundMem(title.bgm) == false) {
		PlaySoundMem(title.bgm, DX_PLAYTYPE_BACK, TRUE);;
	}
	
	SetFontSize(20);

	DrawString(5, 5, "ビルド日付：2020年8月13日20時20分", 0xff0000, 1);

	SetFontSize(16);
	
	
	if (!Start_Anim_Flg && inp.f_up) {
		PlaySoundMem(title.SelectMove_SE, DX_PLAYTYPE_BACK, TRUE);
		if (--title.Arrow < 0) title.Arrow = 1;
	}
	if (!Start_Anim_Flg && inp.f_down) {
		PlaySoundMem(title.SelectMove_SE, DX_PLAYTYPE_BACK, TRUE);
		if (++title.Arrow > 1) title.Arrow = 0;
	}

	if (!Start_Anim_Flg && inp.space) {
		PlaySoundMem(title.Select_SE, DX_PLAYTYPE_BACK, TRUE);
		StopSoundMem(title.bgm);
		if (title.Arrow == 0) Start_Anim_Flg = true;
		if (title.Arrow == 1) g_GameState = END;
	}

	/*移動アニメーション用*/
	if (Start_Anim_Flg) {
		if (CheckSoundMem(title.Start_SE) == false && title.Start_SE_Flg) {
			PlaySoundMem(title.Start_SE, DX_PLAYTYPE_BACK, TRUE);
			title.Start_SE_Flg = false;
		}
		
		SetDrawArea(0 + Start_Anime_Count, 0 + (Start_Anime_Count / 2), Width - Start_Anime_Count, Height - (Start_Anime_Count / 2));
		
		if (Start_Anime_Count > Width / 2) {
			g_GameState = GAME_STORY;
			Start_Anime_Count = 0;
			Start_Anim_Flg = false;
			SetDrawArea(0, 0, Width, Height);
			title.Start_SE_Flg = true;
		}

		Start_Anime_Count += (Width/400);
	}
	
}