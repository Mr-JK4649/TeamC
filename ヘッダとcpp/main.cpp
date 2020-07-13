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

Input inp;
String str;

/*****************************************************
 * �v���O�����̊J�n
 ****************************************************/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_
	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {


	SetMainWindowText("�i�j�`");		// �^�C�g����ݒ�

	ChangeWindowMode(TRUE);							// �E�B���h�E���[�h�ŋN��

	/**********************�摜�̑傫����ς�����*************************/
	/**/WindowScaler scale;											 	 /**/
	/**/scale.GetWindwScale(&scale);								 	 /**/
	/**/SetGraphMode(scale.Width, scale.Height, 16);					 /**/
	/***********************************************************************/


	if (DxLib_Init() == -1)							// DX���C�u�����̏���������
		return -1;

	SetDrawScreen(DX_SCREEN_BACK);					// �`����ʂ𗠂ɂ���


	g_GameState = GAME_TITLE;

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && g_GameState != END/* && !(g_KeyFlg & PAD_INPUT_START)*/) {



		ClearDrawScreen();														// ��ʂ̏�����

		inp.InputKey(&inp);
		inp.InputMouse(&inp);

		switch (g_GameState) {

		case GAME_TITLE:	DrawGameTitle(scale.Width, scale.Height); break;		//�Q�[���^�C�g������

		//case GAME_INIT:		GameInit();  break;									//�Q�[����������

		//case GAME_S_SELECT:	GameSSelect(scale.Width, scale.Height);  break;		//�X�e�[�W�I����ʏ���

		case GAME_BASE:		DrawGameMain(scale.Width, scale.Height);  break;		//�Q�[�����C����ʏ���

		//case GAME_RESULT:	DrawGameResult(scale.Width, scale.Height); break;		//�Q�[�����C������

		//case GAME_OVER:		DrawGameOver(scale.Width, scale.Height); break;		// �Q�[���I�[�o�[�`�揈��

		//case GAME_END:		DrawEnd(scale.Width, scale.Height); break;			// �Q�[���I�[�o�[�`�揈��

		}


		ScreenFlip();    // ����ʂ̓��e��\��ʂɔ��f



	}

	DxLib_End(); // DX���C�u�����g�p�̏I������

	return 0; // �\�t�g�̏I��
}

