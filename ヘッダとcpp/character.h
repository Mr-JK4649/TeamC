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
	/*キャラの初期化フラグ*/
	bool flg = true;

	/*メニュー用の位置と文字サイズ*/
	float w=0, w5=0;			//メニュー表示用の変数
	float h=0, h4=0;			//上に同じ
	int size=0;

	/*メニュー用の列挙*/
	enum Items {
		Wood_Sword=1,	//木の剣
		Iron_Sword,		//鉄の剣
		Excalibur,		//エクスカリバー
		Wood_Rod,		//木のロッド
		Iron_Rod,		//鉄のロッド
		Wood_Shield,	//木の盾
		Iron_Shield,	//鉄の盾
		Tapi_Shield		//タピオカの盾
	};

	/*キャラ構造体の初期化*/
	void Init(Chara* p) {
		LoadDivGraph("images/総集編2.png",9,9,1,200,200,p->jk,0);

		p->c_size = scale.Width / 6;
		p->c_Hsize_s = c_size / 3;
		p->c_Hsize_e = c_size - c_Hsize_s;


		w = scale.Width;				//画面の幅を取得
		w5 = scale.Width / 5;			//画面の幅を5で割る
		h = scale.Height;				//画面の高さを取得
		h4 = scale.Height / 4;			//画面の高さを4で割る
		size = scale.Width / 100;		//画面の横幅に合わせた文字サイズ
	}

	/*キャラ画像の表示と当たり判定の表示*/
	void Disp(Chara *p) {
		DrawExtendGraph(p->x, p->y,p->x + p->c_size, p->y + p->c_size,p->jk[p->num + p->add],1);
		//DrawGraph(p->x, p->y, p->jk[p->num], 1);

		//当たり判定
		/*DrawBox(p->x+p->c_Hsize_s,p->y,
				p->x+p->c_Hsize_e,p->y+p->c_size,
				0xff0000,0);*/

		/*ここから下はデバッグ用*/
		//DrawFormatString(5, 5, 0x000000, "l:%4d r:%4d u:%4d d:%4d", inp.left, inp.right, inp.up, inp.down);
		//DrawFormatString(5, 45, 0x000000, "n:%d a:%d", p->num, p->add);
	}

	/*キャラの移動*/
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
		if (inp.left || inp.right || inp.up || inp.down) Anime(p);
		else { p->count = 0; p->add = 0;}

		/*ステージ上の実際の座標更新*/
		p->sx = p->x - base.move + p->c_Hsize_s;
		p->ex = p->x - base.move + p->c_Hsize_e;
		p->sy = p->y;
		p->ey = p->y + p->c_size;
	}

	/*キャラの移動アニメーション*/
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

	/*キャラとオブジェクトの当たり判定*/
	int HitCheck(Chara* p,const float x1,const float y1,const float x2,const float y2) {
		const int zero = 0,one = 1;
		const int point_x = sx + (ex - sx) / 2;
		const int point_y = sy + (ey - sy) / 4;

		/*DrawLine(0, point_y, scale.Width, point_y, 0x0000ff, 1);
		DrawLine(point_x+base.move, 0, point_x+base.move, scale.Height, 0x0000ff, 1);*/

		if (point_x >= x1 && point_x <= x2 && point_y >= y1 && point_y <= y2) return one;

		return zero;
	}

	//ダンジョン内での当たり判定
	int Battle_HitCheck(Chara* p, int x1, int y1, int x2, int y2) {
		const int zero = 0, one = 1;

		if ((sx >= x1 && sx <= x2 ||
			ex >= x1 && ex <= x2) &&
			(sy >= y1 && sy <= y2 ||
				ey >= y1 && ey <= y2)) return one;
		else if (sx <= x1 && ex >= x2 && sy <= y1 && ey >= y2) return one;

		return zero;
	}

	//キャラの経過時間
	void Add_Time(Chara* p) {
		p->Base_Status[2] += 1;
	}

	/*メニューのステータス表示*/
	void Menu_Status_Disp(Chara* p) {
		const int Equipmented_Atk = (float)p->Chara_Status[3] * wep.atk;	//武器装備後のステータス
		p->Chara_Status[4] = Equipmented_Atk - p->Chara_Status[3];			//増えた分の攻撃力
		const int Equipmented_Def = (float)p->Chara_Status[5] * shi.def;	//盾装備後のステータス
		p->Chara_Status[6] = Equipmented_Def - p->Chara_Status[5];			//増えた分の防御力
		
		SetFontSize(size * 2);

		/*上段*/
		DrawFormatString((w - w5) + 5, 10, 0xffffff, "所持金\n　　　 %9dＧ", p->Base_Status[0]);
		DrawFormatString((w - w5) + 5, 10 + size * 4, 0xffffff, "発展度\n　　　 %9d％", p->Base_Status[1]);
		DrawFormatString((w - w5) + 5, 10 + size * 8, 0xffffff, "生存時間\n　　　 %9d秒", p->Base_Status[2]/60);

		/*中段*/
		str.SuperString((w - w5) + w5 / 2, 10 + size * 2 * (0 + 7), "ステータス", 0xffffff, 1, size * 2);
		DrawFormatString((w - w5) + 5, 10 + size * 2 * (1 + 8), 0xffffff, "レベル　 %9d",p->Chara_Status[0] );
		DrawFormatString((w - w5) + 5, 10 + size * 2 * (2 + 8), 0xffffff, "経験値　 %9d",p->Chara_Status[1] );
		DrawFormatString((w - w5) + 5, 10 + size * 2 * (3 + 8), 0xffffff, "体　力　 %9d",p->Chara_Status[2] );
		DrawFormatString((w - w5) + 5, 10 + size * 2 * (4 + 8), 0xffffff, "攻撃力%5d(%5d)",p->Chara_Status[3],Chara_Status[4]);
		DrawFormatString((w - w5) + 5, 10 + size * 2 * (5 + 8), 0xffffff, "防御力%5d(%5d)",p->Chara_Status[5],p->Chara_Status[6]);

		/*下段*/
		str.SuperString((w - w5) + w5 / 2, size * 2 * (7 + 8), "装備品", 0xffffff, 1, size * 2);
		DrawFormatString((w - w5) + 5, 10 + size * 2 * (8 + 8), 0xffffff, "武器\n%-13s", wep.Weapon_name);
		DrawFormatString((w - w5) + 5, 10 + size * 2 * (11 + 8), 0xffffff, "盾\n%-9s", shi.Shield_name);
		

		SetFontSize(16);
	}

	/*所持アイテム表示*/
	int Menu_Items_Disp(Chara* p,int select){
		
		return Chara_Items[select];
	}

	/*拠点のステータスを返す*/
	int Return_Base_Status(Chara* p, int num) {
		
		return p->Base_Status[num];
	}

	/*アイテム削除*/
	void Delete_Item(Chara* p,int select) {
		p->Chara_Items[select] = 0;
	}

	/*アイテム格納*/
	void Input_Item(Chara* p, int select, int item) {
		p->Chara_Items[select] = item;
	}

	/*所持金が足りてるか返すやつ*/
	int Check_Enough_Money(Chara* p,int price) {

		if (p->Base_Status[0] >= price) return one;

		return zero;
	}

	/*料金のお支払い*/
	void Pay_Money(Chara* p,int price) {
		
		p->Base_Status[0] -= price;

	}


private:
	int x = 100, y = 400;								//キャラの画面上の座標
	int sx = 0, ex = 0, sy = 0, ey = 0;					//キャラのフィールド上の座標
	int c_size = 0;										//キャラの大きさを画面サイズに合わせる変数
	int c_Hsize_s = 0, c_Hsize_e = 0;					//キャラの当たり判定の開始位置と終了位置を決める辺陬
	int count = 0;										//アニメーション遷移用のカウント
	int jk[9] = { 0,0,0,0,0,0,0,0,0};					//キャラの画像
	int num = 0;										//キャラの画像を切り替える変数
	int add=0;											//キャラの画像のアニメーション変数
	int Base_Status[3] = { 999,0,0 };					//キャラの所持金、街の発展度、経過時間
	int Chara_Status[7] = { 1,0,20,200,0,100,0 };		//キャラのレベル、経験値、体力、攻撃力、武器の攻撃力、防御力、盾の防御力
	int Chara_Items[10] = { 0,0,0,0,0,0,0,0,0,0 };		//キャラの所持品

	const int zero = 0, one = 1;
};

extern Chara ch;