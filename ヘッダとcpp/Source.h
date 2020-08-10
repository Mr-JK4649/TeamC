#pragma once
#include "DxLib.h"
#include <stdio.h>

struct SoundE {
	int flg = true;

	int SelectMove_SE = 0;			//メニューでの選択上下音
	int Select_SE = 0;				//メニューでの決定音
	int Cansel_SE = 0;				//メニューでのキャンセル音

	

	void Init(SoundE* p) {
		p->SelectMove_SE = LoadSoundMem("sounds/カーソル移動.mp3");
		p->Select_SE = LoadSoundMem("sounds/メニュー決定.mp3");
		p->Cansel_SE = LoadSoundMem("sounds/メニューキャンセル.mp3");

		
	}
};

extern SoundE se;

/*タイトルシーンの画像*/
struct Title {
	int image[2] = { 0 };
	int Arrow = 0;
	
	int bgm = 0;
	int SelectMove_SE = 0;
	int Select_SE = 0;
	int Start_SE = 0;
	
	//あらすじ用
	int Story_bgm = 0;

	bool flg = true;

	void ImageInput(struct Title* p) {
		p->image[0] = LoadGraph("images/タイトル案１上選択矢印.jpg");
		p->image[1] = LoadGraph("images/タイトル案１下選択矢印.jpg");

		p->bgm = LoadSoundMem("sounds/タイトルBGM2.mp3",3);
		p->SelectMove_SE = LoadSoundMem("sounds/カーソル移動.mp3");
		p->Select_SE = LoadSoundMem("sounds/メニュー決定.mp3");
		p->Start_SE = LoadSoundMem("sounds/ゲームスタート.mp3");

		p->Story_bgm = LoadSoundMem("sounds/あらすじBGM.mp3");
	}
};

extern Title title;

/*ステージシーンの画像*/
struct Stage {
	int background = 0;
	int Button = 0;
	bool flg = true;

	void ImageInput(struct Stage* p) {
		p->background = LoadGraph("images/aaa.png");
		p->Button;
	}

};

extern Stage stage;

/*拠点シーンの画像*/
struct Base {
	int background = 0;
	int background2 = 0;
	int shadow = 0;
	bool flg = true;
	int move=0;

	int bgm = 0;
	int SelectMove_SE = 0;
	int Select_SE = 0;
	int Cansel_SE = 0;

	int Gage_Icon = 0;

	int BC_window_pop = 0;			//建物に入る際の確認ウィンドウをポップアップする音

	int Tips_img[7][5] = { 0 };		//TIPSの画像

	int Tutorial_img[3] = { 0 };	//拠点に入ったときにチュートリアルを出す

	void ImageInput(struct Base* p) {
		p->background = LoadGraph("images/町の風景1.png");
		p->background2 = LoadGraph("images/町の風景2.png");
		p->shadow = LoadGraph("images/街の影.png");
		p->Gage_Icon = LoadGraph("images/ゲージアイコン.png");

		p->bgm = LoadSoundMem("sounds/拠点BGM2.mp3", 3);
		
		p->BC_window_pop = LoadSoundMem("sounds/建物確認.mp3");

		p->Tutorial_img[0] = LoadGraph("images/C操作方法.png");
		p->Tutorial_img[1] = LoadGraph("images/K操作方法.png");
		p->Tutorial_img[2] = LoadGraph("images/TIPS確認.png");

		//操作方法TIPS
		Tips_img[0][0] = LoadGraph("images/C操作方法.png");
		Tips_img[0][1] = LoadGraph("images/K操作方法.png");

		//目的とルール
		Tips_img[1][0] = LoadGraph("images/目的.png");
		Tips_img[1][1] = LoadGraph("images/ルール.png");

		//キャラクターTIPS
		Tips_img[2][0] = LoadGraph("images/ステータス1.png");
		Tips_img[2][1] = LoadGraph("images/ステータス2.png");
		Tips_img[2][2] = LoadGraph("images/装備品.png");
		Tips_img[2][3] = LoadGraph("images/所持品.png");

		//ゲージについて
		Tips_img[6][0] = LoadGraph("images/ゲージについて.png");
		Tips_img[6][1] = LoadGraph("images/各ゲージについて1.png");
		Tips_img[6][2] = LoadGraph("images/各ゲージについて2.png");
		Tips_img[6][3] = LoadGraph("images/各ゲージについて3.png");
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

	int bgm = 0;


	void ImageInput(Casino* p) {
		p->background = LoadGraph("images/Casino.jpg");
		LoadDivGraph("images/トランプカード2.png", 52, 13, 4, 265, 355, p->Cards, 1);
		p->Card_Back = LoadGraph("images/カードの裏.png");
		p->Casino_Table = LoadGraph("images/カジノテーブル.jpg");
		p->Dragon_Tiger_img = LoadGraph("images/ドラゴンタイガー.png");
		p->Casino_War_img = LoadGraph("images/カジノウォー.png");
		p->Dragon_img = LoadGraph("images/ドラゴン.png");
		p->Tiger_img = LoadGraph("images/トラ.png");

		p->bgm = LoadSoundMem("sounds/カジノBGM.mp3");
	}

};

extern Casino casino;

struct Work {
	int background = 0;
	bool flg = true;

	void ImageInput(Work* p) {
		p->background = LoadGraph("images/仕事紹介所.jpg");
	}
};

extern Work work;

struct Shop {
	int background[6] = {0,0,0,0,0,0};		//武器屋背景
	int Weapon_img[5] = { 0 };				//武器の画像
	int Shield_img[3] = { 0 };				//盾の画像
	int Item_img[2] = { 0 };				//アイテムの画像
	int Cover[5] = { 0 };					//買えない商品のカバー
	bool flg = true;
	
	int bgm = 0;							//ＢＧＭ
	int Pay_SE = 0;							//支払い時の効果音

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

		p->Pay_SE = LoadSoundMem("sounds/お店の支払い.mp3");
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

	int bgm = 0;
	int Bed_bgm = 0;

	void ImageInput(Home* p) {
		p->background = LoadGraph("images/home2.jpg");

		p->bgm = LoadSoundMem("sounds/自宅BGM2.mp3");
		p->Bed_bgm = LoadSoundMem("sounds/自宅ベッドBGM.mp3");
	}

};

extern Home home;

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
		p->testimage[0] = LoadGraph("images/JK2_4.png");
		p->testimage[1] = LoadGraph("images/JK2_1.png");
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

extern HATAKE hatake;

// ダンジョンシーン画像
struct Dungeon {
	int Map[12][34] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	int background = 0;		//洞窟背景
	int stage = 0;		//ダンジョン(ステージ)
	bool flg = true;	//ボタン
	int move = 0;
	int up = -684;
	int jump = 0;

	void ImageInput(struct Dungeon* p) {
		p->background = LoadGraph("images/ダンジョン背景.png");
		p->stage = LoadGraph("images/簡単ステージ.png");
	}
};