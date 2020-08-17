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
	int testimage[12];
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
		//下向き image_DOWN
		p->testimage[0] = LoadGraph("images/JK2_1.png");
		p->testimage[1] = LoadGraph("images/JK2_2.png");
		p->testimage[2] = LoadGraph("images/JK2_3.png");
		//上向き image_UP
		p->testimage[3] = LoadGraph("images/JK2_4.png");
		p->testimage[4] = LoadGraph("images/JK2_5.png");
		p->testimage[5] = LoadGraph("images/JK2_6.png");
		//右向き image_RIGHT
		p->testimage[6] = LoadGraph("images/JK2_7.png");
		p->testimage[7] = LoadGraph("images/JK2_8.png");
		p->testimage[8] = LoadGraph("images/JK2_9.png");
		//左向き image_LEFT
		p->testimage[9] = LoadGraph("images/JK2_10.png");
		p->testimage[10] = LoadGraph("images/JK2_11.png");
		p->testimage[11] = LoadGraph("images/JK2_12.png");

		p->tane[0] = LoadGraph("images/KomugiTane.png");
		p->tane[1] = LoadGraph("images/JagaimoTane.png");
		p->tane[2] = LoadGraph("images/NinjinTane.png");
		p->yasai[0] = LoadGraph("images/komugi.png");
		p->yasai[1] = LoadGraph("images/jagaimo.png");
		p->yasai[2] = LoadGraph("images/ninjin.png");
		p->mizu[0] = LoadGraph("images/KomugiMizu.png");
		p->mizu[1] = LoadGraph("images/JagaimoMizu.png");
		p->mizu[2] = LoadGraph("images/NinjinMizu.png");
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
	float TIP_WIDTH = 0;
	float TIP_HEIGHT = 0;

	int background = 0;		//洞窟背景
	int stage = 0;		//ダンジョン(ステージ)
	bool flg = true;	//ボタン
	int move = 0;
	int up = -684;
	int jump = 0;

	int Effect_Anim_Num[5] = { 10,9,15,7,18 };	//エフェクトの画像数
	int Effect_Speed[5] = { 20,5,5,10,10 };	//エフェクトの表示速度
	int Hit_Effect[10] = { 0 };		//攻撃ヒットのエフェクト
	int Sword_Effect1[9] = { 0 };	//剣の攻撃エフェクト1
	int Sword_Effect2[15] = { 0 };	//剣の攻撃エフェクト2
	int Magic_Effect1[7] = { 0 };	//魔法のエフェクト1
	int Magic_Effect2[18] = { 0 };	//魔法のエフェクト
	
	enum Enemy_Action
	{
		Idle,
		Move,
		Attack
	};

	/*待機に使う画像数*/
	int Enemy_Idle_Lim[12] = { 3,4,3,3,4,4,4,4,3,4,4,4 };

	/*移動に使う画像数*/
	int Enemy_Move_Lim[12] = { 4,4,6,6,4,6,6,4,6,4,4,6 };

	/*攻撃に使う画像数*/
	int Enemy_Attack_Lim[12] = { 5,4,5,4,4,4,4,4,4,4,4,5 };

	/*戦闘開始時の敵の位置を初期化する変数*/
	int Battle_Enemy_Pos[12][2] =
	{
		{ -99,422 },		//スライム
		{ -99,400 },		//妖精
		{ -99,320 },		//ゾンビ
		{ 4600,320 },		//コボルト　ボス
		{ -99,320 },		//鳥
		{ -99,320 },		//兵士
		{ -99,320 },		//魔法使い
		{ 4600,320},		//どくろ　　ボス
		{ -99,310 },		//黒コボルト
		{ -99,320 },		//黒どくろ
		{ -99,380 },		//黒妖精
		{ 4600,320 }		//ドラゴン　ボス
	};

	/*敵のサイズ*/
	int Enemy_Size[12][2] =
	{
		{200,200},
		{200,200},
		{300,300},
		{300,300},//
		{150,150},
		{300,300},
		{300,300},
		{300,300},//
		{320,320},
		{320,320},
		{200,200},
		{650,450} //
	};

	/*敵のステータスと経験値(HP、攻撃力、移動速度、経験値)*/
	int Enemy_Status[12][4] =
	{
		{100,1,1,100},		//スライム
		{150,1,2,150},		//妖精
		{200,2,1,200},		//ゾンビ
		{500,3,2,1000},		//コボルト　ボス
		{300,2,3,200},		//鳥
		{500,2,1,500},		//兵士
		{400,2,2,400},		//魔法使い
		{1000,4,2,2000},	//どくろ　　ボス
		{600,4,3,1200},		//黒コボルト
		{1200,5,3,2400},	//黒どくろ
		{400,3,3,800},		//黒妖精
		{5000,6,2,10000}	//ドラゴン　ボス
	};

	/*攻撃のやつ(攻撃範囲、攻撃の種類)*/
	int Enemy_Attacks[12][3] =
	{
		{100,200,0},		//スライム
		{100,200,0},		//妖精
		{100,200,0},		//ゾンビ
		{100,200,0},		//コボルト　ボス
		{100,200,0},		//鳥
		{100,200,0},		//兵士
		{100,200,0},		//魔法使い
		{100,200,0},		//どくろ　　ボス
		{100,200,0},		//黒コボルト
		{100,200,0},		//黒どくろ
		{100,200,0},		//黒妖精
		{100,200,0}			//ドラゴン　ボス
	};

	
	int Cobolt_x = 4600, Cobolt_y = -50;
	int Cobolt_size = 300;
	int Cobolt_Width = 300;
	int Cobolt_Height = 300;
	int Cobolt_Hp = 400;
	int Cobolt_Atk = 4;
	int Cobolt_Exp = 25;
	int CoboltA_Idle[3] = {0};
	int CoboltA_Move[6] = {0};
	int CoboltA_Attack[4] = {0};


	int Enemy_Idle[12][4] = { 0 };
	int Enemy_Move[12][6] = { 0 };
	int Enemy_Attack[12][5] = { 0 };

	

	void ImageInput(struct Dungeon* p) {
		p->background = LoadGraph("images/ダンジョン背景.png");
		p->stage = LoadGraph("images/簡単ステージ.png");

		/*エフェクト*/
		LoadDivGraph("images/Effects/hit_effect.png", 10, 1, 10, 640, 480, p->Hit_Effect, 1);
		LoadDivGraph("images/Effects/sword_effect1.png", 9, 9, 1, 240, 240, p->Sword_Effect1, 1);
		LoadDivGraph("images/Effects/sword_effect2.png", 15, 5, 3, 480, 480, p->Sword_Effect2, 1);
		LoadDivGraph("images/Effects/magic_effect1.png", 7, 7, 1, 240, 240, p->Magic_Effect1, 1);
		LoadDivGraph("images/Effects/magic_effect2.png", 18, 3, 6, 640, 300, p->Magic_Effect2, 1);

		/*スライム*/
		if (true) {
			p->Enemy_Idle[0][0] = LoadGraph("images/ゲーム用モンスター素材/スライム/スライムA_待機000.png");
			p->Enemy_Idle[0][1] = LoadGraph("images/ゲーム用モンスター素材/スライム/スライムA_待機001.png");
			p->Enemy_Idle[0][2] = LoadGraph("images/ゲーム用モンスター素材/スライム/スライムA_待機002.png");

			p->Enemy_Move[0][0] = LoadGraph("images/ゲーム用モンスター素材/スライム/スライムA_移動000.png");
			p->Enemy_Move[0][1] = LoadGraph("images/ゲーム用モンスター素材/スライム/スライムA_移動001.png");
			p->Enemy_Move[0][2] = LoadGraph("images/ゲーム用モンスター素材/スライム/スライムA_移動002.png");
			p->Enemy_Move[0][3] = LoadGraph("images/ゲーム用モンスター素材/スライム/スライムA_移動003.png");

			p->Enemy_Attack[0][0] = LoadGraph("images/ゲーム用モンスター素材/スライム/スライムA_攻撃000.png");
			p->Enemy_Attack[0][1] = LoadGraph("images/ゲーム用モンスター素材/スライム/スライムA_攻撃001.png");
			p->Enemy_Attack[0][2] = LoadGraph("images/ゲーム用モンスター素材/スライム/スライムA_攻撃002.png");
			p->Enemy_Attack[0][3] = LoadGraph("images/ゲーム用モンスター素材/スライム/スライムA_攻撃003.png");
			p->Enemy_Attack[0][4] = LoadGraph("images/ゲーム用モンスター素材/スライム/スライムA_攻撃004.png");
		}

		/*妖精*/
		if (true) {
			p->Enemy_Idle[1][0] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精A_待機000.png");
			p->Enemy_Idle[1][1] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精A_待機001.png");
			p->Enemy_Idle[1][2] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精A_待機002.png");
			p->Enemy_Idle[1][3] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精A_待機003.png");

			p->Enemy_Move[1][0] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精A_移動000.png");
			p->Enemy_Move[1][1] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精A_移動001.png");
			p->Enemy_Move[1][2] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精A_移動002.png");
			p->Enemy_Move[1][3] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精A_移動003.png");

			p->Enemy_Attack[1][0] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精A_攻撃000.png");
			p->Enemy_Attack[1][1] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精A_攻撃001.png");
			p->Enemy_Attack[1][2] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精A_攻撃002.png");
			p->Enemy_Attack[1][3] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精A_攻撃003.png");
		}

		/*ゾンビ*/
		if (true) {
			p->Enemy_Idle[2][0] = LoadGraph("images/ゲーム用モンスター素材/ゾンビ/ゾンビA_待機000.png");
			p->Enemy_Idle[2][1] = LoadGraph("images/ゲーム用モンスター素材/ゾンビ/ゾンビA_待機001.png");
			p->Enemy_Idle[2][2] = LoadGraph("images/ゲーム用モンスター素材/ゾンビ/ゾンビA_待機002.png");

			p->Enemy_Move[2][0] = LoadGraph("images/ゲーム用モンスター素材/ゾンビ/ゾンビA_移動000.png");
			p->Enemy_Move[2][1] = LoadGraph("images/ゲーム用モンスター素材/ゾンビ/ゾンビA_移動001.png");
			p->Enemy_Move[2][2] = LoadGraph("images/ゲーム用モンスター素材/ゾンビ/ゾンビA_移動002.png");
			p->Enemy_Move[2][3] = LoadGraph("images/ゲーム用モンスター素材/ゾンビ/ゾンビA_移動003.png");
			p->Enemy_Move[2][4] = LoadGraph("images/ゲーム用モンスター素材/ゾンビ/ゾンビA_移動004.png");
			p->Enemy_Move[2][5] = LoadGraph("images/ゲーム用モンスター素材/ゾンビ/ゾンビA_移動005.png");

			p->Enemy_Attack[2][0] = LoadGraph("images/ゲーム用モンスター素材/ゾンビ/ゾンビA_攻撃000.png");
			p->Enemy_Attack[2][1] = LoadGraph("images/ゲーム用モンスター素材/ゾンビ/ゾンビA_攻撃001.png");
			p->Enemy_Attack[2][2] = LoadGraph("images/ゲーム用モンスター素材/ゾンビ/ゾンビA_攻撃002.png");
			p->Enemy_Attack[2][3] = LoadGraph("images/ゲーム用モンスター素材/ゾンビ/ゾンビA_攻撃003.png");
			p->Enemy_Attack[2][4] = LoadGraph("images/ゲーム用モンスター素材/ゾンビ/ゾンビA_攻撃004.png");
		}

		/*コボルト*/
		if (true) {
			p->Enemy_Idle[3][0] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトA_待機000.png");
			p->Enemy_Idle[3][1] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトA_待機001.png");
			p->Enemy_Idle[3][2] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトA_待機002.png");

			p->Enemy_Move[3][0] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトA_移動000.png");
			p->Enemy_Move[3][1] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトA_移動001.png");
			p->Enemy_Move[3][2] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトA_移動002.png");
			p->Enemy_Move[3][3] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトA_移動003.png");
			p->Enemy_Move[3][4] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトA_移動004.png");
			p->Enemy_Move[3][5] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトA_移動005.png");

			p->Enemy_Attack[3][0] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトA_攻撃000.png");
			p->Enemy_Attack[3][1] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトA_攻撃001.png");
			p->Enemy_Attack[3][2] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトA_攻撃002.png");
			p->Enemy_Attack[3][3] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトA_攻撃003.png");
			p->Enemy_Attack[3][4] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトA_攻撃004.png");
		}

		/*鳥*/
		if (true) {
			p->Enemy_Idle[4][0] = LoadGraph("images/ゲーム用モンスター素材/鳥/鳥A_待機000.png");
			p->Enemy_Idle[4][1] = LoadGraph("images/ゲーム用モンスター素材/鳥/鳥A_待機001.png");
			p->Enemy_Idle[4][2] = LoadGraph("images/ゲーム用モンスター素材/鳥/鳥A_待機002.png");
			p->Enemy_Idle[4][3] = LoadGraph("images/ゲーム用モンスター素材/鳥/鳥A_待機003.png");

			p->Enemy_Move[4][0] = LoadGraph("images/ゲーム用モンスター素材/鳥/鳥A_移動000.png");
			p->Enemy_Move[4][1] = LoadGraph("images/ゲーム用モンスター素材/鳥/鳥A_移動001.png");
			p->Enemy_Move[4][2] = LoadGraph("images/ゲーム用モンスター素材/鳥/鳥A_移動002.png");
			p->Enemy_Move[4][3] = LoadGraph("images/ゲーム用モンスター素材/鳥/鳥A_移動003.png");

			p->Enemy_Attack[4][0] = LoadGraph("images/ゲーム用モンスター素材/鳥/鳥A_攻撃000.png");
			p->Enemy_Attack[4][1] = LoadGraph("images/ゲーム用モンスター素材/鳥/鳥A_攻撃001.png");
			p->Enemy_Attack[4][2] = LoadGraph("images/ゲーム用モンスター素材/鳥/鳥A_攻撃002.png");
			p->Enemy_Attack[4][3] = LoadGraph("images/ゲーム用モンスター素材/鳥/鳥A_攻撃003.png");
		}

		/*兵士*/
		if (true) {
			p->Enemy_Idle[5][0] = LoadGraph("images/ゲーム用モンスター素材/兵士/兵士A_待機000.png");
			p->Enemy_Idle[5][1] = LoadGraph("images/ゲーム用モンスター素材/兵士/兵士A_待機001.png");
			p->Enemy_Idle[5][2] = LoadGraph("images/ゲーム用モンスター素材/兵士/兵士A_待機002.png");
			p->Enemy_Idle[5][3] = LoadGraph("images/ゲーム用モンスター素材/兵士/兵士A_待機003.png");

			p->Enemy_Move[5][0] = LoadGraph("images/ゲーム用モンスター素材/兵士/兵士A_移動000.png");
			p->Enemy_Move[5][1] = LoadGraph("images/ゲーム用モンスター素材/兵士/兵士A_移動001.png");
			p->Enemy_Move[5][2] = LoadGraph("images/ゲーム用モンスター素材/兵士/兵士A_移動002.png");
			p->Enemy_Move[5][3] = LoadGraph("images/ゲーム用モンスター素材/兵士/兵士A_移動003.png");
			p->Enemy_Move[5][4] = LoadGraph("images/ゲーム用モンスター素材/兵士/兵士A_移動004.png");
			p->Enemy_Move[5][5] = LoadGraph("images/ゲーム用モンスター素材/兵士/兵士A_移動005.png");

			p->Enemy_Attack[5][0] = LoadGraph("images/ゲーム用モンスター素材/兵士/兵士A_攻撃000.png");
			p->Enemy_Attack[5][1] = LoadGraph("images/ゲーム用モンスター素材/兵士/兵士A_攻撃001.png");
			p->Enemy_Attack[5][2] = LoadGraph("images/ゲーム用モンスター素材/兵士/兵士A_攻撃002.png");
			p->Enemy_Attack[5][3] = LoadGraph("images/ゲーム用モンスター素材/兵士/兵士A_攻撃003.png");
		}

		/*魔法使い*/
		if (true) {
			p->Enemy_Idle[6][0] = LoadGraph("images/ゲーム用モンスター素材/魔法使い/魔法使いA_待機000.png");
			p->Enemy_Idle[6][1] = LoadGraph("images/ゲーム用モンスター素材/魔法使い/魔法使いA_待機001.png");
			p->Enemy_Idle[6][2] = LoadGraph("images/ゲーム用モンスター素材/魔法使い/魔法使いA_待機002.png");
			p->Enemy_Idle[6][3] = LoadGraph("images/ゲーム用モンスター素材/魔法使い/魔法使いA_待機003.png");

			p->Enemy_Move[6][0] = LoadGraph("images/ゲーム用モンスター素材/魔法使い/魔法使いA_移動000.png");
			p->Enemy_Move[6][1] = LoadGraph("images/ゲーム用モンスター素材/魔法使い/魔法使いA_移動001.png");
			p->Enemy_Move[6][2] = LoadGraph("images/ゲーム用モンスター素材/魔法使い/魔法使いA_移動002.png");
			p->Enemy_Move[6][3] = LoadGraph("images/ゲーム用モンスター素材/魔法使い/魔法使いA_移動003.png");
			p->Enemy_Move[6][4] = LoadGraph("images/ゲーム用モンスター素材/魔法使い/魔法使いA_移動004.png");
			p->Enemy_Move[6][5] = LoadGraph("images/ゲーム用モンスター素材/魔法使い/魔法使いA_移動005.png");

			p->Enemy_Attack[6][0] = LoadGraph("images/ゲーム用モンスター素材/魔法使い/魔法使いA_攻撃000.png");
			p->Enemy_Attack[6][1] = LoadGraph("images/ゲーム用モンスター素材/魔法使い/魔法使いA_攻撃001.png");
			p->Enemy_Attack[6][2] = LoadGraph("images/ゲーム用モンスター素材/魔法使い/魔法使いA_攻撃002.png");
			p->Enemy_Attack[6][3] = LoadGraph("images/ゲーム用モンスター素材/魔法使い/魔法使いA_攻撃003.png");
		}

		/*どくろ*/
		if (true) {
			p->Enemy_Idle[7][0] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろA_待機・移動000.png");
			p->Enemy_Idle[7][1] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろA_待機・移動001.png");
			p->Enemy_Idle[7][2] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろA_待機・移動002.png");
			p->Enemy_Idle[7][3] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろA_待機・移動003.png");

			p->Enemy_Move[7][0] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろA_待機・移動000.png");
			p->Enemy_Move[7][1] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろA_待機・移動001.png");
			p->Enemy_Move[7][2] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろA_待機・移動002.png");
			p->Enemy_Move[7][3] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろA_待機・移動003.png");

			p->Enemy_Attack[7][0] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろA_攻撃000.png");
			p->Enemy_Attack[7][1] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろA_攻撃001.png");
			p->Enemy_Attack[7][2] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろA_攻撃002.png");
			p->Enemy_Attack[7][3] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろA_攻撃003.png");
		}

		/*黒コボルト*/
		if (true) {
			p->Enemy_Idle[8][0] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトD_待機000.png");
			p->Enemy_Idle[8][1] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトD_待機001.png");
			p->Enemy_Idle[8][2] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトD_待機002.png");

			p->Enemy_Move[8][0] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトD_移動000.png");
			p->Enemy_Move[8][1] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトD_移動001.png");
			p->Enemy_Move[8][2] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトD_移動002.png");
			p->Enemy_Move[8][3] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトD_移動003.png");
			p->Enemy_Move[8][4] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトD_移動004.png");
			p->Enemy_Move[8][5] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトD_移動005.png");

			p->Enemy_Attack[8][0] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトD_攻撃000.png");
			p->Enemy_Attack[8][1] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトD_攻撃001.png");
			p->Enemy_Attack[8][2] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトD_攻撃002.png");
			p->Enemy_Attack[8][3] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトD_攻撃003.png");
			p->Enemy_Attack[8][4] = LoadGraph("images/ゲーム用モンスター素材/コボルト/コボルトD_攻撃004.png");
		}

		/*黒どくろ*/
		if (true) {
			p->Enemy_Idle[9][0] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろD_待機・移動000.png");
			p->Enemy_Idle[9][1] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろD_待機・移動001.png");
			p->Enemy_Idle[9][2] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろD_待機・移動002.png");
			p->Enemy_Idle[9][3] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろD_待機・移動003.png");

			p->Enemy_Move[9][0] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろD_待機・移動000.png");
			p->Enemy_Move[9][1] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろD_待機・移動001.png");
			p->Enemy_Move[9][2] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろD_待機・移動002.png");
			p->Enemy_Move[9][3] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろD_待機・移動003.png");

			p->Enemy_Attack[9][0] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろD_攻撃000.png");
			p->Enemy_Attack[9][1] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろD_攻撃001.png");
			p->Enemy_Attack[9][2] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろD_攻撃002.png");
			p->Enemy_Attack[9][3] = LoadGraph("images/ゲーム用モンスター素材/どくろ/どくろD_攻撃003.png");
		}

		/*黒妖精*/
		if (true) {
			p->Enemy_Idle[10][0] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精D_待機000.png");
			p->Enemy_Idle[10][1] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精D_待機001.png");
			p->Enemy_Idle[10][2] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精D_待機002.png");
			p->Enemy_Idle[10][3] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精D_待機003.png");

			p->Enemy_Move[10][0] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精D_移動000.png");
			p->Enemy_Move[10][1] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精D_移動001.png");
			p->Enemy_Move[10][2] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精D_移動002.png");
			p->Enemy_Move[10][3] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精D_移動003.png");

			p->Enemy_Attack[10][0] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精D_攻撃000.png");
			p->Enemy_Attack[10][1] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精D_攻撃001.png");
			p->Enemy_Attack[10][2] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精D_攻撃002.png");
			p->Enemy_Attack[10][3] = LoadGraph("images/ゲーム用モンスター素材/妖精/妖精D_攻撃003.png");
		}

		/*ドラゴン*/
		if (true) {
			p->Enemy_Idle[11][0] = LoadGraph("images/ゲーム用モンスター素材/ドラゴン/ドラゴンA_待機000.png");
			p->Enemy_Idle[11][1] = LoadGraph("images/ゲーム用モンスター素材/ドラゴン/ドラゴンA_待機001.png");
			p->Enemy_Idle[11][2] = LoadGraph("images/ゲーム用モンスター素材/ドラゴン/ドラゴンA_待機002.png");
			p->Enemy_Idle[11][3] = LoadGraph("images/ゲーム用モンスター素材/ドラゴン/ドラゴンA_待機003.png");

			p->Enemy_Move[11][0] = LoadGraph("images/ゲーム用モンスター素材/ドラゴン/ドラゴンA_移動000.png");
			p->Enemy_Move[11][1] = LoadGraph("images/ゲーム用モンスター素材/ドラゴン/ドラゴンA_移動001.png");
			p->Enemy_Move[11][2] = LoadGraph("images/ゲーム用モンスター素材/ドラゴン/ドラゴンA_移動002.png");
			p->Enemy_Move[11][3] = LoadGraph("images/ゲーム用モンスター素材/ドラゴン/ドラゴンA_移動003.png");
			p->Enemy_Move[11][4] = LoadGraph("images/ゲーム用モンスター素材/ドラゴン/ドラゴンA_移動004.png");
			p->Enemy_Move[11][5] = LoadGraph("images/ゲーム用モンスター素材/ドラゴン/ドラゴンA_移動005.png");

			p->Enemy_Attack[11][0] = LoadGraph("images/ゲーム用モンスター素材/ドラゴン/ドラゴンA_攻撃000.png");
			p->Enemy_Attack[11][1] = LoadGraph("images/ゲーム用モンスター素材/ドラゴン/ドラゴンA_攻撃001.png");
			p->Enemy_Attack[11][2] = LoadGraph("images/ゲーム用モンスター素材/ドラゴン/ドラゴンA_攻撃002.png");
			p->Enemy_Attack[11][3] = LoadGraph("images/ゲーム用モンスター素材/ドラゴン/ドラゴンA_攻撃003.png");
			p->Enemy_Attack[11][4] = LoadGraph("images/ゲーム用モンスター素材/ドラゴン/ドラゴンA_攻撃004.png");
		}

	}
};

extern Dungeon dungeon;