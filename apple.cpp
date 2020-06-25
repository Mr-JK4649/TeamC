/*�K�v�Ȃ�̓ǂݍ���*/
#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>

//#include "motion.h"


#pragma warning(disable : 4244)
#pragma warning(disable : 26812)
#pragma warning(disable : 26451)

/********************************************************************
* �񋓑̂̐錾
********************************************************************/
enum GAME_MODE {
	GAME_TITLE,		//�^�C�g��
	GAME_INIT,		//������
	GAME_END,		//�G���h
	GAME_BATTLE,	//�퓬
	GAME_SELECT,	//�L�����I��
	GAME_RESULT,	//���U���g
	GAME_OVER,		//�Q�[���I�[�o�[(�H)
	END = 99		//�G���h�p�ϐ�
};

enum Genre {
	HORROR,			//�z���[
	ACTION,			//�A�N�V����
	RPG,			//RPG
	NOVEL,			//�m�x��
	CARD,			//�J�[�h
	STEALTH,		//�X�e���X
	SIMULATION,		//�V�~�����[�V����
	SHOOTING,		//�V���[�e�B���O
	PUZZLE,			//�p�Y��
	MUSIC,			//���y
	RACE1,			//���[�X(���[�T�[)
	RACE2			//���[�X(���[�X�I�t�B�V����)
};

/********************************************************************
* �萔�̐錾
********************************************************************/



/*******************************************************************
*�摜�̂���
********************************************************************/
int g_TitleImage;				//�^�C�g���摜
int g_BattleImage;				//�퓬��ʔw�i
int g_SelectImage;				//�L�����I���摜

int g_HorrorImage[4];			//�z���[�L�����̉摜


/********************************************************************
* �ϐ��̐錾
********************************************************************/
//int g_OldKey;						// �O��̓��̓L�[
//int g_NowKey;						// ����̓��̓L�[
//int g_KeyFlg;						// ���̓L�[���
int g_key[256];						// �L�[�̏����i�[������
bool left[2], right[2], up[2], down[2],jump[2],XButton[2],YButton[2];				// �L�[�̉�������(�Y�����Ŕ���F0��1�o�A1��2�o)

int g_OldMouse;				//�O��̃}�E�X
int g_NowMouse;				//����̃}�E�X
int g_MouseFlg;				//�}�E�X�t���O
int g_MouseX;				// �}�E�X��X���W
int g_MouseY;				// �}�E�X��Y���W
bool mleft, mright;			// �}�E�X�̓��͔���

int g_GameState;			//�Q�[���̃V�[���Ǘ�


/*�T�E���h*/


/********************************************************************
* �\���̂̐錾
********************************************************************/
struct chara{
	int hp=100;						//�̗�
	int ap=0;						//�A�r���e�B�̃Q�[�W�p
	float px=400, py=400;			//�L�����̍��W
	bool aFlg=false;				//�A�r���e�B�����t���O
	float jumpForce=8.0f;			//�W�����v��
	int vector=0;					//�i�s�x�N�g��
	int oldVec = 0;					//�O�̃x�N�g��
	float speed = 0;				//�L�����̃X�s�[�h
};

struct chara charaA[11];
struct chara charaB[11];

/***********************************************
  * �֐��̃v���g�^�C�v�錾
***********************************************/
//�L�[���͂̂��
void KeyInput(void);

// �Q�[������������
void GameInit(void);

// �L�����I���V�[��
void GameSelect(void);

// �퓬�V�[��
void GameBattle(void);
void PlayerMove(int genre,struct chara *chara,int pl);

// �Q�[���^�C�g���`�揈��
void DrawGameTitle(void);

// �G���h�`�揈��
void DrawEnd(void);

// �Q�[���N���A�[�̏���
void DrawGameResult(void);

// �Q�[���I�[�o�[�`�揈��
void DrawGameOver(void);


// �摜�ǂݍ���
int LoadImages();

//�T�E���h
int LoadSounds(void);

/*****************************************************
 * �v���O�����̊J�n
 ****************************************************/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_
	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {


	SetMainWindowText("�Q�[���W�������������"); // �^�C�g����ݒ�

	ChangeWindowMode(TRUE);   // �E�B���h�E���[�h�ŋN��

	SetGraphMode(1440, 810,16,60);


	if (DxLib_Init() == -1)   // DX���C�u�����̏���������
		return -1;

	SetDrawScreen(DX_SCREEN_BACK); // �`����ʂ𗠂ɂ���

	// �摜�ǂݍ���
	if (LoadImages() == -1)
		return -1;

	//�T�E���h�ǂݍ���
	if (LoadSounds() == -1)
		return -1;

	g_GameState = GAME_TITLE;

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && g_GameState != END/* && !(g_KeyFlg & PAD_INPUT_START)*/) {

		//�}�E�X�̎擾
		g_OldMouse = g_NowMouse;								//�O�t���[���̃L�[�擾
		g_NowMouse = GetMouseInput();							//���t���[���̎擾
		g_MouseFlg = g_NowMouse & ~g_OldMouse;					//�}�E�X�̃t���O
		GetMousePoint(&g_MouseX, &g_MouseY);					//�}�E�X�̈ʒu���擾


		KeyInput();			//�L�[�̓��͂��Ǘ�


		ClearDrawScreen();  // ��ʂ̏�����

		switch (g_GameState) {

		case GAME_TITLE:	DrawGameTitle(); break;		 //�Q�[���^�C�g������

		case GAME_INIT:		GameInit();  break;			 //�Q�[����������

		case GAME_SELECT:	GameSelect();  break;	     //�L�����I����ʏ���

		case GAME_BATTLE:	GameBattle();  break;		 //�퓬��ʏ���

		case GAME_RESULT:	DrawGameResult(); break;	 //�Q�[�����C������

		case GAME_OVER:		DrawGameOver(); break;		 // �Q�[���I�[�o�[�`�揈��

		case GAME_END:		DrawEnd(); break;		 // �Q�[���I�[�o�[�`�揈��

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


	//�^�C�g���̉摜�\��
	DrawExtendGraph(0, 0,1440,810, g_TitleImage, true);
	//DrawString();

	// �V�[����؂�ւ���
	if (g_MouseFlg & MOUSE_INPUT_LEFT) {
		if ((g_MouseX > 400)
			&& (g_MouseX < 570)
			&& (g_MouseY > 600)
			&& (g_MouseY < 650)) {

			g_GameState = GAME_INIT; // �Q�[���X�^�[�g�̑I��
			//StopSoundMem(g_TitleBGM);
		}
		else if ((g_MouseX > 970)
			&& (g_MouseX < 1140)
			&& (g_MouseY > 600)
			&& (g_MouseY < 650)) {

			g_GameState = GAME_END;  // �Q�[���G���h�̑I��
			//StopSoundMem(g_TitleBGM);
		}
	}

	
	DrawBox(400,600,570,650,0x0000ff,false);
	DrawBox(970,600,1140,650,0x0000ff,false);

}

/********************************************************************
* �Q�[������������
********************************************************************/
void GameInit(void) {
	charaA->jumpForce = 8.0f;
	charaB->jumpForce = 8.0f;
	charaB->px = 840.0f;
	charaA->speed = 5.0f;
	g_GameState = GAME_SELECT;
}


/********************************************************************
* �Q�[���G���h�`�揈��
********************************************************************/
void DrawEnd(void) {
	SetFontSize(50);
	DrawString(705,405,"�Q�[�����I�����܂�",0xffffff,1);
	g_GameState = END;
}

/********************************************************************
* �L�����I���V�[��
********************************************************************/
void GameSelect(void) {
	DrawExtendGraph(0, 0, 1440, 810, g_SelectImage, true);

	if (jump[0]) {
		g_GameState = GAME_BATTLE;
	}
}

/********************************************************************
*							�퓬�V�[��								*
*-------------------------------------------------------------------*
* GameBattle void�^�@[��������]										*
* PlayerDisp void�^�@[�W�������ԍ��A�\���̃f�[�^�A�v���C���[]		*
********************************************************************/


//�֐��̐錾
void HorrorMotion(struct chara* chara, int pl);
int HitCheck(float x,float y,float x2,float y2,int pl);
void subHP(int pl);

void GameBattle(void) {

	const int P1 = 0, P2 = 1;

	//�w�i
	DrawExtendGraph(0, 0, 1440, 810, g_BattleImage, true);

	//UI
	DrawBox(5,5,5 + charaA[Genre::HORROR].hp * 5,25,0xffff00,1);
	DrawBox(1435,5,1435 - charaB[Genre::HORROR].hp * 5,25,0xffff00,1);

	PlayerMove(Genre::HORROR, charaA ,P1);
	PlayerMove(Genre::HORROR, charaB ,P2);

}

void PlayerMove(int Gnum,struct chara *chara,int pl) {
	
	float gravity = 3.0f;
	
	DrawExtendGraph(chara->px,chara->py,chara->px + 200,chara->py + 200,g_HorrorImage[pl],true);

	//�ړ�����
	/*if (left[pl]) { chara->px -= 1.5f; }
	if (right[pl]) { chara->px += 1.5f; }*/

	DrawFormatString(100,200,0xff0000,"vec  = %d",charaA->vector);
	DrawFormatString(100,230,0xff0000,"vecO = %d",charaA->oldVec);
	DrawFormatString(100,260,0xff0000,"spd  = %f",charaA->speed);

	if (chara->vector != 0) {
		chara->speed -= 0.03f;
		if (chara->speed <= 0.0f) { chara->speed = 5.0f; chara->oldVec = chara->vector; chara->vector = 0; }
	}
	chara->px += chara->speed * chara->vector;


	if (up[pl])		chara->hp++;
	if (chara->hp > 100) chara->hp = 100;
	if (down[pl])	chara->hp--;
	if (chara->hp < 0) { chara->hp = 0; g_GameState = GAME_RESULT; }

	//�W�����v����
	if (jump[pl]) {
		
		SetFontSize(30);
		DrawString(chara->px -50, chara->py-35, "�_���͂͂͂͂́^", 0xff0000, 1);
		chara->py -= (chara->jumpForce - gravity);
		chara->jumpForce -= 0.1f;
		
		if (chara->py > 400.0f) {
			chara->py = 400.0f;
			chara->jumpForce = 8.0f;
			jump[pl] = false;
		}

	}

	//�U��
	if (XButton[pl]) {
		HorrorMotion(chara,pl);
		subHP(1 - pl);
		XButton[pl] = false;
	}

	
}

////�֐��̐錾
//void HorrorMotion(struct chara* chara, int pl);
//int HitCheck();


//�ϐ��̐錾
int g_MotionCount;

void HorrorMotion(struct chara* chara, int pl) {


	if (g_MotionCount <= 20) {
		if (pl == 0)DrawBox(chara->px + 120, chara->py + 80, chara->px + 120 + 50, chara->py + 120 + 20, 0xffffff, false);
		if (pl == 1)DrawBox(chara->px + 80, chara->py + 80, chara->px + 80 - 50, chara->py + 120 + 20, 0xffffff, false);
	}
	else { g_MotionCount = 0; XButton[pl] = false; }

	if(pl == 0)HitCheck(chara->px + 120, chara->py + 80, chara->px + 120 + 50, chara->py + 120 + 20,pl);
	if(pl == 1)HitCheck(chara->px + 30, chara->py + 80, chara->px + 30 + 50, chara->py + 120 + 20,pl);

	g_MotionCount++;

}

int HitCheck(float x, float y, float x2, float y2,int pl) {

	

	return 0;
}

void subHP(int pl) {
	switch (pl) {
		case 0:
			charaA->hp-=30;
			break;

		case 1:
			charaB->hp-=30;
			break;
	}
}


/********************************************************************
* �Q�[���N���A�`�揈��
********************************************************************/
void DrawGameResult(void) {

	SetFontSize(45);
	DrawString(720,405,"1�o�̏���!!",0x00ff00,1);

}

/********************************************************************
* �Q�[���I�[�o�[�`�揈��
********************************************************************/
void DrawGameOver(void) {
	
}


/********************************************************************
* �L�[���͊Ǘ�
********************************************************************/
void KeyInput() {

	//�v���C���[1�p
	static int OldKey1, NowKey1 = GetJoypadInputState(DX_INPUT_PAD1), KeyFlg1;
	OldKey1 = NowKey1;									//�O�t���[���̃L�[�擾
	NowKey1 = GetJoypadInputState(DX_INPUT_PAD1);		//���t���[���̃L�[�擾
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
	if (KeyFlg1 & PAD_INPUT_A)			jump[0] = true;
	if (KeyFlg1 & PAD_INPUT_3)			XButton[0] = true;
	if (KeyFlg1 & PAD_INPUT_4)			YButton[0] = true;

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

	if (g_NowMouse & MOUSE_INPUT_LEFT)	mleft = true;	else mleft = false;
	if (g_NowMouse & MOUSE_INPUT_RIGHT) mright = true;	else mright = false;
}


/********************************************************************
* �摜�ǂݍ���
********************************************************************/
int LoadImages() {

	FILE* soiya;
	fopen_s(&soiya,"soiya.txt", "w");

	//�^�C�g��
	if ((g_TitleImage = LoadGraph("images/title.png")) == -1) { 
		fwrite("�^�C�g���̉摜�ǂݍ��݂ŃG���[", sizeof(char),50, soiya);
		return -1;
	}

	//�퓬
	if ((g_BattleImage = LoadGraph("images/�퓬�w�i.png")) == -1) {
		fwrite("�퓬�w�i�ǂݍ��݂ŃG���[", sizeof(char), 50, soiya);
		return -1;
	}

	//�L�����̉摜
	if ((g_HorrorImage[0] = LoadGraph("images/�z���[�L����.png")) == -1) {
		fwrite("�z���[�L�����摜�ǂݍ��݂ŃG���[", sizeof(char), 50, soiya);
		return -1;
	}

	if ((g_HorrorImage[1] = LoadGraph("images/�z���[�L�����t.png")) == -1) {
		fwrite("�z���[�L�����摜�ǂݍ��݂ŃG���[", sizeof(char), 50, soiya);
		return -1;
	}

	if ((g_SelectImage = LoadGraph("images/SadaoSelect.jpg")) == -1) {
		fwrite("�L�����I���摜�ǂݍ��݂ŃG���[", sizeof(char), 50, soiya);
		return -1;
	}



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

	fclose(soiya);

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

