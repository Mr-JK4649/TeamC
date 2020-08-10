
#include "Story.h"

void Story(int width, int height) {

	if (flg) {
		str.setTex = true;
		str.Fade_String_Box = true;
		PlaySoundMem(title.Story_bgm, DX_PLAYTYPE_BACK, TRUE);
		flg = false;
	}
	
	str.Fade_String_Box = true;
	DrawBox(0, 0, width, height, 0x000000, 1);

	if (str.setTex) {
		if (scroll_y <= SCROOL_END) {
			str.SuperString((float)width / 100.0f * 1, (float)height / 100.0f * 96, "[Skip] 'X'key or 'B'Button", 0xffffff, 0, width / 100 * 2);
			scroll_y += SCROLL_SPEED;
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			str.SuperString((float)width / 100.0f * 50, (float)height / 100.0f * 80, "-Press 'X' Key or 'B' Button to Start-", 0xffffff, 1, width / 100 * 2);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

			alpha += add_alpha;
			if (alpha >= 255 || alpha < 0) add_alpha *= -1;
		}
		str.Serihu(Story_String, (float)width / 100.0f * 5, (float)height / 100.0f * 50 - (scroll_y / 2), 0xffffff, width / 100 * 3);
		if (scroll_y <= SCROOL_END && inp.space) {
			str.Serihu_Skip_Fin();
			scroll_y = SCROOL_END;
		}
		else if (inp.space) {
			str.Serihu_Skip_Fin();
		}
	}
	else {
		scroll_y = 0;
		StopSoundMem(title.Story_bgm);
		str.Fade_String_Box = false;
		g_GameState = GAME_BASE;
	}

}