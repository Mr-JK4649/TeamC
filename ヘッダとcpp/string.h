#pragma once
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "DxLib.h"

/*���p�I�Ȋ֐�*/

#pragma warning(disable : 4244)


/******************************************************************
 �@�@�@�@�@�@�@�@�@�����̕\����ς�����
 int�^		x,y		�\�����������W
 char�^		str		�\������������
 short�^	color	�����̐F
 int�^		ch		�����̕\���`�� (0:������  1:��������  2:�E����)
 int�^		size	�����̃T�C�Y   (�W����16)
******************************************************************/

struct String {


	/******************************************************************
 �@�@�@�@�@�@�@�@�@	  �����̕\����ς�����
	 int�^		x,y		�\�����������W
	 char�^		str		�\������������
	 short�^	color	�����̐F
	 int�^		ch		�����̕\���`�� (0:������  1:��������  2:�E����)
	 int�^		size	�����̃T�C�Y   (�W����16)
	******************************************************************/
	void SuperString(int x, int y, const char* str, unsigned int color, int ch, int size) {

		SetFontSize(size);

		const int len = GetDrawStringWidth(str, -1);


		switch (ch) {
		case 0: DrawString(x, y, str, color, 1); break;				//�������ŕ\��

		case 1: DrawString(x - len / 2, y, str, color, 1); break;	//���������ŕ\��

		case 2: DrawString(x - len, y, str, color, 1); break;		//�E�����ŕ\��

		default:DrawString(x, y, "0�`2�̂����ꂩ�őI�����Ă��������B", color, 1);	//�G���[
		}

		SetFontSize(16);

	}

	/******************************************************************
�@�@�@�@�@�@�@�@�@	  �������肷����
	char�^		str		�o����������
	int�^		x,y		�\�����������W
    ******************************************************************/
	void Serihu(char* str, int width, int height) {

		SetFontSize(16);
		DrawRoundRect(5, 5, width - 5, 55, 10, 10, 0x444444, 1);
		DrawRoundRect(5, 5, width - 5, 55, 10, 10, 0xaaaaaa, 0);
		DrawRoundRect(6, 6, width - 6, 54, 10, 10, 0xffffff, 0);

		const int speed = 1;

		if (count++ >= speed) { s += 1; count = 0; }
		strncpy_s(buf, str, s);
		if(count%2==0)DrawFormatString(15, 10, 0xffffff, "%s", buf);
		/*DrawFormatString(5,250,0x000000,"%d",s);
		DrawFormatString(5,275,0x000000,"%d",life);*/

		//if (strcmp(buf, str) >= 0 && inp.Lclick || life++ >= 260) { s = 0; setTex = false; life = 0; }

	}

private:
	int count = 0, s = 0, life = 0;
	char buf[500];
	bool setTex = false;
};

extern String str;