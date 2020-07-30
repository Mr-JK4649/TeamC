#pragma once
#include "DxLib.h"
#include <stdio.h>


/*タイトルシーンの画像*/
struct Title {
	int image[2] = { 0 };
	int Arrow = 0;
	bool flg = true;

	void ImageInput(struct Title* p) {
		p->image[0] = LoadGraph("images/タイトル案１上選択矢印.jpg");
		p->image[1] = LoadGraph("images/タイトル案１下選択矢印.jpg");
	}
};

/*ステージシーンの画像*/
struct Stage {
	int background = 0;
	int Button;

	void ImageInput(struct Stage* p) {
		p->background = LoadGraph("images/aaa.png");
		p->Button;
	}

};

/*拠点シーンの画像*/
struct Base {
	int background = 0;
	int shadow = 0;
	bool flg = true;
	int move=0;

	void ImageInput(struct Base* p) {
		p->background = LoadGraph("images/町の風景1.png");
		p->shadow = LoadGraph("images/街の影.png");
	}

};

extern Base base;

struct Casino {
	int background = 0;
	int flg = true;

	int Casino_Table = 0;			//緑のテーブルの画像
	int Dragon_Tiger_img = 0;		//ドラゴンタイガーの説明
	int Casino_War_img = 0;			//カジノウォーの説明

	int Dragon_img = 0;				//ドラゴンタイガーのドラゴン
	int Tiger_img = 0;				//ドラゴンタイガーのトラ

	int Cards[52] = {0};
	int Card_Back = 0;

	void ImageInput(Casino* p) {
		p->background = LoadGraph("images/Casino.jpg");
		LoadDivGraph("images/トランプカード2.png", 52, 13, 4, 265, 355, p->Cards, 1);
		p->Card_Back = LoadGraph("images/カードの裏.png");
		p->Casino_Table = LoadGraph("images/カジノテーブル.jpg");
		p->Dragon_Tiger_img = LoadGraph("images/ドラゴンタイガー.png");
		p->Casino_War_img = LoadGraph("images/カジノウォー.png");
		p->Dragon_img = LoadGraph("images/ドラゴン.png");
		p->Tiger_img = LoadGraph("images/トラ.png");
	}

};

struct Work {
	int background = 0;
	bool flg = true;

	void ImageInput(Work* p) {
		p->background = LoadGraph("images/仕事紹介所.jpg");
	}
};

struct Shop {
	int background[6] = {0,0,0,0,0,0};
	int Weapon_img[5] = { 0 };
	int Shield_img[3] = { 0 };
	int Item_img[2] = { 0 };
	int Cover[5] = { 0 };
	bool flg = true;
	


	void ImageInput(Shop* p) {
		p->background[0] = LoadGraph("images/ShopSele1.jpg");
		p->background[1] = LoadGraph("images/ShopSele2.jpg");
		p->background[2] = LoadGraph("images/ShopSele3.jpg");
		p->background[3] = LoadGraph("images/ShopSele4.jpg");
		p->background[4] = LoadGraph("images/ShopSele5.jpg");
		p->background[5] = LoadGraph("images/shop.jpg");

		p->Weapon_img[0] = LoadGraph("images/木の剣.png");
		p->Weapon_img[1] = LoadGraph("images/鉄の剣.png");
		p->Weapon_img[2] = LoadGraph("images/エクスカリバー.png");
		p->Weapon_img[3] = LoadGraph("images/木の杖.png");
		p->Weapon_img[4] = LoadGraph("images/鉄の杖.png");

		p->Shield_img[0] = LoadGraph("images/木の盾.png");
		p->Shield_img[1] = LoadGraph("images/石の盾.png");
		p->Shield_img[2] = LoadGraph("images/鉄の盾.png");

		p->Cover[0] = LoadGraph("images/shop_cover1.png");
		p->Cover[1] = LoadGraph("images/shop_cover2.png");
		p->Cover[2] = LoadGraph("images/shop_cover3.png");
		p->Cover[3] = LoadGraph("images/shop_cover4.png");
		p->Cover[4] = LoadGraph("images/shop_cover5.png");

		p->Item_img[0] = LoadGraph("images/ポーション.png");
		p->Item_img[1] = LoadGraph("images/ショップ_タピオカＭＴ.png");
	}

};

extern Shop shop;

struct Home {
	int background = 0;
	bool flg = true;


	int home_select = 0;
	int Box_Select = 0;
	int Box_Select2 = 0;
	int Box_Select3 = 0;
	int Box_Select4 = 0;
	int Min_Box_Disp = 0;
	int Max_Box_Disp = 10;
	int Bed_Count = 0;
	int Bed_Alpha = 0;
	int Bed_Alpha_Add = 1;
	char Selct_String[4][17] = {"アイテムボックス","ベッドで休む","畑に行く","家を出る"};
	char Box_Select_String[2][9] = { "収納する","取り出す" };
	unsigned int color = 0xffffff;
	unsigned int white_color = 0xffffff;
	unsigned int blue_color = 0x6666ff;

	void ImageInput(Home* p) {
		p->background = LoadGraph("images/home2.jpg");
	}

};

struct HATAKE {
	int image = 0;
	int testimage[4];
	int tane[3];
	int yasai[3];
	int mizu[3];
	int fremimage = 0;
	int selectfrem = 0;
	bool flg = true;
	void ImageInput(struct HATAKE* p) {
		p->image = LoadGraph("images/hatakeimage.png");
		p->fremimage = LoadGraph("images/frem.png");
		p->selectfrem = LoadGraph("images/selectfrem.png");
		p->testimage[0] = LoadGraph("images/charUP.png");
		p->testimage[1] = LoadGraph("images/charDOWN.png");
		p->testimage[2] = LoadGraph("images/charLEFT.png");
		p->testimage[3] = LoadGraph("images/charRIGHT.png");
		p->tane[0] = LoadGraph("images/komugitane.png");
		p->tane[1] = LoadGraph("images/jagaimotane.png");
		p->tane[2] = LoadGraph("images/ninjintane.png");
		p->yasai[0] = LoadGraph("images/komugi.png");
		p->yasai[1] = LoadGraph("images/jagaimo.png");
		p->yasai[2] = LoadGraph("images/ninjin.png");
		p->mizu[0] = LoadGraph("images/komugimizu.png");
		p->mizu[1] = LoadGraph("images/jagaimomizu.png");
		p->mizu[2] = LoadGraph("images/ninjinmizu.png");
	}
};