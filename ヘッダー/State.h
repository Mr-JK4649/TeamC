#pragma once

enum GAME_MODE {
	GAME_TITLE,		//�^�C�g��
	GAME_INIT,		//������
	GAME_END,		//�G���h
	GAME_MAIN,		//�Q�[�����C��
	GAME_C_SELECT,	//�L�����I��
	GAME_S_SELECT,	//�X�e�[�W�I��
	GAME_RESULT,	//���U���g
	GAME_OVER,		//�Q�[���I�[�o�[(�H)
	END = 99		//�G���h�p�ϐ�
};

enum Genre {
	HORROR,			//�z���[
	ACTION,			//�A�N�V����
	RPG,			//RPG
	NOVEL,			//�m�x��
	CARD,			//�J�[�h
	STEALTH,		//�X�e���X
	SIMULATION,		//�V�~�����[�V����
	SHOOTING,		//�V���[�e�B���O
	PUZZLE,			//�p�Y��
	MUSIC,			//���y
	RACE1,			//���[�X(���[�T�[)
	RACE2			//���[�X(���[�X�I�t�B�V����)
};