/*�K�v�Ȃ�̓ǂݍ���*/
#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>

/*�w�b�_�t�@�C���ǂݍ���*/
#include "Input.h"
#include "State.h"
#include "LoadSource.h"
#include "WindowScale.h"


extern int g_GameState;
extern struct Input inp;

void DrawGameTitle(int width,int height) {

	struct TitleImage title;
	title.ImageInput(&title);
	
	
	inp.InputKey(&inp);
	inp.InputMouse(&inp);


	//�^�C�g���̉摜�\��
	DrawExtendGraph(0, 0, width, height, title.TitleImage, true);
	//DrawString();


	// �V�[����؂�ւ���
		if ((inp.MouseX > 100)
			&& (inp.MouseX < 600)
			&& (inp.MouseY > 485)
			&& (inp.MouseY < 540)) {

			if (inp.MouseFlg & MOUSE_INPUT_LEFT)g_GameState = GAME_INIT; // �Q�[���X�^�[�g�̑I��
			//StopSoundMem(g_TitleBGM);
		}
		else if ((inp.MouseX > 825)
			&& (inp.MouseX < 1095)
			&& (inp.MouseY > 485)
			&& (inp.MouseY < 540)) {

			if (inp.MouseFlg & MOUSE_INPUT_LEFT)g_GameState = GAME_END;  // �Q�[���G���h�̑I��
			//StopSoundMem(g_TitleBGM);
		}

}


