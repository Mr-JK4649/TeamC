/*�K�v�Ȃ�̓ǂݍ���*/
#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>
#include <windows.h>


/*�w�b�_�t�@�C���̓ǂݍ���*/



#pragma warning(disable : 4244)
#pragma warning(disable : 26812)
#pragma warning(disable : 26451)


/********************************************************************
* �ϐ��̐錾
********************************************************************/

int g_GameState;			//�Q�[���̃V�[���Ǘ�



/********************************************************************
* �\���̂̐錾
********************************************************************/



/*****************************************************
 * �v���O�����̊J�n
 ****************************************************/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_
	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {


	SetMainWindowText("�W�������ŗV�ڂ�!!");		// �^�C�g����ݒ�

	ChangeWindowMode(TRUE);							// �E�B���h�E���[�h�ŋN��

	/**********************�摜�̑傫����ς�����*************************/
	/**/struct WindowScaler scale;
	/**/scale.GetWindwScale(&scale);
	/**/SetGraphMode(scale.Width, scale.Height,16);
	/***********************************************************************/


	if (DxLib_Init() == -1)							// DX���C�u�����̏���������
		return -1;

	SetDrawScreen(DX_SCREEN_BACK);					// �`����ʂ𗠂ɂ���


	//�T�E���h�ǂݍ���
	if (LoadSounds() == -1)
		return -1;

	g_GameState = GAME_TITLE;

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && g_GameState != END/* && !(g_KeyFlg & PAD_INPUT_START)*/) {


		inp.InputKey(&inp);
		inp.InputMouse(&inp);


		ClearDrawScreen();														// ��ʂ̏�����

		switch (g_GameState) {

		case GAME_TITLE:	DrawGameTitle(scale.Width,scale.Height); break;		//�Q�[���^�C�g������

		case GAME_INIT:		GameInit();  break;									//�Q�[����������

		case GAME_C_SELECT:	GameCSelect(scale.Width, scale.Height);  break;	    //�L�����I����ʏ���

		case GAME_S_SELECT:	GameSSelect(scale.Width, scale.Height);  break;		//�X�e�[�W�I����ʏ���

		case GAME_MAIN:		DrawGameMain(scale.Width, scale.Height);  break;	//�Q�[�����C����ʏ���

		case GAME_RESULT:	DrawGameResult(scale.Width, scale.Height); break;	//�Q�[�����C������

		case GAME_OVER:		DrawGameOver(scale.Width, scale.Height); break;		// �Q�[���I�[�o�[�`�揈��

		case GAME_END:		DrawEnd(scale.Width, scale.Height); break;			// �Q�[���I�[�o�[�`�揈��

		}

		if (inp.Cclick) DebugMode(scale.Width, scale.Height, inp.MouseX, inp.MouseY);
		

		ScreenFlip();    // ����ʂ̓��e��\��ʂɔ��f

		

	}

	DxLib_End(); // DX���C�u�����g�p�̏I������

	return 0; // �\�t�g�̏I��
}



/********************************************************************
* �Q�[������������
********************************************************************/
void GameInit(void) {
	charaA->jumpForce = 8.0f;
	charaB->jumpForce = 8.0f;
	charaB->px = 840.0f;
	charaA->speed = 5.0f;
	g_GameState = GAME_C_SELECT;
}


/********************************************************************
* �Q�[���G���h�`�揈��
********************************************************************/
void DrawEnd(int width, int height) {
	SetFontSize(50);
	DrawString(705,405,"�Q�[�����I�����܂�",0xffffff,1);
	g_GameState = END;
}

/********************************************************************
* �L�����I���V�[��
********************************************************************/
void GameCSelect(int width, int height) {

	struct WindowScaler scale;
	scale.GetWindwScale(&scale);

	inp.InputKey(&inp);
	inp.InputMouse(&inp);

	struct SelectImage chara;
	chara.ImageInput(&chara);

	if (inp.MouseX >= width - 65 && inp.MouseX <= width && inp.MouseY >= 315 && inp.MouseY <= 372)chara.Num = 1;
	else if (inp.MouseX >= 0 && inp.MouseX <= 65 && inp.MouseY >= 315 && inp.MouseY <= 372)chara.Num = 2;
	else if (inp.MouseX >= 470 && inp.MouseX <= 685 && inp.MouseY >= 580 && inp.MouseY <= 670) chara.Num = 3;
	else { chara.Num = 0; DrawString(width / 2, height / 2, "�Ȃ񂩂�������", 0xffffff); }

	DrawExtendGraph(0, 0, width, height, chara.SadaoSelectImage[chara.Num], true);

	if (inp.MouseX >= 470 && inp.MouseX <= 685 && inp.MouseY >= 580 && inp.MouseY <= 670) {
		if (inp.NowMouse & MOUSE_INPUT_LEFT)g_GameState = GAME_S_SELECT;
	}
	/*DrawLine(0,inp.MouseY,width,inp.MouseY,0x0000ff,1);
	DrawLine(inp.MouseX,0,inp.MouseX,height,0xff0000,1);
	DrawFormatString(3, 5, 0x0000ff, "MouseX = %d", inp.MouseX);
	DrawFormatString(3, 25, 0xff0000, "MouseY = %d", inp.MouseY);
	DrawFormatString(3, 45, 0x0000ff, "MouseX = %04d %", inp.MouseX/scale.hiX);
	DrawFormatString(3, 65, 0xff0000, "MouseY = %04d %", inp.MouseY/scale.hiY);*/
	
}


/*******************************************************************
* �X�e�[�W�Z���^k
********************************************************************/
void GameSSelect(int width, int height) {
	g_GameState = GAME_MAIN;
}

/********************************************************************
*							�Q�[���V�[��							*
*-------------------------------------------------------------------*
*										*
*		*
********************************************************************/

float SetAngle(int angle);			//�x���@�Ŋp�x�𓾂�
void Flashing(int paturn);			//�d�C�̓_�ł������ǂ�	

//void DrawGameMain(int width, int height) {
//
//	struct Escape esc;
//	esc.ImageInput(&esc);
//
//	static int VecNum = 0;
//	
//	//�w�i
//	DrawExtendGraph(0, 0, width, height, esc.EscapeRoom[g_GraphNum], true);
//
//	if (isOhuda) {
//		DrawRotaGraph(540, 300, 1.0f, SetAngle(200), esc.Ohuda, 1);
//		DrawRotaGraph(540, 400, 1.0f, SetAngle(225), esc.Ohuda, 1);
//		DrawRotaGraph(530, 550, 1.0f, SetAngle(30), esc.Ohuda, 1);
//
//		DrawRotaGraph(680, 300, 1.0f, SetAngle(180), esc.Ohuda, 1);
//		DrawRotaGraph(600, 200, 1.0f, SetAngle(180), esc.Ohuda, 1);
//		DrawRotaGraph(630, 200, 1.0f, SetAngle(150), esc.Ohuda, 1);
//		DrawRotaGraph(690, 200, 1.0f, SetAngle(250), esc.Ohuda, 1);
//		DrawRotaGraph(750, 200, 1.0f, SetAngle(70), esc.Ohuda, 1);
//
//		DrawRotaGraph(830, 500, 1.0f, SetAngle(135), esc.Ohuda, 1);
//		DrawRotaGraph(830, 600, 1.0f, SetAngle(45), esc.Ohuda, 1);
//		DrawRotaGraph(830, 250, 1.0f, SetAngle(135), esc.Ohuda, 1);
//	}
//	
//	if (!isEvent) {
//
//		if (inp.MouseX <= 100) {
//			DrawRotaGraph(80, 400, 0.05f, SetAngle(180), esc.Arrow, 1);
//			if (inp.MouseFlg & MOUSE_INPUT_LEFT) {
//				if (--VecNum < 0) VecNum = 3;
//
//			}
//		}
//		if (inp.MouseX >= 1340) {
//			DrawRotaGraph(1360, 400, 0.05f, SetAngle(0), esc.Arrow, 1);
//			if (inp.MouseFlg & MOUSE_INPUT_LEFT) {
//				if (++VecNum > 3) VecNum = 0;
//
//			}
//		}
//	}
	/*struct SelectImage chara;
	chara.ImageInput(&chara);

	DrawExtendGraph(0, 0, width, height, chara.SelectImage, true);

	if (jump[0] || inp.MouseFlg & MOUSE_INPUT_LEFT) {
		g_GameState = GAME_MAIN;
	}*/
//}




/********************************************************************
* �Q�[���N���A�`�揈��
********************************************************************/
void DrawGameResult(int width, int height) {

	SetFontSize(45);
	DrawString(width/2-100,height/2,"�E�o�����I�I�I�I",0x00ff00,1);

}

/********************************************************************
* �Q�[���I�[�o�[�`�揈��
********************************************************************/
void DrawGameOver(int width, int height) {
	
}


/********************************************************************
* �L�[���͊Ǘ�
********************************************************************/
void KeyInput() {

	//�v���C���[1�p
	static int OldKey1, NowKey1 = GetJoypadInputState(DX_INPUT_KEY_PAD1), KeyFlg1;
	OldKey1 = NowKey1;									//�O�t���[���̃L�[�擾
	NowKey1 = GetJoypadInputState(DX_INPUT_KEY_PAD1);	//���t���[���̃L�[�擾
	KeyFlg1 = NowKey1 & ~OldKey1;						//�L�[�t���O

	if (NowKey1 & PAD_INPUT_LEFT) 
	{
		charaA->speed = 5.0f;
		left[0] = true; charaA->vector = -1; 
	}
	else if (NowKey1 & PAD_INPUT_RIGHT)
	{
		charaA->speed = 5.0f;
		right[0] = true; charaA->vector = 1;
	}
	else { left[0] = false; right[0] = false; charaA->oldVec = charaA->vector; /*charaA->vector = 0;*/ }
	if (NowKey1 & PAD_INPUT_UP)			up[0] = true;		else    up[0] = false;
	if (NowKey1 & PAD_INPUT_DOWN)		down[0] = true;		else  down[0] = false;
	if (KeyFlg1 & PAD_INPUT_A)			jump[0] = !jump[0];
	if (KeyFlg1 & PAD_INPUT_3)			XButton[0] = true;
	if (KeyFlg1 & PAD_INPUT_4)			YButton[0] = true;
	if (KeyFlg1 & PAD_INPUT_B)			kettei = true;		else kettei = false;

	//�v���C���[2�p
	//static int OldKey2, NowKey2 = GetJoypadInputState(DX_INPUT_PAD2), KeyFlg2;
	//OldKey2 = NowKey2;									//�O�t���[���̃L�[�擾
	//NowKey2 = GetJoypadInputState(DX_INPUT_PAD2);		//���t���[���̃L�[�擾
	//KeyFlg2 = NowKey2 & ~OldKey2;						//�L�[�t���O

	//if (NowKey2 & PAD_INPUT_LEFT)		left[1] = true;		else  left[1] = false;
	//if (NowKey2 & PAD_INPUT_RIGHT)		right[1] = true;	else right[1] = false;
	//if (NowKey2 & PAD_INPUT_UP)			up[1] = true;		else    up[1] = false;
	//if (NowKey2 & PAD_INPUT_DOWN)		down[1] = true;		else  down[1] = false;
	//if (KeyFlg2 & PAD_INPUT_A)			jump[1] = true;
	//if (KeyFlg2 & PAD_INPUT_3)			XButton[1] = true;
	//if (KeyFlg2 & PAD_INPUT_4)			YButton[1] = true;

}


/********************************************************************
* �摜�ǂݍ���
********************************************************************/
//int LoadImages() {
//
//	FILE* soiya;
//	fopen_s(&soiya,"soiya.txt", "w");
//
//	//�^�C�g��
//	if ((g_TitleImage = LoadGraph("images/title.png")) == -1) { 
//		fwrite("�^�C�g���̉摜�ǂݍ��݂ŃG���[", sizeof(char),50, soiya);
//		return -1;
//	}
//
//	//�X�e�[�W
//	if ((g_Dh[0] = LoadGraph("images/h1.png")) == -1) {
//		fwrite("�E�o�摜1�ǂݍ��݂ŃG���[", sizeof(char), 50, soiya);
//		return -1;
//	}
//
//	if ((g_Dh[1] = LoadGraph("images/h2-3.png")) == -1) {
//		fwrite("�E�o�摜2�ǂݍ��݂ŃG���[", sizeof(char), 50, soiya);
//		return -1;
//	}
//
//	if ((g_Arrow = LoadGraph("images/���.png")) == -1) {
//		fwrite("���ǂݍ��݂ŃG���[", sizeof(char), 50, soiya);
//		return -1;
//	}
//
//	if ((g_Ohuda = LoadGraph("images/���D2.png")) == -1) {
//		fwrite("���D�ǂݍ��݂ŃG���[", sizeof(char), 50, soiya);
//		return -1;
//	}
//
//
//	//�L�����̉摜
//	if ((g_HorrorImage[0] = LoadGraph("images/�z���[�L����.png")) == -1) {
//		fwrite("�z���[�L�����摜�ǂݍ��݂ŃG���[", sizeof(char), 50, soiya);
//		return -1;
//	}
//
//	if ((g_HorrorImage[1] = LoadGraph("images/�z���[�L�����t.png")) == -1) {
//		fwrite("�z���[�L�����摜�ǂݍ��݂ŃG���[", sizeof(char), 50, soiya);
//		return -1;
//	}
//
//	if ((g_SelectImage = LoadGraph("images/SadaoSelect.jpg")) == -1) {
//		fwrite("�L�����I���摜�ǂݍ��݂ŃG���[", sizeof(char), 50, soiya);
//		return -1;
//	}
//
//
//
//	////�X�e�[�W
//	//if ((g_StageImage = LoadGraph("images/stage.png")) == -1)return -1;
//
//	////�Q�[���N���A
//	//if ((g_GameClearImage = LoadGraph("images/gameclear.png")) == -1)return -1;
//
//	////�Q�[���I�[�o�[
//	//if ((g_GameOverImage = LoadGraph("images/gameover.png")) == -1)return -1;
//
//	////�u���b�N�摜
//	//if (LoadDivGraph("images/block.png", 10, 10, 1, 48, 48, g_BlockImage) == -1)return -1;
//
//	////�i���o�[�摜�̓ǂݍ���
//	//if (LoadDivGraph("images/number.png", 10, 10, 1, 60, 120, g_NumberImage) == -1)return -1;
//
//	fclose(soiya);
//
//	return 0;
//}

/********************************************************************
* �T�E���h�ǂݍ���
********************************************************************/
int LoadSounds(void) {

	////�^�C�g��
	//if ((g_TitleBGM = LoadSoundMem("sounds/muci_hono_r01.mp3")) == -1)return -1;
	////�N���A
	//if ((g_GameClearSE = LoadSoundMem("sounds/muci_fan_06.mp3")) == -1)return -1;
	////�I�[�o�[
	//if ((g_GameOverSE = LoadSoundMem("sounds/muci_bara_07.mp3")) == -1)return -1;
	////�}�E�X�N���b�N
	//if ((g_ClickSE = LoadSoundMem("sounds/ta_ta_warekie02.mp3")) == -1)return -1;
	////�u���b�N����
	//if ((g_TitleBGM = LoadSoundMem("sounds/ani_ta_biyon02.mp3")) == -1)return -1;
	////�u���b�N�ړ�
	//if ((g_TitleBGM = LoadSoundMem("sounds/ta_ta_doron01.mp3")) == -1)return -1;



	return 0;
}

