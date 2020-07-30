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
#include "string.h"
#include "Weapons.h"



struct Chara {
	/*�L�����̏������t���O*/
	bool flg = true;

	bool Open_ItemBox = false;		//�{�b�N�X�t���O
	bool Pic_Item = false;			//�{�b�N�X����A�C�e�������t���O
	bool Put_Item = false;			//�{�b�N�X�ɃA�C�e��������t���O
	bool GoTo_Bed = false;			//�x�b�h�A�j���[�V�����t���O

	/*���j���[�p�̈ʒu�ƕ����T�C�Y*/
	float w=0, w5=0;			//���j���[�\���p�̕ϐ�
	float h=0, h4=0;			//��ɓ���
	int size=0;

	int num = 0;					//�L�����̉摜��؂�ւ���ϐ�

	/*���Ԃ̉��Z��*/
	int Add_Time_num = 1;

	/*���j���[�p�̗�*/
	enum Items {
		Wood_Sword=1,	//�؂̌�
		Iron_Sword,		//�S�̌�
		Excalibur,		//�G�N�X�J���o�[
		Wood_Rod,		//�؂̏�
		Iron_Rod,		//�S�̏�
		Wood_Shield,	//�؂̏�
		Stone_Shield,	//�΂̏�
		Iron_Shield,	//�S�̏�
		Portion,		//�񕜃A�C�e��
		Tapi_MT			//�^�s�I�J�~���N�e�B�[
	};

	/*�L�����\���̂̏�����*/
	void Init(Chara* p) {
		LoadDivGraph("images/���W��3.png",12,12,1,200,200,p->jk,0);

		p->c_size = scale.Width / 6;
		p->c_Hsize_s = c_size / 3;
		p->c_Hsize_e = c_size - c_Hsize_s;


		w = scale.Width;				//��ʂ̕����擾
		w5 = scale.Width / 5;			//��ʂ̕���5�Ŋ���
		h = scale.Height;				//��ʂ̍������擾
		h4 = scale.Height / 4;			//��ʂ̍�����4�Ŋ���
		size = scale.Width / 100;		//��ʂ̉����ɍ��킹�������T�C�Y
	}

	/*�L�����摜�̕\���Ɠ����蔻��̕\��*/
	void Disp(Chara *p) {
		DrawExtendGraph(p->x, p->y,p->x + p->c_size, p->y + p->c_size,p->jk[p->num + p->add],1);
		//DrawGraph(p->x, p->y, p->jk[p->num], 1);

		//�����蔻��
		/*DrawBox(p->x+p->c_Hsize_s,p->y,
				p->x+p->c_Hsize_e,p->y+p->c_size,
				0xff0000,0);*/

		/*�������牺�̓f�o�b�O�p*/
		//DrawFormatString(5, 5, 0x000000, "l:%4d r:%4d u:%4d d:%4d", inp.left, inp.right, inp.up, inp.down);
		//DrawFormatString(5, 45, 0x000000, "n:%d a:%d", p->num, p->add);

		if (inp.x) {
			p->Base_Status[1] += 1;
		}

		DrawFormatString(5, 25, 0xffffff, "���ɕK�v�Ȍo���l = %d", (int)p->Next_Level_Exp);
		DrawFormatString(5, 45, 0xffffff, "���݂̌o���l		= %d", p->Chara_Status[1]);
	}

	/*�L�����̈ړ�*/
	void Move(Chara *p) {

		const int three = scale.Width * 3;
		const int four = scale.Width * 4;
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
					if (p->x+p->c_Hsize_e - base.move >= four-55)p->x = scale.Width - p->c_Hsize_e;
				}
				if (inp.up) {
					p->y -= 5 * speed;
					if (p->y <= scale.Height / 10 * 5)p->y = scale.Height / 10 * 5;
				}
				if (inp.down) {
					p->y += 5 * speed;
					if (p->y + c_size >= scale.Height) p->y = scale.Height - c_size;
				}
				if (base.move >= 0) base.move = 0;
				if (base.move <= -three + 50) base.move = -three + 50;
				break;

			default:
				break;
		}


		if (inp.left)p->num = 3;
		if (inp.right)p->num = 0;
		if (inp.down)p->num = 6;
		if (inp.up)p->num = 9;
		if (inp.left || inp.right || inp.up || inp.down) Anime(p);
		else { p->count = 0; p->add = 0;}

		/*�X�e�[�W��̎��ۂ̍��W�X�V*/
		p->sx = p->x - base.move + p->c_Hsize_s;
		p->ex = p->x - base.move + p->c_Hsize_e;
		p->sy = p->y;
		p->ey = p->y + p->c_size;
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
		const int point_x = sx + (ex - sx) / 2;
		const int point_y = sy + (ey - sy) / 4;

		/*DrawLine(0, point_y, scale.Width, point_y, 0x0000ff, 1);
		DrawLine(point_x+base.move, 0, point_x+base.move, scale.Height, 0x0000ff, 1);*/

		if (point_x >= x1 && point_x <= x2 && point_y >= y1 && point_y <= y2) return one;

		return zero;
	}

	//�_���W�������ł̓����蔻��
	int Battle_HitCheck(Chara* p, int x1, int y1, int x2, int y2) {
		const int zero = 0, one = 1;

		if ((sx >= x1 && sx <= x2 ||
			ex >= x1 && ex <= x2) &&
			(sy >= y1 && sy <= y2 ||
				ey >= y1 && ey <= y2)) return one;
		else if (sx <= x1 && ex >= x2 && sy <= y1 && ey >= y2) return one;

		return zero;
	}

	/*�o���l����*/
	void Add_Exp(Chara* p, int exp) {
		p->Chara_Status[1] += exp;

		p->Chara_Level_Up(p);
	}

	/*���_�X�e�[�^�X�ɉ��Z*/
	void Add_Base_Status(Chara* p,int num, int para) {
		p->Base_Status[num] += para;
	}

	/*���x���A�b�v*/
	void Chara_Level_Up(Chara* p) {
		
		for (int i = 0; i < 5; i++) {
			if (p->Chara_Status[1] >= (int)p->Next_Level_Exp) {
				p->Chara_Status[0] += 1;			//���x����1�グ��
				p->Max_Hp += 8;						//�ő�̗�8�ǉ�
				p->Chara_Status[2] = p->Max_Hp;		//�̗͑S��
				p->Chara_Status[3] += 3;			//�U����3�ǉ�
				p->Chara_Status[5] += 1;			//�h���1�ǉ�
				p->Next_Level_Exp += (p->Next_Level_Exp) / 4;

			}
		}
		
	}

	/*���j���[�̃X�e�[�^�X�\��*/
	void Menu_Status_Disp(Chara* p) {
		const int Equipmented_Atk = (float)p->Chara_Status[3] * wep.atk;	//���푕����̃X�e�[�^�X
		p->Chara_Status[4] = Equipmented_Atk - p->Chara_Status[3];			//���������̍U����
		const int Equipmented_Def = (float)p->Chara_Status[5] * shi.def;	//��������̃X�e�[�^�X
		p->Chara_Status[6] = Equipmented_Def - p->Chara_Status[5];			//���������̖h���
		
		SetFontSize(size * 2);

		/*��i*/
		DrawFormatString((w - w5) + 5, 10, 0xffffff, "������\n�@�@�@ %9d�f", p->Base_Status[0]);
		DrawFormatString((w - w5) + 5, 10 + size * 4, 0xffffff, "���W�x\n�@�@�@ %9d��", p->Base_Status[1]);
		DrawFormatString((w - w5) + 5, 10 + size * 8, 0xffffff, "��������\n�@�@�@ %9d�b", p->Base_Status[2]/60);

		/*���i*/
		str.SuperString((w - w5) + w5 / 2, 10 + size * 2 * (0 + 7), "�X�e�[�^�X", 0xffffff, 1, size * 2);
		DrawFormatString((w - w5) + 5, 10 + size * 2 * (1 + 8), 0xffffff, "���x���@ %9d",p->Chara_Status[0] );
		DrawFormatString((w - w5) + 5, 10 + size * 2 * (2 + 8), 0xffffff, "�o���l�@ %9d",p->Chara_Status[1] );
		DrawFormatString((w - w5) + 5, 10 + size * 2 * (3 + 8), 0xffffff, "�́@�� %5d/%5d",p->Chara_Status[2],p->Max_Hp);
		DrawFormatString((w - w5) + 5, 10 + size * 2 * (4 + 8), 0xffffff, "�U����%5d(%5d)",p->Chara_Status[3],Chara_Status[4]);
		DrawFormatString((w - w5) + 5, 10 + size * 2 * (5 + 8), 0xffffff, "�h���%5d(%5d)",p->Chara_Status[5],p->Chara_Status[6]);

		/*���i*/
		str.SuperString((w - w5) + w5 / 2, size * 2 * (7 + 8), "�����i", 0xffffff, 1, size * 2);
		DrawFormatString((w - w5) + 5, 10 + size * 2 * (8 + 8), 0xffffff, "����\n%-13s", wep.Weapon_name);
		DrawFormatString((w - w5) + 5, 10 + size * 2 * (11 + 8), 0xffffff, "��\n%-9s", shi.Shield_name);
		

		SetFontSize(16);


	}

	/*�����A�C�e���\��*/
	int Menu_Items_Disp(Chara* p,int select){
		
		return Chara_Items[select];
	}

	/*���_�̃X�e�[�^�X��Ԃ�*/
	int Return_Base_Status(Chara* p, int num) {
		
		return p->Base_Status[num];
	}

	/*�A�C�e���폜*/
	void Delete_Item(Chara* p,int select) {
		p->Chara_Items[select] = 0;
	}

	/*�A�C�e���i�[*/
	void Input_Item(Chara* p, int select, int item) {
		p->Chara_Items[select] = item;
	}

	/*������������Ă邩�Ԃ����*/
	int Check_Enough_Money(Chara* p,int price) {

		if (p->Base_Status[0] >= price) return one;

		return zero;
	}

	/*�����̂��x����*/
	void Pay_Money(Chara* p,int price) {
		
		p->Base_Status[0] -= price;

	}

	/*�A�C�e�����g��*/
	void Healing_Life(Chara* p,int num) {
		switch (num)
		{
			case Chara::Portion: p->Chara_Status[2] += (p->Max_Hp / 3); break;
			case Chara::Tapi_MT: p->Chara_Status[2] = p->Max_Hp; break;
		}

		if (p->Chara_Status[2] > p->Max_Hp) p->Chara_Status[2] = p->Max_Hp;
	}

	/*�A�C�e���o�b�O�̋󂫉ӏ��𒲂ׂ� �󂫂��������10���Ԃ��Ă���*/
	int Search_ItemBag(Chara* p) {
		int i = 0;
		for (i; i < 10; i++) {
			if (p->Chara_Items[i] == 0) break;
		}

		return i;

	}

	/*�{�b�N�X�̋󂫉ӏ��𒲂ׂ� �󂫂��������30���Ԃ��Ă���*/
	int Search_Box(Chara* p) {
		int i = 0;
		for (i; i < 30; i++) {
			if (p->Box_Item[i] == 0)break;
		}

		return i;
	}

	/*�{�b�N�X�ɃA�C�e���i�[*/
	void Put_Item_Box(Chara* p, int select) {

		p->Box_Item[Search_Box(p)] = p->Chara_Items[select];

		p->Chara_Items[select] = 0;

	}

	/*�{�b�N�X����A�C�e�������o��*/
	void Pic_Item_Box(Chara* p, int select) {

		Input_Item(p, Search_ItemBag(p), p->Box_Item[select]);

		p->Box_Item[select] = 0;
	}

	/*�{�b�N�X�̃A�C�e�����������ׂ�*/
	int Return_Box_Item(Chara* p, int select) {
		return Box_Item[select];
	}

private:
	int x = 100, y = 400;								//�L�����̉�ʏ�̍��W
	int sx = 0, ex = 0, sy = 0, ey = 0;					//�L�����̃t�B�[���h��̍��W
	int c_size = 0;										//�L�����̑傫������ʃT�C�Y�ɍ��킹��ϐ�
	int c_Hsize_s = 0, c_Hsize_e = 0;					//�L�����̓����蔻��̊J�n�ʒu�ƏI���ʒu�����߂���
	int count = 0;										//�A�j���[�V�����J�ڗp�̃J�E���g
	int jk[12] = {0};									//�L�����̉摜
	
	int add=0;											//�L�����̉摜�̃A�j���[�V�����ϐ�
	int Base_Status[3] = { 0,0,0 };						//�L�����̏������A�X�̔��W�x�A�o�ߎ���
	int Chara_Status[7] = { 1,0,20,20,0,10,0 };			//�L�����̃��x���A�o���l�A�̗́A�U���́A����̍U���́A�h��́A���̖h���
	int Max_Hp = 50;									//�L�����̃}�b�N�X�̗�
	float Next_Level_Exp = 50;							//���̃��x���A�b�v�ɕK�v�Ȍo���l
	int Chara_Items[10] = { 0,0,0,0,0,0,0,0,0,0 };		//�L�����̏����i
	int Box_Item[30] = {0};								//�A�C�e���{�b�N�X

	const int zero = 0, one = 1;
};

extern Chara ch;