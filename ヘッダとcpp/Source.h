#pragma once
#include "DxLib.h"
#include <stdio.h>


/*タイトルシーンの画像*/
struct Title {
	int image=0;
	int logo=0;
	bool flg = true;

	void ImageInput(struct Title* p) {
		p->image = LoadGraph("images/タイトル案１.jpg");
		p->logo = LoadGraph("images/Tlogo2.png");
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

	int Cards[52] = {0};

	void ImageInput(Casino* p) {
		p->background = LoadGraph("images/Casino.jpg");
		LoadDivGraph("images/トランプカード2.png", 52, 13, 4, 265, 355, p->Cards, 1);
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