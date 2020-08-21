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
enum Tane { KOMUGI_TANE = 10, JAGAIMO_TANE, NINJIN_TANE, DAIKON_TANE, KYABETU_TANE, SATUMAIMO_TANE, BUROKORI_TANE, KABOCYA_TANE, SUIKA_TANE };
enum MIZU { KOMUGI_MIZU = 20, JAGAIMO_MIZU, NINJIN_MIZU, DAIKON_MIZU, KYABETU_MIZU, SATUMAIMO_MIZU, BUROKORI_MIZU, KABOCYA_MIZU, SUIKA_MIZU };
enum eYASAI { KOMUGI = 30, JAGAIMO, NINJIN, DAIKON, KYABETU, SATUMAIMO, BUROKORI, KABOCYA, SUIKA };
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

struct YASAIDATA {
	char name[128];
	int num = 0;
	bool flg = 0;
};
struct SELECTMENU {
	int x, y;
	char name[128];
	bool flg;
	bool colorflg;
	int num;
	bool drawflg;
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
SELECTMENU menutane[9] = {
	{400,310,"���ނ��̂���",0,1,5,true},
	{400,330,"���Ⴊ�����̂���",0,0,5,true},
	{400,350,"�ɂ񂶂�̂���",0,0,5,true},
	{400,370,"��������̂���",0,0,5,true},
	{400,390,"����ׂ̂���",0,0,5,true},
	{400,410,"���܂����̂���",0,0,5,true},
	{400,430,"�Ԃ������[�̂���", 0,0,5,true},
	{400,450,"���ڂ���̂���",0,0,5,true},
	{400,470,"�������̂���",0,0,5,true} };
YASAIDATA YasaiData_a[9] = {
	{"���ނ�",0,false},
	{"���Ⴊ����",0,false},
	{"�ɂ񂶂�",0,false},
	{"��������",0,false},
	{"����ׂ�",0,false},
	{"���܂���",0,false},
	{"�Ԃ������[",0,false},
	{"���ڂ���",0,false},
	{"������",0,false} };
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
int startkeycount = 0;
int ykeycoun = 0;
///////////////////��p�ϐ�
bool taneplantflg = true;
int tanenum = 0;
int tanelimitdata = 0;
int select_tane_num = 9;
int select_tane_backnum = 8;
///////////////////��p�ϐ�
bool mizuyari = false;
int Mizu_yasainum = 0;//�����̎��̖�؃f�[�^��ۑ�������
//���n�p�ϐ�
int syukakunum = 0;//���n�ł��邩�̃f�[�^�ۑ�������
//�f�[�^�ۑ�
int SyukakuData = 0;
//�v���C���[�A�j���[�V�����p�ϐ�
int playerjouro = 0;
int player_animeflg = 1;
//*****�v���g�^�C�v�錾*****
void Game_Hatake(int Width, int Height);
void InitPlayer(void);//�v���C���[������
void InitYasaiData(void);
int IsAbleToGo(int x, int y, int muki);//�����蔻�菈��
void Player(int Width, int Height);//�v���C���[����
void PlayerDraw();
int gpUpdateKey();//�L�[�X�V����
void DrawFrem();//�g�\���`��
void DrawHatake(int Width, int Height);//���`��
void MoveYasai();//��؏���
void DrawYasai();//��؁E��ȂǕ`��
//�폈��
void MoveSelectTane();//��I����ʏ���
void DrawSelectTane();//��I����ʕ`��
void TaneLimit();//��̐��𐧌�
void Select_TaneLimit();
//��ƑI��
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
void SyuukakuMov();
void InitselectColor();
//�A���鏈��
void TanePlant();
void MizuPlant();
void SyukakuPlant();
//�o�b�N���
void Bag();
void YasaiJudgment();
//*****�����Ăяo��*****
void Game_Hatake(int Width, int Height) {
	SetFontSize(20);//�����T�C�Y�m�F
	if (flg) {
		InitYasaiData();
		InitPlayer(); flg = false;	//���̂ݏ�����
	}
	gpUpdateKey();//���͍X�V
	Player(Width, Height);//�v���C���[�����֐�
	DrawHatake(Width, Height);//�`�揈��
	//��ƃZ���N�g���j���[�J������
	if (inp.start == true) {
		if (ykeycoun % 2 == 0) {
			selectNum = 0; //�J�����Ƃ��Ɍ��ݑI�����Ă���ꏊ��������
			selectTane = 0;
			selectflg = true; //A���������Ƃ���ƑI����ʊJ��
			initflg = true;
		}
		else
		{
			selectflg = false; //S���������Ƃ���ƑI����ʕ���
			pageflg = MENU;
		}
		ykeycoun++;
	}
	switch (pageflg)
	{
	case MENU:if (selectflg == true)MoveSelectMenu(); break;//��ƑI�����
	case MENU2:if (selectflg == true)MoveSelectTane(); break;//��I�����
	case MENU3: MoveMizu(); break;//������������
	case MENU4: Syukaku(); break;//���n����
	case MENU5: Bag(); break;
	}
	if (pageflg == MENU2) { Plantpageflg = MENU2; }
	else if (pageflg == MENU3) { Plantpageflg = MENU3; }
	else if (pageflg == MENU4) { Plantpageflg = MENU4; }
	else if (pageflg == MENU5) { Plantpageflg = MENU5; }
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//��
	Select_TaneLimit();
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
			//�R���g���[������
			if (inp.up == true) {
				player.muki = UP;
			}
			else if (inp.down == true) {
				player.muki = DOWN;
			}
			else if (inp.left == true) {
				player.muki = LEFT;//�������t���O
			}
			else if (inp.right == true) {
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
	/*�f�o�b�N�\��*/
	if (inp.sele == true) {
		if (startkeycount % 2 == 0) {
			dflg = true;
		}
		else {
			dflg = false;
		}
		startkeycount++;
	}
}
void PlayerDraw() {
	//�v���C���[�A�j���[�V��������******************************************************
	if (player.muki == UP) { player.image_muki = Image_UP; }
	else if (player.muki == DOWN) { player.image_muki = Image_DOWN; }
	else if (player.muki == RIGHT) { player.image_muki = Image_RIGHT; }
	else if (player.muki == LEFT) { player.image_muki = Image_LEFT; }
	player.image = ((player.x % CHIP_SIZE + player.y % CHIP_SIZE) / 21) + player.image_muki;
	//**********************************************************************************
	if (player.muki == DOWN) {
		playerjouro = 0;
	}
	else if (player.muki == LEFT) {
		playerjouro = 1;
	}
	else if (player.muki == RIGHT) {
		playerjouro = 2;
	}
	else if (player.muki == UP) {
		playerjouro = 3;
	}

	if (IsAbleToGo(player.x, player.y, player.muki) == 1 && player.fremflg == true && plantflg == true) {
		if (Plantpageflg == MENU3)player_animeflg = 2;
	}
	else {
		player_animeflg = 1;
	}
	//�v���C���[�`�� [1�v���C���[] [2���傤��̉摜]
	switch (player_animeflg)
	{
	case 1: DrawGraph(player.x, player.y, hatake.testimage[player.image], TRUE); break;
	case 2: DrawGraph(player.x, player.y, hatake.playerjouro[playerjouro], TRUE); break;
	}
}
//*****���`�揈��*****
void DrawHatake(int Width, int Height) {
	if (hatake.flg) { hatake.ImageInput(&hatake); hatake.flg = false; }
	DrawGraph(0, 0, hatake.image, TRUE);
	PlayerDraw();
	DrawYasai();
	//�t���[���\��
	DrawFrem();
}
//��ؔ���
void MoveYasai() {
	if (inp.space == true) {
		if (IsAbleToGo(player.x, player.y, player.muki) == 1 && player.fremflg == true && plantflg == true) {
			switch (Plantpageflg) {
			case MENU2:TanePlant(); break;//��A���鏈��
			case MENU3:MizuPlant(); if (Plantpageflg == MENU3) { mizuyari = true;} break;//���A���鏈��
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
				if (tane[i][j] >= KOMUGI_TANE && tane[i][j] <= SUIKA_TANE) {//��`��
					DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, hatake.tane[tane[i][j] % drawdignum], FALSE);
				}
				else if (tane[i][j] >= KOMUGI_MIZU && tane[i][j] <= SUIKA_MIZU){//�����`��
					DrawGraph(j* CHIP_SIZE, i* CHIP_SIZE, hatake.mizu[tane[i][j] % drawdignum], FALSE);
				}
				else if(tane[i][j] >= KOMUGI && tane[i][j] <= SUIKA) {
					DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, hatake.yasai[tane[i][j] % drawdignum], FALSE);//��ؕ`�� 
				}
			}
		}
	}
}
//**************************************�I����ʏ���**************************************************************************************
//�I������Ă���ꏊ�̐F������
void InitselectColor() {
	//�I����Ə�����
	for (int i = 0; i < 4; i++) {
		if (i == 0) {
			menu1[i].colorflg = 1;
		}
		else {
			menu1[i].colorflg = 0;
		}
	}
	//��I��������
	for (int i = 0; i < 9; i++) {
		if (i == 0) {
			menutane[i].colorflg = 1;
		}
		else {
			menutane[i].colorflg = 0;
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
	if (inp.f_down == true) {
		selectNum = (selectNum + 1) % 4;
	}
	if (inp.f_up == true) {
		selectNum = (selectNum + 3) % 4;
	}
	if (inp.f_down == true || inp.f_up == true) {
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
	if (inp.space == true) {
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
		else if (selectNum == 3) {
			pageflg = MENU5;
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
				DrawFormatString(menu1[i].x, menu1[i].y, 0x5D99FF, menu1[i].name);
		}
		else {
			DrawFormatString(menu1[i].x, menu1[i].y, GetColor(255, 255, 255), menu1[i].name);
		}
	}
}

//��I����ʏ���
void MoveSelectTane() {
	if (inp.f_down == true) {
		selectTane = (selectTane + 1) % select_tane_num;
	}
	if (inp.f_up == true) {
		selectTane = (selectTane + select_tane_backnum) % select_tane_num; //+2 %3
	}
	if (inp.f_down == true || inp.f_up == true) {
		for (int i = 0; i < select_tane_num; i++) {
			if (i == selectTane) {
				menutane[i].colorflg = 1;
			}
			else {
				menutane[i].colorflg = 0;
			}
		}
	}
	//�I�����ꂽ�������
	DrawSelectTane();
	if (inp.space == true) {
		if (selectTane == 0 && menutane[0].num > 0) {
			DrawFormatString(300,200, 0x5D99FF, "����");
			TaneNowyasai = KOMUGI_TANE;
		}
		else if (selectTane == 1) {
			TaneNowyasai = JAGAIMO_TANE;
		}
		else if (selectTane == 2) {
			TaneNowyasai = NINJIN_TANE;
		}
		else if (selectTane == 3) {
			TaneNowyasai = DAIKON_TANE;
		}
		else if (selectTane == 4) {
			TaneNowyasai = KYABETU_TANE;
		}
		else if (selectTane == 5) {
			TaneNowyasai = SATUMAIMO_TANE;
		}
		else if (selectTane == 6) {
			TaneNowyasai = BUROKORI_TANE;
		}
		else if (selectTane == 7) {
			TaneNowyasai = KABOCYA_TANE;
		}
		else if (selectTane == 8) {
			TaneNowyasai = SUIKA_TANE;
		}
		else {
			TaneNowyasai = -99;
		}
		plantflg = true;
		selectflg = false;
		pageflg = MENU;
	}
}
void Select_TaneLimit() {
	if (selectTane == 0 && menutane[0].num > 0) {
		DrawFormatString(300, 200, 0x5D99FF, "����");
		TaneNowyasai = KOMUGI_TANE;
	}
	else if (selectTane == 1 && menutane[1].num > 0) {
		DrawFormatString(300, 200, 0x5D99FF, "����");
		TaneNowyasai = JAGAIMO_TANE;
	}
	else if (selectTane == 2 && menutane[2].num > 0) {
		DrawFormatString(300, 200, 0x5D99FF, "����");
		TaneNowyasai = NINJIN_TANE;
	}
	else if (selectTane == 3 && menutane[3].num > 0) {
		DrawFormatString(300, 200, 0x5D99FF, "����");
		TaneNowyasai = DAIKON_TANE;
	}
	else if (selectTane == 4 && menutane[4].num > 0) {
		DrawFormatString(300, 200, 0x5D99FF, "����");
		TaneNowyasai = KYABETU_TANE;
	}
	else if (selectTane == 5 && menutane[5].num > 0) {
		DrawFormatString(300, 200, 0x5D99FF, "����");
		TaneNowyasai = SATUMAIMO_TANE;
	}
	else if (selectTane == 6 && menutane[6].num > 0) {
		DrawFormatString(300, 200, 0x5D99FF, "����");
		TaneNowyasai = BUROKORI_TANE;
	}
	else if (selectTane == 7 && menutane[7].num > 0) {
		DrawFormatString(300, 200, 0x5D99FF, "����");
		TaneNowyasai = KABOCYA_TANE;
	}
	else if (selectTane == 8 && menutane[8].num > 0) {
		DrawFormatString(300, 200, 0x5D99FF, "����");
		TaneNowyasai = SUIKA_TANE;
	}
	else {
		TaneNowyasai = -99;
	}
}
void DrawSelectTane() {
	DrawBox(390, 300, 610, 420, GetColor(0, 0, 0), true);
	DrawBox(390, 300, 610, 420, GetColor(255, 255, 255), false);

	for (int i = 0; i < select_tane_num; i++) {
		if (menutane[i].drawflg == true) {
			if (menutane[i].colorflg == 1) {
				DrawFormatString(menutane[i].x, menutane[i].y, 0x5D99FF, "%s �~%d", menutane[i].name, menutane[i].num);
			}
			else {
				DrawFormatString(menutane[i].x, menutane[i].y, GetColor(255, 255, 255), "%s �~%d", menutane[i].name, menutane[i].num);
			}
		}
	}
}

void TaneLimit() {
	tanelimitdata = TaneNowyasai;

	if (TaneNowyasai==KOMUGI_TANE) {
		menutane[0].num--;
	}
	else if (TaneNowyasai == JAGAIMO_TANE) {
		menutane[1].num--;
	}
	else if (TaneNowyasai == NINJIN_TANE) {
		menutane[2].num--;
	}
	else if (TaneNowyasai == DAIKON_TANE) {
		menutane[3].num--;
	}
	else if (TaneNowyasai == KYABETU_TANE) {
		menutane[4].num--;
	}
	else if (TaneNowyasai == SATUMAIMO_TANE) {
		menutane[5].num--;
	}
	else if (TaneNowyasai == BUROKORI_TANE) {
		menutane[6].num--;
	}
	else if (TaneNowyasai == KABOCYA_TANE) {
		menutane[7].num--;
	}
	else if (TaneNowyasai == SUIKA_TANE) {
		menutane[8].num--;
	}

	for (int i = 0; i < 9; i++) {
		if (menutane[i].num <= 0) {
			//select_tane_backnum--;
			//select_tane_num--;
			menutane[i].drawflg = false;
		}
	}
}
//*********************************�@�����グ�鏈��********************************************************************************
void YasaiMizuMove() {
	if (KOMUGI_TANE == Mizu_yasainum) { MizuNowyasai = KOMUGI_MIZU; }
	else if (JAGAIMO_TANE == Mizu_yasainum) { MizuNowyasai = JAGAIMO_MIZU; }
	else if (NINJIN_TANE == Mizu_yasainum) { MizuNowyasai = NINJIN_MIZU;}
	else if (DAIKON_TANE == Mizu_yasainum) { MizuNowyasai = DAIKON_MIZU; }//��������
	else if (KYABETU_TANE == Mizu_yasainum) { MizuNowyasai = KYABETU_MIZU; }
	else if (SATUMAIMO_TANE == Mizu_yasainum) { MizuNowyasai = SATUMAIMO_MIZU; }
	else if (BUROKORI_TANE == Mizu_yasainum) { MizuNowyasai = BUROKORI_MIZU; }
	else if (KABOCYA_TANE == Mizu_yasainum) { MizuNowyasai = KABOCYA_MIZU; }
	else if (SUIKA_TANE == Mizu_yasainum) { MizuNowyasai = SUIKA_MIZU; }
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
	else {
		Mizu_yasainum = 0;
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
		if (Yasaidata[i].count >= 360) {
			if (Yasaidata[i].num == KOMUGI_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = KOMUGI;}
			if (Yasaidata[i].num == JAGAIMO_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = JAGAIMO;}
			if (Yasaidata[i].num == NINJIN_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = NINJIN;}
			if (Yasaidata[i].num == DAIKON_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = DAIKON; }
			if (Yasaidata[i].num == KYABETU_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = KYABETU; }
			if (Yasaidata[i].num == SATUMAIMO_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = SATUMAIMO; }
			if (Yasaidata[i].num == BUROKORI_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = BUROKORI; }
			if (Yasaidata[i].num == KABOCYA_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = KABOCYA; }
			if (Yasaidata[i].num == SUIKA_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = SUIKA; }
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
			SyuukakuMov();
		}
		else {
			syukakunum = 0;
		}
}
void SyuukakuMov(){
		if (KOMUGI == syukakunum) {
			SyukakuNowyasai = 0; plantflg = true;
		}
		else if (JAGAIMO == syukakunum) {
			SyukakuNowyasai = 0; plantflg = true;
		}
		else if (NINJIN == syukakunum) {
			SyukakuNowyasai = 0; plantflg = true;
		}
		else if (DAIKON == syukakunum) {
			SyukakuNowyasai = 0; plantflg = true;
		}
		else if (KYABETU == syukakunum) {
			SyukakuNowyasai = 0; plantflg = true;
		}
		else if (SATUMAIMO == syukakunum) {
			SyukakuNowyasai = 0; plantflg = true;
		}
		else if (BUROKORI == syukakunum) {
			SyukakuNowyasai = 0; plantflg = true;
		}
		else if (KABOCYA == syukakunum) {
			SyukakuNowyasai = 0; plantflg = true;
		}
		else if (SUIKA == syukakunum) {
			SyukakuNowyasai = 0; plantflg = true;
		}
		else { plantflg = false; }
}
void YasaiJudgment() {
	SyukakuData = syukakunum;

	if (KOMUGI == SyukakuData) {
		YasaiData_a[0].num++;
	}
	else if (JAGAIMO == SyukakuData) {
		YasaiData_a[1].num++;
	}
	else if (NINJIN == SyukakuData) {
		YasaiData_a[2].num++;
	}
	else if (DAIKON == SyukakuData) {
		YasaiData_a[3].num++;
	}
	else if (KYABETU == SyukakuData) {
		YasaiData_a[4].num++;
	}
	else if (SATUMAIMO == SyukakuData) {
		YasaiData_a[5].num++;
	}
	else if (BUROKORI == SyukakuData) {
		YasaiData_a[6].num++;
	}
	else if (KABOCYA == SyukakuData) {
		YasaiData_a[7].num++;
	}
	else if (SUIKA == SyukakuData) {
		YasaiData_a[8].num++;
	}
}
//�o�b�O����
void Bag() {
	DrawBox(190, 15, 400, 200, GetColor(0, 0, 0), true);
	DrawBox(190, 15, 400, 200, GetColor(255, 255, 255), false);
	for (int i = 0; i < 9; i++) {
		DrawFormatString(200,20*(i+1), GetColor(255,255,255),"[%s][%d]", YasaiData_a[i].name,YasaiData_a[i].num);
	}
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
	if (inp.f_left == true) {
		selectExit = (selectExit + 1) % 2;
	}
	if (inp.f_right == true) {
		selectExit = (selectExit + 1) % 2;
	}
	if (inp.f_left == true || inp.f_right == true) {
		for (int i = 0; i < 2; i++) {
			if (i == selectExit) {
				bacselect[i].colorflg = 1;
			}
			else {
				bacselect[i].colorflg = 0;
			}
		}
	}
	if (inp.space == true) {
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
			DrawFormatString(bacselect[i].x, bacselect[i].y, 0x5D99FF, bacselect[i].name);
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
		if (inp.left == true || inp.right == true || inp.up == true) {
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
	//for (int i = 0; i < MAP_HEIGHT; i++) {
	//	for (int j = 0; j < MAP_WIDTH; j++) {
	//		DrawFormatString(j * CHIP_SIZE + 32, i * CHIP_SIZE + 32, GetColor(255, 255, 0), "%d", tane[i][j]);
	//		DrawBox(j * CHIP_SIZE, i * CHIP_SIZE, (j + 1) * CHIP_SIZE, (i + 1) * CHIP_SIZE, GetColor(255, 255, 255), FALSE);
	//	}
	//}
	//for (int i = 0; i < 30; i++) {
	//	DrawFormatString(100, i * 20, GetColor(255, 255, 0), "[%d]p.y[%d]", i + 1, Yasaidata[i].count);
	//}
	//for (int i = 30; i < 54; i++) {
	//	DrawFormatString(300, (i % 30) * 20, GetColor(255, 255, 0), "[%d]p.y[%d]", i + 1, Yasaidata[i].count);
	//}
	for (int i = 0; i < 9;i++) {
		DrawFormatString(400, (20*i), GetColor(255, 255, 0), "menutane[%d]", menutane[i].num);
	}//DrawFormatString(400, 230, GetColor(255, 255, 0), "�y�[�W�t���O [%d]", pageflg);
	DrawFormatString(400, 230, GetColor(255, 255, 0), "���ނ̐� [%d]", select_tane_num);
	DrawFormatString(400, 250, GetColor(255, 255, 0), "��I���� [%d]", select_tane_backnum);
	//DrawFormatString(400, 270, GetColor(255, 255, 0), "�ۑ��p���n [%d]", syukakunum);
	//DrawFormatString(400, 290, GetColor(255, 255, 0), "���݂̎��n[%d]", SyukakuNowyasai);
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
	//��̃f�[�^�̒��g���擾
	if (IsAbleToGo(player.x, player.y, player.muki) == 1 && player.fremflg == true) {
		if (player.muki == UP) {
			tanenum = tane[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE];
		}
		if (player.muki == DOWN) {
			tanenum = tane[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE];
		}
		if (player.muki == LEFT) {
			tanenum = tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1];
		}
		if (player.muki == RIGHT) {
			tanenum = tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1];
		}
	}
	else {
		tanenum = 0;
	}
	//�f�[�^��0�ȊO�͐A�����Ȃ�
	if (tanenum != 0) {
		taneplantflg = false;
	}
	else {
		taneplantflg = true;
	}
	//�f�[�^��0�Ȃ�A�����
	if (taneplantflg == true) {
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
		TaneLimit();
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
	YasaiJudgment();
}