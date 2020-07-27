#pragma once
#include "DxLib.h"

struct Weapon {

	float atk = 0.0f;				//攻撃力(倍率)
	int extra_life = 0;				//これが0なるまで耐久度が減らない
	int life = 0;					//耐久度
	const char* file_name;			//ファイルの名前
	char Weapon_name[15] = "";			//武器の名前
	int serial_num = 0;

	int image = 0;					//武器の画像
	bool flg = true;

	/*画像を入れる*/
	void Init(Weapon* p) {
		p->image = LoadGraph(file_name);
	}

	/*武器を使うたびに耐久度を減らす*/
	void Sub_Wep_Life(Weapon* p) {

		//素手じゃなければ耐久値を減らす
		if (p->extra_life != -99) {
			p->extra_life > 0 ? p->extra_life -= 1 : p->life -= 1;
		}
	}

};

extern Weapon Hand;					//素手。何でもできるＪＫの素手。強い(確信)
extern Weapon Wood_Sword;			//木の剣
extern Weapon Iron_Sword;			//鉄の剣
extern Weapon Exca_Sword;			//エクスカリバー
extern Weapon Wood_Rod;				//木のロッド
extern Weapon Iron_Rod;				//鉄のロッド
extern Weapon wep;					//武器構造体あれ
extern Weapon wep_work;

struct Shield {

	float def = 0.0f;				//攻撃力(倍率)
	int extra_life = 0;				//これが0なるまで耐久度が減らない
	int life = 0;					//耐久度
	const char* file_name;			//ファイルの名前
	char Shield_name[15] = "";			//武器の名前
	int serial_num = 0;

	int image = 0;					//武器の画像
	bool flg = true;

	/*画像を入れる*/
	void Init(Weapon* p) {
		p->image = LoadGraph(file_name);
	}

	/*武器を使うたびに耐久度を減らす*/
	void Sub_Wep_Life(Weapon* p) {

		//素手じゃなければ耐久値を減らす
		if (p->extra_life != -99) {
			p->extra_life > 0 ? p->extra_life -= 1 : p->life -= 1;
		}
	}

};

extern Shield Air;				//空気の盾。これで防げると思ったら大間違い。
extern Shield Wood_Shield;		//木の盾
extern Shield Iron_Shield;		//鉄の盾
extern Shield Tapi_Shield;		//タピオカの盾　強い(確信)
extern Shield shi;				//盾構造体のあれ
extern Shield shi_work;			

