#include "GameSys.h"


void GameSystem() {
	
	/*時間の更新*/
	ch.Add_Base_Status(&ch, 2, ch.Add_Time_num);

	/*Menuで必要なやつをCharacterから移す*/
	for (int i = 0; i < 3; i++) {
		menu.B_Status_C(i, ch.Return_Base_Status(&ch, i));
	}

	/*建物から出てきたときの向き修正*/
	switch (g_GameState) {
		case GAME_CASINO:
		case GAME_WORK:
		case GAME_SHOP:
		case GAME_HOME:
			ch.num = 6;
			break;
	}

	/*ゲージアイコンの表示*/
	DrawExtendGraph(scale.Width / 100.0f * 1, scale.Height / 100.0f * 93, scale.Width / 100.0f * 5, scale.Height / 100.0f * 99, base.Gage_Icon, 1);

	/*ゲージの描画*/
	if (menu.isGage_Menu) {
		const float w100 = scale.Width / 100.0f;
		const float h100 = scale.Height / 100.0f;

		/*ゲージのボックス*/
		DrawRoundRect(w100,		h100 * 40,	   w100 * 40,	  h100 * 99,	 10, 10, 0x444444, 1);
		DrawRoundRect(w100,		h100 * 40,	   w100 * 40,	  h100 * 99,	 10, 10, 0xaaaaaa, 0);
		DrawRoundRect(w100 + 1, h100 * 40 + 1, w100 * 40 - 1, h100 * 99 - 1, 10, 10, 0xffffff, 0);

		/*ゲージの描画*/
		menu.DrawGage(w100,h100);
	}
	/*ゲージフラグの切り替え*/
	if (inp.sele) {
		if (!menu.isGage_Menu &&
			!menu.isMenu &&
			!menu.isBuilding_Enter &&
			!str.setTex) menu.isGage_Menu = true;
		else menu.isGage_Menu = false;
	}
	

	/*人口ゲージのシステム*/
	GameSystem::Population_System();

	/*魔物ゲージのシステム*/
	GameSystem::Demon_System();

	/*発展ゲージのシステム*/
	GameSystem::Develop_System();

	/*食料ゲージのシステム*/
	GameSystem::Food_System();

}