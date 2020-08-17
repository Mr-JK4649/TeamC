#pragma once
#include "DxLib.h"
#include <stdio.h>

struct SoundE {
	int flg = true;

	int SelectMove_SE = 0;			//���j���[�ł̑I���㉺��
	int Select_SE = 0;				//���j���[�ł̌��艹
	int Cansel_SE = 0;				//���j���[�ł̃L�����Z����

	

	void Init(SoundE* p) {
		p->SelectMove_SE = LoadSoundMem("sounds/�J�[�\���ړ�.mp3");
		p->Select_SE = LoadSoundMem("sounds/���j���[����.mp3");
		p->Cansel_SE = LoadSoundMem("sounds/���j���[�L�����Z��.mp3");
	}
};

extern SoundE se;

/*�^�C�g���V�[���̉摜*/
struct Title {
	int image[2] = { 0 };
	int Arrow = 0;
	
	int bgm = 0;
	int SelectMove_SE = 0;
	int Select_SE = 0;
	int Start_SE = 0;
	
	//���炷���p
	int Story_bgm = 0;

	bool flg = true;

	void ImageInput(struct Title* p) {
		p->image[0] = LoadGraph("images/�^�C�g���ĂP��I����.jpg");
		p->image[1] = LoadGraph("images/�^�C�g���ĂP���I����.jpg");

		p->bgm = LoadSoundMem("sounds/�^�C�g��BGM2.mp3",3);
		p->SelectMove_SE = LoadSoundMem("sounds/�J�[�\���ړ�.mp3");
		p->Select_SE = LoadSoundMem("sounds/���j���[����.mp3");
		p->Start_SE = LoadSoundMem("sounds/�Q�[���X�^�[�g.mp3");

		p->Story_bgm = LoadSoundMem("sounds/���炷��BGM.mp3");
	}
};

extern Title title;

/*�X�e�[�W�V�[���̉摜*/
struct Stage {
	int background = 0;
	int Button = 0;
	bool flg = true;

	void ImageInput(struct Stage* p) {
		p->background = LoadGraph("images/aaa.png");
		p->Button;
	}

};

extern Stage stage;

/*���_�V�[���̉摜*/
struct Base {
	int background = 0;
	int background2 = 0;
	int shadow = 0;
	bool flg = true;
	int move=0;

	int bgm = 0;
	int SelectMove_SE = 0;
	int Select_SE = 0;
	int Cansel_SE = 0;

	int Gage_Icon = 0;

	int BC_window_pop = 0;			//�����ɓ���ۂ̊m�F�E�B���h�E���|�b�v�A�b�v���鉹

	int Tips_img[7][5] = { 0 };		//TIPS�̉摜

	int Tutorial_img[3] = { 0 };	//���_�ɓ������Ƃ��Ƀ`���[�g���A�����o��

	void ImageInput(struct Base* p) {
		p->background = LoadGraph("images/���̕��i1.png");
		p->background2 = LoadGraph("images/���̕��i2.png");
		p->shadow = LoadGraph("images/�X�̉e.png");
		p->Gage_Icon = LoadGraph("images/�Q�[�W�A�C�R��.png");

		p->bgm = LoadSoundMem("sounds/���_BGM2.mp3", 3);
		
		p->BC_window_pop = LoadSoundMem("sounds/�����m�F.mp3");

		p->Tutorial_img[0] = LoadGraph("images/C������@.png");
		p->Tutorial_img[1] = LoadGraph("images/K������@.png");
		p->Tutorial_img[2] = LoadGraph("images/TIPS�m�F.png");

		//������@TIPS
		Tips_img[0][0] = LoadGraph("images/C������@.png");
		Tips_img[0][1] = LoadGraph("images/K������@.png");

		//�ړI�ƃ��[��
		Tips_img[1][0] = LoadGraph("images/�ړI.png");
		Tips_img[1][1] = LoadGraph("images/���[��.png");

		//�L�����N�^�[TIPS
		Tips_img[2][0] = LoadGraph("images/�X�e�[�^�X1.png");
		Tips_img[2][1] = LoadGraph("images/�X�e�[�^�X2.png");
		Tips_img[2][2] = LoadGraph("images/�����i.png");
		Tips_img[2][3] = LoadGraph("images/�����i.png");

		//�Q�[�W�ɂ���
		Tips_img[6][0] = LoadGraph("images/�Q�[�W�ɂ���.png");
		Tips_img[6][1] = LoadGraph("images/�e�Q�[�W�ɂ���1.png");
		Tips_img[6][2] = LoadGraph("images/�e�Q�[�W�ɂ���2.png");
		Tips_img[6][3] = LoadGraph("images/�e�Q�[�W�ɂ���3.png");
	}

};

extern Base base;

struct Casino {
	int background = 0;
	int flg = true;

	int Casino_Table = 0;			//�΂̃e�[�u���̉摜
	int Dragon_Tiger_img = 0;		//�h���S���^�C�K�[�̐���
	int Casino_War_img = 0;			//�J�W�m�E�H�[�̐���

	int Dragon_img = 0;				//�h���S���^�C�K�[�̃h���S��
	int Tiger_img = 0;				//�h���S���^�C�K�[�̃g��

	int Cards[52] = {0};
	int Card_Back = 0;

	int bgm = 0;


	void ImageInput(Casino* p) {
		p->background = LoadGraph("images/Casino.jpg");
		LoadDivGraph("images/�g�����v�J�[�h2.png", 52, 13, 4, 265, 355, p->Cards, 1);
		p->Card_Back = LoadGraph("images/�J�[�h�̗�.png");
		p->Casino_Table = LoadGraph("images/�J�W�m�e�[�u��.jpg");
		p->Dragon_Tiger_img = LoadGraph("images/�h���S���^�C�K�[.png");
		p->Casino_War_img = LoadGraph("images/�J�W�m�E�H�[.png");
		p->Dragon_img = LoadGraph("images/�h���S��.png");
		p->Tiger_img = LoadGraph("images/�g��.png");

		p->bgm = LoadSoundMem("sounds/�J�W�mBGM.mp3");
	}

};

extern Casino casino;

struct Work {
	int background = 0;
	bool flg = true;

	void ImageInput(Work* p) {
		p->background = LoadGraph("images/�d���Љ.jpg");
	}
};

extern Work work;

struct Shop {
	int background[6] = {0,0,0,0,0,0};		//���퉮�w�i
	int Weapon_img[5] = { 0 };				//����̉摜
	int Shield_img[3] = { 0 };				//���̉摜
	int Item_img[2] = { 0 };				//�A�C�e���̉摜
	int Cover[5] = { 0 };					//�����Ȃ����i�̃J�o�[
	bool flg = true;
	
	int bgm = 0;							//�a�f�l
	int Pay_SE = 0;							//�x�������̌��ʉ�

	void ImageInput(Shop* p) {
		p->background[0] = LoadGraph("images/ShopSele1.jpg");
		p->background[1] = LoadGraph("images/ShopSele2.jpg");
		p->background[2] = LoadGraph("images/ShopSele3.jpg");
		p->background[3] = LoadGraph("images/ShopSele4.jpg");
		p->background[4] = LoadGraph("images/ShopSele5.jpg");
		p->background[5] = LoadGraph("images/shop.jpg");

		p->Weapon_img[0] = LoadGraph("images/�؂̌�.png");
		p->Weapon_img[1] = LoadGraph("images/�S�̌�.png");
		p->Weapon_img[2] = LoadGraph("images/�G�N�X�J���o�[.png");
		p->Weapon_img[3] = LoadGraph("images/�؂̏�.png");
		p->Weapon_img[4] = LoadGraph("images/�S�̏�.png");

		p->Shield_img[0] = LoadGraph("images/�؂̏�.png");
		p->Shield_img[1] = LoadGraph("images/�΂̏�.png");
		p->Shield_img[2] = LoadGraph("images/�S�̏�.png");

		p->Cover[0] = LoadGraph("images/shop_cover1.png");
		p->Cover[1] = LoadGraph("images/shop_cover2.png");
		p->Cover[2] = LoadGraph("images/shop_cover3.png");
		p->Cover[3] = LoadGraph("images/shop_cover4.png");
		p->Cover[4] = LoadGraph("images/shop_cover5.png");

		p->Item_img[0] = LoadGraph("images/�|�[�V����.png");
		p->Item_img[1] = LoadGraph("images/�V���b�v_�^�s�I�J�l�s.png");

		p->Pay_SE = LoadSoundMem("sounds/���X�̎x����.mp3");
	}

};

extern Shop shop;

struct Home {
	int background = 0;
	bool flg = true;


	int home_select = 0;
	int Box_Select = 0;
	int Box_Select2 = 0;
	int Box_Select3 = 0;
	int Box_Select4 = 0;
	int Min_Box_Disp = 0;
	int Max_Box_Disp = 10;
	int Bed_Count = 0;
	int Bed_Alpha = 0;
	int Bed_Alpha_Add = 1;
	char Selct_String[4][17] = {"�A�C�e���{�b�N�X","�x�b�h�ŋx��","���ɍs��","�Ƃ��o��"};
	char Box_Select_String[2][9] = { "���[����","���o��" };
	unsigned int color = 0xffffff;
	unsigned int white_color = 0xffffff;
	unsigned int blue_color = 0x6666ff;

	int bgm = 0;
	int Bed_bgm = 0;

	void ImageInput(Home* p) {
		p->background = LoadGraph("images/home2.jpg");

		p->bgm = LoadSoundMem("sounds/����BGM2.mp3");
		p->Bed_bgm = LoadSoundMem("sounds/����x�b�hBGM.mp3");
	}

};

extern Home home;

struct HATAKE {
	int image = 0;
	int testimage[12];
	int tane[3];
	int yasai[3];
	int mizu[3];
	int fremimage = 0;
	int selectfrem = 0;
	bool flg = true;
	void ImageInput(struct HATAKE* p) {
		p->image = LoadGraph("images/hatakeimage.png");
		p->fremimage = LoadGraph("images/frem.png");
		p->selectfrem = LoadGraph("images/selectfrem.png");
		//������ image_DOWN
		p->testimage[0] = LoadGraph("images/JK2_1.png");
		p->testimage[1] = LoadGraph("images/JK2_2.png");
		p->testimage[2] = LoadGraph("images/JK2_3.png");
		//����� image_UP
		p->testimage[3] = LoadGraph("images/JK2_4.png");
		p->testimage[4] = LoadGraph("images/JK2_5.png");
		p->testimage[5] = LoadGraph("images/JK2_6.png");
		//�E���� image_RIGHT
		p->testimage[6] = LoadGraph("images/JK2_7.png");
		p->testimage[7] = LoadGraph("images/JK2_8.png");
		p->testimage[8] = LoadGraph("images/JK2_9.png");
		//������ image_LEFT
		p->testimage[9] = LoadGraph("images/JK2_10.png");
		p->testimage[10] = LoadGraph("images/JK2_11.png");
		p->testimage[11] = LoadGraph("images/JK2_12.png");

		p->tane[0] = LoadGraph("images/KomugiTane.png");
		p->tane[1] = LoadGraph("images/JagaimoTane.png");
		p->tane[2] = LoadGraph("images/NinjinTane.png");
		p->yasai[0] = LoadGraph("images/komugi.png");
		p->yasai[1] = LoadGraph("images/jagaimo.png");
		p->yasai[2] = LoadGraph("images/ninjin.png");
		p->mizu[0] = LoadGraph("images/KomugiMizu.png");
		p->mizu[1] = LoadGraph("images/JagaimoMizu.png");
		p->mizu[2] = LoadGraph("images/NinjinMizu.png");
	}
};

extern HATAKE hatake;

// �_���W�����V�[���摜
struct Dungeon {
	int Map[12][34] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	float TIP_WIDTH = 0;
	float TIP_HEIGHT = 0;

	int background = 0;		//���A�w�i
	int stage = 0;		//�_���W����(�X�e�[�W)
	bool flg = true;	//�{�^��
	int move = 0;
	int up = -684;
	int jump = 0;

	int Effect_Anim_Num[5] = { 10,9,15,7,18 };	//�G�t�F�N�g�̉摜��
	int Effect_Speed[5] = { 20,5,5,10,10 };	//�G�t�F�N�g�̕\�����x
	int Hit_Effect[10] = { 0 };		//�U���q�b�g�̃G�t�F�N�g
	int Sword_Effect1[9] = { 0 };	//���̍U���G�t�F�N�g1
	int Sword_Effect2[15] = { 0 };	//���̍U���G�t�F�N�g2
	int Magic_Effect1[7] = { 0 };	//���@�̃G�t�F�N�g1
	int Magic_Effect2[18] = { 0 };	//���@�̃G�t�F�N�g
	
	enum Enemy_Action
	{
		Idle,
		Move,
		Attack
	};

	/*�ҋ@�Ɏg���摜��*/
	int Enemy_Idle_Lim[12] = { 3,4,3,3,4,4,4,4,3,4,4,4 };

	/*�ړ��Ɏg���摜��*/
	int Enemy_Move_Lim[12] = { 4,4,6,6,4,6,6,4,6,4,4,6 };

	/*�U���Ɏg���摜��*/
	int Enemy_Attack_Lim[12] = { 5,4,5,4,4,4,4,4,4,4,4,5 };

	/*�퓬�J�n���̓G�̈ʒu������������ϐ�*/
	int Battle_Enemy_Pos[12][2] =
	{
		{ -99,422 },		//�X���C��
		{ -99,400 },		//�d��
		{ -99,320 },		//�]���r
		{ 4600,320 },		//�R�{���g�@�{�X
		{ -99,320 },		//��
		{ -99,320 },		//���m
		{ -99,320 },		//���@�g��
		{ 4600,320},		//�ǂ���@�@�{�X
		{ -99,310 },		//���R�{���g
		{ -99,320 },		//���ǂ���
		{ -99,380 },		//���d��
		{ 4600,320 }		//�h���S���@�{�X
	};

	/*�G�̃T�C�Y*/
	int Enemy_Size[12][2] =
	{
		{200,200},
		{200,200},
		{300,300},
		{300,300},//
		{150,150},
		{300,300},
		{300,300},
		{300,300},//
		{320,320},
		{320,320},
		{200,200},
		{650,450} //
	};

	/*�G�̃X�e�[�^�X�ƌo���l(HP�A�U���́A�ړ����x�A�o���l)*/
	int Enemy_Status[12][4] =
	{
		{100,1,1,100},		//�X���C��
		{150,1,2,150},		//�d��
		{200,2,1,200},		//�]���r
		{500,3,2,1000},		//�R�{���g�@�{�X
		{300,2,3,200},		//��
		{500,2,1,500},		//���m
		{400,2,2,400},		//���@�g��
		{1000,4,2,2000},	//�ǂ���@�@�{�X
		{600,4,3,1200},		//���R�{���g
		{1200,5,3,2400},	//���ǂ���
		{400,3,3,800},		//���d��
		{5000,6,2,10000}	//�h���S���@�{�X
	};

	/*�U���̂��(�U���͈́A�U���̎��)*/
	int Enemy_Attacks[12][3] =
	{
		{100,200,0},		//�X���C��
		{100,200,0},		//�d��
		{100,200,0},		//�]���r
		{100,200,0},		//�R�{���g�@�{�X
		{100,200,0},		//��
		{100,200,0},		//���m
		{100,200,0},		//���@�g��
		{100,200,0},		//�ǂ���@�@�{�X
		{100,200,0},		//���R�{���g
		{100,200,0},		//���ǂ���
		{100,200,0},		//���d��
		{100,200,0}			//�h���S���@�{�X
	};

	
	int Cobolt_x = 4600, Cobolt_y = -50;
	int Cobolt_size = 300;
	int Cobolt_Width = 300;
	int Cobolt_Height = 300;
	int Cobolt_Hp = 400;
	int Cobolt_Atk = 4;
	int Cobolt_Exp = 25;
	int CoboltA_Idle[3] = {0};
	int CoboltA_Move[6] = {0};
	int CoboltA_Attack[4] = {0};


	int Enemy_Idle[12][4] = { 0 };
	int Enemy_Move[12][6] = { 0 };
	int Enemy_Attack[12][5] = { 0 };

	

	void ImageInput(struct Dungeon* p) {
		p->background = LoadGraph("images/�_���W�����w�i.png");
		p->stage = LoadGraph("images/�ȒP�X�e�[�W.png");

		/*�G�t�F�N�g*/
		LoadDivGraph("images/Effects/hit_effect.png", 10, 1, 10, 640, 480, p->Hit_Effect, 1);
		LoadDivGraph("images/Effects/sword_effect1.png", 9, 9, 1, 240, 240, p->Sword_Effect1, 1);
		LoadDivGraph("images/Effects/sword_effect2.png", 15, 5, 3, 480, 480, p->Sword_Effect2, 1);
		LoadDivGraph("images/Effects/magic_effect1.png", 7, 7, 1, 240, 240, p->Magic_Effect1, 1);
		LoadDivGraph("images/Effects/magic_effect2.png", 18, 3, 6, 640, 300, p->Magic_Effect2, 1);

		/*�X���C��*/
		if (true) {
			p->Enemy_Idle[0][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�X���C��/�X���C��A_�ҋ@000.png");
			p->Enemy_Idle[0][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�X���C��/�X���C��A_�ҋ@001.png");
			p->Enemy_Idle[0][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�X���C��/�X���C��A_�ҋ@002.png");

			p->Enemy_Move[0][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�X���C��/�X���C��A_�ړ�000.png");
			p->Enemy_Move[0][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�X���C��/�X���C��A_�ړ�001.png");
			p->Enemy_Move[0][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�X���C��/�X���C��A_�ړ�002.png");
			p->Enemy_Move[0][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�X���C��/�X���C��A_�ړ�003.png");

			p->Enemy_Attack[0][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�X���C��/�X���C��A_�U��000.png");
			p->Enemy_Attack[0][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�X���C��/�X���C��A_�U��001.png");
			p->Enemy_Attack[0][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�X���C��/�X���C��A_�U��002.png");
			p->Enemy_Attack[0][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�X���C��/�X���C��A_�U��003.png");
			p->Enemy_Attack[0][4] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�X���C��/�X���C��A_�U��004.png");
		}

		/*�d��*/
		if (true) {
			p->Enemy_Idle[1][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��A_�ҋ@000.png");
			p->Enemy_Idle[1][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��A_�ҋ@001.png");
			p->Enemy_Idle[1][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��A_�ҋ@002.png");
			p->Enemy_Idle[1][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��A_�ҋ@003.png");

			p->Enemy_Move[1][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��A_�ړ�000.png");
			p->Enemy_Move[1][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��A_�ړ�001.png");
			p->Enemy_Move[1][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��A_�ړ�002.png");
			p->Enemy_Move[1][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��A_�ړ�003.png");

			p->Enemy_Attack[1][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��A_�U��000.png");
			p->Enemy_Attack[1][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��A_�U��001.png");
			p->Enemy_Attack[1][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��A_�U��002.png");
			p->Enemy_Attack[1][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��A_�U��003.png");
		}

		/*�]���r*/
		if (true) {
			p->Enemy_Idle[2][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�]���r/�]���rA_�ҋ@000.png");
			p->Enemy_Idle[2][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�]���r/�]���rA_�ҋ@001.png");
			p->Enemy_Idle[2][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�]���r/�]���rA_�ҋ@002.png");

			p->Enemy_Move[2][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�]���r/�]���rA_�ړ�000.png");
			p->Enemy_Move[2][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�]���r/�]���rA_�ړ�001.png");
			p->Enemy_Move[2][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�]���r/�]���rA_�ړ�002.png");
			p->Enemy_Move[2][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�]���r/�]���rA_�ړ�003.png");
			p->Enemy_Move[2][4] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�]���r/�]���rA_�ړ�004.png");
			p->Enemy_Move[2][5] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�]���r/�]���rA_�ړ�005.png");

			p->Enemy_Attack[2][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�]���r/�]���rA_�U��000.png");
			p->Enemy_Attack[2][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�]���r/�]���rA_�U��001.png");
			p->Enemy_Attack[2][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�]���r/�]���rA_�U��002.png");
			p->Enemy_Attack[2][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�]���r/�]���rA_�U��003.png");
			p->Enemy_Attack[2][4] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�]���r/�]���rA_�U��004.png");
		}

		/*�R�{���g*/
		if (true) {
			p->Enemy_Idle[3][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gA_�ҋ@000.png");
			p->Enemy_Idle[3][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gA_�ҋ@001.png");
			p->Enemy_Idle[3][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gA_�ҋ@002.png");

			p->Enemy_Move[3][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gA_�ړ�000.png");
			p->Enemy_Move[3][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gA_�ړ�001.png");
			p->Enemy_Move[3][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gA_�ړ�002.png");
			p->Enemy_Move[3][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gA_�ړ�003.png");
			p->Enemy_Move[3][4] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gA_�ړ�004.png");
			p->Enemy_Move[3][5] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gA_�ړ�005.png");

			p->Enemy_Attack[3][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gA_�U��000.png");
			p->Enemy_Attack[3][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gA_�U��001.png");
			p->Enemy_Attack[3][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gA_�U��002.png");
			p->Enemy_Attack[3][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gA_�U��003.png");
			p->Enemy_Attack[3][4] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gA_�U��004.png");
		}

		/*��*/
		if (true) {
			p->Enemy_Idle[4][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/��/��A_�ҋ@000.png");
			p->Enemy_Idle[4][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/��/��A_�ҋ@001.png");
			p->Enemy_Idle[4][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/��/��A_�ҋ@002.png");
			p->Enemy_Idle[4][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/��/��A_�ҋ@003.png");

			p->Enemy_Move[4][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/��/��A_�ړ�000.png");
			p->Enemy_Move[4][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/��/��A_�ړ�001.png");
			p->Enemy_Move[4][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/��/��A_�ړ�002.png");
			p->Enemy_Move[4][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/��/��A_�ړ�003.png");

			p->Enemy_Attack[4][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/��/��A_�U��000.png");
			p->Enemy_Attack[4][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/��/��A_�U��001.png");
			p->Enemy_Attack[4][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/��/��A_�U��002.png");
			p->Enemy_Attack[4][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/��/��A_�U��003.png");
		}

		/*���m*/
		if (true) {
			p->Enemy_Idle[5][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���m/���mA_�ҋ@000.png");
			p->Enemy_Idle[5][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���m/���mA_�ҋ@001.png");
			p->Enemy_Idle[5][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���m/���mA_�ҋ@002.png");
			p->Enemy_Idle[5][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���m/���mA_�ҋ@003.png");

			p->Enemy_Move[5][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���m/���mA_�ړ�000.png");
			p->Enemy_Move[5][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���m/���mA_�ړ�001.png");
			p->Enemy_Move[5][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���m/���mA_�ړ�002.png");
			p->Enemy_Move[5][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���m/���mA_�ړ�003.png");
			p->Enemy_Move[5][4] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���m/���mA_�ړ�004.png");
			p->Enemy_Move[5][5] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���m/���mA_�ړ�005.png");

			p->Enemy_Attack[5][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���m/���mA_�U��000.png");
			p->Enemy_Attack[5][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���m/���mA_�U��001.png");
			p->Enemy_Attack[5][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���m/���mA_�U��002.png");
			p->Enemy_Attack[5][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���m/���mA_�U��003.png");
		}

		/*���@�g��*/
		if (true) {
			p->Enemy_Idle[6][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���@�g��/���@�g��A_�ҋ@000.png");
			p->Enemy_Idle[6][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���@�g��/���@�g��A_�ҋ@001.png");
			p->Enemy_Idle[6][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���@�g��/���@�g��A_�ҋ@002.png");
			p->Enemy_Idle[6][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���@�g��/���@�g��A_�ҋ@003.png");

			p->Enemy_Move[6][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���@�g��/���@�g��A_�ړ�000.png");
			p->Enemy_Move[6][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���@�g��/���@�g��A_�ړ�001.png");
			p->Enemy_Move[6][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���@�g��/���@�g��A_�ړ�002.png");
			p->Enemy_Move[6][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���@�g��/���@�g��A_�ړ�003.png");
			p->Enemy_Move[6][4] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���@�g��/���@�g��A_�ړ�004.png");
			p->Enemy_Move[6][5] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���@�g��/���@�g��A_�ړ�005.png");

			p->Enemy_Attack[6][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���@�g��/���@�g��A_�U��000.png");
			p->Enemy_Attack[6][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���@�g��/���@�g��A_�U��001.png");
			p->Enemy_Attack[6][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���@�g��/���@�g��A_�U��002.png");
			p->Enemy_Attack[6][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/���@�g��/���@�g��A_�U��003.png");
		}

		/*�ǂ���*/
		if (true) {
			p->Enemy_Idle[7][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���A_�ҋ@�E�ړ�000.png");
			p->Enemy_Idle[7][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���A_�ҋ@�E�ړ�001.png");
			p->Enemy_Idle[7][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���A_�ҋ@�E�ړ�002.png");
			p->Enemy_Idle[7][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���A_�ҋ@�E�ړ�003.png");

			p->Enemy_Move[7][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���A_�ҋ@�E�ړ�000.png");
			p->Enemy_Move[7][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���A_�ҋ@�E�ړ�001.png");
			p->Enemy_Move[7][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���A_�ҋ@�E�ړ�002.png");
			p->Enemy_Move[7][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���A_�ҋ@�E�ړ�003.png");

			p->Enemy_Attack[7][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���A_�U��000.png");
			p->Enemy_Attack[7][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���A_�U��001.png");
			p->Enemy_Attack[7][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���A_�U��002.png");
			p->Enemy_Attack[7][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���A_�U��003.png");
		}

		/*���R�{���g*/
		if (true) {
			p->Enemy_Idle[8][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gD_�ҋ@000.png");
			p->Enemy_Idle[8][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gD_�ҋ@001.png");
			p->Enemy_Idle[8][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gD_�ҋ@002.png");

			p->Enemy_Move[8][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gD_�ړ�000.png");
			p->Enemy_Move[8][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gD_�ړ�001.png");
			p->Enemy_Move[8][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gD_�ړ�002.png");
			p->Enemy_Move[8][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gD_�ړ�003.png");
			p->Enemy_Move[8][4] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gD_�ړ�004.png");
			p->Enemy_Move[8][5] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gD_�ړ�005.png");

			p->Enemy_Attack[8][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gD_�U��000.png");
			p->Enemy_Attack[8][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gD_�U��001.png");
			p->Enemy_Attack[8][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gD_�U��002.png");
			p->Enemy_Attack[8][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gD_�U��003.png");
			p->Enemy_Attack[8][4] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�R�{���g/�R�{���gD_�U��004.png");
		}

		/*���ǂ���*/
		if (true) {
			p->Enemy_Idle[9][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���D_�ҋ@�E�ړ�000.png");
			p->Enemy_Idle[9][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���D_�ҋ@�E�ړ�001.png");
			p->Enemy_Idle[9][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���D_�ҋ@�E�ړ�002.png");
			p->Enemy_Idle[9][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���D_�ҋ@�E�ړ�003.png");

			p->Enemy_Move[9][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���D_�ҋ@�E�ړ�000.png");
			p->Enemy_Move[9][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���D_�ҋ@�E�ړ�001.png");
			p->Enemy_Move[9][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���D_�ҋ@�E�ړ�002.png");
			p->Enemy_Move[9][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���D_�ҋ@�E�ړ�003.png");

			p->Enemy_Attack[9][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���D_�U��000.png");
			p->Enemy_Attack[9][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���D_�U��001.png");
			p->Enemy_Attack[9][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���D_�U��002.png");
			p->Enemy_Attack[9][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�ǂ���/�ǂ���D_�U��003.png");
		}

		/*���d��*/
		if (true) {
			p->Enemy_Idle[10][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��D_�ҋ@000.png");
			p->Enemy_Idle[10][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��D_�ҋ@001.png");
			p->Enemy_Idle[10][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��D_�ҋ@002.png");
			p->Enemy_Idle[10][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��D_�ҋ@003.png");

			p->Enemy_Move[10][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��D_�ړ�000.png");
			p->Enemy_Move[10][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��D_�ړ�001.png");
			p->Enemy_Move[10][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��D_�ړ�002.png");
			p->Enemy_Move[10][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��D_�ړ�003.png");

			p->Enemy_Attack[10][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��D_�U��000.png");
			p->Enemy_Attack[10][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��D_�U��001.png");
			p->Enemy_Attack[10][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��D_�U��002.png");
			p->Enemy_Attack[10][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�d��/�d��D_�U��003.png");
		}

		/*�h���S��*/
		if (true) {
			p->Enemy_Idle[11][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�h���S��/�h���S��A_�ҋ@000.png");
			p->Enemy_Idle[11][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�h���S��/�h���S��A_�ҋ@001.png");
			p->Enemy_Idle[11][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�h���S��/�h���S��A_�ҋ@002.png");
			p->Enemy_Idle[11][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�h���S��/�h���S��A_�ҋ@003.png");

			p->Enemy_Move[11][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�h���S��/�h���S��A_�ړ�000.png");
			p->Enemy_Move[11][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�h���S��/�h���S��A_�ړ�001.png");
			p->Enemy_Move[11][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�h���S��/�h���S��A_�ړ�002.png");
			p->Enemy_Move[11][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�h���S��/�h���S��A_�ړ�003.png");
			p->Enemy_Move[11][4] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�h���S��/�h���S��A_�ړ�004.png");
			p->Enemy_Move[11][5] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�h���S��/�h���S��A_�ړ�005.png");

			p->Enemy_Attack[11][0] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�h���S��/�h���S��A_�U��000.png");
			p->Enemy_Attack[11][1] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�h���S��/�h���S��A_�U��001.png");
			p->Enemy_Attack[11][2] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�h���S��/�h���S��A_�U��002.png");
			p->Enemy_Attack[11][3] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�h���S��/�h���S��A_�U��003.png");
			p->Enemy_Attack[11][4] = LoadGraph("images/�Q�[���p�����X�^�[�f��/�h���S��/�h���S��A_�U��004.png");
		}

	}
};

extern Dungeon dungeon;