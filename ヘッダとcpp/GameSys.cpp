#include "GameSys.h"

void GameSystem() {
	
	/*���Ԃ̍X�V*/
	ch.Add_Base_Status(&ch, 2, ch.Add_Time_num);

	/*Menu�ŕK�v�Ȃ��Character����ڂ�*/
	for (int i = 0; i < 3; i++) {
		menu.B_Status_C(i, ch.Return_Base_Status(&ch, i));
	}

	/*��������o�Ă����Ƃ��̌����C��*/
	switch (g_GameState) {
		case GAME_CASINO:
		case GAME_WORK:
		case GAME_SHOP:
		case GAME_HOME:
			ch.num = 6;
			break;
	}

	/*�l���Q�[�W�̃V�X�e��*/
	GameSystem::Population_System();

	/*�����Q�[�W�̃V�X�e��*/
	GameSystem::Demon_System();

	/*���W�Q�[�W�̃V�X�e��*/
	GameSystem::Develop_System();

	/*�H���Q�[�W�̃V�X�e��*/
	GameSystem::Food_System();

}