#pragma once

#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>
#include <windows.h>

#include "Source.h"
#include "Input.h"
#include "header.h"

extern Base base;

struct Chara {
	/*�L�����̃t���O*/
	bool flg = true;

	/*�L�����\���̂̏�����*/
	void Init(Chara* p,int w,int h) {
		LoadDivGraph("images/���W��a.png",6,6,1,200,200,p->jk,0);

		p->width = w;
		p->height = h;
		p->c_size = width / 6;
		p->c_Hsize_s = c_size / 3;
		p->c_Hsize_e = c_size - c_Hsize_s;
	}

	/*�L�����摜�̕\���Ɠ����蔻��̕\��*/
	void Disp(Chara *p) {
		DrawExtendGraph(p->x, p->y,p->x + p->c_size, p->y + p->c_size,p->jk[p->num + p->add],1);
		//DrawGraph(p->x, p->y, p->jk[p->num], 1);

		//�����蔻��
		DrawBox(p->x+p->c_Hsize_s,p->y,
				p->x+p->c_Hsize_e,p->y+p->c_size,
				0xff0000,0);

		/*�������牺�̓f�o�b�O�p*/
		//DrawFormatString(5, 5, 0x000000, "l:%4d r:%4d u:%4d d:%4d", inp.left, inp.right, inp.up, inp.down);
		//DrawFormatString(5, 45, 0x000000, "n:%d a:%d", p->num, p->add);
	}

	/*�L�����̈ړ�*/
	void Move(Chara *p) {

		const int three = width * 3;
		const int four = width * 4;
		const int speed = 2;

		switch (g_GameState) {
			case GAME_BASE:
				if (inp.left) {
					if (p->x <= four / 8 && base.move != 0) base.move += 5 * speed;
					else p->x -= 5 * speed;
					if (p->x+p->c_Hsize_s <= 0) p->x = -p->c_Hsize_s;
				}
				if (inp.right) {
					if (p->x >= four / 8 && base.move != -three + 50)base.move -= 5 *speed;
					else p->x += 5 * speed;
					if (p->x+p->c_Hsize_e - base.move >= four-55)p->x = p->width - p->c_Hsize_e;
				}
				if (inp.up) {
					p->y -= 5 * speed;
					if (p->y <= p->height / 10 * 5)p->y = p->height / 10 * 5;
				}
				if (inp.down) {
					p->y += 5 * speed;
					if (p->y + c_size >= p->height) p->y = p->height - c_size;
				}
				if (base.move >= 0) base.move = 0;
				if (base.move <= -three + 50) base.move = -three + 50;
				break;

			default:
				break;
		}


		if (inp.left)p->num = 3;
		if (inp.right)p->num = 0;
		if (inp.left || inp.right || inp.up || inp.down) Anime(p);
		else { p->count = 0; p->add = 0;}

	}

	/*�L�����̈ړ��A�j���[�V����*/
	void Anime(Chara* p) {
		
		const int fps = 60;
		const int a = 0,b = fps / 4,c = fps / 2,d = fps / 4 * 3;


		switch (count % fps) {
			case a:
				p->add = 1;
				break;

			case b:
			case d:
				p->add = 0;
				break;

			case c:
				p->add = 2;
				break;
		}
		p->count += 1;
	}

	/*�L�����ƃI�u�W�F�N�g�̓����蔻��*/
	int HitCheck(Chara* p,const float x1,const float y1,const float x2,const float y2) {
		const int zero = 0,one = 1;
		const int sx = p->x - base.move + p->c_Hsize_s;
		const int ex = p->x - base.move + p->c_Hsize_e;
		const int point_x = sx + (ex - sx) / 2;
		const int sy = p->y;
		const int ey = p->y + p->c_size;
		const int point_y = sy + (ey - sy) / 4;

		DrawLine(0, point_y, width, point_y, 0x0000ff, 1);
		DrawLine(point_x+base.move, 0, point_x+base.move, height, 0x0000ff, 1);

		if (point_x >= x1 && point_x <= x2 && point_y >= y1 && point_y <= y2) return one;

		return zero;
	}

	int Battle_HitCheck(Chara* p, int x1, int y1, int x2, int y2) {
		const int zero = 0, one = 1;
		const int sx = p->x - base.move + p->c_Hsize_s;
		const int ex = p->x - base.move + p->c_Hsize_e;
		const int sy = p->y;
		const int ey = p->y + p->c_size;

		if ((sx >= x1 && sx <= x2 ||
			ex >= x1 && ex <= x2) &&
			(sy >= y1 && sy <= y2 ||
				ey >= y1 && ey <= y2)) return one;
		else if (sx <= x1 && ex >= x2 && sy <= y1 && ey >= y2) return one;

		return zero;
	}

private:
	int x = 100, y = 400;								//�L�����̍��W
	int c_size = 0;										//�L�����̑傫������ʃT�C�Y�ɍ��킹��ϐ�
	int c_Hsize_s = 0, c_Hsize_e = 0;					//�L�����̓����蔻��̊J�n�ʒu�ƏI���ʒu�����߂���
	int count = 0;										//�A�j���[�V�����J�ڗp�̃J�E���g
	int jk[6] = { 0,0,0,0,0,0 };						//�L�����̉摜
	int num = 0;										//�L�����̉摜��؂�ւ���ϐ�
	int add=0;											//�L�����̉摜�̃A�j���[�V�����ϐ�
	int width=0, height=0;								//��ʂ̃T�C�Y
};