#pragma once
#include <iostream>
#include <stdio.h>

//�L�[���͂̂��
void KeyInput(void);

// �Q�[������������
void GameInit(void);

//�X�e�[�W�I���V�[��
void GameSSelect(int width, int height);

// �퓬�V�[��
void DrawGameMain(int width, int height);

// �Q�[���^�C�g���`�揈��
void DrawGameTitle(int width, int height);

// �G���h�`�揈��
void DrawEnd(int width, int height);

// �Q�[���N���A�[�̏���
void DrawGameResult(int width, int height);

// �Q�[���I�[�o�[�`�揈��
void DrawGameOver(int width, int height);

