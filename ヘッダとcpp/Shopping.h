#pragma once

#include "character.h"

Shop sh;

struct Shopping {

	bool Confirm_Buy = false;				//購入するか否かを確認するウィンドウを出すためのやつ
	bool Confirm_Sell = false;				//売却するか否かを確認するウィンドウをだすやつ

	bool Search_No_Item = false;			//空ののアイテムを探してくれるやつ上から順に一番最初
	bool Buy_Item = false;					//アイテム購入フラグ

	bool Not_Enough_Space = false;			//アイテムに空きがない
	bool Not_Enough_Cash = false;			//所持金が足りない

	static void Draw(Shopping* shop) {

		//SetFontSize(16);

		if (shop->Depth != 5)DrawExtendGraph(0, 0, ch.w, ch.h, sh.background[shop->Depth_Menu_Select[shop->Depth]], 1);
		else				DrawExtendGraph(0, 0, ch.w, ch.h, sh.background[5], 1);
		if (shop->Depth < 2) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			DrawBox(ch.w / 2, 0, ch.w, ch.h, 0x000000, 1);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}

		/*選択肢の文字表示*/
		if (shop->Depth < 5) {

			SetFontSize(ch.size * 4);

			for (int i = 0; i < shop->Depth_Menu_Num[shop->Depth]; i++) {

				DrawString((ch.w / 100.0f) * 10, (ch.h / 100.0f) * (15 + 18 * i), shop->Depth_Select_Name[shop->Depth][i], 0x000000, 1);

			}

		}

		/*アイテム一覧を開く*/
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
				case Chara::Iron_Shield:	strcpy_s(item_name, Iron_Shield.Shield_name);	break;
				case Chara::Tapi_Shield:	strcpy_s(item_name, Tapi_Shield.Shield_name);	break;
				case Chara::Portion:		strcpy_s(item_name, "ポーション");				break;
				case Chara::Tapi_MT:		strcpy_s(item_name, "タピオカＭＴ");			break;
				default:					strcpy_s(item_name, "　　　　　　　　ーーー　　　　　　　　");		break;
				}

				if (i == shop->Depth_Menu_Select[shop->Depth]) color = 0x6666ff;

				DrawString(ch.w5 * 1 + 11, ch.h4 + 6 + (ch.size * 3) * i, item_name, color, 1);

				color = 0xffffff;
			}
		}

		/*アイテムがいっぱい、もしくは所持金が足りない場合のやつ*/
		if (shop->Not_Enough_Cash || shop->Not_Enough_Space) {
			DrawRoundRect(ch.w5 + 5, ch.h4, ch.w5 * 4, ch.h4 * 2 + 20, 10, 10, 0x444444, 1);
			DrawRoundRect(ch.w5 + 5, ch.h4, ch.w5 * 4, ch.h4 * 2 + 20, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(ch.w5 + 6, ch.h4 + 1, ch.w5 * 4 - 1, ch.h4 * 2 + 19, 10, 10, 0xffffff, 0);

			SetFontSize(ch.size * 3);

			if (shop->Not_Enough_Cash) {
				str.SuperString(ch.w / 2, ch.h4 + 5 + ch.size * 2, "所持金が足りません", 0xffffff, 1, ch.size * 2);
			}
			if (shop->Not_Enough_Space) {
				str.SuperString(ch.w / 2, ch.h4 + 5 + ch.size * 2, "所持品がいっぱいです", 0xffffff, 1, ch.size * 2);
			}
			str.SuperString(ch.w / 2, ch.h4 + 5 + ch.size * 6, "はい", 0xff0000, 1, ch.size * 2);
		}

		/*所持金の表示*/
		DrawRoundRect(5, 5, ch.w5 * 2, ch.h4 / 3, 10, 10, 0x444444, 1);
		DrawRoundRect(5, 5, ch.w5 * 2, ch.h4 / 3, 10, 10, 0xaaaaaa, 0);
		DrawRoundRect(5 + 1, 6, ch.w5 * 2 - 1, ch.h4 / 3 - 1, 10, 10, 0xffffff, 0);
		SetFontSize(ch.size * 3);
		DrawFormatString(10, 10, 0xffffff, "所持金　%15dＧ", ch.Return_Base_Status(&ch, 0));

	}

	/*ショップ内での操作*/
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
				if (--shop->Depth_Menu_Select[shop->Depth] < 0) shop->Depth_Menu_Select[shop->Depth] = shop->Depth_Menu_Num[shop->Depth] - 1;
			}
			if (inp.f_down) {
				if (++shop->Depth_Menu_Select[shop->Depth] > shop->Depth_Menu_Num[shop->Depth] - 1) shop->Depth_Menu_Select[shop->Depth] = 0;
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
					//武器の表示
					if (Search_No_Items() == 10) shop->Not_Enough_Space = true;
					else shop->Confirm_Buy = true;
				}
				else if (shop->Depth == 3) {
					//盾の表示
					if (Search_No_Items() == 10) shop->Not_Enough_Space = true;
					else shop->Confirm_Buy = true;
				}
				else if (shop->Depth == 4) {
					//アイテムの表示
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

	void Confirm_Window_String(Shopping* shop) {
		DrawRoundRect(ch.w5 + 5, ch.h4, ch.w5 * 4, ch.h4 * 2 + 20, 10, 10, 0x444444, 1);
		DrawRoundRect(ch.w5 + 5, ch.h4, ch.w5 * 4, ch.h4 * 2 + 20, 10, 10, 0xaaaaaa, 0);
		DrawRoundRect(ch.w5 + 6, ch.h4 + 1, ch.w5 * 4 - 1, ch.h4 * 2 + 19, 10, 10, 0xffffff, 0);

		SetFontSize(ch.size * 2);

		if (shop->Confirm_Buy) {
			if (shop->Depth == 2)str.SuperString(ch.w / 2, ch.h4 + 5, Item_Name[shop->Depth_Menu_Select[shop->Depth]], 0xffffff, 1, ch.size * 2);
			if (shop->Depth == 3)str.SuperString(ch.w / 2, ch.h4 + 5, Item_Name[shop->Depth_Menu_Select[shop->Depth] + 5], 0xffffff, 1, ch.size * 2);
			if (shop->Depth == 4)str.SuperString(ch.w / 2, ch.h4 + 5, Item_Name[shop->Depth_Menu_Select[shop->Depth] + 8], 0xffffff, 1, ch.size * 2);
			str.SuperString(ch.w / 2, ch.h4 + 5 + ch.size * 2, "を購入しますか？", 0xffffff, 1, ch.size * 2);
			if (shop->Confirm_Select == 0) color = blue_color;
			str.SuperString(ch.w / 2, ch.h4 + 5 + ch.size * 6, "いいえ　　　　　", color, 1, ch.size * 2);
			color = white_color;
			if (shop->Confirm_Select == 1) color = blue_color;
			str.SuperString(ch.w / 2, ch.h4 + 5 + ch.size * 6, "　　　　　　はい", color, 1, ch.size * 2);
			color = white_color;
		}

		if (shop->Confirm_Sell) {
			str.SuperString(ch.w / 2, ch.h4 + 5, Item_Name[ch.Menu_Items_Disp(&ch, shop->Depth_Menu_Select[shop->Depth])], 0xffffff, 1, ch.size * 2);
			str.SuperString(ch.w / 2, ch.h4 + 5 + ch.size * 2, "を売却しますか？", 0xffffff, 1, ch.size * 2);
			if (shop->Confirm_Select == 0) color = blue_color;
			str.SuperString(ch.w / 2, ch.h4 + 5 + ch.size * 6, "いいえ　　　　　", color, 1, ch.size * 2);
			color = white_color;
			if (shop->Confirm_Select == 1) color = blue_color;
			str.SuperString(ch.w / 2, ch.h4 + 5 + ch.size * 6, "　　　　　　はい", color, 1, ch.size * 2);
			color = white_color;
		}

	}

	static void Input_Item(int bag_num, int item) {

		ch.Input_Item(&ch, bag_num, item);

	}

	/*アイテムが空の場所を探し、添え字を返す*/
	static int Search_No_Items() {
		int i = 0;

		for (i; i < 10; i++) {
			if (ch.Menu_Items_Disp(&ch, i) == 0) {
				break;
			}
		}

		return i;
	}

	static void Buy_Items(Shopping* shop, int item, int price) {

		/*このアイテムの値段が所持金を下回ってるか確認*/
		if (ch.Check_Enough_Money(&ch, price) == 1) {

			DrawBox(400, 200, 600, 400, 0xffffff, 1);

			/*お支払い*/
			ch.Pay_Money(&ch, price);

			/*買ったアイテムの格納*/
			Input_Item(Search_No_Items(), item);

		}
		else { shop->Not_Enough_Cash = true; }

	}

private:
	int Depth = 0;	/*ショップの画面遷移用 (0:買う/売る
											1:買う>武器/盾/アイテム,
											2:買う>武器>
											3:買う>盾>
											4:買う>アイテム>
											5:売る>所持品から売る/倉庫から売る
											6:売る>所持品から売る>
											7:売る>倉庫から売る>
											*/

	int Confirm_Select = 0;
	unsigned int color = 0;
	unsigned int blue_color = 0x6666ff;
	unsigned int white_color = 0xffffff;
	int Depth_Menu_Select[6] = { 0,0,0,0,0,0 };	//Depth別選択用の変数
	int Depth_Menu_Num[6] = { 2,3,5,3,2,10 };	//Depth別の選択肢の数

	char Item_Name[10][15] = { "木の剣","鉄の剣","エクスカリバー","木の杖","鉄の杖","木の盾","鉄の盾","タピオカの盾","ポーション","タピオカＭＴ" };
	const int Item_Price[10] = { 50,100,200,75,150,40,160,640,60,100 };

	const char Depth_Select_Name[5][5][30] = {
		{"買う","売る"," "," "," "},
		{"武器","盾","アイテム"," "," "},
		{"木の剣","鉄の剣","エクスカリバー","木の杖","鉄の杖"},
		{"木の盾","鉄の盾","タピオカの盾"," "," "},
		{"ポーション","タピオカＭＴ"," "," "," "}
	};
};
