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

class State {

public:
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
};