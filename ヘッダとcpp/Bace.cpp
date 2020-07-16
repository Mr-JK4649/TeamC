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

char Player_Serihu[5][180] = { "ここは検問所ね。\n街を出入りする際に怪しい動きをしたら逮捕されちゃうかも。\n、、、、、、、、、、、なんてね。",		//検問所で出るセリフ
							   "カジノ建設予定地と書いてあるわ。\n出来たら一回くらい来てみてもいいかもしれないわね。",						//カジノ(未建設)で出るセリフ
							   "a",																											//カジノ(建設済み)で出るセリフ
							   "これは仕事紹介所の掲示板ね。\n色んな仕事の依頼が貼ってあるわ。",											//仕事紹介所の掲示板で出るセリフ
							   "お店で取り扱ってる商品の値段が書いてあるわ。\n斧が250ゴールド、盾が300ゴールド、回復薬が5ゴールド。\n安いのか高いのか分からないわね・・・・・。" };																										//店で出るセリフ

void DrawGameMain(int width, int height) {
	
	/*初期化*/
	if (base.flg) { base.ImageInput(&base); base.flg = false; }
	if (ch.flg) { ch.Init(&ch,width,height); ch.flg = false; }

	/*拠点の描画関数*/
	Base_Disp(width, height);
	
	
	/*拠点の更新関数*/
	if (!base_menu.isMenu)Base_Update(width, height);
	else base_menu.Draw();

	if (!str.setTex && inp.start) base_menu.isMenu = !base_menu.isMenu;

	DrawFormatString(5, 205, 0x000000, "%d", inp.a);

}

/*拠点の表示*/
void Base_Disp(int width, int height) {
	/*背景表示*/
	DrawExtendGraph(base.move, 0, width * 4 + base.move, height, base.background, 1);

	/*キャラクターの描画と更新*/
	ch.Disp(&ch);

	/*街の影表示*/
	DrawExtendGraph(base.move, 0, width * 4 + base.move, height, base.shadow, 1);
}

/*拠点のシステム*/
void Base_Update(int width, int height) {
	/*プレイヤーの移動*/
	if (!str.setTex)ch.Move(&ch);

	/*建物の判定*/
	Building_Serihu(width, height);

	/*オブジェクトの範囲に入ってスペースを押したときの*/
	if (TexNum != 99 && inp.space == true) {
		if (str.setTex) str.Serihu_Skip_Fin();
		else str.setTex = true;
	}

	/*セリフを出す*/
	if (str.setTex) str.Serihu(Player_Serihu[TexNum], 15, height - (height / 4 - 10), 0xffffff, width / 40);

}

/*オブジェクトを調べた時のセリフ*/
void Building_Serihu(int width,int height) {
	const float w = (float)width * 4.0 / 100.0;
	const float h = (float)height / 100.0;

	if (Building_Trriger(w, h, 19.0f, 50.0f, 26.8f, 58.5f))TexNum = 0;			//検問所
	else if (Building_Trriger(w, h, 34.2f, 50.0f, 36.6f, 58.5f))TexNum = 1;		//カジノ看板
	else if (Building_Trriger(w, h, 56.6f, 50.0f, 61.6f, 58.5f))TexNum = 3;		//掲示板
	else if (Building_Trriger(w, h, 77.0f, 50.0f, 79.0f, 58.0f))TexNum = 4;		//お店のメニュー
	else TexNum = 99;
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
		DrawBox(5, 5, 100, 100, 0xff0000, 1);
		return one;
	}

	return zero;
}