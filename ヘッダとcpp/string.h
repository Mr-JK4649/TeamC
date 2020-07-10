#pragma once
#include <iostream>
#include <stdio.h>
#include "DxLib.h"

/*���p�I�Ȋ֐�*/


/******************************************************************
 �@�@�@�@�@�@�@�@�@�����̕\����ς�����
 int�^		x,y		�\�����������W
 char�^		str		�\������������
 short�^	color	�����̐F
 int�^		ch		�����̕\���`�� (0:������  1:��������  2:�E����)
 int�^		size	�����̃T�C�Y   (�W����16)
******************************************************************/
void SuperString(int x, int y,const char* str, unsigned int color, int ch,int size) {

	SetFontSize(size);

	const int len = GetDrawStringWidth(str, -1);
	

	switch (ch) {
	case 0: DrawString(x, y, str, color, 1); break;				//�������ŕ\��

	case 1: DrawString(x - len / 2, y, str, color, 1); break;	//���������ŕ\��

	case 2: DrawString(x - len, y, str, color, 1); break;		//�E�����ŕ\��

	default:DrawString(x,y,"0�`2�̂����ꂩ�őI�����Ă��������B",color,1);				//�G���[
	}

	SetFontSize(16);

}