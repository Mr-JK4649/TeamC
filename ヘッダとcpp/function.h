#pragma once

//�L�[���͂̂��
void KeyInput(void);

//�Q�[���V�[�P���X�H
void Story(int width, int height);

// �Q�[������������
void GameInit(void);

//�X�e�[�W�I���V�[��
void GameSSelect(int width, int height);

// ���_�V�[��
void DrawGameMain(int width, int height);

/*�Q�[���i�s�ɕK�v�Ȑ��l�𐧌䂷��*/
void GameSystem(void);

/*�J�W�m*/
void Casino_Draw(int width, int height);

//�d���Љ
void Work_Draw(int width, int height);

//�X�̃V�[��
void Shop_Draw(int width, int height);

//����
void Home_Draw(int width, int height);

// �Q�[���^�C�g���`�揈��
void DrawGameTitle(int width, int height);

// �G���h�`�揈��
void DrawEnd(int width, int height);

//�Q�[���N���W�b�g
void DrawCredit(int width, int height);

// �Q�[���N���A�[�̏���
void DrawGameResult(int width, int height);

// �Q�[���I�[�o�[�`�揈��
void DrawGameOver(int width, int height);

//�\���̂̏�����
void Init(void);

//�_���W����
void DrawGameDungeon(int Width, int Height);