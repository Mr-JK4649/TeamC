#include "DxLib.h"

int Building_Trriger(float w25, float h100, float x1, float y1, float x2, float y2);

#include "character.h"

/*オブジェクトを調べた時のセリフ*/
void Building_Serihu(int width, int height) {
	const float w = (float)width * 4.0 / 100.0;
	const float h = (float)height / 100.0;

	if (Building_Trriger(w, h, 19.0f, 50.0f, 26.8f, 58.5f))str.TexNum = 0;			//検問所
	else if (Building_Trriger(w, h, 34.2f, 50.0f, 36.6f, 58.5f))str.TexNum = 1;		//カジノ看板
	else if (Building_Trriger(w, h, 56.6f, 50.0f, 61.6f, 58.5f))str.TexNum = 3;		//掲示板
	else if (Building_Trriger(w, h, 77.0f, 50.0f, 79.0f, 58.0f))str.TexNum = 4;		//お店のメニュー
	else str.TexNum = 99;
}

/*************************************************
				建物の判定
int型	w25		画面の全長を25分割した値
int型	h100	画面の高さを100分割した値
int型	x1,x2	x座標の始点と終点
int型	y1,y2	y座標の視点と終点
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