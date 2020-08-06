#pragma once

#include "character.h"
#include "Menu.h"

Shop sh;

struct Shopping {

	bool Confirm_Buy = false;				//�w�����邩�ۂ����m�F����E�B���h�E���o�����߂̂��
	bool Confirm_Sell = false;				//���p���邩�ۂ����m�F����E�B���h�E���������

	bool Search_No_Item = false;			//��̂̃A�C�e����T���Ă�����ォ�珇�Ɉ�ԍŏ�
	bool Buy_Item = false;					//�A�C�e���w���t���O

	bool Not_Enough_Space = false;			//�A�C�e���ɋ󂫂��Ȃ�
	bool Not_Enough_Cash = false;			//������������Ȃ�

	static void Draw(Shopping* shop) {

		//SetFontSize(16);

		if (shop->Depth != 5)DrawExtendGraph(0, 0, ch.w, ch.h, sh.background[shop->Depth_Menu_Select[shop->Depth]], 1);
		else				DrawExtendGraph(0, 0, ch.w, ch.h, sh.background[5], 1);
		if (shop->Depth < 2) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			DrawBox(ch.w / 2, 0, ch.w, ch.h, 0x000000, 1);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}

		/*�I�����Ȃ����̃J�o�[*/
		if (shop->Depth == 0) {
			DrawExtendGraph(0, 0, ch.w, ch.h, sh.Cover[2], 1);
			DrawExtendGraph(0, 0, ch.w, ch.h, sh.Cover[3], 1);
			DrawExtendGraph(0, 0, ch.w, ch.h, sh.Cover[4], 1);
		}
		if (shop->Depth == 1 || shop->Depth == 3) {
			DrawExtendGraph(0, 0, ch.w, ch.h, sh.Cover[3], 1);
			DrawExtendGraph(0, 0, ch.w, ch.h, sh.Cover[4], 1);
		}
		if (shop->Depth == 4) {
			DrawExtendGraph(0, 0, ch.w, ch.h, sh.Cover[2], 1);
			DrawExtendGraph(0, 0, ch.w, ch.h, sh.Cover[3], 1);
			DrawExtendGraph(0, 0, ch.w, ch.h, sh.Cover[4], 1);
		}

		/*�I�����̕����\��*/
		if (shop->Depth < 5) {

			
			const float w100 = ch.w / 100.0f;
			const float h100 = ch.h / 100.0f;
			
			
			/*�V���b�v���̑I�����\��*/
			for (int i = 0; i < shop->Depth_Menu_Num[shop->Depth]; i++) {

				if (shop->Depth > 1) SetFontSize(ch.size * 3);
				else SetFontSize(ch.size * 4);

				DrawString((ch.w / 100.0f) * 10, (ch.h / 100.0f) * (15 + 18 * i), shop->Depth_Select_Name[shop->Depth][i], 0x000000, 1);

				SetFontSize(ch.size * 2);

				/*�l�i�̕\��*/
				if (shop->Depth == 2) DrawFormatString((ch.w / 100.0f) * 34, (ch.h / 100.0f) * (13 + 18 * i), 0x000000, "%4dG", shop->Item_Price[i]);
				if (shop->Depth == 3) DrawFormatString((ch.w / 100.0f) * 34, (ch.h / 100.0f) * (13 + 18 * i), 0x000000, "%4dG", shop->Item_Price[i+5]);
				if (shop->Depth == 4) DrawFormatString((ch.w / 100.0f) * 34, (ch.h / 100.0f) * (13 + 18 * i), 0x000000, "%4dG", shop->Item_Price[i+8]);

				/*���̓Q�[�W�Z�����ɂ��A�C�e����\��*/
				if (menu.Return_Gage_Para(4) < 50) {
					if (shop->Depth == 2 && (i == 1 || i == 2 || i == 4) || shop->Depth == 3 && (i == 1 || i == 2) || shop->Depth == 4 && i == 1) {
						DrawExtendGraph(0, 0, ch.w, ch.h, sh.Cover[i], 1);
					}
				}
				else if (menu.Return_Gage_Para(4) < 100) {
					if (shop->Depth == 2 && i == 2 || shop->Depth == 3 && i == 2) {
						DrawExtendGraph(0, 0, ch.w, ch.h, sh.Cover[i], 1);
					}
				}
			}

			SetFontSize(ch.size * 3);
			
			/*�A�C�e���̉摜�Ɛ����̕\��*/
			if (shop->Depth == 2) {
				DrawExtendGraph(w100 * 60, h100 * 10, w100 * 90, h100 * 55, sh.Weapon_img[shop->Depth_Menu_Select[shop->Depth]], 1);
				DrawString(w100 * 51, h100 * 61, shop->Weapon_Info_String[shop->Depth_Menu_Select[shop->Depth]], 0x000000, 1);
			}
			if (shop->Depth == 3) {
				DrawExtendGraph(w100 * 60, h100 * 10, w100 * 90, h100 * 55, sh.Shield_img[shop->Depth_Menu_Select[shop->Depth]], 1);
				DrawString(w100 * 51, h100 * 61, shop->Shield_Info_String[shop->Depth_Menu_Select[shop->Depth]], 0x000000, 1);
			}
			if (shop->Depth == 4) {
				DrawExtendGraph(w100 * 60, h100 * 10, w100 * 90, h100 * 55, sh.Item_img[shop->Depth_Menu_Select[shop->Depth]], 1);
				DrawString(w100 * 51, h100 * 61, shop->Item_Info_String[shop->Depth_Menu_Select[shop->Depth]], 0x000000, 1);
			}
			
			
		}

		/*�A�C�e���ꗗ���J��*/
		if (shop->Depth == 5) {

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 164);
			DrawBox(0, 0, ch.w, ch.h, 0x000000, 1);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

			DrawRoundRect(ch.w5 * 1 + 5, ch.h4, ch.w5 * 3, ch.h4 * 3 + 20, 10, 10, 0x444444, 1);
			DrawRoundRect(ch.w5 * 1 + 5, ch.h4, ch.w5 * 3, ch.h4 * 3 + 20, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(ch.w5 * 1 + 6, ch.h4 + 1, ch.w5 * 3 - 1, ch.h4 * 3 + 19, 10, 10, 0xffffff, 0);

			char item_name[51];
			unsigned int color = 0xffffff;
			SetFontSize(ch.size * 2);

			for (int i = 0; i < 10; i++) {



				switch (ch.Menu_Items_Disp(&ch, i))
				{
				case Chara::Wood_Sword:		strcpy_s(item_name, Wood_Sword.Weapon_name);	break;
				case Chara::Iron_Sword:		strcpy_s(item_name, Iron_Sword.Weapon_name);	break;
				case Chara::Excalibur:		strcpy_s(item_name, Exca_Sword.Weapon_name);	break;
				case Chara::Wood_Rod:		strcpy_s(item_name, Wood_Rod.Weapon_name);		break;
				case Chara::Iron_Rod:		strcpy_s(item_name, Iron_Rod.Weapon_name);		break;
				case Chara::Wood_Shield:	strcpy_s(item_name, Wood_Shield.Shield_name);	break;
				case Chara::Stone_Shield:	strcpy_s(item_name, Stone_Shield.Shield_name);	break;
				case Chara::Iron_Shield:	strcpy_s(item_name, Iron_Shield.Shield_name);	break;
				case Chara::Portion:		strcpy_s(item_name, "�|�[�V����");				break;
				case Chara::Tapi_MT:		strcpy_s(item_name, "�^�s�I�J�l�s");			break;
				default:					strcpy_s(item_name, "�@�@�@�@�@�@�@�@�[�[�[�@�@�@�@�@�@�@�@");		break;
				}

				if (i == shop->Depth_Menu_Select[shop->Depth]) color = 0x6666ff;

				DrawString(ch.w5 * 1 + 11, ch.h4 + 6 + (ch.size * 3) * i, item_name, color, 1);

				color = 0xffffff;
			}
		}

		/*�A�C�e���������ς��A�������͏�����������Ȃ��ꍇ�̂��*/
		if (shop->Not_Enough_Cash || shop->Not_Enough_Space) {
			DrawRoundRect(ch.w5 + 5, ch.h4, ch.w5 * 4, ch.h4 * 2 + 20, 10, 10, 0x444444, 1);
			DrawRoundRect(ch.w5 + 5, ch.h4, ch.w5 * 4, ch.h4 * 2 + 20, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(ch.w5 + 6, ch.h4 + 1, ch.w5 * 4 - 1, ch.h4 * 2 + 19, 10, 10, 0xffffff, 0);

			SetFontSize(ch.size * 3);

			if (shop->Not_Enough_Cash) {
				str.SuperString(ch.w / 2, ch.h4 + 5 + ch.size * 2, "������������܂���", 0xffffff, 1, ch.size * 2);
			}
			if (shop->Not_Enough_Space) {
				str.SuperString(ch.w / 2, ch.h4 + 5 + ch.size * 2, "�����i�������ς��ł�", 0xffffff, 1, ch.size * 2);
			}
			str.SuperString(ch.w / 2, ch.h4 + 5 + ch.size * 6, "�͂�", 0xff0000, 1, ch.size * 2);
		}

		/*�������̕\��*/
		DrawRoundRect(5, 5, ch.w5 * 2, ch.h4 / 3, 10, 10, 0x444444, 1);
		DrawRoundRect(5, 5, ch.w5 * 2, ch.h4 / 3, 10, 10, 0xaaaaaa, 0);
		DrawRoundRect(5 + 1, 6, ch.w5 * 2 - 1, ch.h4 / 3 - 1, 10, 10, 0xffffff, 0);
		SetFontSize(ch.size * 3);
		DrawFormatString(10, 10, 0xffffff, "�������@%15d�f", ch.Return_Base_Status(&ch, 0));

	}

	/*�V���b�v���ł̑���*/
	static void Update(Shopping* shop) {

		if (shop->Confirm_Buy || shop->Confirm_Sell) {

			if (inp.f_left) {
				if (--shop->Confirm_Select < 0) shop->Confirm_Select = 1;
			}
			if (inp.f_right) {
				if (++shop->Confirm_Select > 1) shop->Confirm_Select = 0;
			}

			if (inp.space) {
				if (shop->Confirm_Buy) {
					if (shop->Confirm_Select == 1) {
						if (shop->Depth == 2) {
							shop->Buy_Items(shop, shop->Depth_Menu_Select[shop->Depth] + 1, shop->Item_Price[shop->Depth_Menu_Select[shop->Depth]]);
							DrawBox(200, 200, 400, 400, 0xff0000, 1);
						}
						if (shop->Depth == 3) {
							shop->Buy_Items(shop, shop->Depth_Menu_Select[shop->Depth] + 6, shop->Item_Price[shop->Depth_Menu_Select[shop->Depth] + 5]);
							DrawBox(200, 200, 400, 400, 0x0000ff, 1);
						}
						if (shop->Depth == 4) {
							shop->Buy_Items(shop, shop->Depth_Menu_Select[shop->Depth] + 9, shop->Item_Price[shop->Depth_Menu_Select[shop->Depth] + 8]);
						}
						//if(shop->Depth == 4)Buy_Items(shop->Depth_Menu_Select[shop->Depth], shop->Item_Price[shop->Depth_Menu_Select[shop->Depth]]);
						//DrawBox(200, 200, 400, 400, 0x00ff00, 1);
					}
					shop->Confirm_Buy = false;
					shop->Confirm_Select = 0;
				}
				else if (shop->Confirm_Sell) {
					if (shop->Confirm_Select == 1) {
						ch.Pay_Money(&ch, -(shop->Item_Price[ch.Menu_Items_Disp(&ch, shop->Depth_Menu_Select[shop->Depth]) - 1] / 2));
						ch.Delete_Item(&ch, shop->Depth_Menu_Select[shop->Depth]);
					}
					shop->Confirm_Sell = false;
					shop->Confirm_Select = 0;
				}
			}

		}
		else if (shop->Not_Enough_Cash || shop->Not_Enough_Space) {
			if (inp.space) { 
				if(shop->Not_Enough_Cash)shop->Not_Enough_Cash = false;
				if (shop->Not_Enough_Space)shop->Not_Enough_Space = false;
			}
		}
		else {

			if (inp.f_up) {
				if (shop->Depth == 0 || shop->Depth == 1 || shop->Depth == 5) {
					if (--shop->Depth_Menu_Select[shop->Depth] < 0) shop->Depth_Menu_Select[shop->Depth] = shop->Depth_Menu_Num[shop->Depth] - 1;
				}
				else {
					if (shop->Depth == 2) {
						if (menu.Return_Gage_Para(4) < 50) {
							if (shop->Depth_Menu_Select[shop->Depth] == 0) shop->Depth_Menu_Select[shop->Depth] = 3;
							else if (shop->Depth_Menu_Select[shop->Depth] == 3) shop->Depth_Menu_Select[shop->Depth] = 0;
						}
						else if (menu.Return_Gage_Para(4) < 100) {
							if (shop->Depth_Menu_Select[shop->Depth] == 0) shop->Depth_Menu_Select[shop->Depth] = 4;
							else if (shop->Depth_Menu_Select[shop->Depth] == 1) shop->Depth_Menu_Select[shop->Depth] = 0;
							else if (shop->Depth_Menu_Select[shop->Depth] == 3) shop->Depth_Menu_Select[shop->Depth] = 1;
							else if (shop->Depth_Menu_Select[shop->Depth] == 4) shop->Depth_Menu_Select[shop->Depth] = 3;
						}
						else {
							if (--shop->Depth_Menu_Select[shop->Depth] < 0) shop->Depth_Menu_Select[shop->Depth] = shop->Depth_Menu_Num[shop->Depth] - 1;
						}
					}
					if (shop->Depth == 3) {
						if (menu.Return_Gage_Para(4) < 50) {
							if (shop->Depth_Menu_Select[shop->Depth] == 0) shop->Depth_Menu_Select[shop->Depth] = 0;
						}
						else if (menu.Return_Gage_Para(4) < 100) {
							if (shop->Depth_Menu_Select[shop->Depth] == 0) shop->Depth_Menu_Select[shop->Depth] = 1;
							else if (shop->Depth_Menu_Select[shop->Depth] == 1) shop->Depth_Menu_Select[shop->Depth] = 0;
						}
						else {
							if (--shop->Depth_Menu_Select[shop->Depth] < 0) shop->Depth_Menu_Select[shop->Depth] = shop->Depth_Menu_Num[shop->Depth] - 1;
						}
					}
					if (shop->Depth == 4) {
						if (menu.Return_Gage_Para(4) < 50) {
							if (shop->Depth_Menu_Select[shop->Depth] == 0) shop->Depth_Menu_Select[shop->Depth] = 0;
						}
						else {
							if (--shop->Depth_Menu_Select[shop->Depth] < 0) shop->Depth_Menu_Select[shop->Depth] = shop->Depth_Menu_Num[shop->Depth] - 1;
						}
					}
				}
			}
			if (inp.f_down) {
				if (shop->Depth == 0 || shop->Depth == 1 || shop->Depth == 5) {
					if (++shop->Depth_Menu_Select[shop->Depth] > shop->Depth_Menu_Num[shop->Depth] - 1) shop->Depth_Menu_Select[shop->Depth] = 0;
				}
				else {
					if (shop->Depth == 2) {
						if (menu.Return_Gage_Para(4) < 50) {
							if (shop->Depth_Menu_Select[shop->Depth] == 0) shop->Depth_Menu_Select[shop->Depth] = 3;
							else if (shop->Depth_Menu_Select[shop->Depth] == 3) shop->Depth_Menu_Select[shop->Depth] = 0;
						}
						else if (menu.Return_Gage_Para(4) < 100) {
							if (shop->Depth_Menu_Select[shop->Depth] == 0) shop->Depth_Menu_Select[shop->Depth] = 1;
							else if (shop->Depth_Menu_Select[shop->Depth] == 1) shop->Depth_Menu_Select[shop->Depth] = 3;
							else if (shop->Depth_Menu_Select[shop->Depth] == 3) shop->Depth_Menu_Select[shop->Depth] = 4;
							else if (shop->Depth_Menu_Select[shop->Depth] == 4) shop->Depth_Menu_Select[shop->Depth] = 0;
						}
						else {
							if (++shop->Depth_Menu_Select[shop->Depth] > shop->Depth_Menu_Num[shop->Depth] - 1) shop->Depth_Menu_Select[shop->Depth] = 0;
						}
					}
					if (shop->Depth == 3) {
						if (menu.Return_Gage_Para(4) < 50) {
							if (shop->Depth_Menu_Select[shop->Depth] == 0) shop->Depth_Menu_Select[shop->Depth] = 0;
						}
						else if (menu.Return_Gage_Para(4) < 100) {
							if (shop->Depth_Menu_Select[shop->Depth] == 0) shop->Depth_Menu_Select[shop->Depth] = 1;
							else if (shop->Depth_Menu_Select[shop->Depth] == 1) shop->Depth_Menu_Select[shop->Depth] = 0;
						}
						else {
							if (++shop->Depth_Menu_Select[shop->Depth] > shop->Depth_Menu_Num[shop->Depth] - 1) shop->Depth_Menu_Select[shop->Depth] = 0;
						}
					}
					if (shop->Depth == 4) {
						if (menu.Return_Gage_Para(4) < 50) {
							if (shop->Depth_Menu_Select[shop->Depth] == 0) shop->Depth_Menu_Select[shop->Depth] = 0;
						}
						else {
							if (++shop->Depth_Menu_Select[shop->Depth] > shop->Depth_Menu_Num[shop->Depth] - 1) shop->Depth_Menu_Select[shop->Depth] = 0;
						}
					}
				}
			}

			if (inp.cancel) {

				shop->Depth_Menu_Select[shop->Depth] = 0;

				if (shop->Depth == 0) g_GameState = GAME_BASE;
				else if (shop->Depth == 1) shop->Depth = 0;
				else if (shop->Depth == 2) shop->Depth = 1;
				else if (shop->Depth == 3) shop->Depth = 1;
				else if (shop->Depth == 4) shop->Depth = 1;
				else if (shop->Depth == 5) shop->Depth = 0;


			}

			if (inp.space) {
				if (shop->Depth == 0) {
					if (shop->Depth_Menu_Select[shop->Depth] == 0) {
						shop->Depth = 1;
					}
					if (shop->Depth_Menu_Select[shop->Depth] == 1) shop->Depth = 5;
				}
				else if (shop->Depth == 1) {
					if (shop->Depth_Menu_Select[shop->Depth] == 0) shop->Depth = 2;
					if (shop->Depth_Menu_Select[shop->Depth] == 1) shop->Depth = 3;
					if (shop->Depth_Menu_Select[shop->Depth] == 2) shop->Depth = 4;
				}
				else if (shop->Depth == 2) {
					//����̕\��
					if (Search_No_Items() == 10) shop->Not_Enough_Space = true;
					else shop->Confirm_Buy = true;
				}
				else if (shop->Depth == 3) {
					//���̕\��
					if (Search_No_Items() == 10) shop->Not_Enough_Space = true;
					else shop->Confirm_Buy = true;
				}
				else if (shop->Depth == 4) {
					//�A�C�e���̕\��
					if (Search_No_Items() == 10) shop->Not_Enough_Space = true;
					else shop->Confirm_Buy = true;
				}
				else if (shop->Depth == 5) {
					if(ch.Menu_Items_Disp(&ch,shop->Depth_Menu_Select[shop->Depth]) != 0)
						shop->Confirm_Sell = true;
				}

			}

		}

	}

	/*�w���A�m�F�p�̃��b�Z�[�W*/
	void Confirm_Window_String(Shopping* shop) {
		DrawRoundRect(ch.w5 + 5, ch.h4, ch.w5 * 4, ch.h4 * 2 + 20, 10, 10, 0x444444, 1);
		DrawRoundRect(ch.w5 + 5, ch.h4, ch.w5 * 4, ch.h4 * 2 + 20, 10, 10, 0xaaaaaa, 0);
		DrawRoundRect(ch.w5 + 6, ch.h4 + 1, ch.w5 * 4 - 1, ch.h4 * 2 + 19, 10, 10, 0xffffff, 0);

		SetFontSize(ch.size * 2);

		if (shop->Confirm_Buy) {
			if (shop->Depth == 2)str.SuperString(ch.w / 2, ch.h4 + 5, Item_Name[shop->Depth_Menu_Select[shop->Depth]], 0xffffff, 1, ch.size * 2);
			if (shop->Depth == 3)str.SuperString(ch.w / 2, ch.h4 + 5, Item_Name[shop->Depth_Menu_Select[shop->Depth] + 5], 0xffffff, 1, ch.size * 2);
			if (shop->Depth == 4)str.SuperString(ch.w / 2, ch.h4 + 5, Item_Name[shop->Depth_Menu_Select[shop->Depth] + 8], 0xffffff, 1, ch.size * 2);
			str.SuperString(ch.w / 2, ch.h4 + 5 + ch.size * 2, "���w�����܂����H", 0xffffff, 1, ch.size * 2);
			if (shop->Confirm_Select == 0) color = blue_color;
			str.SuperString(ch.w / 2, ch.h4 + 5 + ch.size * 6, "�������@�@�@�@�@", color, 1, ch.size * 2);
			color = white_color;
			if (shop->Confirm_Select == 1) color = blue_color;
			str.SuperString(ch.w / 2, ch.h4 + 5 + ch.size * 6, "�@�@�@�@�@�@�͂�", color, 1, ch.size * 2);
			color = white_color;
		}

		if (shop->Confirm_Sell) {
			str.SuperString(ch.w / 2, ch.h4 + 5, Item_Name[ch.Menu_Items_Disp(&ch, shop->Depth_Menu_Select[shop->Depth])-1], 0xffffff, 1, ch.size * 2);
			str.SuperString(ch.w / 2, ch.h4 + 5 + ch.size * 2, "�𔄋p���܂����H", 0xffffff, 1, ch.size * 2);
			if (shop->Confirm_Select == 0) color = blue_color;
			str.SuperString(ch.w / 2, ch.h4 + 5 + ch.size * 6, "�������@�@�@�@�@", color, 1, ch.size * 2);
			color = white_color;
			if (shop->Confirm_Select == 1) color = blue_color;
			str.SuperString(ch.w / 2, ch.h4 + 5 + ch.size * 6, "�@�@�@�@�@�@�͂�", color, 1, ch.size * 2);
			color = white_color;
		}

	}

	/*�w���������̂��o�b�O�ɓ����*/
	static void Input_Item(int bag_num, int item) {

		ch.Input_Item(&ch, bag_num, item);

	}

	/*�A�C�e������̏ꏊ��T���A�Y������Ԃ�*/
	static int Search_No_Items() {
		int i = 0;

		for (i; i < 10; i++) {
			if (ch.Menu_Items_Disp(&ch, i) == 0) {
				break;
			}
		}

		return i;
	}

	/*�A�C�e���w���܂ł̗���*/
	static void Buy_Items(Shopping* shop, int item, int price) {

		/*���̃A�C�e���̒l�i����������������Ă邩�m�F*/
		if (ch.Check_Enough_Money(&ch, price) == 1) {

			DrawBox(400, 200, 600, 400, 0xffffff, 1);

			/*���x����*/
			ch.Pay_Money(&ch, price);

			/*�������A�C�e���̊i�[*/
			Input_Item(Search_No_Items(), item);

		}
		else { shop->Not_Enough_Cash = true; }

	}

private:
	int Depth = 0;	/*�V���b�v�̉�ʑJ�ڗp (0:����/����
											1:����>����/��/�A�C�e��,
											2:����>����>
											3:����>��>
											4:����>�A�C�e��>
											5:����>�����i���甄��/�q�ɂ��甄��
											6:����>�����i���甄��>
											7:����>�q�ɂ��甄��>
											*/

	int Confirm_Select = 0;
	unsigned int color = 0;
	unsigned int blue_color = 0x6666ff;
	unsigned int white_color = 0xffffff;
	int Depth_Menu_Select[6] = { 0,0,0,0,0,0 };	//Depth�ʑI��p�̕ϐ�
	int Depth_Menu_Num[6] = { 2,3,5,3,2,10 };	//Depth�ʂ̑I�����̐�

	char Item_Name[10][15] = { "�؂̌�","�S�̌�","�G�N�X�J���o�[","�؂̏�","�S�̏�","�؂̏�","�΂̏�","�S�̏�","�|�[�V����","�^�s�I�J�l�s" };
	const int Item_Price[10] = { 100,400,800,75,450,120,360,1000,100,250 };

	const char Depth_Select_Name[5][5][30] = {
		{"����","����"," "," "," "},
		{"����","��","�A�C�e��"," "," "},
		{"�؂̌�","�S�̌�","�G�N�X�J���o�[","�؂̏�","�S�̏�"},
		{"�؂̏�","�΂̏�","�S�̏�"," "," "},
		{"�|�[�V����","�^�s�I�J�l�s"," "," "," "}
	};

	/*�A�C�e���̐���*/
	const char Weapon_Info_String[5][200] = {
		"�U���́F�a�@�@�ϋv�́F�c�@\n�[�[�[�[�[�[�[�[�[�[�[�[�[�[\n����ӂꂽ�ؐ��̌��B\n�E���\�͂͂��邪�������邽\n�߁A�����{�g�т��K�{��",
		"�U���́F�`�@�@�ϋv�́F�b�@\n�[�[�[�[�[�[�[�[�[�[�[�[�[�[\n�ǂ��l���Ă��d���S���̌��B\n���ꑕ���ł���ؗ͂�����Ȃ�\n�f��ŌF�ɏ��Ă��Ⴄ�����B",
		"�U���́F�r�@�@�ϋv�́F�`�@\n�[�[�[�[�[�[�[�[�[�[�[�[�[�[\n�N�����m���Ă�`���̌��B\n���̐��E�ł͗ʎY�^�ł��邽��\n��������Ȃ牽�{�ł�������B",
		"�U���́F�c�@�@�ϋv�́F�r�@\n�[�[�[�[�[�[�[�[�[�[�[�[�[�[\n�ؐ��̏�B\n����𑕔����Ă���Ɩ��@���g\n����B�U���͂����Ȃ���΃��}\n���ɂ��ӂ�Ă��镐��B",
		"�U���́F�b�@�@�ϋv�́F�r�r\n�[�[�[�[�[�[�[�[�[�[�[�[�[�[\n�S���̏�B\n����𑕔����Ă���Ɩ��@���g\n����B�U���E�ϋv�Ƃ��ɃO���[\n�h�A�b�v���Ă���B"
	};
	const char Shield_Info_String[3][200] = {
		"�h��́G�a�@�@�ϋv�́F�`�@\n�[�[�[�[�[�[�[�[�[�[�[�[�[�[\n�S�z�����₦�Ȃ��ؐ��̏��B\n�h���邩�h���Ȃ����̞B������\n�ꕔ�X�����}�j�A�̊ԂŐl�C�B\n�Ȃ̂�������Ȃ��B",
		"�h��́F�`�@�@�ϋv�́F�r�@\n�[�[�[�[�[�[�[�[�[�[�[�[�[�[\n���Â̒ʉ݂̂悤�Ȑ΂̏��B\n��n�̉��b��������C�����邪\n����Ȏ������锤���Ȃ��B",
		"�h��́F�r�@�@�ϋv�́G�r�r\n�[�[�[�[�[�[�[�[�[�[�[�[�[�[\n360�x�ǂ����猩�Ă������B\n���̋�������ɂ͒N���������\n�����ȂǕs�v�I����(��x��)�B"
	};
	const char Item_Info_String[2][200] = {
		"�񕜁F�`�@\n�[�[�[�[�[�[�[�[�[�[�[�[�[�[\n����ӂꂽ�|�[�V�����B\n�g���Ƒ̂̏��������Ă����B\n����ł�́H���ɓh���Ă�́H\n�ȂǂƂ͕����Ȃ���B",
		"�񕜁F�r�r\n�[�[�[�[�[�[�[�[�[�[�[�[�[�[\n���[���ꂱ��B\n���JK�܂ߑSJK��p�B�̈��ݕ�\n������L����΍���������撣\n���B"
	};
};
