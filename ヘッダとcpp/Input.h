#pragma once
#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>
#include <windows.h>

struct Input {
	
	/*�\���L�[�̔���*/
	bool up = 0;				//��(������)
	bool down = 0;				//��(������)
	bool left = 0;				//��(������)
	bool right = 0;				//�E(������)

	bool f_up = 0;				//��(���)
	bool f_down = 0;			//��(���)
	bool f_left = 0;			//�E(���)
	bool f_right = 0;			//��(���)


	/*���̑��̃L�[*/
	bool space = 0,start = 0,sele = 0,cancel = 0,x = 0, z = 0,y = 0;

	int a=0;

	
	/*�}�E�X�̔���*/
	int MouseX = 0;					//�}�E�X�̂w���W
	int MouseY = 0;					//�}�E�X�̂x���W
	bool Lclick = 0, Rclick = 0, Cclick = 0, Lhold = 0, Rhold = 0, Ldrag = 0, Rgrag = 0;		//�}�E�X�̃u�[���^


	/*�L�[����*/
	struct Input InputKey(struct Input* inp) {
		inp->OldKey = inp->NowKey;									//�O�t���[���̃L�[�擾
		inp->NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);		//���t���[���̃L�[�擾
		inp->KeyFlg = inp->NowKey & ~inp->OldKey;					//�L�[�t���O

		if (NowKey & PAD_INPUT_LEFT)	inp->left = true;		else inp->left = false;			//��������
		if (NowKey & PAD_INPUT_RIGHT)	inp->right = true;		else inp->right = false;		//�E������
		if (NowKey & PAD_INPUT_UP)		inp->up = true;			else inp->up = false;			//�㒷����
		if (NowKey & PAD_INPUT_DOWN)	inp->down = true;		else inp->down = false;			//��������
		if (KeyFlg & PAD_INPUT_B)		inp->space = true;		else inp->space = false;		//�a�{�^�����
		if (KeyFlg & PAD_INPUT_A)		inp->cancel = true;		else inp->cancel = false;		//�`�{�^�����
		if (NowKey & PAD_INPUT_C)		inp->y = true;			else inp->y = false;			//�x�{�^�����
		if (NowKey & PAD_INPUT_X)		inp->x = true;			else inp->x = false;			//�w�{�^�����
		if (KeyFlg & PAD_INPUT_R)		inp->start = true;		else inp->start = false;		//�r�s�`�q�s�{�^�����
		if (KeyFlg & PAD_INPUT_L)		inp->sele = true;		else inp->sele = false;			//�r�d�k�d�b�s�{�^�����
		if (KeyFlg & PAD_INPUT_LEFT)	inp->f_left = true;		else inp->f_left = false;		//�����
		if (KeyFlg & PAD_INPUT_RIGHT)	inp->f_right = true;	else inp->f_right = false;		//�E���
		if (KeyFlg & PAD_INPUT_UP)		inp->f_up = true;		else inp->f_up = false;			//����
		if (KeyFlg & PAD_INPUT_DOWN)	inp->f_down = true;		else inp->f_down = false;		//�����

		a = inp->NowKey;

		return *inp;
	}

	/*�}�E�X����*/
	struct Input InputMouse(struct Input* inp)
	{
		inp->OldMouse = inp->NowMouse;
		inp->NowMouse = GetMouseInput();
		inp->MouseFlg = inp->NowMouse & ~inp->OldMouse;

		GetMousePoint(&inp->MouseX, &inp->MouseY);

		if (inp->NowMouse & MOUSE_INPUT_LEFT) inp->Lhold = true; else inp->Lhold = false;
		if (inp->NowMouse & MOUSE_INPUT_RIGHT)inp->Rhold = true; else inp->Rhold = false;
		if (inp->MouseFlg & MOUSE_INPUT_LEFT)inp->Lclick = true; else inp->Lclick = false;
		if (inp->MouseFlg & MOUSE_INPUT_MIDDLE) inp->Cclick = !inp->Cclick;
		if (inp->MouseFlg & MOUSE_INPUT_RIGHT) inp->Rclick = true; else inp->Rclick = false;

		return *inp;
	}

private:
	int OldKey = 0;						//�O��̃L�[����
	int NowKey = 0;						//���݂̃L�[����
	int KeyFlg = 0;						//�L�[���͂̃t���O

	int OldMouse = 0;					//�O��̃}�E�X����
	int NowMouse = 7;					//���݂̃}�E�X����
	int MouseFlg = 0;					//�}�E�X���͂̃t���O
};

extern Input inp;