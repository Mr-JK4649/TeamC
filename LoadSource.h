#pragma once

#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>



///*�ϐ��̐錾*/
//int g_TitleImage;				//�^�C�g���摜
//int g_SelectImage;				//�L�����I���摜
//
////�L�����̉摜
//int g_HorrorImage[4];			//�z���[�L�����摜
//
////�X�e�[�W�̉摜
//int g_Dh[2];					//�E�o�����̉摜
//int g_Ohuda;					//���D�̉摜
//int g_Arrow;					//���̉摜


/*�摜�̃A�h���X��������*/


/*�^�C�g���V�[���Ŏg���摜*/
struct TitleImage {
	int TitleImage;				//�^�C�g�����

	void ImageInput(struct TitleImage *p) {
		p->TitleImage = LoadGraph("images/title.png");
	}
};

/*�L�����I���V�[���Ŏg���摜*/
struct SelectImage{
	int SelectImage;		//�z���[�L�����p

	void ImageInput(struct SelectImage* p) {
		p->SelectImage = LoadGraph("images/SadaoSelect.jpg");
	}
};

/*�X�e�[�W�I���V�[���Ŏg���摜*/
struct StageImage {
	int EscapeImage;											//�E�o�X�e�[�W�p

	void ImageInput(struct StageImage* p) {
		p->EscapeImage = LoadGraph("images/h1.png");
	}
};

/*�Q�[���V�[���Ŏg���摜*/
struct Escape{
	int EscapeRoom[2];			//�E�o�����̉摜
	int Ohuda;					//���D�̉摜
	int Arrow;					//���̉摜

	void ImageInput(struct Escape* p) {
		LoadDivGraph("images/�E�o�X�e�[�W�摜.png",2,2,1,720,405,p->EscapeRoom,0);
		p->Ohuda = LoadGraph("images/���D2.png");
		p->Arrow = LoadGraph("images/���.png");
	}
};


//int LoadImages() {
//
//	FILE* soiya;
//	fopen_s(&soiya, "soiya.txt", "w");
//
//
//	switch()
//
//	//�^�C�g��
//	if ((title->TitleImage = LoadGraph("images/title.png")) == -1) {
//		fwrite("�^�C�g���̉摜�ǂݍ��݂ŃG���[", sizeof(char), 50, soiya);
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
//	if ((LoadDivGraph("images/�E�o�X�e�[�W�摜.png", 2, 2, 1, 720, 405, EscapeRoom, 0)) == -1) {
//		fwrite("�E�o�摜�̓ǂݍ��݂ŃG���[", sizeof(char), 50, soiya);
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