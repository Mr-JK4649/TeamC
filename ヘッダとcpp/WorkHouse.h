#pragma once

#include "GameSys.h"

#pragma warning(disable : 4244)

//Work work;

struct Working {

	bool isPower_Work = false;			//�͎d���̃A�j���[�V�����t���O
	bool isFood_Work = false;			//�H�����B�̃A�j���[�V�����t���O
	int Anim_Count = 0;					//�d���A�j���[�V�����̃J�E���g
	int Anim_Alpha = 0;					//�d���A�j���[�V�����̕s�����x

	int Result_Money = 0;
	

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
		if (wp->Depth == 2) {
			for (int i = 0; i < 3; i++) {
				if (Work_Select[2] == i)wp->color = wp->blue_color;
				str.SuperString(ch.w / 2, ch.h / 100.0f * (41 + 8 * i), wp->Selct_String3[i], wp->color, 1, ch.size * 2);
				wp->color = wp->white_color;
			}

			if (inp.space) {
				

			}
		}
		if (wp->Depth == 3) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, Anim_Alpha);
			DrawBox(0, 0, ch.w, ch.h, 0x000000, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

			if (Anim_Count == 0) {
				if (Anim_Alpha > 255) Anim_Count = 1;
				Anim_Alpha += 2;
			}
			if (Anim_Count == 1) {
				Anim_Alpha -= 4;
				if (Anim_Alpha < 0) {
					Anim_Alpha = 0;
					Anim_Count = 2;
				}
			}
			if (Anim_Count == 2) {
				const int w = ch.w;
				const int h = ch.h;
				const int w5 = w / 5;
				const int h4 = h / 4;


				DrawRoundRect(5, h - h4, w - 5, h - 5, 10, 10, 0x444444, 1);
				DrawRoundRect(5, h - h4, w - 5, h - 5, 10, 10, 0xaaaaaa, 0);
				DrawRoundRect(6, h - (h4 - 1), w - 6, h - 6, 10, 10, 0xffffff, 0);
				str.SuperString(w / 2, h - (h / 10), "�n�j", 0xff0000, 1, ch.size * 2);
				if (isPower_Work) {
					DrawFormatString(10, (h - h4) + 5, 0xffffff, "�X�̔��W�ɋ��͂������ɂ��A�ȉ��̕�V�𓾂��B\n�����@+%9d�f\n���W�x+%9d��", Result_Money, 5);
				}
				if (isFood_Work) {
					DrawFormatString(10, (h - h4) + 5, 0xffffff, "�H�����B���������ɂ��A�ȉ��̕�V�𓾂��B\n�����@+%9d�f\n�H���@+%9d��", Result_Money, 5);
				}

				
			}
		}
		
	}

	void Update(Working* wp) {
		if (inp.f_up) {
			if (--wp->Work_Select[wp->Depth] < 0) wp->Work_Select[wp->Depth] = Selct_Num[wp->Depth] - 1;
		}
		if (inp.f_down) {
			if (++wp->Work_Select[wp->Depth] > Selct_Num[wp->Depth] - 1) wp->Work_Select[wp->Depth] = 0;
		}

		if (inp.space) {
			if (wp->Depth == 0) {
				
				if(wp->Work_Select[wp->Depth] == 0)wp->Depth = 1;
				if(wp->Work_Select[wp->Depth] == 1)g_GameState = GAME_BASE;
				wp->Work_Select[0] = 0;
				
			}
			else if (wp->Depth == 1) {

				//�͎d��
				if (wp->Work_Select[wp->Depth] == 0) {
					Result_Money = 50 + ch.Return_Base_Status(&ch, 1);

					ch.Add_Base_Status(&ch, 1, 5);							//���W�x�𑝂₷

					menu.Result_DWork_Flg = true;
					isPower_Work = true;
				}

				//�H�����B
				if (wp->Work_Select[wp->Depth] == 1) {
					Result_Money = 20 + ch.Return_Base_Status(&ch, 1) / 2;

					menu.Inclease_Gage(3, 5);								//�H���Q�[�W�𑝂₷

					menu.Result_FWork_Flg = true;
					isFood_Work = true;
				}

				wp->Work_Select[1] = 0;
				wp->Depth = 3;
				ch.Add_Base_Status(&ch, 0, Result_Money);					//��V�̂���
				menu.Input_Work_Result(Result_Money, 5, 5);					//���ʕ\���p�̕ϐ��ɑ��
				
			}
			else if (wp->Depth == 2) {
				if (Work_Select[2] == 0) {
					if (isPower_Work) {
						Result_Money = 50 + ch.Return_Base_Status(&ch, 1);

						ch.Add_Base_Status(&ch, 1, 5);							//���W�x�𑝂₷

						menu.Result_DWork_Flg = true;
						isFood_Work = false;
					}
					if (isFood_Work) {
						Result_Money = 20 + ch.Return_Base_Status(&ch, 1) / 2;

						menu.Inclease_Gage(3, 5);								//�H���Q�[�W�𑝂₷

						menu.Result_FWork_Flg = true;
					}

					wp->Work_Select[2] = 0;
					wp->Depth = 3;
					ch.Add_Base_Status(&ch, 0, Result_Money);					//��V�̂���
					menu.Input_Work_Result(Result_Money, 5, 5);					//���ʕ\���p�̕ϐ��ɑ��
				}
				if (Work_Select[2] == 1) {
					Result_Money = 0;
					isPower_Work = false;
					isFood_Work = false;
					Depth = 1;
				}
				if (Work_Select[2] == 2) {
					Result_Money = 0;
					isPower_Work = false;
					isFood_Work = false;
					g_GameState = GAME_BASE;
				}
			}
			else if (wp->Depth == 3) {

				Depth = 2;
				Anim_Count = 0;
				Anim_Alpha = 0;
			}
			
		}

		if (inp.cancel) {
			if (wp->Depth < 3) wp->Work_Select[wp->Depth] = 0;
			if (wp->Depth == 0)g_GameState = GAME_BASE;
			if (wp->Depth == 1)wp->Depth = 0;
		}
	}

	void Power_Work_Anim() {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Anim_Alpha);
		DrawBox(0, 0, scale.Width, scale.Height, 0x000000, 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

private:
	int Depth = 0;
	const char Selct_String[2][17] = { "����","�X�ɏo��" };
	const char Selct_String2[2][17] = { "�͎d��","�H�����B" };
	const char Selct_String3[3][17] = { "������x����","���̎d���ɂ���","�X�֖߂�" };
	const char Selct_Num[3] = { 2,2,3 };
	int Work_Select[3] = {0};
	unsigned int color = 0xffffff;
	unsigned int white_color = 0xffffff;
	unsigned int blue_color = 0x6666ff;
};