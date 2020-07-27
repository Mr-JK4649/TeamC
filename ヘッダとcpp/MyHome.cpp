#include "DxLib.h"
#include "character.h"

#pragma warning(disable : 4244)

Home home;



void Home_Draw(int width, int height) {
	if (home.flg) { home.ImageInput(&home); }

	const float w = (float)width / 100.0f;
	const float h = (float)height / 100.0f;
	const int size = w / 100;

	DrawExtendGraph(0, 0, width, height, home.background, 1);

	if (ch.Pic_Item || ch.Put_Item) {
		/*ボックスアイテム表示*/
		DrawRoundRect(w * 10,	  h * 15,	  w * 45,	  h * 80,	  10, 10, 0x444444, 1);
		DrawRoundRect(w * 10,	  h * 15,	  w * 45,	  h * 80,	  10, 10, 0xaaaaaa, 0);
		DrawRoundRect(w * 10 + 1, h * 15 + 1, w * 45 - 1, h * 80 - 1, 10, 10, 0xffffff, 0);
		str.SuperString((w * 10) + (w * 35) / 2, (h * 15) + size * 30,"アイテムボックス",0xffffff,1, size * 30);
		DrawFormatString((w * 10) + (w * 35) / 2, h * 75, 0xffffff, "%d/3", home.Max_Box_Disp / 10);

		/*アイテムの表示*/
		DrawRoundRect(w * 55,	  h * 15,	  w * 90,	  h * 80,	  10, 10, 0x444444, 1);
		DrawRoundRect(w * 55,	  h * 15,	  w * 90,	  h * 80,	  10, 10, 0xaaaaaa, 0);
		DrawRoundRect(w * 55 + 1, h * 15 + 1, w * 90 - 1, h * 80 - 1, 10, 10, 0xffffff, 0);
		str.SuperString((w * 55) + (w * 35) / 2, (h * 15) + size * 30, "アイテムバッグ", 0xffffff, 1, size * 30);

		char item_name[51];

		/*アイテム表示*/
		for (int i = 0; i < 10; i++) {

			SetFontSize(ch.size * 2);

			switch (ch.Menu_Items_Disp(&ch, i))
			{
			case Chara::Wood_Sword:		strcpy_s(item_name, Wood_Sword.Weapon_name);		break;
			case Chara::Iron_Sword:		strcpy_s(item_name, Iron_Sword.Weapon_name);		break;
			case Chara::Excalibur:		strcpy_s(item_name, Exca_Sword.Weapon_name);		break;
			case Chara::Wood_Rod:		strcpy_s(item_name, Wood_Rod.Weapon_name);		break;
			case Chara::Iron_Rod:		strcpy_s(item_name, Iron_Rod.Weapon_name);		break;
			case Chara::Wood_Shield:	strcpy_s(item_name, Wood_Shield.Shield_name);	break;
			case Chara::Iron_Shield:	strcpy_s(item_name, Iron_Shield.Shield_name);	break;
			case Chara::Tapi_Shield:	strcpy_s(item_name, Tapi_Shield.Shield_name);	break;
			case Chara::Portion:		strcpy_s(item_name, "ポーション");				break;
			case Chara::Tapi_MT:		strcpy_s(item_name, "タピオカＭＴ");				break;
			default:					strcpy_s(item_name, "　　　　　　　ーーー　　　　　　　");		break;
			}

			if (i == home.Box_Select4) home.color = home.blue_color;

			if (ch.Pic_Item) home.color = home.white_color;

			DrawString(w * 55 + 5, h * 20 + 5 + (ch.size * 3) * i, item_name, home.color, 1);

			home.color = home.white_color;
		}

		for (int i = home.Min_Box_Disp; i < home.Max_Box_Disp; i++) {
			
			SetFontSize(ch.size * 2);

			switch (ch.Return_Box_Item(&ch, i))
			{
			case Chara::Wood_Sword:		strcpy_s(item_name, Wood_Sword.Weapon_name);		break;
			case Chara::Iron_Sword:		strcpy_s(item_name, Iron_Sword.Weapon_name);		break;
			case Chara::Excalibur:		strcpy_s(item_name, Exca_Sword.Weapon_name);		break;
			case Chara::Wood_Rod:		strcpy_s(item_name, Wood_Rod.Weapon_name);		break;
			case Chara::Iron_Rod:		strcpy_s(item_name, Iron_Rod.Weapon_name);		break;
			case Chara::Wood_Shield:	strcpy_s(item_name, Wood_Shield.Shield_name);	break;
			case Chara::Iron_Shield:	strcpy_s(item_name, Iron_Shield.Shield_name);	break;
			case Chara::Tapi_Shield:	strcpy_s(item_name, Tapi_Shield.Shield_name);	break;
			case Chara::Portion:		strcpy_s(item_name, "ポーション");				break;
			case Chara::Tapi_MT:		strcpy_s(item_name, "タピオカＭＴ");				break;
			default:					strcpy_s(item_name, "　　　　　　　ーーー　　　　　　　");		break;
			}

			if (i == home.Box_Select3) home.color = home.blue_color;

			if (ch.Put_Item) home.color = home.white_color;

			DrawString(w * 10 + 5, h * 20 + 5 + (ch.size * 3) * (i - home.Min_Box_Disp), item_name, home.color, 1);

			home.color = home.white_color;

		}

	}
	else if (ch.Open_ItemBox) {
		DrawRoundRect(w * 40, h * 40, w * 60, h * 70, 10, 10, 0x444444, 1);
		DrawRoundRect(w * 40, h * 40, w * 60, h * 70, 10, 10, 0xaaaaaa, 0);
		DrawRoundRect(w * 40 + 1, h * 40 + 1, w * 60 - 1, h * 70 - 1, 10, 10, 0xffffff, 0);
		for (int i = 0; i < 2; i++) {
			if (home.Box_Select2 == i)home.color = home.blue_color;
			str.SuperString(width / 2, h * (41 + 8 * i), home.Box_Select_String[i], home.color, 1, size * 20);
			home.color = home.white_color;
		}
	}
	else {
		DrawRoundRect(w * 40, h * 40, w * 60, h * 70, 10, 10, 0x444444, 1);
		DrawRoundRect(w * 40, h * 40, w * 60, h * 70, 10, 10, 0xaaaaaa, 0);
		DrawRoundRect(w * 40 + 1, h * 40 + 1, w * 60 - 1, h * 70 - 1, 10, 10, 0xffffff, 0);
		for (int i = 0; i < 4; i++) {
			if (home.home_select == i)home.color = home.blue_color;
			str.SuperString(width / 2, h * (41 + 8 * i), home.Selct_String[i], home.color, 1, size * 20);
			home.color = home.white_color;
		}
	}
	
	/*ベッドで休むアニメーション*/
	if (ch.GoTo_Bed) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, home.Bed_Alpha);
		DrawBox(0, 0, width, height, 0x000000, 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		
		if (home.Bed_Alpha >= 255) home.Bed_Alpha_Add *= -1;
		if (home.Bed_Alpha < 0) {
			home.Bed_Alpha = 0;
			home.Bed_Alpha_Add = 1;
			ch.Healing_Life(&ch, Chara::Tapi_MT);
			ch.GoTo_Bed = false;
		}
		home.Bed_Alpha += home.Bed_Alpha_Add;
	}

	/*操作*/
	if (!ch.GoTo_Bed) {
		if (!ch.Open_ItemBox) {
			if (inp.f_up) {
				if (--home.home_select < 0) home.home_select = 3;
			}
			if (inp.f_down) {
				if (++home.home_select > 3) home.home_select = 0;
			}
			if (inp.space) {
				if (home.home_select == 0) ch.Open_ItemBox = true;
				if (home.home_select == 1) ch.GoTo_Bed = true;
				if (home.home_select == 2) g_GameState = GAME_HATAKE;
				if (home.home_select == 3) g_GameState = GAME_BASE;
			}
		}
		else if (ch.Pic_Item) {
			if (inp.f_up) {
				if (--home.Box_Select3 < 0) home.Box_Select3 = 29;
			}
			if (inp.f_down) {
				if (++home.Box_Select3 > 29) home.Box_Select3 = 0;
			}
			if (inp.space) {
				ch.Pic_Item_Box(&ch, home.Box_Select3);
			}
			if (inp.f_right) {
				ch.Pic_Item = false;
				ch.Put_Item = true;
				home.Box_Select3 = 0;
			}
			if (inp.cancel) {
				ch.Pic_Item = false;
				home.Box_Select3 = 0;
			}

			if (home.Box_Select3 >= 0 && home.Box_Select3 < 10) { home.Min_Box_Disp = 0; home.Max_Box_Disp = 10; }
			if (home.Box_Select3 >= 10 && home.Box_Select3 < 20) { home.Min_Box_Disp = 10; home.Max_Box_Disp = 20; }
			if (home.Box_Select3 >= 20 && home.Box_Select3 < 30) { home.Min_Box_Disp = 20; home.Max_Box_Disp = 30; }

		}
		else if (ch.Put_Item) {
			if (inp.f_up) {
				if (--home.Box_Select4 < 0) home.Box_Select4 = 9;
			}
			if (inp.f_down) {
				if (++home.Box_Select4 > 9) home.Box_Select4 = 0;
			}
			if (inp.space) {
				ch.Put_Item_Box(&ch, home.Box_Select4);
			}
			if (inp.f_left) {
				ch.Put_Item = false;
				ch.Pic_Item = true;
				home.Box_Select4 = 0;
			}
			if (inp.cancel) {
				ch.Put_Item = false;
				home.Box_Select4 = 0;
			}
		}
		else if (ch.Open_ItemBox) {
			if (inp.f_up) {
				if (--home.Box_Select2 < 0) home.Box_Select2 = 1;
			}
			if (inp.f_down) {
				if (++home.Box_Select2 > 1) home.Box_Select2 = 0;
			}
			if (inp.space) {
				if (home.Box_Select2 == 0) ch.Pic_Item = true;
				if (home.Box_Select2 == 1) ch.Put_Item = true;
			}
			if (inp.cancel) {
				ch.Open_ItemBox = false;
				home.Box_Select2 = 0;
			}

		}
	}

}