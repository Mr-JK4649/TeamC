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

	/*人口ゲージのシステム*/
	GameSystem::Population_System();

	/*魔物ゲージのシステム*/
	GameSystem::Demon_System();

	/*発展ゲージのシステム*/
	GameSystem::Develop_System();

	/*食料ゲージのシステム*/
	GameSystem::Food_System();

}