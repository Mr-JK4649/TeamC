#pragma once
#include "DxLib.h"
#include <stdio.h>

#include "header.h"
#include "string.h"
#include "Input.h"
#include "Source.h"

/*メニュー表示用のやつ*/
struct Menu {
	bool isMenu = false;
	bool isItem_Menu = false;			//所持品確認
	bool isItem_Select_Menu = false;	//アイテム一覧で選択した時のメニュー
	bool isItem_Delete = false;			//アイテム捨てるフラグ
	bool isItem_Equip = false;			//アイテム装備フラグ
	bool isGage_Menu = false;			//ゲージ確認
	bool isMove_Scene = false;			//シーン移動
	bool Move_Scene = false;			//シーン移動時の処理用
	int scene_t = 0;					//移動先のシーンを保存
	bool isTIPS = false;				//メニューのTIPSの表示

	bool isBuilding_Enter = false;		//建物に入るフラグ
	int Enter_Num = 0;					//建物の種類
	int Enter_Select = 0;				//確認ウィンドウの選択で使うやつ
	char Building_Name[4][20] = { "「仕事紹介所」","「雑貨屋」","「自宅」","「カジノ」"};

	bool Result_DWork_Flg = false;		//力仕事の報酬を表示
	bool Result_FWork_Flg = false;		//調達の報酬を表示
	int Result_Work_Money = 0;			//仕事で得た報酬
	int Result_Work_Par[2] = {2};		//仕事で得たゲージの増加

	int item_select = 0;				//アイテム一覧ようの添え字
	int item_select2 = 0;				//アイテム選択ウィンドウ用の添え字

	bool isTutorial = true;				//チュートリアル
	int Tutorial_Select = 0;			//チュートリアルの選択肢

	/*メニュー素材の初期化*/
	void Init() {
		SelectMove_SE = LoadSoundMem("sounds/カーソル移動.mp3");
		Select_SE = LoadSoundMem("sounds/メニュー決定.mp3");
		Cansel_SE = LoadSoundMem("sounds/メニューキャンセル.mp3");
	}

	/*メニューの表示*/
	void Draw() {
		const float w = scale.Width, w5 = w / 5;
		const float h = scale.Height, h4 = h / 4;
		const int size = scale.Width / 100;
		
		/*メニュー素材の初期化*/
		if (Init_Flg) { Init(); Init_Flg = false; }

		/*メニューの枠表示*/
		Draw_Menu_Box(w, w5, h, h4);

		
		SetFontSize(size * 2);

		if (isMenu && !isTIPS) {

			/*左メニューの文字*/
			for (int i = 0; i < 3; i++) {

				if (menu_num == i) color = blue_color;

				if (g_GameState == GAME_BASE || g_GameState == GAME_DUNGEON && i != 2)
					str.SuperString(10 + (w5 - 10) / 2, 20 + (size * 4) * i, Menu_String[i], color, 1, size * 2);
				else
					str.SuperString(10 + (w5 - 10) / 2, 20 + (size * 4) * i, Menu_String[i + 1], color, 1, size * 2);

				color = white_color;
			}

			/*アイテム選択のメニュー*/
			if (isItem_Select_Menu) {
				for (int i = 0; i < 2; i++) {
					unsigned int l_color = 0xffffff;
					if (i == item_select2) l_color = 0x6666ff;

					DrawString(w5 * 3 + 20, (h4 + size * 4 * i) + item_select * 20 + 26, Item_Select_String[i], l_color, 1);

					l_color = 0xffffff;
				}
			}

			/*シーン移動のやつ*/
			if (isMove_Scene) {
				str.SuperString(w / 2, h4 + 5, "本当に戻りますか？", 0xffffff, 1, size * 2);
				if (item_select == 0) color = blue_color;
				str.SuperString(w / 2, h4 + 5 + size * 2, "いいえ　　　　　", color, 1, size * 2);
				color = white_color;
				if (item_select == 1) color = blue_color;
				str.SuperString(w / 2, h4 + 5 + size * 2, "　　　　　　はい", color, 1, size * 2);
				color = white_color;
			}

		}

		if (isBuilding_Enter) {
			DrawRoundRect(w5 + 5, h4, w5 * 4, h4 * 2 + 20, 10, 10, 0x444444, 1);
			DrawRoundRect(w5 + 5, h4, w5 * 4, h4 * 2 + 20, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w5 + 6, h4 + 1, w5 * 4 - 1, h4 * 2 + 19, 10, 10, 0xffffff, 0);

			str.SuperString(w / 2, h4 + 5, Building_Name[Enter_Num], 0xffffff, 1, size * 2);
			str.SuperString(w / 2, h4 + 5 + size * 2, "に入りますか？", 0xffffff, 1, size * 2);
			if (Enter_Select == 0) color = blue_color;
			str.SuperString(w / 2, h4 + 5 + size * 6, "いいえ　　　　　", color, 1, size * 2);
			color = white_color;
			if (Enter_Select == 1) color = blue_color;
			str.SuperString(w / 2, h4 + 5 + size * 6, "　　　　　　はい", color, 1, size * 2);
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
					if (Enter_Num == 0)scene_t = GAME_WORK;		//仕事紹介所
					if (Enter_Num == 1)scene_t = GAME_SHOP;		//お店
					if (Enter_Num == 2)scene_t = GAME_HOME;		//自宅
					if (Enter_Num == 3)scene_t = GAME_CASINO;	//カジノ
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
			str.SuperString(w / 2, h - (h / 10), "ＯＫ", 0xff0000, 1, size * 2);
			/*if (Result_DWork_Flg) {
				DrawFormatString(10, (h - h4) + 5, 0xffffff, "街の発展に協力した事により、以下の報酬を得た。\nお金　+%9dＧ\n発展度+%9d％", Result_Work_Money, 5);
			}
			if (Result_FWork_Flg) {
				DrawFormatString(10, (h - h4) + 5, 0xffffff, "食料調達をした事により、以下の報酬を得た。\nお金　+%9dＧ\n食料　+%9d％", Result_Work_Money, 5);
			}*/

			if (Result_FWork_Flg || Result_DWork_Flg) {
				DrawFormatString(10, (h - h4) + 5, 0xffffff, "仕事をした事により、以下の報酬を得た。\nお金　+%9dＧ\n発展度+%9d％\n食料　+%9d％", Result_Work_Money, Result_Work_Par[0],Result_Work_Par[1]);

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

		/*メニュー内での操作*/
		if(isMenu || isGage_Menu)Update();

	}

	/*メニューの操作*/
	void Update() {

		if (isGage_Menu) {
			if (inp.cancel) {
				PlaySoundMem(Cansel_SE, DX_PLAYTYPE_BACK, TRUE);
				isGage_Menu = false;
			}
		}
		else if (isItem_Menu) {

			if (isItem_Select_Menu) {								//アイテムを選択したとき
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
					if (item_select2 == 0) isItem_Equip = true;		//アイテムを装備する
					if (item_select2 == 1) isItem_Delete = true;	//アイテムを捨てる	
					isItem_Select_Menu = false;

				}
				if (inp.cancel) {
					PlaySoundMem(Cansel_SE, DX_PLAYTYPE_BACK, TRUE);
					isItem_Select_Menu = false;
				}
			}
			else {													//アイテムを選択してないとき

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

	/*ステータスを表示する枠*/
	void Draw_Menu_Box(float w,float w5, float h,float h4) {

		const float w100 = w / 100.0f;
		const float h100 = h / 100.0f;

		if (isMenu && !isTIPS) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			DrawBox(0, 0, scale.Width, scale.Height, 0x000000, 1);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

			//上段　所持金、発展度、生存時間
			DrawRoundRect(w - w5, 5, w - 5, h4, 10, 10, 0x444444, 1);
			DrawRoundRect(w - w5, 5, w - 5, h4, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w - w5 + 1, 6, w - 6, h4 - 1, 10, 10, 0xffffff, 0);

			//中段　レベル、経験値、体力、攻撃力、防御力
			DrawRoundRect(w - w5, (h4 + 5), w - 5, (h4 + 5) + h4 * 1, 10, 10, 0x444444, 1);
			DrawRoundRect(w - w5, (h4 + 5), w - 5, (h4 + 5) + h4 * 1, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w - w5 + 1, (h4 + 5) + 1, w - 6, (h4 + 5) + h4 * 1 - 1, 10, 10, 0xffffff, 0);

			//下段	装備
			DrawRoundRect(w - w5, (h4 + 5) + h4 * 1 + 5, w - 5, (h4 + 5) + h4 * 2, 10, 10, 0x444444, 1);
			DrawRoundRect(w - w5, (h4 + 5) + h4 * 1 + 5, w - 5, (h4 + 5) + h4 * 2, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w - w5 + 1, (h4 + 5) + h4 * 1 + 6, w - 6, (h4 + 5) + h4 * 2 - 1, 10, 10, 0xffffff, 0);

			/*左側*/
			DrawRoundRect(5, 5, w5, h4, 10, 10, 0x444444, 1);
			DrawRoundRect(5, 5, w5, h4, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(5 + 1, 6, w5 - 1, h4 - 1, 10, 10, 0xffffff, 0);
		}

		/*アイテムのやーつとゲージのやーつ*/
		if (isItem_Menu) {
			DrawRoundRect(w5 * 1 + 5, h4, w5 * 3, h4 * 3 + 20, 10, 10, 0x444444, 1);
			DrawRoundRect(w5 * 1 + 5, h4, w5 * 3, h4 * 3 + 20, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w5 * 1 + 6, h4 + 1, w5 * 3 - 1, h4 * 3 +19, 10, 10, 0xffffff, 0);
		}

		/*シーン移動のやーつ*/
		if (isMove_Scene) {
			DrawRoundRect(w5 + 5, h4, w5 * 4, h4 * 2 + 20, 10, 10, 0x444444, 1);
			DrawRoundRect(w5 + 5, h4, w5 * 4, h4 * 2 + 20, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w5 + 6, h4 + 1, w5 * 4 - 1, h4 * 2 + 19, 10, 10, 0xffffff, 0);
		}

		/*アイテム選択のやーつ*/
		if (isItem_Select_Menu) {
			DrawRoundRect(w5 * 3 + 5, h4 + 20 * item_select, w5 * 4 - 20, h4 * 2 + 20 * item_select, 10, 10, 0x444444, 1);
			DrawRoundRect(w5 * 3 + 5, h4 + 20 * item_select, w5 * 4 - 20, h4 * 2 + 20 * item_select, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w5 * 3 + 6, h4 + 20 * item_select + 1, w5 * 4 - 21, h4 * 2 + 20 * item_select - 1, 10, 10, 0xffffff, 0);
		}

		/*TIPS表示のやーつ*/
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

	/*ゲージを表示するやつ*/
	void DrawGage(float w100, float h100) {
		const int Gage_Height = scale.Height / 30;			//ゲージの幅
		Gage_Max[0] = Base_Status_Copy[1] * 2 + 100;		//人口ゲージのマックス値を設定
		Gage[2] = Base_Status_Copy[1];						//発展度

		str.SuperString(w100 * 20.5, h100 * 41.5f, "ゲージシステム", 0xccccff,1,scale.Width / 100 * 3);

		for (int i = 0; i < 5; i++) {
			
			//DrawString(w100 * 22, h100 * 27 + Gage_Height * 3 * i, Gage_Name[i], Gage_Color[i], 1);
			str.SuperString(w100 * 2, h100 * 47.5f + Gage_Height * 3 * i, Gage_Name[i], Gage_Color[i], 0, scale.Width / 100 * 2);
			DrawBox(w100 * 2, (h100 * 51 + Gage_Height * 3 * i), (w100 * 2) + (w100 * 37) * (Gage[i] / Gage_Max[i]), (h100 * 51 + Gage_Height * 3 * i) + Gage_Height, Gage_Color[i], 1);
			DrawBox(w100 * 2, (h100 * 51 + Gage_Height * 3 * i), (w100 * 2) + (w100 * 37), (h100 * 51 + Gage_Height * 3 * i) + Gage_Height, Gage_Color[i], 0);

		}
		
	}
	
	/*アイテムの種類を取得*/
	void Item_Kind(int item_num) {
		item_kind = item_num;
	}

	/*キャラのステータスを持ってくる奴*/
	void B_Status_C(int num, int para) {
		Base_Status_Copy[num] = para;
	}

	/*ゲージの量を返す*/
	float Return_Gage_Para(int num) {
		
		return Gage[num];
	}

	/*ゲージの最大値を返す*/
	float Return_Gage_Max(int num) {

		return Gage_Max[num];
	}

	/*ゲージを上昇させるやつ*/
	void Inclease_Gage(int num,int para) {
		Gage[num] += para;
		if (Gage[num] < 0) Gage[num] = 0;
	}

	/*ゲージの最大値を増幅させる奴*/
	void Incleace_Gage_Max(int num, int para) {
		Gage_Max[num] += para;
	}

	/*仕事の結果を入れる*/
	void Input_Work_Result(int money, int dev, int food) {
		Result_Work_Money += money;
		Result_Work_Par[0] += dev;
		Result_Work_Par[1] += food;
	}

	/*仕事の報酬表示*/
	void Result_Work() {
		const int w = scale.Width;
		const int h = scale.Height, h4 = scale.Height / 4;
		DrawRoundRect(5, h - h4, w - 5, h - 5, 10, 10, 0x444444, 1);
		DrawRoundRect(5, h - h4, w - 5, h - 5, 10, 10, 0xaaaaaa, 0);
		DrawRoundRect(6, h - (h4 - 1), w - 6, h - 6, 10, 10, 0xffffff, 0);

	}

private:
	char Menu_String[4][20] = {"所持品を見る","ＴＩＰＳ","タイトルへ戻る","街へ戻る"};		//メニューレイヤー1で表示するやつ
	char Item_Select_String[2][14] = { "装備する/使う","捨てる" };							//アイテム一覧でアイテム選択時に表示するやつ
	short color = 0;																		//現在の位置を表すのに使うやつ
	int menu_num = 0,menu_num2 = 0;															//メニュー選択に使うやつ
	int item_kind = 0;																		//現在の位置のアイテムが何か調べてもらうやつ
	const unsigned int white_color = 0xffffff;												//白
	const unsigned int blue_color = 0x6666ff;												//青
	float Gage[5] = { 0,0,0,50,0 };															//ゲージの値を保存するやつ
	float Gage_Max[5] = { 100,100,100,100,100 };														//各ゲージのマックスの値
	char Gage_Name[5][11] = { "人口ゲージ","魔物ゲージ","発展ゲージ","食料ゲージ","武力ゲージ" };		//ゲージの名前
	unsigned int Gage_Color[5] = { 0xffff00,0x880088,0x00ffff,0x00ff00,0xff0000 };						//各ゲージの色
	char TIPS_String[7][21] = { "操作方法","目的とルール","キャラクター","拠点でできる事","畑でできる事","ダンジョン","ゲージ" };	//TIPSの文字列
	int TIPS_Depth = 0;																	//TIPSメニューのれべる
	int TIPS_Select_Pages[7] = { 2,2,4,5,5,5,4 };										//各TIPSのページ数
	int TIPS_Select[2] = {0};															//TIPS選択と各ページ用
	int Base_Status_Copy[3] = { 0 };

	bool Init_Flg = true;

	int SelectMove_SE = 0;
	int Select_SE = 0;
	int Cansel_SE = 0;
};

extern Menu menu;