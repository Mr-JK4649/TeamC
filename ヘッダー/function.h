#pragma once
//�L�[���͂̂��
void KeyInput(void);

// �Q�[������������
void GameInit(void);

// �L�����I���V�[��
void GameCSelect(int width, int height);

//�X�e�[�W�I���V�[��
void GameSSelect(int width, int height);

// �퓬�V�[��
void DrawGameMain(int width, int height);
//void PlayerMove(int genre,struct chara *chara,int pl);

// �Q�[���^�C�g���`�揈��
void DrawGameTitle(int width, int height);

// �G���h�`�揈��
void DrawEnd(int width, int height);

// �Q�[���N���A�[�̏���
void DrawGameResult(int width, int height);

// �Q�[���I�[�o�[�`�揈��
void DrawGameOver(int width, int height);

// �摜�ǂݍ���
int LoadImages();

//�T�E���h
int LoadSounds(void);


//�f�o�b�O�p
void DebugMode(int w, int h,int x,int y);