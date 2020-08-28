#pragma once
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "DxLib.h"

#include "header.h"

#pragma warning(disable : 4244)
#pragma warning(disable : 4267)

/*�����������\����*/
struct String {
	bool setTex = false;
	int TexNum = 99;

	bool Fade_String_Box = false;

	/******************************************************************
 �@�@�@�@�@�@�@�@�@	  �����̕\����ς�����
	 int�^		x,y		�\�����������W
	 char�^		str		�\������������
	 int�^		color	�����̐F
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

	}

	/******************************************************************
�@�@�@�@�@�@�@�@�@	  �������肷����
	char�^		str		�o����������
	int�^		x,y		�\�����������W
	int�^		color	�����̐F
	int�^		size	�����̃T�C�Y(�W����16)
    ******************************************************************/
	void Serihu(const char* str, int x, int y,unsigned int color, int size) {

		/*�����������X�s�[�h�𒲐�*/
		const int speed = 3;

		/*������̒������擾*/
		length = strlen(str);

		if (str_init_flg) { strncpy_s(buf2, Init_str, length - 1); str_init_flg = false; }

		/*�Z���t���o��g*/
		if(!Fade_String_Box)Serihu_Window();

		/*�Z���t�̕\��*/
		if (setTex) {
			if (count++ >= speed) { 
				if(s <= length) s += 2; 
				count = 0;
				if(length > 500)
					strncpy_s(buf, str, s);
				else {
					strncpy_s(buf2, Init_str, s);
					strncpy_s(buf2, str, s);
				}
			}

			DrawFormatString(100, 100, 0xffffff, "c %d \n s %d \n b2_len %d \n f_f %d", count, s, strlen(buf2), FinFlg);

			/*�����̕\��*/
			if (length > 500) {
				SuperString(x, y, buf, color, 0, size);
				if (strlen(buf) >= strlen(str)) FinFlg = true;
			}
			else {
				SuperString(x, y, buf2, color, 0, size);
				if (strlen(buf2) >= strlen(str)) FinFlg = true;
			}
		}
	}

	/*�Z���t��\������E�B���h�E���쐬*/
	void Serihu_Window() {
		const int w = scale.Width;
		const int h = scale.Height,h4 = scale.Height / 4;
		DrawRoundRect(5, h - h4, w - 5, h - 5, 10, 10, 0x444444, 1);
		DrawRoundRect(5, h - h4, w - 5, h - 5, 10, 10, 0xaaaaaa, 0);
		DrawRoundRect(6, h - (h4 - 1), w - 6, h - 6, 10, 10, 0xffffff, 0);
	}

	/*�������蒆�̃X�L�b�v�ƏI����̃E�B���h�E��\��*/
	void Serihu_Skip_Fin() {
		if (FinFlg) {
			Init();
			setTex = false;
			FinFlg = false;
			str_init_flg = true;
		}
		else {
			s = length;
			FinFlg = true;
		}
	}

	/*�ϐ��̏�����*/
	void Init() {
		s = 0;
		length = 0;
		count = 0;
		life = 0;
		
	}

private:
	int length=0;
	bool FinFlg = false;
	int count = 0, s = 0, life = 0;
	char buf[4000] = " ";
	char buf2[500] = " ";
	char Init_str[498] = 
		"                                               "
		"                                               "
		"                                               "
		"                                               "
		"                                               "
		"                                               "
		"                                               "
		"                                               "
		"                                               "
		"";
	bool str_init_flg = true;
};

extern String str;

struct Point_Box_HitCheck {

	int HitCheck(int point_x, int point_y, int x1, int y1, int x2, int y2) const {
		const int zero = 0, one = 1;

		if (point_x >= x1 && point_x <= x2 && point_y >= y1 && point_y <= y2) return one;

		return zero;
	}

};

extern Point_Box_HitCheck pbh;