#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>
#include <windows.h>

#include "Source.h"
#include "string.h"
#include "Input.h"
#include "header.h"

#include "GameSys.h"			//�Q�[���̃V�X�e��

#define WIDTH 1280	//�摜���T�C�Y
#define HEIGHT 704	//�摜�c�T�C�Y
#define CHIP_SIZE 64 //��̉摜�T�C�Y
#define MAP_WIDTH WIDTH/CHIP_SIZE	//�}�b�v���T�C�Y
#define MAP_HEIGHT HEIGHT/CHIP_SIZE //�}�b�v�c�T�C�Y

//*****�񋓑�*****
enum Key { UP, DOWN, LEFT, RIGHT };
enum PlayerImage { Image_DOWN = 0, Image_UP = 3, Image_RIGHT = 6, Image_LEFT = 9 };
enum Tane { KOMUGI_TANE = 10, JAGAIMO_TANE, NINJIN_TANE };
enum MIZU { KOMUGI_MIZU = 20, JAGAIMO_MIZU, NINJIN_MIZU };
enum eYASAI { KOMUGI = 30, JAGAIMO, NINJIN };
enum Page { MENU, MENU2, MENU3 ,MENU4,MENU5};
enum MAPDATA { NUL, WALL = 2, EXIT };
//*****�\����*****
struct PLAYER {
	//�v���C���[���W
	int x, y;
	int muki;
	int image_muki = Image_LEFT;
	int  speed;
	bool walking_flg;
	bool fremflg;
	int image=0;
};
struct YASAI{
	int x, y;//���W
	int count;//�b��
	int num = 0;//���̖�؃f�[�^�ۑ�������
	bool flg;//�����Ă��邩
};
struct SELECTMENU {
	int x, y;
	char name[128];
	bool flg;
	bool colorflg;
};
struct KYOTEN {
	int mapdata = 0;
	bool flg = false;
	bool selectflg = false;
};
//*****�}�b�v�`�b�v***** 0 �s����ꏊ 1 �� 2 ��
int hatakemap[MAP_HEIGHT][MAP_WIDTH] = {
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,2},
	{2,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,2},
	{2,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,2,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,2,2},
};
//*****��؃f�[�^*****
int tane[MAP_HEIGHT][MAP_WIDTH] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
//*****�\���̕ϐ��錾*****
HATAKE hatake;
PLAYER player;
KYOTEN kyoten;
//���j���[�I�����
SELECTMENU menu1[4] = {
	{400,310,"���������",0,1},
	{400,330,"�����܂�",0,0},
	{400,350,"���n",0,0},
	{400,370,"�o�b�O",0,0} };
//���j���[��
SELECTMENU menutane[3] = {
	{400,310,"���ނ��̂���",0,1},
	{400,330,"���Ⴊ�����̂���",0,0},
	{400,350,"�ɂ񂶂�̂���",0,0}};
//���_�߂�I��
SELECTMENU bacselect[3] = {
	{500,350,"�͂�",0,1},
	{740,350,"������",0,0},
	{520,280,"���_�֖߂�܂����H",0,0},
};
YASAI Yasaidata[54];
//*****�ϐ��錾*****
//�������p�ϐ�
int Key[256]; // �L�[��������Ă���t���[�������i�[����
bool dflg = false; //�f�o�b�N�t���O
bool flg = true; //�֐��������t���O
//��ƑI��ϐ�
bool selectflg = false; //��ƑI����ʃt���O
int pageflg = MENU; //���݂̍�ƃt���O ��A���� ����� ���n�Ȃ�
int selectNum = 0; //��ƑI���̌��ݑI�����Ă���ꏊ
int selectTane = 0; //��I���̌��ݑI�����Ă���ꏊ
int selectExit = 0; //�o���̌��ݑI�����Ă���ꏊ
bool initflg = false; //�I�����ꂽ�����̐F��ς���֐��̌Ăяo���t���O
//�������ϐ�
int Plantpageflg = MENU3;
bool plantflg = false;//�A����Ƃ��̃t���O
int drawdignum = 10;//�`�悷��Ƃ��ɐ����𒲐�����
int TaneNowyasai = 0;//���݂̖�؃f�[�^���������
int MizuNowyasai = 0;
int SyukakuNowyasai = 0;
///////////////////��p�ϐ�
bool mizuyari = false;
int Mizu_yasainum = 0;//�����̎��̖�؃f�[�^��ۑ�������
//���n�p�ϐ�
int syukakunum = 0;//���n�ł��邩�̃f�[�^�ۑ�������
//*****�v���g�^�C�v�錾*****
void Game_Hatake(int Width, int Height);
void InitPlayer(void);//�v���C���[������
int IsAbleToGo(int x, int y, int muki);//�����蔻�菈��
void Player(int Width, int Height);//�v���C���[����
int gpUpdateKey();//�L�[�X�V����
void DrawFrem();//�g�\���`��
void DrawHatake(int Width, int Height);//���`��
void MoveYasai();//��؏���
void DrawYasai();//��؁E��ȂǕ`��
void MoveSelectTane();//��I����ʏ���
void DrawSelectTane();//��I����ʕ`��
void MoveSelectMenu();//��ƑI�����j���[����
void DrawSelectMenu(); //��ƑI�����j���[�`��
void YasaiMizuMove();
void MoveMizu();//���������鏈��
void Debag();//�f�o�b�N�`�揈��
//�����
void Growth();//��������
void YasaiCountFlg();
void Count();//�J�E���g
//���_����
void DrawKyotenExitSelect();
void KyotenExitSelect();
void KyotenBag();
//���n����
void Syukaku();
void SyuukakuMove();
void InitselectColor();
//��؃f�[�^
void InitYasaiData();
//�A���鏈��
void TanePlant();
void MizuPlant();
void SyukakuPlant();
//�o�b�N���
//void Bag();//�����܂�8/06
//*****�����Ăяo��*****
void Game_Hatake(int Width, int Height) {
	SetFontSize(20);//�����T�C�Y�m�F
	if (flg) {
		InitPlayer(); flg = false;	//���̂ݏ�����
		InitYasaiData();
	}
	gpUpdateKey();//���͍X�V
	Player(Width, Height);//�v���C���[�����֐�
	DrawHatake(Width, Height);//�`�揈��
	//��ƃZ���N�g���j���[�J������
	if (Key[KEY_INPUT_A] == 1) {
		selectNum = 0; //�J�����Ƃ��Ɍ��ݑI�����Ă���ꏊ��������
		selectTane = 0;
		selectflg = true; //A���������Ƃ���ƑI����ʊJ��
		initflg = true;
	}else if (Key[KEY_INPUT_S] == 1) {
		selectflg = false; //S���������Ƃ���ƑI����ʕ���
		pageflg = MENU;
	}
	//�����Z���N�g�t���OON�Ȃ�Z���N�g��ʊJ��
	switch (pageflg)
	{
	case MENU:if (selectflg == true)MoveSelectMenu(); break;//��ƑI�����
	case MENU2:if (selectflg == true)MoveSelectTane(); break;//��I�����
	case MENU3: MoveMizu(); break;//������������
	case MENU4: Syukaku(); break;//���n����
	/*case MENU5: Bag(); break;*/
	}
	if (pageflg == MENU2) { Plantpageflg = MENU2; }
	else if (pageflg == MENU3) { Plantpageflg = MENU3; }
	else if (pageflg == MENU4) { Plantpageflg = MENU4; }
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���_�߂菈��
	KyotenBag();
	//��������
	Count();
	Growth();
	YasaiCountFlg();
	//�f�o�b�N����
	if (dflg) {
		Debag();
	}
}
//��؃f�[�^�̏�����
void InitYasaiData(void) {
	int i = 2;//�s
	int j = 2;//��
	//�ق����l��**************************
	//   �s ��
	//2�s[2][2]�`[2][16]
	//3�s[3][2]�`[3][16]
	//7�s[7][2]�`[7][7] [7][12]�`[7][17]
	//8�s[8][2]�`[8][7] [8][12]�`[8][17] ���v54
	//***************************************
	for (int s = 0; s < 54; s++) {
		if (i == 2 || i == 3) {//2�s��3�s�̊ԌJ��Ԃ�����
			if (j >= 17) { i++; j = 2; }//17��ڂɍs������3�s�ڂɂ��ė�����Z�b�g����
			Yasaidata[s].x = j++; //�����
		}
		if (i == 4) { i = 7; j = 2; }//[7�s�ڂɂ��邽�߂̒���][��̏�����]
		if (i == 7 || i == 8) {//7��ڂ�8��ڂ̊ԌJ��Ԃ�
			if (j > 17) { i++; j = 2; }//17��ڂɍs������8�s�ڂɂ��ė�����Z�b�g����
			Yasaidata[s].x = j++;//�����
			if (j == 8) { j = 12; }//��8��ɂȂ�������12��ڂɒ�������
		}
		Yasaidata[s].count = 0;
		Yasaidata[s].flg = false;
		Yasaidata[s].y = i;//�s����
		Yasaidata[s].num = 0;
	}
}

//�v���C���[������
void InitPlayer(void) {
	player.x = 576;
	player.y = 576;
	player.speed = 2;
	player.muki = UP;
	player.image_muki = Image_LEFT;
	player.walking_flg = false;
	kyoten.selectflg = false;
	player.image = 0;
	kyoten.mapdata = 0;
}

//�v���C���[����
void Player(int Width, int Height) {
	if (selectflg == false && kyoten.flg == false) {
		if (player.x % CHIP_SIZE == 0 && player.y % CHIP_SIZE == 0) {
			player.walking_flg = true;
			if (Key[KEY_INPUT_UP] > 1) {
				player.muki = UP;//������t���O
			}
			else if (Key[KEY_INPUT_DOWN] > 1) {
				player.muki = DOWN;//�������t���O
			}
			else if (Key[KEY_INPUT_LEFT] > 1) {
				player.muki = LEFT;//�������t���O
			}
			else if (Key[KEY_INPUT_RIGHT] > 1) {
				player.muki = RIGHT;//�E�����t���O
			}
			else {
				player.walking_flg = false;//�����Ȃ��t���O
			}
			if (IsAbleToGo(player.x, player.y, player.muki) == 1)
				player.walking_flg = false;
		}
		if (player.walking_flg == true) {//�����t���O��������������
			if (player.muki == UP) {
				player.y -= player.speed;
			}
			else if (player.muki == DOWN) {
				player.y += player.speed;
			}
			else if (player.muki == LEFT) {
				player.x -= player.speed;
			}
			else if (player.muki == RIGHT) {
				player.x += player.speed;
			}
		}
		MoveYasai();
	}
	//��ʊO�����Ȃ�����
	if (player.x < 0) {
		player.x = 0;
	}
	else if (player.y < 0) {
		player.y = 0;
	}

	//�f�o�b�N�\��
	if (Key[KEY_INPUT_D] == 1) {
		dflg = true;
	}else if (Key[KEY_INPUT_B] == 1) {
		dflg = false;
	}
}
//*****���`�揈��*****
void DrawHatake(int Width, int Height) {
	if (hatake.flg) { hatake.ImageInput(&hatake); hatake.flg = false; }
	//�v���C���[�A�j���[�V��������******************************************************
	if (player.muki == UP) { player.image_muki = Image_UP; }
	else if (player.muki == DOWN) { player.image_muki = Image_DOWN; }
	else if (player.muki == RIGHT) { player.image_muki = Image_RIGHT;}
	else if (player.muki == LEFT) { player.image_muki = Image_LEFT;}
	player.image = ((player.x % CHIP_SIZE + player.y % CHIP_SIZE) / 21) + player.image_muki;
	//**********************************************************************************
	DrawGraph(0, 0, hatake.image, TRUE);
	DrawGraph(player.x, player.y, hatake.testimage[player.image], TRUE);
	DrawYasai();
	//�t���[���\��
	DrawFrem();
}
//��ؔ���
void MoveYasai() {
	if (Key[KEY_INPUT_X] == 1) {
		if (IsAbleToGo(player.x, player.y, player.muki) == 1 && player.fremflg == true && plantflg == true) {
			switch (Plantpageflg) {
			case MENU2:TanePlant(); break;//��A���鏈��
			case MENU3:MizuPlant(); if (Plantpageflg == MENU3)mizuyari = true; break;//���A���鏈��
			case MENU4:SyukakuPlant(); break;
			}
		}
	}
}
//��ؕ`��
void DrawYasai(){
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (tane[i][j] != 0) {
				if (tane[i][j] >= KOMUGI_TANE && tane[i][j] <= NINJIN_TANE) {//��`��
					DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, hatake.tane[tane[i][j] % drawdignum], FALSE);
				}
				else if (tane[i][j] >= KOMUGI_MIZU && tane[i][j] <= NINJIN_MIZU){//�����`��
					DrawGraph(j* CHIP_SIZE, i* CHIP_SIZE, hatake.mizu[tane[i][j] % drawdignum], FALSE);
				}
				else if(tane[i][j] >= KOMUGI && tane[i][j] <= NINJIN) {
					DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, hatake.yasai[tane[i][j] % drawdignum], FALSE);//��ؕ`�� 
				}
			}
		}
	}
}
//**************************************�I����ʏ���**************************************************************************************
//�I������Ă���ꏊ�̐F������
void InitselectColor() {
	for (int i = 0; i < 4; i++) {
		if (i == 0) {
			menu1[i].colorflg = 1;
		}
		else {
			menu1[i].colorflg = 0;
		}
	}
}
//�A����E�����E���n�E�o�b�O�E�I����ʏ���
void MoveSelectMenu(){
	//�I����ʏ�����
	if (initflg) {
		InitselectColor();
		initflg = false;
	}
	if (Key[KEY_INPUT_DOWN] == 1) {
		selectNum = (selectNum + 1) % 4;
	}
	if (Key[KEY_INPUT_UP] == 1) {
		selectNum = (selectNum + 3) % 4;
	}
	if (Key[KEY_INPUT_DOWN] == 1 || Key[KEY_INPUT_UP] == 1) {
		for (int i = 0; i < 4; i++) {
			if (i == selectNum) {
				menu1[i].colorflg = 1;
			}
			else {
				menu1[i].colorflg = 0;
			}
		}
	}
	//�I�����������ɔ�΂� 0�͎��A���� 1������� 2���n
	if (Key[KEY_INPUT_X] == 1) {
		if (selectNum == 0) {
			pageflg = MENU2;
		}
		else if (selectNum == 1) {
			pageflg = MENU3;
			selectflg = false;
		}
		else if (selectNum == 2) {
			pageflg = MENU4;
			selectflg = false;
		}
	}
	DrawSelectMenu();
}
//�I����ʕ`��
void DrawSelectMenu() {
	DrawBox(390, 300, 610, 420, GetColor(0, 0, 0), true);
	DrawBox(390, 300, 610, 420, GetColor(255, 255, 255), false);
	
	for (int i = 0; i < 4; i++) {
		if (menu1[i].colorflg == 1) {
				DrawFormatString(menu1[i].x, menu1[i].y, GetColor(0, 0, 255), menu1[i].name);
		}
		else {
			DrawFormatString(menu1[i].x, menu1[i].y, GetColor(255, 255, 255), menu1[i].name);
		}
	}
}

//��I����ʏ���
void MoveSelectTane() {
	if (Key[KEY_INPUT_DOWN] == 1) {
		selectTane = (selectTane + 1) % 3;
	}
	if (Key[KEY_INPUT_UP] == 1) {
		selectTane = (selectTane + 2) % 3;
	}
	if (Key[KEY_INPUT_DOWN] == 1 || Key[KEY_INPUT_UP] == 1) {
		for (int i = 0; i < 3; i++) {
			if (i == selectTane) {
				menu1[i].colorflg = 1;
			}
			else {
				menu1[i].colorflg = 0;
			}
		}
	}
	//�I�����ꂽ�������
	DrawSelectTane();
	if (Key[KEY_INPUT_X] == 1) {
		if (selectTane == 0) {
			TaneNowyasai = KOMUGI_TANE;
		}
		else if (selectTane == 1) {
			TaneNowyasai = JAGAIMO_TANE;
		}
		else if (selectTane == 2) {
			TaneNowyasai = NINJIN_TANE;
		}
		plantflg = true;
		selectflg = false;
		pageflg = MENU;
	}
}
void DrawSelectTane() {
	DrawBox(390, 300, 610, 420, GetColor(0, 0, 0), true);
	DrawBox(390, 300, 610, 420, GetColor(255, 255, 255), false);

	for (int i = 0; i < 3; i++) {
		if (menu1[i].colorflg == 1) {
			DrawFormatString(menutane[i].x, menutane[i].y, GetColor(0, 0, 255), menutane[i].name);
		}
		else {
			DrawFormatString(menutane[i].x, menutane[i].y, GetColor(255, 255, 255), menutane[i].name);
		}
	}
}
//*********************************�@�����グ�鏈��********************************************************************************
void YasaiMizuMove() {
	if (KOMUGI_TANE == Mizu_yasainum) { MizuNowyasai = KOMUGI_MIZU; }
	else if (JAGAIMO_TANE == Mizu_yasainum) { MizuNowyasai = JAGAIMO_MIZU; }
	else if (NINJIN_TANE == Mizu_yasainum) { MizuNowyasai = NINJIN_MIZU;}
}
void MoveMizu() {
	MizuNowyasai = Mizu_yasainum;//���X�V
	if (IsAbleToGo(player.x, player.y, player.muki) == 1 && player.fremflg == true) {
		if (player.muki == UP) {
			Mizu_yasainum = tane[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE];
		}
		if (player.muki == DOWN) {
			Mizu_yasainum = tane[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE];
		}
		if (player.muki == LEFT) {
			Mizu_yasainum = tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1];
		}
		if (player.muki == RIGHT) {
			Mizu_yasainum = tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1];
		}
	}
	if (Mizu_yasainum != 0) {
		plantflg = true;
	}
	else {
		plantflg = false;
	}
	YasaiMizuMove();
}

///////////////////////�����(��)////////////////////////////////////////////////////////////////////////////////////////////////////////////
void YasaiCountFlg() {
	if(mizuyari == true){
		for (int i = 0; i < 54; i++) {
			if (IsAbleToGo(player.x, player.y, player.muki) == 1) {
				if (player.fremflg == true) {
					if (Yasaidata[i].y == player.y/CHIP_SIZE - 1 && Yasaidata[i].x == player.x / CHIP_SIZE) {//��
						Yasaidata[i].flg = 1;
						Yasaidata[i].num = tane[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE];
					}
					if (Yasaidata[i].y == player.y / CHIP_SIZE + 1 && Yasaidata[i].x == player.x / CHIP_SIZE) {//��
						Yasaidata[i].flg = 1;
						Yasaidata[i].num = tane[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE];
					}
					if (Yasaidata[i].y == player.y / CHIP_SIZE && Yasaidata[i].x == player.x / CHIP_SIZE - 1) {//��
						Yasaidata[i].flg = 1;
						Yasaidata[i].num = tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1];
					}
					if (Yasaidata[i].y == player.y / CHIP_SIZE && Yasaidata[i].x == player.x / CHIP_SIZE + 1) {//�E
						Yasaidata[i].flg = 1;
						Yasaidata[i].num = tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1];
					}
				}
			}
		}
		mizuyari = false;
	}
}
///////////////////////////////////(�����J�E���g�֐�)////////////////////////////////////////////////////////////////////////////////////////////
//������̃J�E���g���Ă���
void Count(){
	for (int i = 0; i < 54;i++) {
		if (Yasaidata[i].flg == true) {
			Yasaidata[i].count++;
		}
	}
}
//�����f�[�^
void Growth() {
	for (int i = 0; i < 54; i++) {//1��
		if (Yasaidata[i].count >= 3600) {
			if (Yasaidata[i].num == KOMUGI_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = KOMUGI;}
			if (Yasaidata[i].num == JAGAIMO_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = JAGAIMO;}
			if (Yasaidata[i].num == NINJIN_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = NINJIN;}
			Yasaidata[i].num = 0;//num�̃f�[�^������
			Yasaidata[i].count = 0;
			Yasaidata[i].flg = false;
		}
	}
}
////////////���n����////////////////////////////////////////////////////////////////////////////////////////////////////
void Syukaku() {
	if (IsAbleToGo(player.x, player.y, player.muki) == 1 && player.fremflg == true) {
		if (player.muki == UP) {
			syukakunum = tane[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE];
		}
		if (player.muki == DOWN) {
			syukakunum = tane[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE];
		}
		if (player.muki == LEFT) {
			syukakunum = tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1];
		}
		if (player.muki == RIGHT) {
			syukakunum = tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1];
		}
		SyuukakuMove();
	}
}
void SyuukakuMove() {
	if (KOMUGI == syukakunum) {
		SyukakuNowyasai = 0; plantflg = true;
	}
	else if (JAGAIMO == syukakunum) {
		SyukakuNowyasai = 0; plantflg = true;
	}
	else if (NINJIN == syukakunum) {
		SyukakuNowyasai = 0; plantflg = true;
	}
	else { plantflg = false; }
}
//�t���[���`��
void DrawFrem() {
	if (IsAbleToGo(player.x, player.y, player.muki) == 1) {
		if (player.fremflg == true) {
			if (player.muki == UP) {
				DrawGraph((player.x / CHIP_SIZE) * CHIP_SIZE, (player.y / CHIP_SIZE - 1) * CHIP_SIZE, hatake.fremimage, TRUE);
			}
			if (player.muki == DOWN) {
				DrawGraph((player.x / CHIP_SIZE) * CHIP_SIZE, (player.y / CHIP_SIZE + 1) * CHIP_SIZE, hatake.fremimage, TRUE);
			}
			if (player.muki == LEFT) {
				DrawGraph((player.x / CHIP_SIZE - 1) * CHIP_SIZE, (player.y / CHIP_SIZE) * CHIP_SIZE, hatake.fremimage, TRUE);
			}
			if (player.muki == RIGHT) {
				DrawGraph((player.x / CHIP_SIZE + 1) * CHIP_SIZE, (player.y / CHIP_SIZE) * CHIP_SIZE, hatake.fremimage, TRUE);
			}
		}
	}
}
//////////////////////���_�@�߂鏈��//////////////////////////////////////////////////////////////////////////////////////
void KyotenExitSelect() {
	if (Key[KEY_INPUT_LEFT] == 1) {
		selectExit = (selectExit + 1) % 2;
	}
	if (Key[KEY_INPUT_RIGHT] == 1) {
		selectExit = (selectExit + 1) % 2;
	}
	if (Key[KEY_INPUT_LEFT] == 1 || Key[KEY_INPUT_RIGHT] == 1) {
		for (int i = 0; i < 2; i++) {
			if (i == selectExit) {
				bacselect[i].colorflg = 1;
			}
			else {
				bacselect[i].colorflg = 0;
			}
		}
	}
	if (Key[KEY_INPUT_X] == 1) {
		if (selectExit == 0) {
			g_GameState = GAME_HOME;
			/*GameSystem::Input_Time(1);*/
			InitPlayer();
		}
		else if (selectExit == 1) {
			kyoten.selectflg = false;
			hatakemap[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE] = WALL;//�ǃf�[�^������
			kyoten.mapdata = NUL;//�ړ��ł���ꏊ�f�[�^������
		}
	}
}
//���_�߂�I����ʕ`��
void DrawKyotenExitSelect() {
	DrawBox(390, 270, 890, 420, GetColor(0, 0, 0), true);
	DrawBox(390, 270, 890, 420, GetColor(255, 255, 255), false);
	for (int i = 0; i <3; i++) {
		if (bacselect[i].colorflg == 1) {
			DrawFormatString(bacselect[i].x, bacselect[i].y, GetColor(0, 0, 255), bacselect[i].name);
		}
		else {
			DrawFormatString(bacselect[i].x, bacselect[i].y, GetColor(255, 255, 255), bacselect[i].name);
		}
	}
}
//���_�߂鏈��
void KyotenBag() {
	if (IsAbleToGo(player.x, player.y, player.muki) == 1) {
		//�����������Ƃ����̌��݃}�b�v�f�[�^������
		if (player.muki == DOWN) {
			kyoten.mapdata = hatakemap[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE];
		}
	}
	//���_�߂鏈��
	//[NUL=0]�ړ��ł���ꏊ [WALL=2}�ǃf�[�^ [EXIT=3]�o���f�[�^
	//kyoten.flg [true]�v���C���[�ړ�ON:[false]�v���C���[�ړ�off
	if (kyoten.mapdata == EXIT) {//�v���C���[���̌��݂̃}�b�v�f�[�^���o���f�[�^��������
		kyoten.flg = true;//�v���C���[�ړ�OFF
		kyoten.selectflg = true;//�I����ʕ`��ON
		KyotenExitSelect();
	}else
	{//�L�[�������ꂽ��o���f�[�^������
		if (Key[KEY_INPUT_LEFT] == 1 || Key[KEY_INPUT_RIGHT] == 1 || Key[KEY_INPUT_UP] == 1) {
			hatakemap[10][9] = EXIT;//�o���̈ʒu
			hatakemap[10][10] = EXIT;//�o���̈ʒu
			kyoten.flg = false;
			kyoten.mapdata = NUL;
		}
	}
	//�I����ʕ`��ON:OFF����
	if (kyoten.selectflg) { DrawKyotenExitSelect(); }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//�����蔻��p����
int IsAbleToGo(int x,int y,int muki){
	if (muki == UP) {
		if (hatakemap[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE] == 1) {
			player.fremflg = true;
			return 1;
		}
		else if (hatakemap[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE] == 2 || (hatakemap[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE] == 3)) {
			player.fremflg = false;
			return 1;
		}
	}
	if (muki == DOWN) {
		if (hatakemap[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE] == 1) {
			player.fremflg = true;
			return 1;
		}
		else if (hatakemap[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE] == 2 || (hatakemap[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE] == 3)) {
			player.fremflg = false;
			return 1;
		}
	}
	if (muki == LEFT) {
		if (hatakemap[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1] == 1) {
			player.fremflg = true;
			return 1;
		}
		else if (hatakemap[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1] == 2 || (hatakemap[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1] == 3)) {
			player.fremflg = false;
			return 1;
		}
	}if (muki == RIGHT) {
		if (hatakemap[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1] == 1) {
			player.fremflg = true;
			return 1;
		}
		else if (hatakemap[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1] == 2 || (hatakemap[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1] == 3)) {
			player.fremflg = false;
			return 1;
		}
	}
	return 0;
}
// �L�[�̓��͏�Ԃ��X�V����
int gpUpdateKey() {
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			Key[i]++;     // ���Z
		}
		else {              // ������Ă��Ȃ����
			Key[i] = 0;   // 0�ɂ���
		}
	}
	return 0;
}
//�f�o�b�N
void Debag() {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			DrawFormatString(j * CHIP_SIZE + 32, i * CHIP_SIZE + 32, GetColor(255, 255, 0), "%d", tane[i][j]);
			DrawBox(j * CHIP_SIZE, i * CHIP_SIZE, (j + 1) * CHIP_SIZE, (i + 1) * CHIP_SIZE, GetColor(255, 255, 255), FALSE);
		}
	}
	//for (int i = 0; i < 30; i++) {
	//	DrawFormatString(100, i * 20, GetColor(255, 255, 0), "[%d]flg[%d]", i + 1, Yasaidata[i].num);
	//}
	//for (int i = 30; i < 54; i++) {
	//	DrawFormatString(300, (i % 30) * 20, GetColor(255, 255, 0), "[%d]flg[%d]", i + 1, Yasaidata[i].num);
	//}
	//DrawFormatString(400, 210, GetColor(255, 255, 0), "�A���鎞�̃y�[�W�t���O [%d]", Plantpageflg);
	//DrawFormatString(400, 230, GetColor(255, 255, 0), "�y�[�W�t���O [%d]", pageflg);
	//DrawFormatString(400, 250, GetColor(255, 255, 0), "���n�p�ۑ� [%d]", syukakunum);
	//DrawFormatString(400, 270, GetColor(255, 255, 0), "���݂̎� [%d]", TaneNowyasai);
	/*DrawFormatString(400, 310, GetColor(255, 255, 0), "���݂̎��n[%d]", SyukakuNowyasai);*/
	//DrawFormatString(400, 370, GetColor(255, 255, 0), "player.DOWN[%d]", Image_DOWN);
	//DrawFormatString(400, 390, GetColor(255, 255, 0), "player.UP[%d]", Image_UP);
	//DrawFormatString(400, 410, GetColor(255, 255, 0), "player.LEFT[%d]", Image_LEFT);
	//DrawFormatString(400, 430, GetColor(255, 255, 0), "player.RIGHT[%d]", Image_RIGHT);
		//DrawFormatString(400, 100, GetColor(255, 255, 0), "��[%d]", tane[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE]);
		//DrawFormatString(400, 150, GetColor(255, 255, 0), "��[%d]", tane[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE]);
		//DrawFormatString(400, 200, GetColor(255, 255, 0), "��[%d]", tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1]);
		//DrawFormatString(400, 250, GetColor(255, 255, 0), "�E[%d]", tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1]);
	//DrawFormatString(400, 100, GetColor(255, 0, 0), "plantflg [%d]",plantflg);
	//DrawFormatString(400, 150, GetColor(255, 255, 0), "Nowyasai [%d]", Nowyasai);
	//DrawFormatString(400, 200, GetColor(255, 255, 0), "Mizu_yasainum [%d]", Mizu_yasainum);
	//DrawFormatString(400, 250, GetColor(255, 255, 0), "selectflg [%d]", selectflg);
	//GameSystem::Input_Time(0);//�ł鎞�Ԃ������@������
}
//�A���鏈��
void TanePlant() {
	if (player.muki == UP) {
		tane[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE] = TaneNowyasai;
	}
	if (player.muki == DOWN) {
		tane[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE] = TaneNowyasai;
	}
	if (player.muki == LEFT) {
		tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1] = TaneNowyasai;
	}
	if (player.muki == RIGHT) {
		tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1] = TaneNowyasai;
	}
}
void MizuPlant() {
	if (player.muki == UP) {
		tane[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE] = MizuNowyasai;
	}
	if (player.muki == DOWN) {
		tane[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE] = MizuNowyasai;
	}
	if (player.muki == LEFT) {
		tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1] = MizuNowyasai;
	}
	if (player.muki == RIGHT) {
		tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1] = MizuNowyasai;
	}
}
void SyukakuPlant() {
	if (player.muki == UP) {
		tane[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE] = SyukakuNowyasai;
	}
	if (player.muki == DOWN) {
		tane[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE] = SyukakuNowyasai;
	}
	if (player.muki == LEFT) {
		tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1] = SyukakuNowyasai;
	}
	if (player.muki == RIGHT) {
		tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1] = SyukakuNowyasai;
	}
}