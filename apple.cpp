#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>

#pragma warning(disable : 4244)
#pragma warning(disable : 26812)
#pragma warning(disable : 26451)

#define SELECT_ITEM 7
#define WIDTH 970	//��ʉ��T�C�Y
#define HEIGHT 600	//��ʏc�T�C�Y
/********************************************************************
* �񋓑̂̐錾
********************************************************************/
enum GAME_MODE {
	GAME_TITLE,
	GAME_INIT,
	GAME_END,
	GAME_MAIN,
	GAME_RESULT,
	GAME_OVER,
	END = 99
};

/********************************************************************
* �萔�̐錾
********************************************************************/

/********************************************************************
* �\���̂̐錾
********************************************************************/
//typedef struct {
//	int x1, y1, x2, y2;
//	int w, h;
//}Cursor;

typedef struct {
	int x, y;
	int w, h;
	int img;
	int main_img;
	int flg;
}Selectitem;


/***********************************************
  * �֐��̃v���g�^�C�v�錾
***********************************************/
// �Q�[������������
void GameInit(void);
// �Q�[�����C������
void GameMain(void);
// �Q�[���^�C�g���`�揈��
void DrawGameTitle(void);
// �G���h�`�揈��
void DrawEnd(void);
// �Q�[���N���A�[�̏���
void DrawGameResult(void);
// �Q�[���I�[�o�[�`�揈��
void DrawGameOver(void);
//�L�[�ǂݍ���
int UpdatKey();
//�X�e�[�W�Z���N�g���
void Stageselect(void);
void StageselectDraw(void);

void Keyselect(void);
void Mouseselect(void);
// �摜�ǂݍ���
int LoadImages();

//�T�E���h
int LoadSounds(void);

/********************************************************************
* �ϐ��̐錾
********************************************************************/
int g_OldKey;    // �O��̓��̓L�[
int g_NowKey;    // ����̓��̓L�[
int g_KeyFlg;    // ���̓L�[���
int Key[256];//�L�[��������Ă���t���[�������i�[

int g_MouseX;    // �}�E�X��X���W
int g_MouseY;    // �}�E�X��Y���W

int g_GameState = GAME_INIT;

int haikeiA;//�w�i�i�[�ϐ�
int selectnum;

//Cursor cursor;
Selectitem sitem[SELECT_ITEM];


/*�T�E���h*/
/*****************************************************
 * �v���O�����̊J�n
 ****************************************************/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_
	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {


	SetMainWindowText("Comin"); // �^�C�g����ݒ�

	ChangeWindowMode(TRUE);   // �E�B���h�E���[�h�ŋN��
	SetGraphMode(WIDTH, HEIGHT, 32);


	if (DxLib_Init() == -1)   // DX���C�u�����̏���������
		return -1;

	SetDrawScreen(DX_SCREEN_BACK); // �`����ʂ𗠂ɂ���

	// �摜�ǂݍ���
	if (LoadImages() == -1)
		return -1;

	//�T�E���h�ǂݍ���
	if (LoadSounds() == -1)
		return -1;

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && g_GameState != END && !(g_KeyFlg & PAD_INPUT_START)) {


		// ���̓L�[�擾
		g_OldKey = g_NowKey;
		g_NowKey = GetMouseInput();
		g_KeyFlg = g_NowKey & ~g_OldKey;

		//�}�E�X�̈ʒu���擾
		GetMousePoint(&g_MouseX, &g_MouseY);

		ClearDrawScreen();  // ��ʂ̏�����

		switch (g_GameState) {

		case GAME_TITLE:DrawGameTitle(); break;		 //�Q�[���^�C�g������

		case GAME_INIT: GameInit();  break;			 //�Q�[����������

		case GAME_END: DrawEnd();  break;			 //�����L���O�`�揈��

		case GAME_MAIN: GameMain();  break;			 //�G���h�`�揈��

		case GAME_RESULT:DrawGameResult(); break;		 //�Q�[�����C������

		case GAME_OVER: DrawGameOver(); break;		 // �Q�[���I�[�o�[�`�揈��

		}

		ScreenFlip();    // ����ʂ̓��e��\��ʂɔ��f

	}

	DxLib_End(); // DX���C�u�����g�p�̏I������

	return 0; // �\�t�g�̏I��
}

/********************************************************************
* �Q�[���^�C�g���`�揈��(���j���[���)
********************************************************************/
void DrawGameTitle(void) {

}

/********************************************************************
* �Q�[������������
********************************************************************/
void GameInit(void) {
	//���ڏ�����
	for (int i = 0; i < 6; i++) {
		sitem[i].x = 40;
		sitem[i].y = (80 * i) + 20; //+20�͗]��
		sitem[i].w = 300;
		sitem[i].h = 60;
		sitem[i].flg = false;
	}
	sitem[6].x = 40;
	sitem[6].y = 550;

	g_GameState = GAME_MAIN;
}


/********************************************************************
* �Q�[���G���h�`�揈��
********************************************************************/
void DrawEnd(void) {

}

/********************************************************************
* �Q�[�����C��
********************************************************************/
void GameMain(void) {
	UpdatKey();
	Stageselect();
	StageselectDraw();
}

/********************************************************************
* �Q�[���N���A�`�揈��
********************************************************************/
void DrawGameResult(void) {

}

/********************************************************************
* �Q�[���I�[�o�[�`�揈��
********************************************************************/
void DrawGameOver(void) {


}


/********************************************************************
* �摜�ǂݍ���
********************************************************************/
int LoadImages() {

	//// �^�C�g��
	//if ((g_TitleImage = LoadGraph("images/title.png")) == -1)return -1;

	////�X�e�[�W
	//if ((g_StageImage = LoadGraph("images/stage.png")) == -1)return -1;

	////�Q�[���N���A
	//if ((g_GameClearImage = LoadGraph("images/gameclear.png")) == -1)return -1;

	////�Q�[���I�[�o�[
	//if ((g_GameOverImage = LoadGraph("images/gameover.png")) == -1)return -1;

	////�u���b�N�摜
	//if (LoadDivGraph("images/block.png", 10, 10, 1, 48, 48, g_BlockImage) == -1)return -1;

	////�i���o�[�摜�̓ǂݍ���
	//if (LoadDivGraph("images/number.png", 10, 10, 1, 60, 120, g_NumberImage) == -1)return -1;

	//�w�i�ǂݍ���
	if ((haikeiA = LoadGraph("images/stageselect_backtest.png")) == -1)return -1;
	if ((sitem[0].img = LoadGraph("images/test1.png")) == -1)return -1;
	if ((sitem[1].img = LoadGraph("images/test2.png")) == -1)return -1;
	if ((sitem[2].img = LoadGraph("images/test3.png")) == -1)return -1;
	if ((sitem[3].img = LoadGraph("images/test4.png")) == -1)return -1;
	if ((sitem[4].img = LoadGraph("images/test2.png")) == -1)return -1;
	if ((sitem[5].img = LoadGraph("images/test3.png")) == -1)return -1;
	if ((sitem[5].img = LoadGraph("images/test4.png")) == -1)return -1;
	if ((sitem[6].img = LoadGraph("images/back.png")) == -1)return -1;

	if ((sitem[0].main_img = LoadGraph("images/image.png")) == -1)return -1;
	if ((sitem[1].main_img = LoadGraph("images/maintest2.png")) == -1)return -1;
	if ((sitem[2].main_img = LoadGraph("images/maintest3.png")) == -1)return -1;
	if ((sitem[3].main_img = LoadGraph("images/maintest4.png")) == -1)return -1;

	return 0;
}

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
//�Z���N�g���쏈��
void Stageselect(void) {
	Keyselect();
	Mouseselect();
}
int UpdatKey() {
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) {
			Key[i]++;
		}
		else {
			Key[i] = 0;
		}
	}
	return 0;
}
//�L�[�I��
void Keyselect(void) {
	//�L�[�őI��
	if (Key[KEY_INPUT_RETURN] == 1) {
		//g_GameState=
	}
	if (Key[KEY_INPUT_DOWN] == 1) {
		selectnum = (selectnum + 1) % SELECT_ITEM;
	}
	if (Key[KEY_INPUT_UP] == 1) {
		selectnum = (selectnum + (SELECT_ITEM-1)) % SELECT_ITEM;
	}
	if (Key[KEY_INPUT_DOWN] == 1 || Key[KEY_INPUT_UP] == 1) {
		for (int i = 0; i < SELECT_ITEM; i++) {
			if (i == selectnum) {
				sitem[i].x = 80;
			}
			else {
				sitem[i].x = 40;
			}
		}
	}

}
//�}�E�X�I��
void Mouseselect(void) {
	//�}�E�X�I��
	if (g_KeyFlg & MOUSE_INPUT_LEFT) {
		if (g_MouseX > 40 && g_MouseX < 340 && g_MouseY>20 && g_MouseY < 80) {
			selectnum = (selectnum + (SELECT_ITEM - 1)) % SELECT_ITEM;
			selectnum = 0;
		}
		else if (g_MouseX > 40 && g_MouseX < 340 && g_MouseY>100 && g_MouseY < 160) {
			selectnum = (selectnum + (SELECT_ITEM - 1)) % SELECT_ITEM;
			selectnum = 1;
		}
		else if (g_MouseX > 40 && g_MouseX < 340 && g_MouseY>180 && g_MouseY < 240) {
			selectnum = (selectnum + (SELECT_ITEM - 1)) % SELECT_ITEM;
			selectnum = 2;
		}
		else if (g_MouseX > 40 && g_MouseX < 340 && g_MouseY>260 && g_MouseY < 340) {
			selectnum = (selectnum + (SELECT_ITEM - 1)) % SELECT_ITEM;
			selectnum = 3;
		}
		//�߂�{�^��
		else if (g_MouseX > 40 && g_MouseX < 190 && g_MouseY>550 && g_MouseY < 600) {
			//g_GameState =
		}

		for (int i = 0; i < SELECT_ITEM; i++) {
			if (i == selectnum) {
				sitem[i].x = 80;
			}
			else {
				sitem[i].x = 40;
			}
		}
	}
}
void StageselectDraw(void) {
	DrawGraph(0, 0, haikeiA, TRUE);
	for (int i = 0; i < SELECT_ITEM; i++) {
		DrawGraph(sitem[i].x, sitem[i].y, sitem[i].img, FALSE);
	}
	DrawGraph(445, 100, sitem[selectnum].main_img, FALSE);
	for (int i = 1; i < 5; i++) {
		DrawFormatString(300, 100*i-50, GetColor(0, 0, 0), "flg %d", sitem[i-1].flg);
	}
	//DrawFormatString(500, 400, GetColor(255, 255, 0), "Y %d",g_MouseY);
	/*SetFontSize(50);
	DrawFormatString(480, 20, GetColor(255, 255, 0), "�X�e�[�W�Z���N�g");*/
	//for (int i = 0; i < SELECT_ITEM; i++) {
	//}
}