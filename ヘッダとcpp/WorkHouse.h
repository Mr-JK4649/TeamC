#pragma once

#include "Menu.h"
#include "character.h"


#pragma warning(disable : 4244)

Work work;

struct Working {

	

	void Draw(Working* wp) {

		const float w = ch.w / 100.0f;
		const float h = ch.h / 100.0f;

		DrawExtendGraph(0, 0, ch.w, ch.h, work.background, 1);


		DrawRoundRect(w * 40, h * 40, w * 60, h * 70, 10, 10, 0x444444, 1);
		DrawRoundRect(w * 40, h * 40, w * 60, h * 70, 10, 10, 0xaaaaaa, 0);
		DrawRoundRect(w * 40 + 1, h * 40 + 1, w * 60 - 1, h * 70 - 1, 10, 10, 0xffffff, 0);

		if (wp->Depth == 0) {
			for (int i = 0; i < 2; i++) {
				if (wp->Work_Select[wp->Depth] == i)wp->color = wp->blue_color;
				str.SuperString(ch.w / 2, h * (41 + 8 * i), wp->Selct_String[i], wp->color, 1, ch.size * 2);
				wp->color = wp->white_color;
			}
		}
		if (wp->Depth == 1) {
			for (int i = 0; i < 2; i++) {
				if (wp->Work_Select[wp->Depth] == i)wp->color = wp->blue_color;
				str.SuperString(ch.w / 2, h * (41 + 8 * i), wp->Selct_String2[i], wp->color, 1, ch.size * 2);
				wp->color = wp->white_color;
			}
		}
	}

	void Update(Working* wp) {
		if (inp.f_up) {
			if (--wp->Work_Select[wp->Depth] < 0) wp->Work_Select[wp->Depth] = 1;
		}
		if (inp.f_down) {
			if (++wp->Work_Select[wp->Depth] > 1) wp->Work_Select[wp->Depth] = 0;
		}

		if (inp.space) {
			if (wp->Depth == 0) {
				
				if(wp->Work_Select[wp->Depth] == 0)wp->Depth = 1;
				if(wp->Work_Select[wp->Depth] == 1)g_GameState = GAME_BASE;
				wp->Work_Select[0] = 0;
				
			}
			else if (wp->Depth == 1) {
				int Result_Money = 0;

				//力仕事
				if (wp->Work_Select[wp->Depth] == 0) {
					Result_Money = 50 + ch.Return_Base_Status(&ch, 1);

					ch.Add_Base_Status(&ch, 1, 5);							//発展度を増やす

					menu.Result_DWork_Flg = true;
				}

				//食料調達
				if (wp->Work_Select[wp->Depth] == 1) {
					Result_Money = 20 + ch.Return_Base_Status(&ch, 1) / 2;

					menu.Inclease_Gage(3, 5);								//食料ゲージを増やす

					menu.Result_FWork_Flg = true;
				}

				wp->Work_Select[1] = 0;
				wp->Depth = 0;
				ch.Add_Base_Status(&ch, 0, Result_Money);					//報酬のお金
				menu.Result_Work_Money = Result_Money;						//結果表示用の変数に代入
				g_GameState = GAME_BASE;
			}
		}

		if (inp.cancel) {
			wp->Work_Select[wp->Depth] = 0;
			if (wp->Depth == 0)g_GameState = GAME_BASE;
			if (wp->Depth == 1)wp->Depth = 0;
		}
	}

private:
	int Depth = 0;
	const char Selct_String[2][17] = { "働く","街に出る" };
	const char Selct_String2[2][17] = { "力仕事","食料調達" };
	int Work_Select[2] = {0};
	unsigned int color = 0xffffff;
	unsigned int white_color = 0xffffff;
	unsigned int blue_color = 0x6666ff;
};