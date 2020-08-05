#include "DxLib.h"

#include "Source.h"
#include "Input.h"
#include "header.h"


Title title;

void DrawGameTitle(int Width, int Height) {

	const float w = (float)Width * 4.0 / 100.0;
	const float h = (float)Height / 100.0;

	//��񂾂�������
	if (title.flg) { title.ImageInput(&title); title.flg = false; }

	DrawExtendGraph(0, 0, Width, Height, title.image[title.Arrow], 1);
	
	SetFontSize(20);

	DrawString(5, 5, "�r���h���t�F2020�N7��31��11��06��", 0xff0000, 1);

	SetFontSize(16);

	/*DrawFormatString(0, 0, 0x0000ff,"x=%d y=%d",inp.MouseX,inp.MouseY);*/
	
	
	if (inp.f_up) {
		if (--title.Arrow < 0) title.Arrow = 1;
	}
	if (inp.f_down) {
		if (++title.Arrow > 1) title.Arrow = 0;
	}

	if (inp.space) {
		if (title.Arrow == 0) g_GameState = GAME_BASE;
		if (title.Arrow == 1) g_GameState = END;
	}

	
	
	
}