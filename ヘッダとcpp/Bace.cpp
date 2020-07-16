#include "DxLib.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "Source.h"
#include "string.h"
#include "Input.h"
#include "header.h"
#include "character.h"

#pragma warning(disable : 6385)

void Base_Disp(int width,int height);
void Base_Update(int width, int height);
int Building_Trriger(float w25, float h100,float x1,float y1,float x2,float y2);
void Building_Serihu(int width,int height);

Menu base_menu;
Base base;
Chara ch;

int TexNum = 99;

char Player_Serihu[5][180] = { "�����͌��⏊�ˁB\n�X���o���肷��ۂɉ�����������������ߕ߂��ꂿ�Ⴄ�����B\n�A�A�A�A�A�A�A�A�A�A�A�Ȃ�ĂˁB",		//���⏊�ŏo��Z���t
							   "�J�W�m���ݗ\��n�Ə����Ă����B\n�o�������񂭂炢���Ă݂Ă�������������Ȃ���ˁB",						//�J�W�m(������)�ŏo��Z���t
							   "a",																											//�J�W�m(���ݍς�)�ŏo��Z���t
							   "����͎d���Љ�̌f���ˁB\n�F��Ȏd���̈˗����\���Ă����B",											//�d���Љ�̌f���ŏo��Z���t
							   "���X�Ŏ�舵���Ă鏤�i�̒l�i�������Ă����B\n����250�S�[���h�A����300�S�[���h�A�񕜖�5�S�[���h�B\n�����̂������̂�������Ȃ���ˁE�E�E�E�E�B" };																										//�X�ŏo��Z���t

void DrawGameMain(int width, int height) {
	
	/*������*/
	if (base.flg) { base.ImageInput(&base); base.flg = false; }
	if (ch.flg) { ch.Init(&ch,width,height); ch.flg = false; }

	/*���_�̕`��֐�*/
	Base_Disp(width, height);
	
	
	/*���_�̍X�V�֐�*/
	if (!base_menu.isMenu)Base_Update(width, height);
	else base_menu.Draw();

	if (!str.setTex && inp.start) base_menu.isMenu = !base_menu.isMenu;

	DrawFormatString(5, 205, 0x000000, "%d", inp.a);

}

/*���_�̕\��*/
void Base_Disp(int width, int height) {
	/*�w�i�\��*/
	DrawExtendGraph(base.move, 0, width * 4 + base.move, height, base.background, 1);

	/*�L�����N�^�[�̕`��ƍX�V*/
	ch.Disp(&ch);

	/*�X�̉e�\��*/
	DrawExtendGraph(base.move, 0, width * 4 + base.move, height, base.shadow, 1);
}

/*���_�̃V�X�e��*/
void Base_Update(int width, int height) {
	/*�v���C���[�̈ړ�*/
	if (!str.setTex)ch.Move(&ch);

	/*�����̔���*/
	Building_Serihu(width, height);

	/*�I�u�W�F�N�g�͈̔͂ɓ����ăX�y�[�X���������Ƃ���*/
	if (TexNum != 99 && inp.space == true) {
		if (str.setTex) str.Serihu_Skip_Fin();
		else str.setTex = true;
	}

	/*�Z���t���o��*/
	if (str.setTex) str.Serihu(Player_Serihu[TexNum], 15, height - (height / 4 - 10), 0xffffff, width / 40);

}

/*�I�u�W�F�N�g�𒲂ׂ����̃Z���t*/
void Building_Serihu(int width,int height) {
	const float w = (float)width * 4.0 / 100.0;
	const float h = (float)height / 100.0;

	if (Building_Trriger(w, h, 19.0f, 50.0f, 26.8f, 58.5f))TexNum = 0;			//���⏊
	else if (Building_Trriger(w, h, 34.2f, 50.0f, 36.6f, 58.5f))TexNum = 1;		//�J�W�m�Ŕ�
	else if (Building_Trriger(w, h, 56.6f, 50.0f, 61.6f, 58.5f))TexNum = 3;		//�f����
	else if (Building_Trriger(w, h, 77.0f, 50.0f, 79.0f, 58.0f))TexNum = 4;		//���X�̃��j���[
	else TexNum = 99;
}

/*************************************************
				�����̔���
int�^	w25		��ʂ̑S����25���������l
int�^	h100	��ʂ̍�����100���������l
int�^	x1,x2	x���W�̎n�_�ƏI�_
int�^	y1,y2	y���W�̎��_�ƏI�_
*************************************************/
int Building_Trriger(float w25, float h100, float x1, float y1, float x2, float y2) {
	const int zero = 0, one = 1;
	const float sx = w25 * x1, ex = w25 * x2;
	const float sy = h100 * y1, ey = h100 * y2;

	DrawBox(sx + base.move, sy, ex + base.move, ey, 0xffff00, 0);

	if (ch.HitCheck(&ch, sx, sy, ex, ey)) {
		DrawBox(5, 5, 100, 100, 0xff0000, 1);
		return one;
	}

	return zero;
}