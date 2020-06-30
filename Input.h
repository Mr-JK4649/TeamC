#pragma once
#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>

#include "State.h"

/*�֐��̃v���g*/


//int g_OldMouse;				//�O��̃}�E�X
//int g_NowMouse;				//����̃}�E�X
//int g_MouseFlg;				//�}�E�X�t���O
//int g_MouseX;				// �}�E�X��X���W
//int g_MouseY;				// �}�E�X��Y���W



struct Input {
	int OldKey=0;				//�O��̃L�[����
	int NowKey=0;				//���݂̃L�[����
	int KeyFlg=0;				//�L�[���͂̃t���O
	
	int OldMouse=0;				//�O��̃}�E�X����
	int NowMouse=0;				//���݂̃}�E�X����
	int MouseFlg=0;				//�}�E�X���͂̃t���O
	int MouseX=0;				//�}�E�X�̂w���W
	int MouseY=0;				//�}�E�X�̂x���W
	bool mleft=0, mright=0;			//�}�E�X�̃u�[���^

	struct Input InputKey(struct Input* inp) {
		inp->OldKey = inp->NowKey;									//�O�t���[���̃L�[�擾
		inp->NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);		//���t���[���̃L�[�擾
		inp->KeyFlg = inp->NowKey & ~inp->OldKey;					//�L�[�t���O

		return *inp;
	}

	struct Input InputMouse(struct Input* inp)
	{	
		inp->OldMouse = inp->NowMouse;
		inp->NowMouse = GetMouseInput();
		inp->MouseFlg = inp->NowMouse & ~inp->OldMouse;

		GetMousePoint(&inp->MouseX, &inp->MouseY);

		if (inp->MouseFlg & MOUSE_INPUT_LEFT) inp->mleft = true;	else inp->mleft = false;

		return *inp;
	}

};