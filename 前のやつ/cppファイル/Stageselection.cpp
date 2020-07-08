#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>

#include "Input.h"
#include "LoadSource.h"
#include "State.h"

#pragma warning(disable : 4244)
#pragma warning(disable : 26812)
#pragma warning(disable : 26451)

#define WIDTH 970	//��ʉ��T�C�Y
#define HEIGHT 600	//��ʏc�T�C�Y
#define SELECT_ITEM 5 //�W�������I�����ڐ�

int UpdatKey();
void Keyselect(void);
void Mouseselect(void);
void StageselectDraw(void);

/********************************************************************
* �ϐ��̐錾
********************************************************************/
int g_OldKey;    // �O��̓��̓L�[
int g_NowKey;    // ����̓��̓L�[
int g_KeyFlg;    // ���̓L�[���
int Key[256];//�L�[��������Ă���t���[�������i�[

int g_MouseX;    // �}�E�X��X���W
int g_MouseY;    // �}�E�X��Y���W
int selectnum = 0;
int Flg = true;
extern int g_GameState;
struct StageImage ssitem;


/********************************************************************
* �\���̂̐錾
********************************************************************/

typedef struct {
	int x, y;
	int w, h;
	int flg;
}StageSerect;

//�Q�[������������
void StageselectInit(void) {
	//���ڏ�����

	for (int i = 0; i < 4; i++) {
		ssitem.sitem[i].x = 40;
		ssitem.sitem[i].y = (80 * i) + 20; //+20�͗]��
		ssitem.sitem[i].w = 300;
		ssitem.sitem[i].h = 60;
		ssitem.sitem[i].flg = false;
	}
	ssitem.sitem[4].x = 40;
	ssitem.sitem[4].y = 550;
}

//�X�e�[�W�Z���N�g�֐�
void GameSSelect(int width,int height) {
	if (Flg) {
		StageselectInit();
		Flg = false;
	}
	StageselectDraw();
	UpdatKey();
	Keyselect();
	Mouseselect();
}
//���t���[���L�[�Ăяo��
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
		selectnum = (selectnum + (SELECT_ITEM - 1)) % SELECT_ITEM;
	}
	if (Key[KEY_INPUT_DOWN] == 1 || Key[KEY_INPUT_UP] == 1) {
		for (int i = 0; i < SELECT_ITEM; i++) {
			if (i == selectnum) {
				ssitem.sitem[i].x = 80;
			}
			else {
				ssitem.sitem[i].x = 40;
			}
		}
	}
	//�L�[�p�X�e�[�W�I��
	if (Key[KEY_INPUT_RETURN] != 0) {
		switch (selectnum)
		{
		case 0:
			g_GameState = GAME_MAIN;
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			g_GameState = GAME_C_SELECT;
			break;
		}
	}
}
//�}�E�X�I��
void Mouseselect(void) {
	// ���̓L�[�擾
	g_OldKey = g_NowKey;
	g_NowKey = GetMouseInput();
	g_KeyFlg = g_NowKey & ~g_OldKey;

	//�}�E�X�̈ʒu���擾
	GetMousePoint(&g_MouseX, &g_MouseY);

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
			g_GameState = GAME_C_SELECT;
		}

		for (int i = 0; i < SELECT_ITEM; i++) {
			if (i == selectnum) {
				ssitem.sitem[i].x = 80;
			}
			else {
				ssitem.sitem[i].x = 40;
			}
		}
	}
}
//�X�e�[�W�Z���N�g�`��
void StageselectDraw(void) {
	struct StageImage stage;
	stage.ImageInput(&stage);
	DrawGraph(0, 0, stage.haikeiA, FALSE);
	for (int i = 0; i < SELECT_ITEM; i++) {
		DrawGraph(ssitem.sitem[i].x, ssitem.sitem[i].y, stage.image[i], FALSE);
	}
	DrawGraph(445, 100, stage.image[selectnum+5], FALSE);
	//�f�o�b�N�p
	//for (int i = 0; i < 5; i++) {
	//	DrawFormatString(20, 20 * i + 450, GetColor(0, 0, 0), "����%d�Ԗ� [X���W%d] [Y���W%d]",i+1, ssitem.sitem[i].x, ssitem.sitem[i].y);
	//}
	//DrawFormatString(30, 350, GetColor(0, 0, 0), "���ڔԍ� %d", selectnum);
	//DrawFormatString(40, 350, GetColor(0, 0, 0), "�G���^�[�L�[ %d", Key[KEY_INPUT_RETURN]);

	//DrawFormatString(800, 400, GetColor(255, 255, 0), "Y %d",g_MouseY);
	/*SetFontSize(50);
	DrawFormatString(480, 20, GetColor(255, 255, 0), "�X�e�[�W�Z���N�g");*/
	//for (int i = 0; i < SELECT_ITEM; i++) {
	//}
}