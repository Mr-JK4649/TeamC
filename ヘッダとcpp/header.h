#pragma once
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <windows.h>

#pragma warning(disable : 4244)

/*�Q�[���V�[���ꗗ*/
enum GAME_MODE {
	GAME_TITLE,		//�^�C�g��
	GAME_INIT,		//������
	GAME_STORY,		//�V�[�P���X�H
	GAME_END,		//�G���h
	GAME_BASE,		//���_
	GAME_HATAKE,	//���̂��
	GAME_SHOP,		//�X�̂��
	GAME_HOME,		//����
	GAME_WORK,		//�d���Љ
	GAME_CASINO,	//�J�W�m
	GAME_S_SELECT,	//�X�e�[�W�I��
	CAME_ENDING,	//3�{�X�|������̂��
	GAME_CREDIT,	//�N���W�b�g
	GAME_RESULT,	//���U���g
	GAME_CREAR,		//�Q�[���N���A
	GAME_OVER,		//�Q�[���I�[�o�[(�H)
	END = 99,		//�G���h�p�ϐ�
	GAME_DUNGEON	//�_���W����
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

