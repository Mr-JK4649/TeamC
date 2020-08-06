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

	/*�Q�[�W�A�C�R���̕\��*/
	DrawExtendGraph(scale.Width / 100.0f * 1, scale.Height / 100.0f * 93, scale.Width / 100.0f * 5, scale.Height / 100.0f * 99, base.Gage_Icon, 1);

	/*�Q�[�W�̕`��*/
	if (menu.isGage_Menu) {
		const float w100 = scale.Width / 100.0f;
		const float h100 = scale.Height / 100.0f;

		/*�Q�[�W�̃{�b�N�X*/
		DrawRoundRect(w100,		h100 * 40,	   w100 * 40,	  h100 * 99,	 10, 10, 0x444444, 1);
		DrawRoundRect(w100,		h100 * 40,	   w100 * 40,	  h100 * 99,	 10, 10, 0xaaaaaa, 0);
		DrawRoundRect(w100 + 1, h100 * 40 + 1, w100 * 40 - 1, h100 * 99 - 1, 10, 10, 0xffffff, 0);

		/*�Q�[�W�̕`��*/
		menu.DrawGage(w100,h100);
	}
	/*�Q�[�W�t���O�̐؂�ւ�*/
	if (inp.sele) {
		if (!menu.isGage_Menu &&
			!menu.isMenu &&
			!menu.isBuilding_Enter &&
			!str.setTex) menu.isGage_Menu = true;
		else menu.isGage_Menu = false;
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