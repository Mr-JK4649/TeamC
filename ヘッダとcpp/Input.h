#pragma once
#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>
#include <windows.h>

struct Input {
	int OldKey = 0;						//�O��̃L�[����
	int NowKey = 0;						//���݂̃L�[����
	int KeyFlg = 0;						//�L�[���͂̃t���O
	bool up = 0, down = 0, left = 0, right = 0;	//�\���L�[�̂��
	bool space = 0, x = 0, z = 0;				//���̑��̃L�[�̂��

	int OldMouse = 0;					//�O��̃}�E�X����
	int NowMouse = 7;					//���݂̃}�E�X����
	int MouseFlg = 0;					//�}�E�X���͂̃t���O
	int MouseX = 0;					//�}�E�X�̂w���W
	int MouseY = 0;					//�}�E�X�̂x���W
	bool Lclick = 0, Rclick = 0, Cclick = 0, Lhold = 0, Rhold = 0, Ldrag = 0, Rgrag = 0;		//�}�E�X�̃u�[���^

	struct Input InputKey(struct Input* inp) {
		inp->OldKey = inp->NowKey;									//�O�t���[���̃L�[�擾
		inp->NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);		//���t���[���̃L�[�擾
		inp->KeyFlg = inp->NowKey & ~inp->OldKey;					//�L�[�t���O

		if (NowKey & PAD_INPUT_LEFT)	inp->left = true;		else inp->left = false;
		if (NowKey & PAD_INPUT_RIGHT)	inp->right = true;		else inp->right = false;
		if (NowKey & PAD_INPUT_UP)		inp->up = true;			else inp->up = false;
		if (NowKey & PAD_INPUT_DOWN)	inp->down = true;		else inp->down = false;
		if (KeyFlg & KEY_INPUT_SPACE)	inp->space = !inp->space;


		return *inp;
	}

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

};

extern Input inp;