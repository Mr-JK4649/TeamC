#include "DxLib.h"

int Building_Trriger(float w25, float h100, float x1, float y1, float x2, float y2);

#include "character.h"

/*�I�u�W�F�N�g�𒲂ׂ����̃Z���t*/
void Building_Serihu(int width, int height) {
	const float w = (float)width * 4.0 / 100.0;
	const float h = (float)height / 100.0;

	if (Building_Trriger(w, h, 19.0f, 50.0f, 26.8f, 58.5f))str.TexNum = 0;			//���⏊
	else if (Building_Trriger(w, h, 34.2f, 50.0f, 36.6f, 58.5f))str.TexNum = 1;		//�J�W�m�Ŕ�
	else if (Building_Trriger(w, h, 56.6f, 50.0f, 61.6f, 58.5f))str.TexNum = 3;		//�f����
	else if (Building_Trriger(w, h, 77.0f, 50.0f, 79.0f, 58.0f))str.TexNum = 4;		//���X�̃��j���[
	else str.TexNum = 99;
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
		//DrawBox(5, 5, 100, 100, 0xff0000, 1);
		return one;
	}

	return zero;
}