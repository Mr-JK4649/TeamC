#pragma once
#include "DxLib.h"

struct Weapon {

	float atk = 0.0f;				//�U����(�{��)
	int extra_life = 0;				//���ꂪ0�Ȃ�܂őϋv�x������Ȃ�
	int life = 0;					//�ϋv�x
	const char* file_name;			//�t�@�C���̖��O
	char Weapon_name[15] = "";			//����̖��O
	int serial_num = 0;

	int image = 0;					//����̉摜
	bool flg = true;

	/*�摜������*/
	void Init(Weapon* p) {
		p->image = LoadGraph(file_name);
	}

	/*������g�����тɑϋv�x�����炷*/
	void Sub_Wep_Life(Weapon* p) {

		//�f�肶��Ȃ���Αϋv�l�����炷
		if (p->extra_life != -99) {
			p->extra_life > 0 ? p->extra_life -= 1 : p->life -= 1;
		}
	}

};

extern Weapon Hand;					//�f��B���ł��ł���i�j�̑f��B����(�m�M)
extern Weapon Wood_Sword;			//�؂̌�
extern Weapon Iron_Sword;			//�S�̌�
extern Weapon Exca_Sword;			//�G�N�X�J���o�[
extern Weapon Wood_Rod;				//�؂̃��b�h
extern Weapon Iron_Rod;				//�S�̃��b�h
extern Weapon wep;					//����\���̂���
extern Weapon wep_work;

struct Shield {

	float def = 0.0f;				//�U����(�{��)
	int extra_life = 0;				//���ꂪ0�Ȃ�܂őϋv�x������Ȃ�
	int life = 0;					//�ϋv�x
	const char* file_name;			//�t�@�C���̖��O
	char Shield_name[15] = "";			//����̖��O
	int serial_num = 0;

	int image = 0;					//����̉摜
	bool flg = true;

	/*�摜������*/
	void Init(Weapon* p) {
		p->image = LoadGraph(file_name);
	}

	/*������g�����тɑϋv�x�����炷*/
	void Sub_Wep_Life(Weapon* p) {

		//�f�肶��Ȃ���Αϋv�l�����炷
		if (p->extra_life != -99) {
			p->extra_life > 0 ? p->extra_life -= 1 : p->life -= 1;
		}
	}

};

extern Shield Air;				//��C�̏��B����Ŗh����Ǝv�������ԈႢ�B
extern Shield Wood_Shield;		//�؂̏�
extern Shield Iron_Shield;		//�S�̏�
extern Shield Tapi_Shield;		//�^�s�I�J�̏��@����(�m�M)
extern Shield shi;				//���\���̂̂���
extern Shield shi_work;			

