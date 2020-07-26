#pragma once
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <wingdi.h>
#include <windows.h>

#pragma warning(disable : 4244)

/*�Q�[���V�[���ꗗ*/
enum GAME_MODE {
	GAME_TITLE,		//�^�C�g��
	GAME_INIT,		//������
	GAME_END,		//�G���h
	GAME_BASE,		//���_
	GAME_HATAKE,	//���̂��
	GAME_SHOP,		//�X�̂��
	GAME_S_SELECT,	//�X�e�[�W�I��
	GAME_RESULT,	//���U���g
	GAME_OVER,		//�Q�[���I�[�o�[(�H)
	END = 99		//�G���h�p�ϐ�
};


/*��ʂ̃T�C�Y��S��ʂɂ��Ȃ����߂̂�� 1920x1080 �` 1528x810*/
struct WindowScaler {
	int Width, Height;
	RECT recDisplay;
	HWND hDeskWnd;

	void GetWindwScale(struct WindowScaler* p) {
		p->hDeskWnd = GetDesktopWindow();
		GetWindowRect(p->hDeskWnd, &p->recDisplay);

		p->Width = p->recDisplay.right;
		p->Height = p->recDisplay.bottom;

		do {
			p->Width *= 0.8;
			p->Height *= 0.8;
		} while (Width >= 1500);

	}

};

extern WindowScaler scale;
extern int g_GameState;

