/*�K�v�Ȃ�̓ǂݍ���*/
#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>
#include <windows.h>


/*�w�b�_�t�@�C���̓ǂݍ���*/
#include "header.h"
#include "function.h"
#include "Input.h"
#include "string.h"


#pragma warning(disable : 4244)
#pragma warning(disable : 26812)
#pragma warning(disable : 26451)


/********************************************************************
* �ϐ��̐錾
********************************************************************/
int g_GameState;			//�Q�[���̃V�[���Ǘ�
//void DrawHatake(int Width, int Height);
//void Game_Hatake(int Width, int Height);
Input inp;
String str;
WindowScaler scale;

/*****************************************************
 * �v���O�����̊J�n
 ****************************************************/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_
	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {


	SetMainWindowText("�i�j�`");		// �^�C�g����ݒ�

	ChangeWindowMode(TRUE);							// �E�B���h�E���[�h�ŋN��

	/**********************�摜�̑傫����ς�����*************************/
	/**/										 	 /**/
	/**/scale.GetWindwScale(&scale);								 	 /**/
	/**/SetGraphMode(scale.Width, scale.Height, 16);					 /**/
	/***********************************************************************/


	if (DxLib_Init() == -1)							// DX���C�u�����̏���������
		return -1;

	SetDrawScreen(DX_SCREEN_BACK);					// �`����ʂ𗠂ɂ���

	//Init();										//�摜�≹�y�Ȃǂ̃t�@�C��������������

	g_GameState = GAME_INIT;

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && g_GameState != END/* && !(g_KeyFlg & PAD_INPUT_START)*/) {



		ClearDrawScreen();														// ��ʂ̏�����

		inp.InputKey(&inp);
		inp.InputMouse(&inp);

		switch (g_GameState) {

		case GAME_TITLE:	DrawGameTitle(scale.Width, scale.Height); break;		//�Q�[���^�C�g������

		case GAME_INIT:		Init();  break;											//�Q�[����������

		case GAME_STORY:	Story(scale.Width, scale.Height); break;				//�Q�[���V�[�P���X

		//case GAME_S_SELECT:	GameSSelect(scale.Width, scale.Height);  break;		//�X�e�[�W�I����ʏ���

		case GAME_DUNGEON:  DrawGameDungeon(scale.Width, scale.Height); break;			//�Q�[���_���W������ʏ���

		case GAME_BASE:		DrawGameMain(scale.Width, scale.Height);  break;		//�Q�[�����C����ʏ���

		case GAME_SHOP:		Shop_Draw(scale.Width, scale.Height);	break;			//���_�̓X

		case GAME_HOME:		Home_Draw(scale.Width, scale.Height); break;			//����

		case GAME_WORK:		Work_Draw(scale.Width, scale.Height); break;			//�d���Љ

		//case GAME_HATAKE: Game_Hatake(scale.Width, scale.Height); break;			//���֐�

		case GAME_CASINO:	Casino_Draw(scale.Width, scale.Height);	break;			//�J�W�m

		//case GAME_RESULT:	DrawGameResult(scale.Width, scale.Height); break;		//�Q�[�����C������

		//case GAME_OVER:		DrawGameOver(scale.Width, scale.Height); break;		// �Q�[���I�[�o�[�`�揈��

		//case GAME_END:	DrawEnd(scale.Width, scale.Height); break;				// �Q�[���I�[�o�[�`�揈��

		}

		/*���Ԃ̍X�V�Ƃ��������*/
		if (g_GameState == GAME_BASE ||
			g_GameState == GAME_SHOP ||
			g_GameState == GAME_HOME ||
			g_GameState == GAME_WORK ||
			g_GameState == GAME_HATAKE ||
			g_GameState == GAME_CASINO) {
			GameSystem();
		}

		ScreenFlip();    // ����ʂ̓��e��\��ʂɔ��f
	}

	DxLib_End(); // DX���C�u�����g�p�̏I������

	return 0; // �\�t�g�̏I��
}