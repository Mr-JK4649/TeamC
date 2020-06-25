#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>

#pragma warning(disable : 4244)
#pragma warning(disable : 26812)
#pragma warning(disable : 26451)

#define TIME 99	//���� 99�b
#define MHP 1000	//MAX HP
#define HP0 10		//HP��0	10�͍��W�ʒu
#define HPWID 325	

#define WIDTH 800	//��ʉ��T�C�Y
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
struct PLAYER {
	int x, y;
	int w, h;
	int speed;		//�ړ��X�s�[�h
	int image;		//�摜
	int hp;			//�v���C���[HP
	int hp_gauge;	//HP�Q�[�W
};


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

//�퓬��ʌv�Z
void CombatCal(void);
//�퓬��ʕ`��
void CombatDraw(void);

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

int g_MouseX;    // �}�E�X��X���W
int g_MouseY;    // �}�E�X��Y���W

int g_GameState = GAME_INIT;
int haikeiA;//�w�i�i�[�ϐ�
struct PLAYER player;
struct PLAYER player2;
int timecount = 0;
int timedraw = TIME;


/*�T�E���h*/
/*****************************************************
 * �v���O�����̊J�n
 ****************************************************/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_
	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {


	SetMainWindowText("Comin"); // �^�C�g����ݒ�

	ChangeWindowMode(TRUE);   // �E�B���h�E���[�h�ŋN��
	SetGraphMode(800, 600, 32);


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
	//1P
	player.x = 10;
	player.y = 300;
	player.w = 150;
	player.h = 250;
	player.speed = 5;
	player.hp_gauge = 325;
	player.hp = MHP;

	//2P
	player2.w = 150;
	player2.x = WIDTH - player2.w;
	player2.y = 300;
	player2.h = 250;
	player2.speed = 5;
	player2.hp_gauge = 425;
	player2.hp = MHP;

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
	CombatCal();	//�퓬��ʌv�Z
	CombatDraw();	//�퓬��ʕ`��

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
	if ((haikeiA = LoadGraph("images/janlgame.jpg")) == -1)return -1;
	if ((player.image = LoadGraph("images/player01.png")) == -1)return -1;
	if ((player2.image = LoadGraph("images/player01.png")) == -1)return -1;
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

/************************************************************************
* �퓬��ʌv�Z
*************************************************************************/
void CombatCal(void) {
	//�ړ�����
	if (CheckHitKey(KEY_INPUT_RIGHT) != 0) {
		player.x += player.speed;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) != 0) {
		player.x -= player.speed;
	}

	//��ʒ[�@����	��(��ʕ�����L�����N�^�[�̕����������l)
	if (player.x >= WIDTH - player.w) {
		player.x = WIDTH - player.w;
	}
	if (player.x <= 0) {
		player.x = 0;
	}

	//�e�X�g�pHP�o�[
	//HP��0�̏���
	if (player.hp_gauge <= HP0) {
		player.hp_gauge = HP0;
	}
	if (player2.hp_gauge >= WIDTH - 10) {
		player2.hp_gauge = WIDTH - 10;
	}

	//���Ԍv��
	timecount++;//1�b�J�E���g
	if (timecount >= 60) {
		timedraw--;//�^�C���\��
		timecount = 0;
		player2.hp_gauge += 5;
		player.hp_gauge -= 5;
		//player.hp_gauge = player.hp / MHP * HPWID;*/
	}
}
/************************************************************************
* �퓬��ʕ`��
*************************************************************************/
void CombatDraw(void) {
	DrawGraph(0, 0, haikeiA, FALSE);//�w�i�`��

	DrawGraph(player.x, player.y, player.image, FALSE);//�v���C���[1P�`��
	DrawGraph(player2.x, player2.y, player2.image, FALSE);//�v���C���[2P�`��

	//1P HP�o�[�`��
	DrawBox(10, 10, player.hp_gauge, 50, GetColor(0, 255, 0), TRUE);//�Q�[�W
	DrawBox(8, 8, 327, 52, GetColor(0, 255, 0), FALSE);//HP�o�[�g

	//2P HP�o�[�`��
	DrawBox(player2.hp_gauge, 10, 790, 50, GetColor(0, 255, 0), TRUE);//�Q�[�W
	DrawBox(423, 8, 792, 52, GetColor(0, 255, 0), FALSE);//HP�o�[�g

	//���ԕ`��
	SetFontSize(50);
	DrawFormatString(350, 10, GetColor(255, 255, 255), "%d", timedraw);
}