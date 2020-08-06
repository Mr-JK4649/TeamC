#pragma once

#include "character.h"

//Casino casino;

struct Casino_System {
	bool Dragon_Tiger = false;		//ドラゴンタイガーをプレイ
	bool DT_Info = false;			//ドラゴンタイガーの説明
	int DT_Phase = 0;				//ドラゴンタイガーのフェイズ
	int DT_Result = 0;				//ドラゴンタイガーの結果
	char DT_Result_Sting[4][20] = {	//ドラゴンタイガーの結果文字列
		"ドラゴンの勝ち",
		"タイガーの勝ち",
		"タイ",
		"スーテッドタイ"
	};
	int DT_Result_Money = 0;		//ドラゴンタイガーの返金額

	bool Casino_War = false;		//カジノウォーをプレイ
	bool CW_Info = false;			//カジノウォーの説明
	int CW_Phase = 0;				//カジノウォーのフェイズ
	int CW_Tie_Bet = 0;				//カジノウォーのTIEベットのやつ(1ならTIEベット)
	int CW_Tie_Select = 0;			//タイの場合の選択(サレンダー、ウォー)
	int CW_Result = 0;				//カジノウォーの結果
	char CW_Result_String[3][20] = {//カジノウォーの結果文字列
		"相手の勝ち",
		"あなたの勝ち",
		"タイ"
	};
	char CW_TieBet_String[2][20] = { "しない","する" };
	char CW_Tie_Select_String[2][20] = { "サレンダー","ウォー" };
	int CW_Result_Money = 0;		//カジノウォーの返金額

	/*カードの初期化*/
	void Card_Init() {
		for (int i = 0; i < 2; i++) {
			
			Card_Status[i][0] = 55;		//ｘ初期化
			Card_Status[i][1] = -30;	//ｙ初期化
			Card_Status[i][2] = 10;		//幅初期化
			Card_Status[i][3] = 30;		//高さ初期化
			Card_Status[i][4] = GetRand(51);	//カードの番号とマーク
			Back_or_Front[i] = 0;				//最初のカードは裏
		}
	}

	void Draw() {
		const float w = (float)scale.Width / 100.0f;
		const float h = (float)scale.Height / 100.0f;
		const int size = scale.Width / 100;

		/*セリフと選択枠*/
		if (Casino_War) {
			/*セリフ枠*/
			DrawRoundRect(w * 1, h * 50, w * 35, h * 99, 10, 10, 0x444444, 1);
			DrawRoundRect(w * 1, h * 50, w * 35, h * 99, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w * 1 + 1, h * 50 + 1, w * 35 - 1, h * 99 - 1, 10, 10, 0xffffff, 0);

			/*選択肢枠*/
			DrawRoundRect(w * 71, h * 70, w * 99, h * 99, 10, 10, 0x444444, 1);
			DrawRoundRect(w * 71, h * 70, w * 99, h * 99, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w * 71 + 1, h * 70 + 1, w * 99 - 1, h * 99 - 1, 10, 10, 0xffffff, 0);
		}
		else {
			/*セリフ枠*/
			DrawRoundRect(w * 1, h * 70, w * 70, h * 99, 10, 10, 0x444444, 1);
			DrawRoundRect(w * 1, h * 70, w * 70, h * 99, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w * 1 + 1, h * 70 + 1, w * 70 - 1, h * 99 - 1, 10, 10, 0xffffff, 0);

			/*選択肢枠*/
			DrawRoundRect(w * 71, h * 70, w * 99, h * 99, 10, 10, 0x444444, 1);
			DrawRoundRect(w * 71, h * 70, w * 99, h * 99, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w * 71 + 1, h * 70 + 1, w * 99 - 1, h * 99 - 1, 10, 10, 0xffffff, 0);
		}


		/*カジノのゲームの説明*/
		Casino_Game_Info(w, h, size);

		/*説明中は通常操作不可*/
		if (!Dragon_Tiger && !Casino_War) {
			for (int i = 0; i < 2; i++) {
				if (Depth_Select[Depth] == i) color = blue_color;
				str.SuperString(w * 85, h * (75 + 10 * i), Depth_Select_String[Depth][i], color, 1, size * 3);
				color = white_color;
			}

			
			if(Depth == 0)str.SuperString(w * 2, h * 71, "どうしようかしら", 0xffffff, 0, size * 2);
			if(Depth == 1)str.SuperString(w * 2, h * 71, "何で遊ぼうかしら", 0xffffff, 0, size * 2);
			if(Depth == 2)str.SuperString(w * 2, h * 71, "ドラゴンタイガーをやってみようかしら", 0xffffff, 0, size * 2);
			if(Depth == 3)str.SuperString(w * 2, h * 71, "カジノウォーをやってみようかしら", 0xffffff, 0, size * 2);

			/*カジノでの操作*/
			Update();
		}

		

		/*ゲームプレイ*/
		GamePlay(w,h,size);

	}

	void Update() {
		if (inp.f_up) {
			if (--Depth_Select[Depth] < 0) Depth_Select[Depth] = 1;
		}
		if (inp.f_down) {
			if (++Depth_Select[Depth] > 1) Depth_Select[Depth] = 0;
		}

		if (inp.space) {
			switch (Depth) {
				case 0:
					if (Depth_Select[0] == 0) Depth = 1;
					if (Depth_Select[0] == 1) g_GameState = GAME_BASE;
					Depth_Select[0] = 0;
					break;

				case 1:
					if (Depth_Select[1] == 0) Depth = 2;
					if (Depth_Select[1] == 1) Depth = 3;
					Depth_Select[1] = 0;
					break;

				case 2:
					if (Depth_Select[2] == 0) { Dragon_Tiger = true; Card_Init(); }
					if (Depth_Select[2] == 1) { DT_Info = true; Depth = 4; }
					Depth_Select[2] = 0;
					break;

				case 3:
					if (Depth_Select[3] == 0) { Casino_War = true; Card_Init(); }
					if (Depth_Select[3] == 1) { CW_Info = true; Depth = 5; }
					Depth_Select[3] = 0;
					break;

				case 4:
					if (inp.space) Depth = 2;
					DT_Info = false;
					break;

				case 5:
					if (inp.space) Depth = 3;
					CW_Info = false;
					break;
			}
		}

		if (inp.cancel) {
			if (Depth < 4) {
				Depth_Select[Depth] = 0;
				if (--Depth < 0) Depth = 0;
			}
		}
	}

	void GamePlay(float w,float h,int size) {

		SetFontSize(size * 2);

		/*ドラゴンタイガー*/
		if (Dragon_Tiger) {

			DrawExtendGraph(w * 20, h * 30, w * 40, h * 60, casino.Dragon_img, 1);			//ドラゴンの絵
			DrawExtendGraph(w * 60, h * 30, w * 80, h * 60, casino.Tiger_img, 1);			//トラの絵

			/*相手のカードの描画*/
			if (Back_or_Front[0] == 0) {
				DrawExtendGraph(w * Card_Status[0][0],								//ｘ座標
								h * Card_Status[0][1],								//ｙ座標
								(w * Card_Status[0][0] + w * Card_Status[0][2]),	//幅
								(h * Card_Status[0][1] + h * Card_Status[0][3]),	//高さ
								casino.Card_Back, 1);
			}
			else {
				DrawExtendGraph(w * Card_Status[0][0],								//ｘ座標
								h * Card_Status[0][1],								//ｙ座標
								(w * Card_Status[0][0] + w * Card_Status[0][2]),	//幅
								(h * Card_Status[0][1] + h * Card_Status[0][3]),	//高さ
								casino.Cards[Card_Status[0][4]], 1);
				
			}

			/*自分のカードの描画*/
			if (Back_or_Front[1] == 0) {
				DrawExtendGraph(w * Card_Status[1][0],								//ｘ座標
								h * Card_Status[1][1],								//ｙ座標
								(w * Card_Status[1][0] + w * Card_Status[1][2]),	//幅
								(h * Card_Status[1][1] + h * Card_Status[1][3]),	//高さ
								casino.Card_Back, 1);
			}
			else {
				DrawExtendGraph(w * Card_Status[1][0],								//ｘ座標
								h * Card_Status[1][1],								//ｙ座標
								(w * Card_Status[1][0] + w * Card_Status[1][2]),	//幅
								(h * Card_Status[1][1] + h * Card_Status[1][3]),	//高さ
								casino.Cards[Card_Status[1][4]], 1);
			}



			switch (DT_Phase) {
				case 0:																		//カードを配ります。
					DrawString(w * 2, h * 71, "では、カードをドラゴンとタイガーに配ります", 0xffffff, 1);
					++Anime_Count;
					if (Anime_Count < 50) {
						if (Card_Status[0][0] >= 25) Card_Status[0][0] -= 2;
						if (Card_Status[1][0] <= 55) Card_Status[1][0] += 2;
						if (Card_Status[0][1] <= 30) Card_Status[0][1] += 2;
						if (Card_Status[1][1] <= 30) Card_Status[1][1] += 2;
					}
					if (Anime_Count > 100) {
						DT_Phase = 1;
						Anime_Count = 0;
						Bet_Select = 0;
						Bet_Money = 0;
					}
					break;

				case 1:																		//ＢＥＴタイム
					DrawString(w * 2, h * 71, "何に賭けますか？", 0xffffff, 1);
					for (int i = 0; i < 4; i++) {
						if (Bet_Select == i) color = blue_color;
						str.SuperString(w * 85, h * (73 + (size / 2) * i), Bet_Select_String[i], color, 1, size * 2);
						color = white_color;
					}
					if (inp.f_up) {
						if (--Bet_Select < 0) Bet_Select = 3;
					}
					if (inp.f_down) {
						if (++Bet_Select > 3) Bet_Select = 0;
					}
					if (inp.space) {
						DT_Phase = 2;
					}
					break;

				case 2:
					DrawString(w * 2, h * 71, "いくらＢＥＴしますか\n上：　１Ｇ加算\n下：　１Ｇ減算\n右：　１０Ｇ加算\n左：　１０Ｇ減算\nボタン押下でＢＥＴ確定", 0xffffff, 1);
					DrawFormatString(w * 85, h * 71, 0xffffff, "BET金額：\n%9d\n\n所持金：\n%9d", Bet_Money, ch.Return_Base_Status(&ch, 0));
					if (inp.f_up) {
						Bet_Money += 1;
					}
					if (inp.f_down) {
						Bet_Money -= 1;
					}
					if (inp.f_right) {
						Bet_Money += 10;
					}
					if (inp.f_left) {
						Bet_Money -= 10;
					}

					if (Bet_Money < 0)Bet_Money = 0;
					if (Bet_Money > ch.Return_Base_Status(&ch, 0)) Bet_Money = ch.Return_Base_Status(&ch, 0);

					if (inp.space) {
						ch.Add_Base_Status(&ch, 0, -Bet_Money);
						DT_Phase = 3;
					}

					break;

				case 3:
					DrawString(w * 2, h * 71, "では、カードをめくります。", 0xffffff, 1);
					++Anime_Count;
					if (Anime_Count < 100) {
						;
					}
					else if (Anime_Count < 200) {
						Back_or_Front[0] = 1;
						Back_or_Front[1] = 1;
					}
					if (Anime_Count > 200) {
						Anime_Count = 0;
						DT_Phase = 4;
					}
					break;

				case 4:
					DrawString(w * 2, h * 71, "結果は..............\n", 0xffffff, 1);
					if ((Card_Status[0][4] % 13 + 1) > (Card_Status[1][4] % 13 + 1)) DT_Result = 0;
					if ((Card_Status[0][4] % 13 + 1) < (Card_Status[1][4] % 13 + 1)) DT_Result = 1;
					if ((Card_Status[0][4] % 13 + 1) == (Card_Status[1][4] % 13 + 1)) DT_Result = 2;
					if ((Card_Status[0][4]) == (Card_Status[1][4])) DT_Result = 3;

					if (Bet_Select == 0) {							//ドラゴンに賭けてたとき
						switch (DT_Result) {
							case 0:
								DT_Result_Money = Bet_Money * 2;
								break;

							case 1:
								DT_Result_Money = 0;
								break;

							case 2:
								DT_Result_Money = Bet_Money / 2;
								break;

							case 3:
								DT_Result_Money = Bet_Money / 2;
								break;
						}
					}
					if (Bet_Select == 1) {
						switch (DT_Result) {
							case 0:
								DT_Result_Money = 0;
								break;

							case 1:
								DT_Result_Money = Bet_Money * 2;
								break;

							case 2:
								DT_Result_Money = Bet_Money / 2;
								break;

							case 3:
								DT_Result_Money = Bet_Money / 2;
								break;
						}
					}
					if (Bet_Select == 2) {
						switch (DT_Result) {
							case 0:
								DT_Result_Money = 0;
								break;

							case 1:
								DT_Result_Money = 0;
								break;

							case 2:
								DT_Result_Money = Bet_Money * 11;
								break;

							case 3:
								DT_Result_Money = Bet_Money * 11;
								break;
						}
					}
					if (Bet_Select == 3) {
						switch (DT_Result) {
							case 0:
								DT_Result_Money = 0;
								break;

							case 1:
								DT_Result_Money = 0;
								break;

							case 2:
								DT_Result_Money = Bet_Money * 50;
								break;

							case 3:
								DT_Result_Money = Bet_Money * 50;
								break;
						}
					}
					DrawFormatString(w * 2, h * 75, 0xffffff, "「%s」です。%9dＧの払い戻しになります。", DT_Result_Sting[DT_Result], DT_Result_Money);
					

					str.SuperString(w * 85, h * 80, "戻る", 0xff0000, 1, size * 3);
					if (inp.space) {
						ch.Add_Base_Status(&ch, 0, DT_Result_Money);
						Depth = 0;
						DT_Phase = 0;
						Dragon_Tiger = false;
						DT_Result = 0;
						Bet_Money = 0;
						DT_Result_Money = 0;
					}

					break;
			}
		}

		/*カジノウォーをプレイ*/
		if (Casino_War) {

			/*相手のカードの描画*/
			if (Back_or_Front[0] == 0) {
				DrawExtendGraph(w * Card_Status[0][0],					//ｘ座標
					h * Card_Status[0][1],								//ｙ座標
					(w * Card_Status[0][0] + w * Card_Status[0][2]),	//幅
					(h * Card_Status[0][1] + h * Card_Status[0][3]),	//高さ
					casino.Card_Back, 1);
			}
			else {
				DrawExtendGraph(w * Card_Status[0][0],					//ｘ座標
					h * Card_Status[0][1],								//ｙ座標
					(w * Card_Status[0][0] + w * Card_Status[0][2]),	//幅
					(h * Card_Status[0][1] + h * Card_Status[0][3]),	//高さ
					casino.Cards[Card_Status[0][4]], 1);

			}

			/*自分のカードの描画*/
			if (Back_or_Front[1] == 0) {
				DrawExtendGraph(w * Card_Status[1][0],					//ｘ座標
					h * Card_Status[1][1],								//ｙ座標
					(w * Card_Status[1][0] + w * Card_Status[1][2]),	//幅
					(h * Card_Status[1][1] + h * Card_Status[1][3]),	//高さ
					casino.Card_Back, 1);
			}
			else {
				DrawExtendGraph(w * Card_Status[1][0],					//ｘ座標
					h * Card_Status[1][1],								//ｙ座標
					(w * Card_Status[1][0] + w * Card_Status[1][2]),	//幅
					(h * Card_Status[1][1] + h * Card_Status[1][3]),	//高さ
					casino.Cards[Card_Status[1][4]], 1);
			}

			switch (CW_Phase) {
				case 0:
					DrawString(w * 2, h * 51, "では、カードを配ります。", 0xffffff, 1);
					++Anime_Count;
					if (Anime_Count < 50) {
						if (Card_Status[0][0] >= 45) Card_Status[0][0] -= 1;
						if (Card_Status[1][0] >= 45) Card_Status[1][0] -= 1;
						if (Card_Status[0][1] <= 7) Card_Status[0][1] += 1;
						if (Card_Status[1][1] <= 50) Card_Status[1][1] += 2;
					}
					if (Anime_Count > 100) {
						CW_Phase = 1;
						Anime_Count = 0;
						Bet_Select = 0;
					}
					break;

				case 1:
					DrawString(w * 2, h * 51, "それではＢＥＴタイムに移ります。\nいくらＢＥＴしますか\n上：　１Ｇ加算\n下：　１Ｇ減算\n右：　１０Ｇ加算\n左：　１０Ｇ減算\nボタン押下でＢＥＴ確定", 0xffffff, 1);
					DrawFormatString(w * 85, h * 71, 0xffffff, "BET金額：\n%9d\n\n所持金：\n%9d", Bet_Money, ch.Return_Base_Status(&ch, 0));
					if (inp.f_up) {
						Bet_Money += 1;
					}
					if (inp.f_down) {
						Bet_Money -= 1;
					}
					if (inp.f_right) {
						Bet_Money += 10;
					}
					if (inp.f_left) {
						Bet_Money -= 10;
					}

					if (Bet_Money < 0)Bet_Money = 0;
					if (Bet_Money > ch.Return_Base_Status(&ch, 0)) Bet_Money = ch.Return_Base_Status(&ch, 0);

					if (inp.space) {
						ch.Add_Base_Status(&ch, 0, -Bet_Money);
						CW_Phase = 2;
					}
					break;

				case 2:
					DrawString(w * 2, h * 51, "「TIEベット」しますか？", 0xffffff, 1);
					for (int i = 0; i < 2; i++) {
						if (CW_Tie_Bet == i) color = blue_color;
						str.SuperString(w * 85, h * (73 + (size / 2) * i), CW_TieBet_String[i], color, 1, size * 2);
						color = white_color;
					}
					if (inp.f_up) {
						if (--CW_Tie_Bet < 0) CW_Tie_Bet = 1;
					}
					if (inp.f_down) {
						if (++CW_Tie_Bet > 1) CW_Tie_Bet = 0;
					}
					if (inp.space) {
						CW_Phase = 3;
					}
					break;

				case 3:
					DrawString(w * 2, h * 51, "では、カードをめくります。", 0xffffff, 1);
					++Anime_Count;
					if (Anime_Count < 100) {
						;
					}
					else if (Anime_Count < 200) {
						Back_or_Front[0] = 1;
						Back_or_Front[1] = 1;
					}
					if (Anime_Count > 200) {
						Anime_Count = 0;
						CW_Phase = 4;
					}
					break;

				case 4:
					
					if (CW_Tie_Bet == 1) {
						if ((Card_Status[0][4] % 13 + 1) > (Card_Status[1][4] % 13 + 1)) { CW_Phase = 5; CW_Result = 0; CW_Result_Money = 0; }
						if ((Card_Status[0][4] % 13 + 1) < (Card_Status[1][4] % 13 + 1)) { CW_Phase = 5; CW_Result = 0; CW_Result_Money = 0; }
						if ((Card_Status[0][4] % 13 + 1) == (Card_Status[1][4] % 13 + 1)) {
							CW_Phase = 5;
							CW_Result = 1;
							CW_Result_Money = Bet_Money * 11;
						}
					}
					else {
						if ((Card_Status[0][4] % 13 + 1) > (Card_Status[1][4] % 13 + 1)) { CW_Phase = 5; CW_Result = 0; CW_Result_Money = 0; }
						if ((Card_Status[0][4] % 13 + 1) < (Card_Status[1][4] % 13 + 1)) { CW_Phase = 5; CW_Result = 1; CW_Result_Money = Bet_Money * 2; }
						if ((Card_Status[0][4] % 13 + 1) == (Card_Status[1][4] % 13 + 1)) { CW_Result = 2; CW_Phase = 6; }
					}

					break;

				case 5:
					DrawString(w * 2, h * 51, "結果は..............\n", 0xffffff, 1);
					DrawFormatString(w * 2, h * 75, 0xffffff, "「%s」です。\n%9dＧ\nの払い戻しになります。", CW_Result_String[CW_Result], CW_Result_Money);

					

					str.SuperString(w * 85, h * 80, "戻る", 0xff0000, 1, size * 3);
					if (inp.space) {
						ch.Add_Base_Status(&ch, 0, CW_Result_Money);
						Bet_Money = 0;
						CW_Tie_Select = 0;
						CW_Result = 0;
						CW_Phase = 0;
						CW_Result_Money = 0;
						CW_Tie_Bet = 0;
						CW_Tie_Select = 0;
						Casino_War = false;
						Depth = 0;
					}
					break;

				case 6:
					DrawString(w * 2, h * 51, "結果は..............\n", 0xffffff, 1);
					DrawFormatString(w * 2, h * 75, 0xffffff, "「%s」です。\n「サレンダー(降参)」\nか\n「ウォー(同額ベットで再戦)」\nのいずれかを選択してください", CW_Result_String[CW_Result]);
					for (int i = 0; i < 2; i++) {
						if (CW_Tie_Select == i) color = blue_color;
						str.SuperString(w * 85, h * (73 + (size / 2) * i), CW_Tie_Select_String[i], color, 1, size * 2);
						color = white_color;
					}
					if (inp.f_up) {
						if (--CW_Tie_Select < 0) CW_Tie_Select = 1;
					}
					if (inp.f_down) {
						if (++CW_Tie_Select > 1) CW_Tie_Select = 0;
					}
					if (inp.space) {
						if (CW_Tie_Select == 0) {					//降参。ベット額の半分を支払う
							ch.Add_Base_Status(&ch, 0, Bet_Money / 2);
							Bet_Money = 0;
							CW_Tie_Select = 0;
							CW_Result = 0;
							CW_Phase = 0;
							CW_Result_Money = 0;
							CW_Tie_Bet = 0;
							CW_Tie_Select = 0;
							Casino_War = false;
							Depth = 0;
						}
						if (CW_Tie_Select == 1) {
							Bet_Money *= 2;
							Card_Init();
							CW_Phase = 0;
						}
					}
					
					break;
			}
		}
	}

	void Casino_Game_Info(float w,float h,int size) {
		
		/*ドラゴンタイガーの説明*/
		if (DT_Info) {
			DrawExtendGraph(w * 10, h * 5, w * 90, h * 65, casino.Dragon_Tiger_img, 1);
			str.SuperString(w * 2, h * 71, "ドラゴンタイガーのルールは以下の通りだ。\n・場のドラゴンとタイガーに一枚ずつカードが配られる\n・「ドラゴン」「タイガー」「タイ」「スーテッドタイ」\n　のいずれかにBETすることができる\n・賭けに勝つことが出来れば画像の配当金が得られる", 0xffffff, 0, size * 2);
		
			str.SuperString(w * 85, h * 80, "戻る", 0xff0000, 1, size * 3);
		}

		/*カジノウォーの説明*/
		if (CW_Info) {
			DrawExtendGraph(w * 10, h * 5, w * 90, h * 65, casino.Casino_War_img, 1);
			str.SuperString(w * 2, h * 71, "カジノウォーのルールは以下の通りだ。\n・ディーラーとプレイヤーにカードが一枚ずつ配られる\n・数字を確認して大きい方の勝ちとなる。ただし、タイの場合は\n　「サレンダー(降参)」か「ウォー(同額BETでもう一回)」\n　を選ぶことができる\n・TIEベットをした場合はTIE以外は負けとなる\n・賭けに勝つことが出来れば画像の配当金が得られる", 0xffffff, 0, size * 2);

			str.SuperString(w * 85, h * 80, "戻る", 0xff0000, 1, size * 3);
		}

	}

private:
	int Depth = 0;								//カジノメニューのれべる
	int Depth_Select[4] = { 0 };				//Depthごとの選択
	unsigned int color = 0xffffff;				//文字の色
	unsigned int white_color = 0xffffff;		//白色
	unsigned int blue_color = 0x6666aa;			//青色
	char Depth_Select_String[4][2][20] = {		//Depthごとの選択肢
		{"遊ぶ","街に戻る"},
		{"ドラゴンタイガー","カジノウォー"},
		{"やる","説明を聞く"},
		{"やる","説明を聞く"}
	};

	int Bet_Money = 0;							//掛け金
	int Bet_Select = 0;							//掛け選択
	char Bet_Select_String[4][20] = {			//選択肢
		"ドラゴン",
		"タイガー",
		"タイ",
		"スーテッドタイ"
	};
	int Anime_Count = 0;						//ゲームのアニメーションカウント
	int Card_Status[2][5] = { 0 };				//相手と自分のカードステータス(ｘ座標、ｙ座標、幅、高さ、数字とマーク)
	int Back_or_Front[2] = { 0 };				//相手と自分のカードが裏か表か(0：裏、1：表)
};

Casino_System cas;