///*�K�v�Ȃ�̓ǂݍ���*/
//#include "DxLib.h"
//#include <stdio.h>
//#include <iostream>
//#define _USE_MATH_DEFINES
//#include <math.h>
//#include <wingdi.h>
//
//
///*�w�b�_�t�@�C���̓ǂݍ���*/
//#include "Input.h"			//�L�[�ƃ}�E�X���͂̂��
//#include "State.h"			//�Q�[���̃V�[�����Ǘ�������
//#include "LoadSource.h"		//�摜�Ƃ����Ƃ��̐錾�Ɠǂݍ���
//
//
//#pragma warning(disable : 4244)
//#pragma warning(disable : 26812)
//#pragma warning(disable : 26451)
//
///********************************************************************
//* �񋓑̂̐錾
//********************************************************************/
////enum GAME_MODE {
////	GAME_TITLE,		//�^�C�g��
////	GAME_INIT,		//������
////	GAME_END,		//�G���h
////	GAME_BATTLE,	//�퓬
////	GAME_SELECT,	//�L�����I��
////	GAME_RESULT,	//���U���g
////	GAME_OVER,		//�Q�[���I�[�o�[(�H)
////	END = 99		//�G���h�p�ϐ�
////};
//
//enum Genre {
//	HORROR,			//�z���[
//	ACTION,			//�A�N�V����
//	RPG,			//RPG
//	NOVEL,			//�m�x��
//	CARD,			//�J�[�h
//	STEALTH,		//�X�e���X
//	SIMULATION,		//�V�~�����[�V����
//	SHOOTING,		//�V���[�e�B���O
//	PUZZLE,			//�p�Y��
//	MUSIC,			//���y
//	RACE1,			//���[�X(���[�T�[)
//	RACE2			//���[�X(���[�X�I�t�B�V����)
//};
//
//char genre[11][20] = {"�z���[","�A�N�V����","�q�o�f","�m�x��","�J�[�h","�X�e���X","�V�~��","�V���[�g","�p�Y��/�E�o","���y","���[�X"};
//
///********************************************************************
//* �萔�̐錾
//********************************************************************/
//
//
//
///*******************************************************************
//*�摜�̂���
//********************************************************************/
//////int g_TitleImage;				//�^�C�g���摜
////int g_SelectImage;				//�L�����I���摜
////
//////�L�����̉摜
////int g_HorrorImage[4];			//�z���[�L����
////
//////�X�e�[�W�̉摜
////int g_Dh[2];
////int g_Ohuda;
////
////�X�e�[�W�̉摜�؂�ւ��p
//int g_GraphNum=0; 
//
//
///********************************************************************
//* �ϐ��̐錾
//********************************************************************/
////int g_OldKey;						// �O��̓��̓L�[
////int g_NowKey;						// ����̓��̓L�[
////int g_KeyFlg;						// ���̓L�[���
//int g_key[256];						// �L�[�̏����i�[������
//bool left[2], right[2], up[2], down[2],jump[2],XButton[2],YButton[2];				// �L�[�̉�������(�Y�����Ŕ���F0��1�o�A1��2�o)
//bool kettei;
//
////int g_OldMouse;				//�O��̃}�E�X
////int g_NowMouse;				//����̃}�E�X
////int g_MouseFlg;				//�}�E�X�t���O
////int g_MouseX;				// �}�E�X��X���W
////int g_MouseY;				// �}�E�X��Y���W
//bool mleft, mright;			// �}�E�X�̓��͔���
//
//int g_GameState;			//�Q�[���̃V�[���Ǘ�
//int GenreNum;
//
////�C�x���g�p
//bool isEvent;
//int g_alpha;
//int g_EveCount;
//bool isOhuda;
//
///*�T�E���h*/
//
//
////�f�o�b�O�p
//bool isDebug;
//bool isStamp;
//bool isSave;
//int Ohu[20][3];
//int OhuNum;
//
///********************************************************************
//* �\���̂̐錾
//********************************************************************/
//struct chara{
//	int hp=100;						//�̗�
//	int ap=0;						//�A�r���e�B�̃Q�[�W�p
//	float px=400, py=400;			//�L�����̍��W
//	bool aFlg=false;				//�A�r���e�B�����t���O
//	float jumpForce=8.0f;			//�W�����v��
//	int vector=0;					//�i�s�x�N�g��
//	int oldVec = 0;					//�O�̃x�N�g��
//	float speed = 0;				//�L�����̃X�s�[�h
//};
//
//struct chara charaA[11];
//struct chara charaB[11];
//
///***********************************************
//  * �֐��̃v���g�^�C�v�錾
//***********************************************/
////�L�[���͂̂��
//void KeyInput(void);
//
//// �Q�[������������
//void GameInit(void);
//
//// �L�����I���V�[��
//void GameCSelect(void);
//
////�X�e�[�W�I���V�[��
//void GameSSelect(void);
//
//// �퓬�V�[��
//void DrawGameMain(void);
//void PlayerMove(int genre,struct chara *chara,int pl);
//
//// �Q�[���^�C�g���`�揈��
//void DrawGameTitle(void);
//
//// �G���h�`�揈��
//void DrawEnd(void);
//
//// �Q�[���N���A�[�̏���
//void DrawGameResult(void);
//
//// �Q�[���I�[�o�[�`�揈��
//void DrawGameOver(void);
//
//// �摜�ǂݍ���
//int LoadImages();
//
////�T�E���h
//int LoadSounds(void);
//
//
//Input inp;
//
///*****************************************************
// * �v���O�����̊J�n
// ****************************************************/
//int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_
//	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
//
//
//	SetMainWindowText("�Q�[���W�������������"); // �^�C�g����ݒ�
//
//	ChangeWindowMode(TRUE);   // �E�B���h�E���[�h�ŋN��
//
//	SetGraphMode(1440, 810,16,60);
//
//
//	if (DxLib_Init() == -1)   // DX���C�u�����̏���������
//		return -1;
//
//	SetDrawScreen(DX_SCREEN_BACK); // �`����ʂ𗠂ɂ���
//
//	// �摜�ǂݍ���
//	/*if (LoadImages() == -1)
//		return -1;*/
//
//	//�T�E���h�ǂݍ���
//	if (LoadSounds() == -1)
//		return -1;
//
//	g_GameState = GAME_TITLE;
//
//	// �Q�[�����[�v
//	while (ProcessMessage() == 0 && g_GameState != END/* && !(g_KeyFlg & PAD_INPUT_START)*/) {
//
//		//�}�E�X�̎擾
//		//g_OldMouse = g_NowMouse;								//�O�t���[���̃L�[�擾
//		//g_NowMouse = GetMouseInput();							//���t���[���̎擾
//		//g_MouseFlg = g_NowMouse & ~g_OldMouse;					//�}�E�X�̃t���O
//		//GetMousePoint(&g_MouseX, &g_MouseY);					//�}�E�X�̈ʒu���擾
//
//		inp.InputKey(&inp);
//		inp.InputMouse(&inp);
//
//
//		//KeyInput();			//�L�[�̓��͂��Ǘ�
//
//
//		ClearDrawScreen();  // ��ʂ̏�����
//
//		switch (g_GameState) {
//
//		case GAME_TITLE:	DrawGameTitle(); break;		 //�Q�[���^�C�g������
//
//		case GAME_INIT:		GameInit();  break;			 //�Q�[����������
//
//		case GAME_C_SELECT:	GameCSelect();  break;	     //�L�����I����ʏ���
//
//	//	case GAME_S_SELECT:	GameSSelect();  break;	     //�X�e�[�W�I����ʏ���
//
//		case GAME_MAIN:		DrawGameMain();  break;		 //�Q�[�����C����ʏ���
//
//		case GAME_RESULT:	DrawGameResult(); break;	 //�Q�[�����C������
//
//		case GAME_OVER:		DrawGameOver(); break;		 // �Q�[���I�[�o�[�`�揈��
//
//		case GAME_END:		DrawEnd(); break;		 // �Q�[���I�[�o�[�`�揈��
//
//		}
//
//		ScreenFlip();    // ����ʂ̓��e��\��ʂɔ��f
//
//	}
//
//	DxLib_End(); // DX���C�u�����g�p�̏I������
//
//	return 0; // �\�t�g�̏I��
//}
//
///********************************************************************
//* �Q�[���^�C�g���`�揈��(���j���[���)
//********************************************************************/
////void DrawGameTitle(void) {
////
////
////	//�^�C�g���̉摜�\��
////	DrawExtendGraph(0, 0,1440,810, g_TitleImage, true);
////	//DrawString();
////
////	// �V�[����؂�ւ���
////	if (g_MouseFlg & MOUSE_INPUT_LEFT) {
////		if ((g_MouseX > 400)
////			&& (g_MouseX < 570)
////			&& (g_MouseY > 600)
////			&& (g_MouseY < 650)) {
////
////			g_GameState = GAME_INIT; // �Q�[���X�^�[�g�̑I��
////			//StopSoundMem(g_TitleBGM);
////		}
////		else if ((g_MouseX > 970)
////			&& (g_MouseX < 1140)
////			&& (g_MouseY > 600)
////			&& (g_MouseY < 650)) {
////
////			g_GameState = GAME_END;  // �Q�[���G���h�̑I��
////			//StopSoundMem(g_TitleBGM);
////		}
////	}
////
////	
////	DrawBox(400,600,570,650,0x0000ff,false);
////	DrawBox(970,600,1140,650,0x0000ff,false);
////
////}
//
////void DrawGameTitle(void) {
////	
////	inp.InputKey(&inp);
////	inp.InputMouse(&inp);
////
////	//�^�C�g���̉摜�\��
////	DrawExtendGraph(0, 0, 1440, 810, g_TitleImage, true);
////	//DrawString();
////
////	// �V�[����؂�ւ���
////	if (inp.MouseFlg & MOUSE_INPUT_LEFT) {
////		if ((inp.MouseX > 400)
////			&& (inp.MouseX < 570)
////			&& (inp.MouseY > 600)
////			&& (inp.MouseY < 650)) {
////
////			g_GameState = GAME_INIT; // �Q�[���X�^�[�g�̑I��
////			DrawBox(0,0,200,200,0x000000,1);
////			//StopSoundMem(g_TitleBGM);
////		}
////		else if ((inp.MouseX > 970)
////			&& (inp.MouseX < 1140)
////			&& (inp.MouseY > 600)
////			&& (inp.MouseY < 650)) {
////
////			g_GameState = GAME_END;  // �Q�[���G���h�̑I��
////			//StopSoundMem(g_TitleBGM);
////		}
////	}
////
////	DrawFormatString(5,5,0x000000,"mlef = %d",inp.mleft);
////	DrawFormatString(5,25,0x000000,"mrig = %d",inp.mright);
////	DrawFormatString(5,45,0x000000,"mouseO = %d",inp.OldMouse);
////	DrawFormatString(5,65,0x000000,"mouseN = %d",inp.NowMouse);
////	DrawFormatString(5,85,0x000000,"mouseF = %d",inp.MouseFlg);
////
////	DrawBox(400, 600, 570, 650, 0x0000ff, false);
////	DrawBox(970, 600, 1140, 650, 0x0000ff, false);
////
////}
//
///********************************************************************
//* �Q�[������������
//********************************************************************/
//void GameInit(void) {
//	charaA->jumpForce = 8.0f;
//	charaB->jumpForce = 8.0f;
//	charaB->px = 840.0f;
//	charaA->speed = 5.0f;
//	g_GameState = GAME_C_SELECT;
//	g_alpha = 255;
//	g_EveCount = 0;
//	isOhuda = false;
//	isStamp = false;
//	isSave = false;
//}
//
//
///********************************************************************
//* �Q�[���G���h�`�揈��
//********************************************************************/
//void DrawEnd(void) {
//	SetFontSize(50);
//	DrawString(705,405,"�Q�[�����I�����܂�",0xffffff,1);
//	g_GameState = END;
//}
//
///********************************************************************
//* �L�����I���V�[��
//********************************************************************/
//void GameCSelect(void) {
//
//	struct SelectImage chara;
//	chara.ImageInput(&chara);
//
//	DrawExtendGraph(0, 0, 1440, 810, chara.SelectImage, true);
//
//	if (jump[0] || inp.MouseFlg & MOUSE_INPUT_LEFT) {
//		g_GameState = GAME_MAIN;
//	}
//}
//
///********************************************************************
//*							�Q�[���V�[��							*
//*-------------------------------------------------------------------*
//*										*
//*		*
//********************************************************************/
//
//float SetAngle(int angle);			//�x���@�Ŋp�x�𓾂�
//void Flashing(int paturn);			//�d�C�̓_�ł������ǂ�	
//
//void DrawGameMain(void) {
//
//	struct Escape esc;
//	esc.ImageInput(&esc);
//
//	static int VecNum = 0;
//	
//	//�w�i
//	DrawExtendGraph(0, 0, 1440, 810, esc.EscapeRoom[g_GraphNum], true);
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
//
//		g_GraphNum = VecNum == 0 ? 0 : 1;
//	}
//	else {
//		
//		Flashing(1);
//
//	}
//
//	if (inp.MouseX >= 890 && inp.MouseX <= 940 && inp.MouseY >= 760 && inp.MouseY <= 810) {
//		DrawBox(890,760,940,810,0x00ff00,true);
//		if (inp.MouseFlg & MOUSE_INPUT_LEFT) { isEvent = !isEvent; g_EveCount = 0; }
//	}
//
//	//�������牺�̓f�o�b�O�p
//	if (inp.MouseFlg & MOUSE_INPUT_RIGHT) isDebug = !isDebug;
//	
//	if (isDebug) {
//		DrawString(1275,5,"Mode : �f�o�b�O",0xff0000,1);
//		SetFontSize(20);
//		DrawFormatString(3,5,0xff0000,"VecNum = %d",VecNum);
//		DrawFormatString(3,25,0xff0000,"Graph  = %d",g_GraphNum);
//		DrawFormatString(3,45,0xff0000,"isEve  = %d",isEvent);
//		DrawFormatString(3,65,0xff0000,"�W�������F%s �~ %s�X�e�[�W",genre[GenreNum],genre[Genre::PUZZLE]);
//		DrawFormatString(3,85,0x0000ff,"MouseX = %d",inp.MouseX);
//		DrawFormatString(3,105,0xff0000,"MouseY = %d",inp.MouseY);
//
//		DrawLine(0,inp.MouseY,1440,inp.MouseY,0x0000ff,1);
//		DrawLine(inp.MouseX,0,inp.MouseX,810,0xff0000,1);
//
//		if (jump[0]) {
//			static int angle;
//
//			if (up[0]) angle++;
//			if (down[0]) angle--;
//
//			if (kettei) { Ohu[OhuNum][0] = inp.MouseX; Ohu[OhuNum][1] = inp.MouseY; Ohu[OhuNum++][2] = angle; }
//
//			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
//			DrawRotaGraph(inp.MouseX, inp.MouseY, 1.0f, SetAngle(angle), esc.Ohuda, 1);
//			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
//
//			for (int i = 0; i < 20; i++) {
//				if (Ohu[i][0] != 0) {
//					DrawRotaGraph(Ohu[i][0], Ohu[i][1], 1.0f, SetAngle(Ohu[i][2]), esc.Ohuda, 1);
//					DrawFormatString(3,125 + 20*i,0x000000,"%d = x:%d y:%d",i,Ohu[i][0],Ohu[i][1]);
//				}
//			}
//
//
//		}
//
//	}
//
//
//
//}
//
//float SetAngle(int angle){
//	
//	const float rad = 3.14159 / 180;
//
//	return rad * angle;
//
//}
//
//void Flashing(int paturn) {
//	++g_EveCount;
//
//	switch (paturn) {
//		case 1:
//			if (g_EveCount <= 5) g_alpha = 156;
//			else if (g_EveCount <= 40) g_alpha = 0;
//			else if (g_EveCount <= 45) g_alpha = 156;
//			else if (g_EveCount <= 55) g_alpha = 0;
//			else if (g_EveCount <= 65) g_alpha = 180;
//			else if (g_EveCount <= 80) g_alpha = 0;
//			else if (g_EveCount <= 110) { g_alpha = 230; isOhuda = true; }
//			else if (g_EveCount >= 120) g_alpha = 0;
//			break;
//
//		case 2:
//			break;
//
//		case 3:
//			break;
//	}
//
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, g_alpha);
//	DrawBox(0, 0, 1440, 810, 0x000000, true);
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
//}
//
//
///********************************************************************
//* �Q�[���N���A�`�揈��
//********************************************************************/
//void DrawGameResult(void) {
//
//	SetFontSize(45);
//	DrawString(720,405,"1�o�̏���!!",0x00ff00,1);
//
//}
//
///********************************************************************
//* �Q�[���I�[�o�[�`�揈��
//********************************************************************/
//void DrawGameOver(void) {
//	
//}
//
//
///********************************************************************
//* �L�[���͊Ǘ�
//********************************************************************/
//void KeyInput() {
//
//	//�v���C���[1�p
//	static int OldKey1, NowKey1 = GetJoypadInputState(DX_INPUT_KEY_PAD1), KeyFlg1;
//	OldKey1 = NowKey1;									//�O�t���[���̃L�[�擾
//	NowKey1 = GetJoypadInputState(DX_INPUT_KEY_PAD1);	//���t���[���̃L�[�擾
//	KeyFlg1 = NowKey1 & ~OldKey1;						//�L�[�t���O
//
//	if (NowKey1 & PAD_INPUT_LEFT) 
//	{
//		charaA->speed = 5.0f;
//		left[0] = true; charaA->vector = -1; 
//	}
//	else if (NowKey1 & PAD_INPUT_RIGHT)
//	{
//		charaA->speed = 5.0f;
//		right[0] = true; charaA->vector = 1;
//	}
//	else { left[0] = false; right[0] = false; charaA->oldVec = charaA->vector; /*charaA->vector = 0;*/ }
//	if (NowKey1 & PAD_INPUT_UP)			up[0] = true;		else    up[0] = false;
//	if (NowKey1 & PAD_INPUT_DOWN)		down[0] = true;		else  down[0] = false;
//	if (KeyFlg1 & PAD_INPUT_A)			jump[0] = !jump[0];
//	if (KeyFlg1 & PAD_INPUT_3)			XButton[0] = true;
//	if (KeyFlg1 & PAD_INPUT_4)			YButton[0] = true;
//	if (KeyFlg1 & PAD_INPUT_B)			kettei = true;		else kettei = false;
//	if (KeyFlg1 & KEY_INPUT_H)			isSave = true;		else isSave = false;
//
//	//�v���C���[2�p
//	//static int OldKey2, NowKey2 = GetJoypadInputState(DX_INPUT_PAD2), KeyFlg2;
//	//OldKey2 = NowKey2;									//�O�t���[���̃L�[�擾
//	//NowKey2 = GetJoypadInputState(DX_INPUT_PAD2);		//���t���[���̃L�[�擾
//	//KeyFlg2 = NowKey2 & ~OldKey2;						//�L�[�t���O
//
//	//if (NowKey2 & PAD_INPUT_LEFT)		left[1] = true;		else  left[1] = false;
//	//if (NowKey2 & PAD_INPUT_RIGHT)		right[1] = true;	else right[1] = false;
//	//if (NowKey2 & PAD_INPUT_UP)			up[1] = true;		else    up[1] = false;
//	//if (NowKey2 & PAD_INPUT_DOWN)		down[1] = true;		else  down[1] = false;
//	//if (KeyFlg2 & PAD_INPUT_A)			jump[1] = true;
//	//if (KeyFlg2 & PAD_INPUT_3)			XButton[1] = true;
//	//if (KeyFlg2 & PAD_INPUT_4)			YButton[1] = true;
//
//}
//
//
///********************************************************************
//* �摜�ǂݍ���
//********************************************************************/
////int LoadImages() {
////
////	FILE* soiya;
////	fopen_s(&soiya,"soiya.txt", "w");
////
////	//�^�C�g��
////	if ((g_TitleImage = LoadGraph("images/title.png")) == -1) { 
////		fwrite("�^�C�g���̉摜�ǂݍ��݂ŃG���[", sizeof(char),50, soiya);
////		return -1;
////	}
////
////	//�X�e�[�W
////	if ((g_Dh[0] = LoadGraph("images/h1.png")) == -1) {
////		fwrite("�E�o�摜1�ǂݍ��݂ŃG���[", sizeof(char), 50, soiya);
////		return -1;
////	}
////
////	if ((g_Dh[1] = LoadGraph("images/h2-3.png")) == -1) {
////		fwrite("�E�o�摜2�ǂݍ��݂ŃG���[", sizeof(char), 50, soiya);
////		return -1;
////	}
////
////	if ((g_Arrow = LoadGraph("images/���.png")) == -1) {
////		fwrite("���ǂݍ��݂ŃG���[", sizeof(char), 50, soiya);
////		return -1;
////	}
////
////	if ((g_Ohuda = LoadGraph("images/���D2.png")) == -1) {
////		fwrite("���D�ǂݍ��݂ŃG���[", sizeof(char), 50, soiya);
////		return -1;
////	}
////
////
////	//�L�����̉摜
////	if ((g_HorrorImage[0] = LoadGraph("images/�z���[�L����.png")) == -1) {
////		fwrite("�z���[�L�����摜�ǂݍ��݂ŃG���[", sizeof(char), 50, soiya);
////		return -1;
////	}
////
////	if ((g_HorrorImage[1] = LoadGraph("images/�z���[�L�����t.png")) == -1) {
////		fwrite("�z���[�L�����摜�ǂݍ��݂ŃG���[", sizeof(char), 50, soiya);
////		return -1;
////	}
////
////	if ((g_SelectImage = LoadGraph("images/SadaoSelect.jpg")) == -1) {
////		fwrite("�L�����I���摜�ǂݍ��݂ŃG���[", sizeof(char), 50, soiya);
////		return -1;
////	}
////
////
////
////	////�X�e�[�W
////	//if ((g_StageImage = LoadGraph("images/stage.png")) == -1)return -1;
////
////	////�Q�[���N���A
////	//if ((g_GameClearImage = LoadGraph("images/gameclear.png")) == -1)return -1;
////
////	////�Q�[���I�[�o�[
////	//if ((g_GameOverImage = LoadGraph("images/gameover.png")) == -1)return -1;
////
////	////�u���b�N�摜
////	//if (LoadDivGraph("images/block.png", 10, 10, 1, 48, 48, g_BlockImage) == -1)return -1;
////
////	////�i���o�[�摜�̓ǂݍ���
////	//if (LoadDivGraph("images/number.png", 10, 10, 1, 60, 120, g_NumberImage) == -1)return -1;
////
////	fclose(soiya);
////
////	return 0;
////}
//
///********************************************************************
//* �T�E���h�ǂݍ���
//********************************************************************/
//int LoadSounds(void) {
//
//	////�^�C�g��
//	//if ((g_TitleBGM = LoadSoundMem("sounds/muci_hono_r01.mp3")) == -1)return -1;
//	////�N���A
//	//if ((g_GameClearSE = LoadSoundMem("sounds/muci_fan_06.mp3")) == -1)return -1;
//	////�I�[�o�[
//	//if ((g_GameOverSE = LoadSoundMem("sounds/muci_bara_07.mp3")) == -1)return -1;
//	////�}�E�X�N���b�N
//	//if ((g_ClickSE = LoadSoundMem("sounds/ta_ta_warekie02.mp3")) == -1)return -1;
//	////�u���b�N����
//	//if ((g_TitleBGM = LoadSoundMem("sounds/ani_ta_biyon02.mp3")) == -1)return -1;
//	////�u���b�N�ړ�
//	//if ((g_TitleBGM = LoadSoundMem("sounds/ta_ta_doron01.mp3")) == -1)return -1;
//
//
//
//	return 0;
//}
//
