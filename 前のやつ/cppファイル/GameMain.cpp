/*�K�v�Ȃ�̓ǂݍ���*/
#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>
#include <windows.h>

#include "Input.h"			//�L�[�ƃ}�E�X���͂̂��
#include "State.h"			//�Q�[���̃V�[�����Ǘ�������
#include "LoadSource.h"		//�摜�Ƃ����Ƃ��̐錾�Ɠǂݍ���
#include "Variable.h"		//�ϐ��Ƃ�

float SetAngle(int angle);								//�x���@�Ŋp�x�𓾂�(��肽���p�x�������œn��)
void Flashing(int paturn);								//�d�C�̓_�ł�����֐�(1�A���ʂ̓_�Ł����Â��Ȃ� 2�A3�A����)
void DrawObj(int width,int height,int num);				//�I�u�W�F�N�g��`�悷��֐�
int SuperExtend(int x,int y,int w,int h,int handle);	//Extend�摜�̕\���Ɠ����蔻�肪�ł���֐�(�Ԃ�l�F�����蔻��)
int SuperRote(int x, int y, int w, int h, int handle);	//Extend�摜�̕\���Ɠ����蔻�肪�ł���֐�(�Ԃ�l�F�����蔻��)
void Serihu(char *str,int width,int height);

char s1[][200] = {"��ʓI�Ț₾�B\n��قǂ͖��������͂������E�E�E�E�E�E�E�E�E�E�B",
				  "��ʓI�ȒʋC�����B\n��������Ȃ�o���邩������Ȃ����A�s�v�c�ȗ͂ŊJ���邱�Ƃ��ł��Ȃ��E�E�E�E�E�E�E�B",
				  "�h�A�ɂ͋C�������΂���ɂ��D���\���Ă���B\n��������o�邱�Ƃ͂ł��Ȃ������E�E�E�E�E�E�E�E�E�E�B",
				  "�t�^�����ƁA�����炨���܂������̎׈��ȋC��������B\n����Ȃ�ʋC����}���Ă�͂��΂��邩������Ȃ�",
				  "�ʋC���̃t�^���J�����B\n��������o�邱�Ƃ��ł��������B"};
char buf[200] = "";
char* strts;
int s=0;
int count, life;

bool setTex=false;
int dankai = 0;

struct Escape esc;					//�摜�̍\����
struct EscVar var;					//�ϐ��̍\����
extern Input inp;					//���͂��i��\����
extern int g_GameState;


void DrawGameMain(int width, int height) {

	if (var.LoadFlg) { esc.ImageInput(&esc); var.LoadFlg = false; }

	//�w�i
	DrawExtendGraph(0, 0, width, height, esc.EscapeRoom[var.GraphNum], true);
	

	if (var.isObj) { DrawObj(width, height, var.VecNum); }

	if (!var.isEvent) {

		if (inp.MouseX <= 100) {
			DrawRotaGraph(80, height / 2 - 40, 0.05f, SetAngle(180), esc.Arrow, 1);
			if (inp.MouseFlg & MOUSE_INPUT_LEFT) {
				if (--var.VecNum < 0) var.VecNum = 3;
				if(dankai++ >= 10 && !var.isObj) { var.isEvent = true; var.EveCount = 0; LoadDivGraph("images/�E�o�X�e�[�W�摜.png", 2, 2, 1, 720, 405, esc.EscapeRoom, 0);
				}
			}
		}
		if (inp.MouseX >= width - 100) {
			DrawRotaGraph(width - 80, height / 2 - 40, 0.05f, SetAngle(0), esc.Arrow, 1);
			if (inp.MouseFlg & MOUSE_INPUT_LEFT) {
				if (++var.VecNum > 3) var.VecNum = 0;
				if (dankai++ >= 10 && !var.isObj) { var.isEvent = true; var.EveCount = 0; LoadDivGraph("images/�E�o�X�e�[�W�摜.png", 2, 2, 1, 720, 405, esc.EscapeRoom, 0);
				}
			}
		}

		var.GraphNum = var.VecNum == 0 ? 0 : 1;
	}
	else {

		Flashing(1);

	}


	//�N���A����
	if (var.Lock1 && var.Lock2 && var.Lock3) {
		static bool OpenFlg = false;
		if (SuperExtend(100, 100, 250, 175, esc.Vent) == 2 && !OpenFlg) { OpenFlg = true; setTex = true; strts = s1[4]; }	//�����X�e�[�W�N���A

		else if (OpenFlg) {
			DrawBox(99, 99, 251, 176, 0x000000, 1);

			if(inp.MouseX >= 99 && inp.MouseX <= 251 &&
				inp.MouseY >= 100 && inp.MouseY <= 176 && inp.Lclick) g_GameState = GAME_RESULT;
		}

	}

	/*�h�A�̔���*/
	if (inp.MouseX >= width / 2 - 155 && inp.MouseX <= width / 2 + 95 &&
		inp.MouseY >= height / 2 -160 &&inp.MouseY <= height/2 + 250 && var.VecNum == 0 && var.isObj) {
		if (inp.MouseFlg & MOUSE_INPUT_LEFT) { setTex = true; strts = s1[2]; s = 0; count = 0; }
	}

	//�Â�����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, var.alpha);
	DrawBox(0, 0, width, height, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	//�Z���t���o��
	if (setTex) Serihu(strts, width, height);

	

}

float SetAngle(int angle) {

	const double rad = 3.14159 / 180;

	return rad * angle;

}

void Flashing(int paturn) {
	++var.EveCount;

	switch (paturn) {
	case 1:
		if (var.EveCount <= 5) var.alpha = 156;
		else if (var.EveCount <= 40) var.alpha = 0;
		else if (var.EveCount <= 45) var.alpha = 156;
		else if (var.EveCount <= 55) var.alpha = 0;
		else if (var.EveCount <= 65) var.alpha = 180;
		else if (var.EveCount <= 80) var.alpha = 0;
		else if (var.EveCount <= 110) { var.alpha = 230; var.isObj = true; }
		else if (var.EveCount >= 120) { var.alpha = 128; var.isEvent = false; }
		break;

	case 2:
		break;

	case 3:
		break;
	}

}

void DrawObj(int width, int height, int num) {
	
	switch (num) {
		case 0:
			/*���D*/
			DrawRotaGraph(width / 2 - 100, height / 2 - 40, 1.0f, SetAngle(200), esc.Ohuda, 1);
			DrawRotaGraph(width / 2 - 20, height / 2 + 145, 1.0f, SetAngle(275), esc.Ohuda, 1);
			DrawRotaGraph(width / 2 + 45, height / 2 - 45, 1.0f, SetAngle(30), esc.Ohuda, 1);

			DrawRotaGraph(width / 2 - 30, 300, 1.0f, SetAngle(180), esc.Ohuda, 1);

			DrawRotaGraph(width / 2 + 20, height / 2 - 80, 1.0f, SetAngle(135), esc.Ohuda, 1);
			DrawRotaGraph(width / 2 - 90, height / 2 + 100, 1.0f, SetAngle(45), esc.Ohuda, 1);
			DrawRotaGraph(width / 2 + 60, height / 2 + 160, 1.0f, SetAngle(195), esc.Ohuda, 1);
			break;

		case 1:
			break;

		case 2:
			/**/
			if (SuperExtend(100, 100, 250, 175, esc.Vent) == 2) { setTex = true; strts = s1[1]; }
			if (SuperExtend(width - 400, height - 409, width - 200, height - 100, esc.Vase) == 2) { setTex = true; strts = s1[3]; var.Lock1 = true; }
			break;

		case 3:
			break;
	}

}

int SuperExtend(int x, int y, int w, int h,int handle) {
	DrawExtendGraph(x, y, w, h, handle, true);

	//DrawFormatString(100,400,0x000000,"%d:%d",inp.MouseY,h);

	int aa=0;

	if (inp.MouseX >= x && inp.MouseX <= w && inp.MouseY >= y && inp.MouseY <= h) {
		if (inp.Lclick) { aa = 2; s = 0; count = 0; life = 0; }
		else aa = 1;

		/*g_GameState = GAME_TITLE;*/
	}

	return aa;
}

void Serihu(char* str,int width,int height) {

	SetFontSize(16);
	DrawRoundRect(5, 5, width - 5, 55, 10, 10, 0x444444, 1);
	DrawRoundRect(5, 5, width - 5, 55, 10, 10, 0xaaaaaa, 0);
	DrawRoundRect(6, 6, width - 6, 54, 10, 10, 0xffffff, 0);

	const int speed = 1;

	if (count++ >= speed) { s += 1; count = 0; }
	strncpy_s(buf,str,s);
	DrawFormatString(15,10,0xffffff,"%s",buf);
	/*DrawFormatString(5,250,0x000000,"%d",s);
	DrawFormatString(5,275,0x000000,"%d",life);*/

	if (strcmp(buf, str) >= 0 && inp.Lclick || life++ >= 260) { s = 0; setTex = false; life = 0; }

}