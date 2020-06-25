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
int g_TitleImage;
int g_BattleImage;

int g_HorrorImage[4];


/********************************************************************
* �ϐ��̐錾
********************************************************************/
int g_OldKey;						// �O��̓��̓L�[
int g_NowKey;						// ����̓��̓L�[
int g_KeyFlg;						// ���̓L�[���
int g_key[256];						// �L�[�̏����i�[������
bool left, right, up, down,jump;	// �L�[�̉�������

int g_OldMouse;				//�O��̃}�E�X
int g_NowMouse;				//����̃}�E�X
int g_MouseFlg;				//�}�E�X�t���O
int g_MouseX;				// �}�E�X��X���W
int g_MouseY;				// �}�E�X��Y���W
bool mleft, mright;			// �}�E�X�̓��͔���

int g_GameState;			//�Q�[���̃V�[���Ǘ�


//�L�����Ɋւ�����
float jumpForce = 8.0f;			//�W�����v��


/*�T�E���h*/


/********************************************************************
* �\���̂̐錾
********************************************************************/
struct chara{
	int hp=5;					//�̗�
	int ap=5;					//�A�r���e�B�̃Q�[�W�p
	float px=400, py=400;	//�L�����̍��W
	bool aFlg;				//�A�r���e�B�����t���O
};

struct chara chara[11];



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
void PlayerA(int genre,float* px ,float* py);

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
	while (ProcessMessage() == 0 && g_GameState != END && !(g_KeyFlg & PAD_INPUT_START)) {


		// ���̓L�[�擾
		g_OldKey = g_NowKey;									//�O�t���[���̃L�[�擾
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);		//���t���[���̃L�[�擾
		g_KeyFlg = g_NowKey & ~g_OldKey;						//�L�[�t���O

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
			&& (g_MouseY > 500)
			&& (g_MouseY < 550)) {

			g_GameState = GAME_BATTLE; // �Q�[���X�^�[�g�̑I��
			//StopSoundMem(g_TitleBGM);
		}
		else if ((g_MouseX > 870)
			&& (g_MouseX < 1040)
			&& (g_MouseY > 500)
			&& (g_MouseY < 550)) {

			g_GameState = GAME_END;  // �Q�[���G���h�̑I��
			//StopSoundMem(g_TitleBGM);
		}
	}

	
	DrawBox(400,500,570,550,0x0000ff,false);
	DrawBox(870,500,1040,550,0x0000ff,false);

}

/********************************************************************
* �Q�[������������
********************************************************************/
void GameInit(void) {
	jumpForce = 8.0f;
}


/********************************************************************
* �Q�[���G���h�`�揈��
********************************************************************/
void DrawEnd(void) {

}

/********************************************************************
* �L�����I���V�[��
********************************************************************/
void GameSelect(void) {

}

/********************************************************************
*							�퓬�V�[��								*
*-------------------------------------------------------------------*
* GameBattle void�^�@[��������]										*
* PlayerDisp void�^�@[�W�������ԍ��A�����W�A�����W]					*
********************************************************************/
void GameBattle(void) {

	DrawExtendGraph(0, 0, 1440, 810, g_BattleImage, true);

	PlayerA(Genre::HORROR, &chara[Genre::HORROR].px, &chara[Genre::HORROR].py);

}

void PlayerA(int Gnum, float* px, float* py) {
	
	float gravity = 3.0f;

	//DrawBoxAA(*px, *py, *px + 30, *py + 80, 0xffffff, true, 1.0f);
	DrawExtendGraph(*px,*py,*px + 200,*py + 200,g_HorrorImage[0],true);

	if (left)	*px -= 1.5f;
	if (right)	*px += 1.5f;
	if (jump) {
		
		SetFontSize(30);
		DrawString(*px-60, *py-35, "�_���͂͂͂͂́^", 0xff0000, 1);
		*py -= (jumpForce - gravity);
		jumpForce -= 0.1f;
		
		if (*py > 450.0f) {
			*py = 450.0f;
			jumpForce = 8.0f;
			jump = false; 
		}


	}
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
* �L�[���͊Ǘ�
********************************************************************/
void KeyInput() {
	if (g_NowKey & PAD_INPUT_4 || g_NowKey & PAD_INPUT_LEFT)	 left = true;	else  left = false;
	if (g_NowKey & PAD_INPUT_6 || g_NowKey & PAD_INPUT_RIGHT)	 right = true;	else right = false;
	if (g_NowKey & PAD_INPUT_8 || g_NowKey & PAD_INPUT_UP)		 up = true;		else    up = false;
	if (g_NowKey & PAD_INPUT_5 || g_NowKey & PAD_INPUT_DOWN)	 down = true;	else  down = false;
	if (g_KeyFlg & PAD_INPUT_10)								 jump = true;	//else  jump = false;

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
	if ((g_TitleImage = LoadGraph("images/�^�C�g�����.png")) == -1) { 
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

