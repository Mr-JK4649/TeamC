#include "DxLib.h"

#include "Source.h"
#include "Input.h"
#include "header.h"


//Title title;

void DrawGameTitle(int Width, int Height) {

	const float w = (float)Width * 4.0 / 100.0;
	const float h = (float)Height / 100.0;

	//一回だけ初期化
	//if (title.flg) { title.ImageInput(&title); title.flg = false; }

	/*背景の表示*/
	DrawExtendGraph(0, 0, Width, Height, title.image[title.Arrow], 1);

	/*ＢＧＭの再生*/
	if (CheckSoundMem(title.bgm) == false) {
		PlaySoundMem(title.bgm, DX_PLAYTYPE_BACK, TRUE);
		DrawBox(0, 0, 200, 200, 0xffff00, 1);
	}
	
	SetFontSize(20);

	DrawString(5, 5, "ビルド日付：2020年8月6日20時00分", 0xff0000, 1);

	SetFontSize(16);
	
	
	if (inp.f_up) {
		PlaySoundMem(title.SelectMove_SE, DX_PLAYTYPE_BACK, TRUE);
		if (--title.Arrow < 0) title.Arrow = 1;
	}
	if (inp.f_down) {
		PlaySoundMem(title.SelectMove_SE, DX_PLAYTYPE_BACK, TRUE);
		if (++title.Arrow > 1) title.Arrow = 0;
	}

	if (inp.space) {
		PlaySoundMem(title.Select_SE, DX_PLAYTYPE_BACK, TRUE);
		StopSoundMem(title.bgm);
		if (title.Arrow == 0) g_GameState = GAME_STORY;
		if (title.Arrow == 1) g_GameState = END;
	}
	
}