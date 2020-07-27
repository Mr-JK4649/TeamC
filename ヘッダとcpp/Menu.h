#pragma once
#include "DxLib.h"
#include <stdio.h>

#include "header.h"
#include "string.h"

/*���j���[�\���p�̂��*/
struct Menu {
	bool isMenu = false;
	bool isItem_Menu = false;			//�����i�m�F
	bool isItem_Select_Menu = false;	//�A�C�e���ꗗ�őI���������̃��j���[
	bool isItem_Delete = false;			//�A�C�e���̂Ă�t���O
	bool isItem_Equip = false;			//�A�C�e�������t���O
	bool isGage_Menu = false;			//�Q�[�W�m�F
	bool isMove_Scene = false;			//�V�[���ړ�

	bool isBuilding_Enter = false;		//�����ɓ���t���O
	int Enter_Num = 0;					//�����̎��
	int Enter_Select = 0;				//�m�F�E�B���h�E�̑I���Ŏg�����
	char Building_Name[3][20] = { "�u�d���Љ�v","�u�G�݉��v","�u����v" };


	int item_select = 0;				//�A�C�e���ꗗ�悤�̓Y����
	int item_select2 = 0;				//�A�C�e���I���E�B���h�E�p�̓Y����
	//int item_select_window_height = 0;	//�A�C�e���I���̃��j���[�̍���

	/*���j���[�̕\��*/
	void Draw() {
		const float w = scale.Width, w5 = w / 5;
		const float h = scale.Height, h4 = h / 4;
		const int size = scale.Width / 100;
		
		/*���j���[�̘g�\��*/
		if(isMenu)
			Draw_Menu_Box(w, w5, h, h4);

		
		SetFontSize(size * 2);

		if (isMenu) {

			/*�����j���[�̕���*/
			for (int i = 0; i < 3; i++) {

				if (menu_num == i) color = blue_color;

				if (g_GameState == GAME_BASE/* || g_GameState == GAME_DUNGEON && i != 2*/)
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

			/*�Q�[�W�̂�[��*/
			if (isGage_Menu)
				DrawGage(w, w5, h, h4);

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
				if (--Enter_Select < 0) Enter_Select = 1;
			}
			if (inp.f_right) {
				if (++Enter_Select > 1) Enter_Select = 0;
			}

			if (inp.space) {
				if (Enter_Select == 1) {
					if (Enter_Num == 0)g_GameState = GAME_WORK;	//�d���Љ
					if (Enter_Num == 1)g_GameState = GAME_SHOP;	//���X
					if (Enter_Num == 2)g_GameState = GAME_HOME;	//����

				}
			}

			if (inp.cancel) { isBuilding_Enter = false; Enter_Select = 0; }

		}

		SetFontSize(16);

		/*���j���[���ł̑���*/
		if(isMenu)Update();

	}

	void Update() {

		if (isItem_Menu) {

			if (isItem_Select_Menu) {								//�A�C�e����I�������Ƃ�
				if (inp.f_up) {
					if (--item_select2 < 0) item_select2 = 1;
				}
				if (inp.f_down) {
					if (++item_select2 > 1) item_select2 = 0;
				}
				if (inp.space) {
					if (item_select2 == 0) isItem_Equip = true;		//�A�C�e���𑕔�����
					if (item_select2 == 1) isItem_Delete = true;	//�A�C�e�����̂Ă�	
					isItem_Select_Menu = false;

				}
				if (inp.cancel) isItem_Select_Menu = false;
			}
			else {													//�A�C�e����I�����ĂȂ��Ƃ�

				if (inp.f_up) {
					if (--item_select < 0) item_select = 9;
				}
				if (inp.f_down) {
					if (++item_select > 9) item_select = 0;
				}
				if (inp.space && item_kind != 0) { isItem_Select_Menu = true; item_select2 = 0; }
				if (inp.cancel) isItem_Menu = false;

			}

		}
		else if (isGage_Menu) {
			if (inp.cancel) isGage_Menu = false;
		}
		else if (isMove_Scene) {

			if (inp.f_left) {
				if (--item_select < 0) item_select = 1;
			}
			if (inp.f_right) {
				if (++item_select > 1) item_select = 0;
			}

			if (inp.space) {
				if (item_select == 0) isMove_Scene = false;
				if (item_select == 1 && g_GameState == GAME_BASE) {
					g_GameState = GAME_TITLE;
					item_select = 0;
					menu_num = 0;
					isMove_Scene = false;
					isMenu = false;
				}
				//if (item_select == 1 && g_GameState == GAME_DUNGEON) g_GameState = GAME_BASE;
				
			}

			if (inp.cancel)isMove_Scene = false;
		}
		else {
			if (inp.f_up) {
				if (--menu_num < 0) menu_num = 2;
			}
			if (inp.f_down) {
				if (++menu_num > 2) menu_num = 0;
			}

			if (inp.space) {
				switch (menu_num) {
				case 0: isItem_Menu = true;		break;
				case 1:	isGage_Menu = true;		break;
				case 2: isMove_Scene = true;	break;
				}
				item_select = 0;
			}

			if (inp.cancel) {
				isMenu = false;
			}
		}
		
	}

	/*�X�e�[�^�X��\������g*/
	void Draw_Menu_Box(float w,float w5, float h,float h4) {

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
		DrawRoundRect(5 + 1, 6, w5-1, h4 - 1, 10, 10, 0xffffff, 0);

		/*�A�C�e���̂�[�ƃQ�[�W�̂�[��*/
		if (isItem_Menu || isGage_Menu) {
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
		
	}

	/*�Q�[�W��\��������*/
	void DrawGage(float w, float w5, float h, float h4) {
		const int Gage_Height = h / 30;

		for (int i = 0; i < 5; i++) {
			
			DrawString(w / 100.0f * 22, h / 100.0f * 27 + Gage_Height * 3 * i, Gage_Name[i], Gage_Color[i], 1);
			DrawBox(w5 + 20, (h4 + Gage_Height * 3 * i + 40), (w5 + 20) + Gage[i] * (w5 * 2) / 120, (h4 + Gage_Height * 3 * i + 40) + Gage_Height, Gage_Color[i], 1);
			DrawBox(w5 + 20, (h4 + Gage_Height * 3 * i + 40), (w5 + 20) + 100 * (w5 * 2) / 120, (h4 + Gage_Height * 3 * i + 40) + Gage_Height, Gage_Color[i], 0);

		}
		
	}
	
	/*�A�C�e���̎�ނ��擾*/
	void Item_Kind(int item_num) {
		item_kind = item_num;
	}

	/*���W�x�̎擾*/
	void Input_Gage(int time,int dev) {
		Gage[0] = time / 600;
		Gage[2] = dev;
		Inclease();
	}

	void Inclease() {
		
	}

private:
	char Menu_String[4][20] = {"�����i������","����̊m�F","�^�C�g���֖߂�","�X�֖߂�"};	//���j���[���C���[1�ŕ\��������
	char Item_Select_String[2][14] = { "��������/�g��","�̂Ă�" };							//�A�C�e���ꗗ�ŃA�C�e���I�����ɕ\��������
	short color = 0;																		//���݂̈ʒu��\���̂Ɏg�����
	int menu_num = 0,menu_num2 = 0;															//���j���[�I���Ɏg�����
	int item_kind = 0;																		//���݂̈ʒu�̃A�C�e�����������ׂĂ��炤���
	const unsigned int white_color = 0xffffff;												//��
	const unsigned int blue_color = 0x6666ff;												//��
	int Gage[5] = { 10,25,45,75,100 };														//�Q�[�W�̒l��ۑ�������
	char Gage_Name[5][11] = { "�l���Q�[�W","�����Q�[�W","���W�Q�[�W","�H���Q�[�W","���̓Q�[�W" };	//�Q�[�W�̖��O
	unsigned int Gage_Color[5] = { 0xffff00,0x880088,0x00ffff,0x00ff00,0xff0000 };
};

extern Menu menu;