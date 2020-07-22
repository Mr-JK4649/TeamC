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

	int item_select = 0;				//�A�C�e���ꗗ�悤�̓Y����
	int item_select2 = 0;				//�A�C�e���I���E�B���h�E�p�̓Y����
	//int item_select_window_height = 0;	//�A�C�e���I���̃��j���[�̍���

	/*���j���[�̕\��*/
	void Draw() {
		const float w = scale.Width, w5 = w / 5;
		const float h = scale.Height, h4 = h / 4;
		const int size = scale.Width / 100;
		
		/*���j���[�̘g�\��*/
		Draw_Menu_Box(w, w5, h, h4);

		SetFontSize(size * 2);

		/*�����j���[�̕���*/
		for (int i = 0; i < 3; i++) {

			if (menu_num == i) color = blue_color;

			if(g_GameState == GAME_BASE/* || g_GameState == GAME_DUNGEON && i != 2*/)
				str.SuperString(10 + (w5 - 10) / 2, 20 + (size * 4) * i, Menu_String[i], color, 1, size * 2);
			else
				str.SuperString(10 + (w5 - 10) / 2, 20 + (size * 4) * i, Menu_String[i+1], color, 1, size * 2);

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

		SetFontSize(16);

		/*���j���[���ł̑���*/
		Update();

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
				if (inp.space && item_kind != 0)isItem_Select_Menu = true;
				if (inp.cancel) isItem_Menu = false;

			}

		}
		else if (isGage_Menu) {
			if (inp.cancel) isGage_Menu = false;
		}
		else if (isMove_Scene) {
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
			}

			if (inp.start || inp.cancel) {
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
			DrawRoundRect(w5 * 2 + 5, h4, w5 * 3, h4 * 2 + 20, 10, 10, 0x444444, 1);
			DrawRoundRect(w5 * 2 + 5, h4, w5 * 3, h4 * 2 + 20, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w5 * 2 + 6, h4 + 1, w5 * 3 - 1, h4 * 2 + 19, 10, 10, 0xffffff, 0);
		}

		/*�A�C�e���I���̂�[��*/
		if (isItem_Select_Menu) {
			DrawRoundRect(w5 * 3 + 5, h4 + 20 * item_select, w5 * 4 - 20, h4 * 2 + 20 * item_select, 10, 10, 0x444444, 1);
			DrawRoundRect(w5 * 3 + 5, h4 + 20 * item_select, w5 * 4 - 20, h4 * 2 + 20 * item_select, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w5 * 3 + 6, h4 + 20 * item_select + 1, w5 * 4 - 21, h4 * 2 + 20 * item_select - 1, 10, 10, 0xffffff, 0);
		}
		
	}

	void Item_Kind(int item_num) {
		item_kind = item_num;
	}

private:
	char Menu_String[4][20] = {"�����i������","����̊m�F","�^�C�g���֖߂�","�X�֖߂�"};
	char Item_Select_String[2][14] = { "��������/�g��","�̂Ă�" };
	short color = 0;
	int menu_num = 0;
	int item_kind = 0;
	const unsigned int white_color = 0xffffff;
	const unsigned int blue_color = 0x6666ff;
};