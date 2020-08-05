#pragma once

#include "character.h"
#include "Menu.h"

#pragma warning(disable : 4244)
#pragma warning(disable : 26451)

struct GameSystem {

	static int Exit_Hatake;			//�����o������
	static int Enter_Hatake;			//�����ɓ���������

	/*�l���Q�[�W�̃V�X�e��*/
	static void Population_System() {
		int GameTime = ch.Return_Base_Status(&ch, 2);
		float Population_Par = (menu.Return_Gage_Para(0) / menu.Return_Gage_Max(0)) * 100;

		if (GameTime % 600 == 0)menu.Inclease_Gage(0, GetRand(3));				//�Q�[��������10�b���Ƃ�0�`3�l�l����������
		if (Population_Par - menu.Return_Gage_Para(1) > -25) {				//�����Q�[�W�Ɛl���Q�[�W�̍���25������
			if (GameTime % 2400 == 0)menu.Inclease_Gage(0, -GetRand(2));		//�Q�[��������40�b���Ƃ�0�`2�l�l��������
		}
		else if (Population_Par - menu.Return_Gage_Para(1) > -40) {			//�����Q�[�W�Ɛl���Q�[�W�̍���25���ȏ�
			if (GameTime % 1200 == 0)menu.Inclease_Gage(0, -2);					//�Q�[��������20�b���Ƃ�2�l�l��������
		}
		else if (Population_Par - menu.Return_Gage_Para(1) <= -40) {			//�����Q�[�W�Ɛl���Q�[�W�̍���40���ȏ�
			g_GameState = GAME_OVER;											//�Q�[���I�[�o�[
		}

	}

	/*�����Q�[�W�̃V�X�e��*/
	static void Demon_System() {
		int GameTime = ch.Return_Base_Status(&ch, 2);

		if (GameTime % 1200 == 0) {												//�Q�[��������20�b���Ƃɖ����Q�[�W��1��������
			menu.Inclease_Gage(1, 1);		
		}
	}

	/*���W�Q�[�W�̃V�X�e��*/
	static void Develop_System() {
		/*���W�Q�[�W�����^���ɂȂ�����ő�l��L�΂�*/
		if (menu.Return_Gage_Para(2) >= menu.Return_Gage_Max(2)) {
			menu.Incleace_Gage_Max(2, menu.Return_Gage_Max(2) / 3);
		}
	}

	/*�H���Q�[�W�̃V�X�e��*/
	static void Food_System() {
		int GameTime = ch.Return_Base_Status(&ch, 2);
		int Population_Par = (menu.Return_Gage_Para(0) / menu.Return_Gage_Max(0))*100;

		if (GameTime % 1500 == 0) {												//�Q�[��������25�b���ƂɐH���Q�[�W�l���Q�[�W/25������
			menu.Inclease_Gage(3, -(Population_Par/25));							
		}

	}


	/*���̎��Ԃ�����֐�*/
	static void Input_Time(int num) {
		if (num == 0)Exit_Hatake = ch.Return_Base_Status(&ch, 2);				//�����o�����̎��Ԃ�����
		if (num == 1)Enter_Hatake = ch.Return_Base_Status(&ch, 2);				//�����o�����̎��Ԃ�����
	}

	static int Return_Hatake_Time() {
		
		return (Enter_Hatake - Exit_Hatake);
	}

};