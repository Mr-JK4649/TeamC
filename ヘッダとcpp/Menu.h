#pragma once
#include "DxLib.h"
#include <stdio.h>

#include "header.h"
#include "string.h"
#include "Input.h"
#include "Source.h"

/*���j���[�\���p�̂��*/
struct Menu {
	bool isMenu = false;
	bool isItem_Menu = false;			//�����i�m�F
	bool isItem_Select_Menu = false;	//�A�C�e���ꗗ�őI���������̃��j���[
	bool isItem_Delete = false;			//�A�C�e���̂Ă�t���O
	bool isItem_Equip = false;			//�A�C�e�������t���O
	bool isGage_Menu = false;			//�Q�[�W�m�F
	bool isMove_Scene = false;			//�V�[���ړ�
	bool Move_Scene = false;			//�V�[���ړ����̏����p
	int scene_t = 0;					//�ړ���̃V�[����ۑ�
	bool isTIPS = false;				//���j���[��TIPS�̕\��

	bool isBuilding_Enter = false;		//�����ɓ���t���O
	int Enter_Num = 0;					//�����̎��
	int Enter_Select = 0;				//�m�F�E�B���h�E�̑I���Ŏg�����
	char Building_Name[4][20] = { "�u�d���Љ�v","�u�G�݉��v","�u����v","�u�J�W�m�v"};

	bool Result_DWork_Flg = false;		//�͎d���̕�V��\��
	bool Result_FWork_Flg = false;		//���B�̕�V��\��
	int Result_Work_Money = 0;			//�d���œ�����V
	int Result_Work_Par[2] = {2};		//�d���œ����Q�[�W�̑���

	int item_select = 0;				//�A�C�e���ꗗ�悤�̓Y����
	int item_select2 = 0;				//�A�C�e���I���E�B���h�E�p�̓Y����

	bool isTutorial = true;				//�`���[�g���A��
	int Tutorial_Select = 0;			//�`���[�g���A���̑I����

	/*���j���[�f�ނ̏�����*/
	void Init() {
		SelectMove_SE = LoadSoundMem("sounds/�J�[�\���ړ�.mp3");
		Select_SE = LoadSoundMem("sounds/���j���[����.mp3");
		Cansel_SE = LoadSoundMem("sounds/���j���[�L�����Z��.mp3");
	}

	/*���j���[�̕\��*/
	void Draw() {
		const float w = scale.Width, w5 = w / 5;
		const float h = scale.Height, h4 = h / 4;
		const int size = scale.Width / 100;
		
		/*���j���[�f�ނ̏�����*/
		if (Init_Flg) { Init(); Init_Flg = false; }

		/*���j���[�̘g�\��*/
		Draw_Menu_Box(w, w5, h, h4);

		
		SetFontSize(size * 2);

		if (isMenu && !isTIPS) {

			/*�����j���[�̕���*/
			for (int i = 0; i < 3; i++) {

				if (menu_num == i) color = blue_color;

				if (g_GameState == GAME_BASE || g_GameState == GAME_DUNGEON && i != 2)
					str.SuperString(10 + (w5 - 10) / 2, 20 + (size * 4) * i, Menu_String[i], color, 1, size * 2);
				else
					str.SuperString(10 + (w5 - 10) / 2, 20 + (size * 4) * i, Menu_String[i + 1], color, 1, size * 2);

				color = white_color;
			}

			/*�A�C�e���I���̃��j���[*/
			if (isItem_Select_Menu) {
				for (int i = 0; i < 2; i++) {
					unsigned int l_color = 0xffffff;
					if (i == item_select2) l_color = 0x6666ff;

					DrawString(w5 * 3 + 20, (h4 + size * 4 * i) + item_select * 20 + 26, Item_Select_String[i], l_color, 1);

					l_color = 0xffffff;
				}
			}

			/*�V�[���ړ��̂��*/
			if (isMove_Scene) {
				str.SuperString(w / 2, h4 + 5, "�{���ɖ߂�܂����H", 0xffffff, 1, size * 2);
				if (item_select == 0) color = blue_color;
				str.SuperString(w / 2, h4 + 5 + size * 2, "�������@�@�@�@�@", color, 1, size * 2);
				color = white_color;
				if (item_select == 1) color = blue_color;
				str.SuperString(w / 2, h4 + 5 + size * 2, "�@�@�@�@�@�@�͂�", color, 1, size * 2);
				color = white_color;
			}

		}

		if (isBuilding_Enter) {
			DrawRoundRect(w5 + 5, h4, w5 * 4, h4 * 2 + 20, 10, 10, 0x444444, 1);
			DrawRoundRect(w5 + 5, h4, w5 * 4, h4 * 2 + 20, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w5 + 6, h4 + 1, w5 * 4 - 1, h4 * 2 + 19, 10, 10, 0xffffff, 0);

			str.SuperString(w / 2, h4 + 5, Building_Name[Enter_Num], 0xffffff, 1, size * 2);
			str.SuperString(w / 2, h4 + 5 + size * 2, "�ɓ���܂����H", 0xffffff, 1, size * 2);
			if (Enter_Select == 0) color = blue_color;
			str.SuperString(w / 2, h4 + 5 + size * 6, "�������@�@�@�@�@", color, 1, size * 2);
			color = white_color;
			if (Enter_Select == 1) color = blue_color;
			str.SuperString(w / 2, h4 + 5 + size * 6, "�@�@�@�@�@�@�͂�", color, 1, size * 2);
			color = white_color;

			if (inp.f_left) {
				PlaySoundMem(SelectMove_SE, DX_PLAYTYPE_BACK, TRUE);
				if (--Enter_Select < 0) Enter_Select = 1;
			}
			if (inp.f_right) {
				PlaySoundMem(SelectMove_SE, DX_PLAYTYPE_BACK, TRUE);
				if (++Enter_Select > 1) Enter_Select = 0;
			}

			if (inp.space) {
				if (Enter_Select == 0) {
					PlaySoundMem(Cansel_SE, DX_PLAYTYPE_BACK, TRUE);
					scene_t = g_GameState;
				}
				if (Enter_Select == 1) {
					PlaySoundMem(Select_SE, DX_PLAYTYPE_BACK, TRUE);
					if (Enter_Num == 0)scene_t = GAME_WORK;		//�d���Љ
					if (Enter_Num == 1)scene_t = GAME_SHOP;		//���X
					if (Enter_Num == 2)scene_t = GAME_HOME;		//����
					if (Enter_Num == 3)scene_t = GAME_CASINO;	//�J�W�m
				}
				Move_Scene = true;
			}

			if (inp.cancel) {
				PlaySoundMem(Cansel_SE, DX_PLAYTYPE_BACK, TRUE);
				scene_t = g_GameState;
				isBuilding_Enter = false;
				Enter_Select = 0;
			}

		}

		if (Result_DWork_Flg || Result_FWork_Flg) {
			DrawRoundRect(5, h - h4, w - 5, h - 5, 10, 10, 0x444444, 1);
			DrawRoundRect(5, h - h4, w - 5, h - 5, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(6, h - (h4 - 1), w - 6, h - 6, 10, 10, 0xffffff, 0);
			str.SuperString(w / 2, h - (h / 10), "�n�j", 0xff0000, 1, size * 2);
			/*if (Result_DWork_Flg) {
				DrawFormatString(10, (h - h4) + 5, 0xffffff, "�X�̔��W�ɋ��͂������ɂ��A�ȉ��̕�V�𓾂��B\n�����@+%9d�f\n���W�x+%9d��", Result_Work_Money, 5);
			}
			if (Result_FWork_Flg) {
				DrawFormatString(10, (h - h4) + 5, 0xffffff, "�H�����B���������ɂ��A�ȉ��̕�V�𓾂��B\n�����@+%9d�f\n�H���@+%9d��", Result_Work_Money, 5);
			}*/

			if (Result_FWork_Flg || Result_DWork_Flg) {
				DrawFormatString(10, (h - h4) + 5, 0xffffff, "�d�����������ɂ��A�ȉ��̕�V�𓾂��B\n�����@+%9d�f\n���W�x+%9d��\n�H���@+%9d��", Result_Work_Money, Result_Work_Par[0],Result_Work_Par[1]);

			}

			if (inp.space) {
				PlaySoundMem(Select_SE, DX_PLAYTYPE_BACK, TRUE);
				Result_Work_Money = 0;
				Result_Work_Par[0] = 0;
				Result_Work_Par[1] = 0;
				Result_DWork_Flg = false;
				Result_FWork_Flg = false;
			}
		}

		if (isTIPS) {

			for (int i = 0; i < 7; i++) {

				if (TIPS_Select[0] == i) color = blue_color;

				str.SuperString(20, 20 + (size * 4) * i, TIPS_String[i], color, 0, size * 2);

				color = white_color;
			}
			
			if (TIPS_Depth == 1) {
				DrawExtendGraph(w / 100.0f * 22, h / 100.0f * 4, w / 100.0f * 79, h / 100.0f * 82, base.Tips_img[TIPS_Select[0]][TIPS_Select[1]], 1);
				DrawFormatString(w/100.0f * 67, h/100.0f * 85, 0xffffff, "Pages %d / %d", TIPS_Select[1] + 1, TIPS_Select_Pages[TIPS_Select[0]]);
			}
		}

		SetFontSize(16);

		/*���j���[���ł̑���*/
		if(isMenu || isGage_Menu)Update();

	}

	/*���j���[�̑���*/
	void Update() {

		if (isGage_Menu) {
			if (inp.cancel) {
				PlaySoundMem(Cansel_SE, DX_PLAYTYPE_BACK, TRUE);
				isGage_Menu = false;
			}
		}
		else if (isItem_Menu) {

			if (isItem_Select_Menu) {								//�A�C�e����I�������Ƃ�
				if (inp.f_up) {
					PlaySoundMem(SelectMove_SE, DX_PLAYTYPE_BACK, TRUE);
					if (--item_select2 < 0) item_select2 = 1;
				}
				if (inp.f_down) {
					PlaySoundMem(SelectMove_SE, DX_PLAYTYPE_BACK, TRUE);
					if (++item_select2 > 1) item_select2 = 0;
				}
				if (inp.space) {
					PlaySoundMem(Select_SE, DX_PLAYTYPE_BACK, TRUE);
					if (item_select2 == 0) isItem_Equip = true;		//�A�C�e���𑕔�����
					if (item_select2 == 1) isItem_Delete = true;	//�A�C�e�����̂Ă�	
					isItem_Select_Menu = false;

				}
				if (inp.cancel) {
					PlaySoundMem(Cansel_SE, DX_PLAYTYPE_BACK, TRUE);
					isItem_Select_Menu = false;
				}
			}
			else {													//�A�C�e����I�����ĂȂ��Ƃ�

				if (inp.f_up) {
					PlaySoundMem(SelectMove_SE, DX_PLAYTYPE_BACK, TRUE);
					if (--item_select < 0) item_select = 9;
				}
				if (inp.f_down) {
					PlaySoundMem(SelectMove_SE, DX_PLAYTYPE_BACK, TRUE);
					if (++item_select > 9) item_select = 0;
				}
				if (inp.space && item_kind != 0) {
					PlaySoundMem(Select_SE, DX_PLAYTYPE_BACK, TRUE);
					isItem_Select_Menu = true;
					item_select2 = 0;
				}
				if (inp.cancel) {
					PlaySoundMem(Cansel_SE, DX_PLAYTYPE_BACK, TRUE);
					isItem_Menu = false;
				}

			}

		}
		else if (isTIPS) {
			if (TIPS_Depth == 0) {
				if (inp.f_up) {
					PlaySoundMem(SelectMove_SE, DX_PLAYTYPE_BACK, TRUE);
					if (--TIPS_Select[TIPS_Depth] < 0) TIPS_Select[TIPS_Depth] = 6;
				}
				if (inp.f_down) {
					PlaySoundMem(SelectMove_SE, DX_PLAYTYPE_BACK, TRUE);
					if (++TIPS_Select[TIPS_Depth] > 6) TIPS_Select[TIPS_Depth] = 0;
				}

				if (inp.space) {
					PlaySoundMem(Select_SE, DX_PLAYTYPE_BACK, TRUE);
					TIPS_Depth = 1;
				}

				if (inp.cancel) {
					PlaySoundMem(Cansel_SE, DX_PLAYTYPE_BACK, TRUE);
					TIPS_Select[TIPS_Depth] = 0;
					isTIPS = false;
				}
			}
			else if (TIPS_Depth == 1) {
				if (inp.f_left) {
					PlaySoundMem(SelectMove_SE, DX_PLAYTYPE_BACK, TRUE);
					if (--TIPS_Select[TIPS_Depth] < 0) TIPS_Select[TIPS_Depth] = TIPS_Select_Pages[TIPS_Select[0]] - 1;
				}
				if (inp.f_right) {
					PlaySoundMem(SelectMove_SE, DX_PLAYTYPE_BACK, TRUE);
					if (++TIPS_Select[TIPS_Depth] > TIPS_Select_Pages[TIPS_Select[0]] - 1) TIPS_Select[TIPS_Depth] = 0;
				}

				if (inp.cancel) {
					TIPS_Select[TIPS_Depth] = 0;
					TIPS_Depth = 0;
				}
			}
		}
		else if (isMove_Scene) {

			if (inp.f_left) {
				PlaySoundMem(SelectMove_SE, DX_PLAYTYPE_BACK, TRUE);
				if (--item_select < 0) item_select = 1;
			}
			if (inp.f_right) {
				PlaySoundMem(SelectMove_SE, DX_PLAYTYPE_BACK, TRUE);
				if (++item_select > 1) item_select = 0;
			}

			if (inp.space) {
				PlaySoundMem(Select_SE, DX_PLAYTYPE_BACK, TRUE);
				if (item_select == 0) isMove_Scene = false;
				else if (item_select == 1 && g_GameState == GAME_BASE) {
					scene_t = GAME_TITLE;
					item_select = 0;
					menu_num = 0;
					isMove_Scene = false;
					isMenu = false;
					Move_Scene = true;
				}
				else if (item_select == 1 && g_GameState == GAME_DUNGEON) {
					scene_t = GAME_BASE;
					item_select = 0;
					menu_num = 0;
					isMove_Scene = false;
					isMenu = false;
					Move_Scene = true;
				}
				
			}

			if (inp.cancel) {
				PlaySoundMem(Cansel_SE, DX_PLAYTYPE_BACK, TRUE);
				isMove_Scene = false;
			}
		}
		else {
			if (inp.f_up) {
				PlaySoundMem(SelectMove_SE, DX_PLAYTYPE_BACK, TRUE);
				if (--menu_num < 0) menu_num = 2;
			}
			if (inp.f_down) {
				PlaySoundMem(SelectMove_SE, DX_PLAYTYPE_BACK, TRUE);
				if (++menu_num > 2) menu_num = 0;
			}

			if (inp.space) {
				PlaySoundMem(Select_SE, DX_PLAYTYPE_BACK, TRUE);
				switch (menu_num) {
				case 0: isItem_Menu = true;		break;
				case 1:	isTIPS = true;			break;
				case 2: isMove_Scene = true;	break;
				}
				item_select = 0;
			}

			if (inp.cancel) {
				PlaySoundMem(Cansel_SE, DX_PLAYTYPE_BACK, TRUE);
				isMenu = false;
			}
		}
		
	}

	/*�X�e�[�^�X��\������g*/
	void Draw_Menu_Box(float w,float w5, float h,float h4) {

		const float w100 = w / 100.0f;
		const float h100 = h / 100.0f;

		if (isMenu && !isTIPS) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			DrawBox(0, 0, scale.Width, scale.Height, 0x000000, 1);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

			//��i�@�������A���W�x�A��������
			DrawRoundRect(w - w5, 5, w - 5, h4, 10, 10, 0x444444, 1);
			DrawRoundRect(w - w5, 5, w - 5, h4, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w - w5 + 1, 6, w - 6, h4 - 1, 10, 10, 0xffffff, 0);

			//���i�@���x���A�o���l�A�̗́A�U���́A�h���
			DrawRoundRect(w - w5, (h4 + 5), w - 5, (h4 + 5) + h4 * 1, 10, 10, 0x444444, 1);
			DrawRoundRect(w - w5, (h4 + 5), w - 5, (h4 + 5) + h4 * 1, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w - w5 + 1, (h4 + 5) + 1, w - 6, (h4 + 5) + h4 * 1 - 1, 10, 10, 0xffffff, 0);

			//���i	����
			DrawRoundRect(w - w5, (h4 + 5) + h4 * 1 + 5, w - 5, (h4 + 5) + h4 * 2, 10, 10, 0x444444, 1);
			DrawRoundRect(w - w5, (h4 + 5) + h4 * 1 + 5, w - 5, (h4 + 5) + h4 * 2, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w - w5 + 1, (h4 + 5) + h4 * 1 + 6, w - 6, (h4 + 5) + h4 * 2 - 1, 10, 10, 0xffffff, 0);

			/*����*/
			DrawRoundRect(5, 5, w5, h4, 10, 10, 0x444444, 1);
			DrawRoundRect(5, 5, w5, h4, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(5 + 1, 6, w5 - 1, h4 - 1, 10, 10, 0xffffff, 0);
		}

		/*�A�C�e���̂�[�ƃQ�[�W�̂�[��*/
		if (isItem_Menu) {
			DrawRoundRect(w5 * 1 + 5, h4, w5 * 3, h4 * 3 + 20, 10, 10, 0x444444, 1);
			DrawRoundRect(w5 * 1 + 5, h4, w5 * 3, h4 * 3 + 20, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w5 * 1 + 6, h4 + 1, w5 * 3 - 1, h4 * 3 +19, 10, 10, 0xffffff, 0);
		}

		/*�V�[���ړ��̂�[��*/
		if (isMove_Scene) {
			DrawRoundRect(w5 + 5, h4, w5 * 4, h4 * 2 + 20, 10, 10, 0x444444, 1);
			DrawRoundRect(w5 + 5, h4, w5 * 4, h4 * 2 + 20, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w5 + 6, h4 + 1, w5 * 4 - 1, h4 * 2 + 19, 10, 10, 0xffffff, 0);
		}

		/*�A�C�e���I���̂�[��*/
		if (isItem_Select_Menu) {
			DrawRoundRect(w5 * 3 + 5, h4 + 20 * item_select, w5 * 4 - 20, h4 * 2 + 20 * item_select, 10, 10, 0x444444, 1);
			DrawRoundRect(w5 * 3 + 5, h4 + 20 * item_select, w5 * 4 - 20, h4 * 2 + 20 * item_select, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w5 * 3 + 6, h4 + 20 * item_select + 1, w5 * 4 - 21, h4 * 2 + 20 * item_select - 1, 10, 10, 0xffffff, 0);
		}

		/*TIPS�\���̂�[��*/
		if (isTIPS) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
			DrawBox(0, 0, scale.Width, scale.Height, 0x000000, 1);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

			DrawRoundRect(w100, h100, w100 * 20, h100 * 70, 10, 10, 0x444444, 1);
			DrawRoundRect(w100, h100, w100 * 20, h100 * 70, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w100 + 1, h100 + 1, w100 * 20 - 1, h100 * 70 - 1, 10, 10, 0xffffff, 0);
			if (TIPS_Depth == 1) {
				DrawRoundRect(w100 * 21, h100, w100 * 80, h100 * 90, 10, 10, 0x444444, 1);
				DrawRoundRect(w100 * 21, h100, w100 * 80, h100 * 90, 10, 10, 0xaaaaaa, 0);
				DrawRoundRect(w100 * 21 + 1, h100 + 1, w100 * 80 - 1, h100 * 90 - 1, 10, 10, 0xffffff, 0);
			}
		}
		
	}

	/*�Q�[�W��\��������*/
	void DrawGage(float w100, float h100) {
		const int Gage_Height = scale.Height / 30;			//�Q�[�W�̕�
		Gage_Max[0] = Base_Status_Copy[1] * 2 + 100;		//�l���Q�[�W�̃}�b�N�X�l��ݒ�
		Gage[2] = Base_Status_Copy[1];						//���W�x

		str.SuperString(w100 * 20.5, h100 * 41.5f, "�Q�[�W�V�X�e��", 0xccccff,1,scale.Width / 100 * 3);

		for (int i = 0; i < 5; i++) {
			
			//DrawString(w100 * 22, h100 * 27 + Gage_Height * 3 * i, Gage_Name[i], Gage_Color[i], 1);
			str.SuperString(w100 * 2, h100 * 47.5f + Gage_Height * 3 * i, Gage_Name[i], Gage_Color[i], 0, scale.Width / 100 * 2);
			DrawBox(w100 * 2, (h100 * 51 + Gage_Height * 3 * i), (w100 * 2) + (w100 * 37) * (Gage[i] / Gage_Max[i]), (h100 * 51 + Gage_Height * 3 * i) + Gage_Height, Gage_Color[i], 1);
			DrawBox(w100 * 2, (h100 * 51 + Gage_Height * 3 * i), (w100 * 2) + (w100 * 37), (h100 * 51 + Gage_Height * 3 * i) + Gage_Height, Gage_Color[i], 0);

		}
		
	}
	
	/*�A�C�e���̎�ނ��擾*/
	void Item_Kind(int item_num) {
		item_kind = item_num;
	}

	/*�L�����̃X�e�[�^�X�������Ă���z*/
	void B_Status_C(int num, int para) {
		Base_Status_Copy[num] = para;
	}

	/*�Q�[�W�̗ʂ�Ԃ�*/
	float Return_Gage_Para(int num) {
		
		return Gage[num];
	}

	/*�Q�[�W�̍ő�l��Ԃ�*/
	float Return_Gage_Max(int num) {

		return Gage_Max[num];
	}

	/*�Q�[�W���㏸��������*/
	void Inclease_Gage(int num,int para) {
		Gage[num] += para;
		if (Gage[num] < 0) Gage[num] = 0;
	}

	/*�Q�[�W�̍ő�l�𑝕�������z*/
	void Incleace_Gage_Max(int num, int para) {
		Gage_Max[num] += para;
	}

	/*�d���̌��ʂ�����*/
	void Input_Work_Result(int money, int dev, int food) {
		Result_Work_Money += money;
		Result_Work_Par[0] += dev;
		Result_Work_Par[1] += food;
	}

	/*�d���̕�V�\��*/
	void Result_Work() {
		const int w = scale.Width;
		const int h = scale.Height, h4 = scale.Height / 4;
		DrawRoundRect(5, h - h4, w - 5, h - 5, 10, 10, 0x444444, 1);
		DrawRoundRect(5, h - h4, w - 5, h - 5, 10, 10, 0xaaaaaa, 0);
		DrawRoundRect(6, h - (h4 - 1), w - 6, h - 6, 10, 10, 0xffffff, 0);

	}

private:
	char Menu_String[4][20] = {"�����i������","�s�h�o�r","�^�C�g���֖߂�","�X�֖߂�"};		//���j���[���C���[1�ŕ\��������
	char Item_Select_String[2][14] = { "��������/�g��","�̂Ă�" };							//�A�C�e���ꗗ�ŃA�C�e���I�����ɕ\��������
	short color = 0;																		//���݂̈ʒu��\���̂Ɏg�����
	int menu_num = 0,menu_num2 = 0;															//���j���[�I���Ɏg�����
	int item_kind = 0;																		//���݂̈ʒu�̃A�C�e�����������ׂĂ��炤���
	const unsigned int white_color = 0xffffff;												//��
	const unsigned int blue_color = 0x6666ff;												//��
	float Gage[5] = { 0,0,0,50,0 };															//�Q�[�W�̒l��ۑ�������
	float Gage_Max[5] = { 100,100,100,100,100 };														//�e�Q�[�W�̃}�b�N�X�̒l
	char Gage_Name[5][11] = { "�l���Q�[�W","�����Q�[�W","���W�Q�[�W","�H���Q�[�W","���̓Q�[�W" };		//�Q�[�W�̖��O
	unsigned int Gage_Color[5] = { 0xffff00,0x880088,0x00ffff,0x00ff00,0xff0000 };						//�e�Q�[�W�̐F
	char TIPS_String[7][21] = { "������@","�ړI�ƃ��[��","�L�����N�^�[","���_�łł��鎖","���łł��鎖","�_���W����","�Q�[�W" };	//TIPS�̕�����
	int TIPS_Depth = 0;																	//TIPS���j���[�̂�ׂ�
	int TIPS_Select_Pages[7] = { 2,2,4,5,5,5,4 };										//�eTIPS�̃y�[�W��
	int TIPS_Select[2] = {0};															//TIPS�I���Ɗe�y�[�W�p
	int Base_Status_Copy[3] = { 0 };

	bool Init_Flg = true;

	int SelectMove_SE = 0;
	int Select_SE = 0;
	int Cansel_SE = 0;
};

extern Menu menu;