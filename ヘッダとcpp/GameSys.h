#pragma once

#include "character.h"
#include "Menu.h"

#pragma warning(disable : 4244)
#pragma warning(disable : 26451)

struct GameSystem {

	static int Exit_Hatake;			//畑を出た時間
	static int Enter_Hatake;			//畑をに入った時間

	/*人口ゲージのシステム*/
	static void Population_System() {
		int GameTime = ch.Return_Base_Status(&ch, 2);
		float Population_Par = (menu.Return_Gage_Para(0) / menu.Return_Gage_Max(0)) * 100;

		if (GameTime % 600 == 0)menu.Inclease_Gage(0, GetRand(3));				//ゲーム内時間10秒ごとに0～3人人口が増える
		if (Population_Par - menu.Return_Gage_Para(1) > -25) {				//魔物ゲージと人口ゲージの差が25％未満
			if (GameTime % 2400 == 0)menu.Inclease_Gage(0, -GetRand(2));		//ゲーム内時間40秒ごとに0～2人人口が減る
		}
		else if (Population_Par - menu.Return_Gage_Para(1) > -40) {			//魔物ゲージと人口ゲージの差が25％以上
			if (GameTime % 1200 == 0)menu.Inclease_Gage(0, -2);					//ゲーム内時間20秒ごとに2人人口が減る
		}
		else if (Population_Par - menu.Return_Gage_Para(1) <= -40) {			//魔物ゲージと人口ゲージの差が40％以上
			g_GameState = GAME_OVER;											//ゲームオーバー
		}

	}

	/*魔物ゲージのシステム*/
	static void Demon_System() {
		int GameTime = ch.Return_Base_Status(&ch, 2);

		if (GameTime % 1200 == 0) {												//ゲーム内時間20秒ごとに魔物ゲージが1％増える
			menu.Inclease_Gage(1, 1);		
		}
	}

	/*発展ゲージのシステム*/
	static void Develop_System() {
		/*発展ゲージが満タンになったら最大値を伸ばす*/
		if (menu.Return_Gage_Para(2) >= menu.Return_Gage_Max(2)) {
			menu.Incleace_Gage_Max(2, menu.Return_Gage_Max(2) / 3);
		}
	}

	/*食料ゲージのシステム*/
	static void Food_System() {
		int GameTime = ch.Return_Base_Status(&ch, 2);
		int Population_Par = (menu.Return_Gage_Para(0) / menu.Return_Gage_Max(0))*100;

		if (GameTime % 1500 == 0) {												//ゲーム内時間25秒ごとに食料ゲージ人口ゲージ/25％減る
			menu.Inclease_Gage(3, -(Population_Par/25));							
		}

	}


	/*畑の時間を入れる関数*/
	static void Input_Time(int num) {
		if (num == 0)Exit_Hatake = ch.Return_Base_Status(&ch, 2);				//畑を出た時の時間を入れる
		if (num == 1)Enter_Hatake = ch.Return_Base_Status(&ch, 2);				//畑を出た時の時間を入れる
	}

	static int Return_Hatake_Time() {
		
		return (Enter_Hatake - Exit_Hatake);
	}

};