#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>
#include <windows.h>

#include "Source.h"
#include "string.h"
#include "Input.h"
#include "header.h"

#include "GameSys.h"			//ゲームのシステム

#define WIDTH 1280	//画像横サイズ
#define HEIGHT 704	//画像縦サイズ
#define CHIP_SIZE 64 //一つの画像サイズ
#define MAP_WIDTH WIDTH/CHIP_SIZE	//マップ横サイズ
#define MAP_HEIGHT HEIGHT/CHIP_SIZE //マップ縦サイズ

//*****列挙隊*****
enum Key { UP, DOWN, LEFT, RIGHT };
enum PlayerImage { Image_DOWN = 0, Image_UP = 3, Image_RIGHT = 6, Image_LEFT = 9 };
enum Tane { KOMUGI_TANE = 10, JAGAIMO_TANE, NINJIN_TANE, DAIKON_TANE, KYABETU_TANE, SATUMAIMO_TANE, BUROKORI_TANE, KABOCYA_TANE, SUIKA_TANE };
enum MIZU { KOMUGI_MIZU = 20, JAGAIMO_MIZU, NINJIN_MIZU, DAIKON_MIZU, KYABETU_MIZU, SATUMAIMO_MIZU, BUROKORI_MIZU, KABOCYA_MIZU, SUIKA_MIZU };
enum eYASAI { KOMUGI = 30, JAGAIMO, NINJIN, DAIKON, KYABETU, SATUMAIMO, BUROKORI, KABOCYA, SUIKA };
enum Page { MENU, MENU2, MENU3, MENU4, MENU5};
enum MAPDATA { NUL, WALL = 2, EXIT };
//*****構造隊*****
struct PLAYER {
	//プレイヤー座標
	int x, y;
	int muki;
	int image_muki = Image_LEFT;
	int  speed;
	bool walking_flg;
	bool fremflg;
	int image = 0;
};
struct YASAI {
	int x, y;//座標
	int Timecount;//秒数
	int num = 0;//今の野菜データ保存するやつ
	bool flg;//増えているか
	int price = 0;
	int Enter_Time = 0;
	int Exit_Time = 0;
	int TmpCount = 0;
};

struct YASAIDATA {
	char name[128];//野菜の名前
	int num = 0;	//野菜の数
	bool flg = 0;	//フラグ
	int price = 0;	//野菜の値段
	int Yasainum = 0;
};
struct SELECTMENU {	//種
	int x, y;
	char name[128];
	bool flg;
	bool colorflg;
	int num;
	bool drawflg;
};
struct KYOTEN {
	int mapdata = 0;
	bool flg = false;
	bool selectflg = false;
};
//*****マップチップ***** 0 行ける場所 1 壁 2 壁
int hatakemap[MAP_HEIGHT][MAP_WIDTH] = {
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,2},
	{2,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,2},
	{2,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,2,2,2,2,2,2,2,2,3,3,2,2,2,2,2,2,2,2,2},
};
//*****野菜データ*****
int tane[MAP_HEIGHT][MAP_WIDTH] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
//*****構造体変数宣言*****
HATAKE hatake;
PLAYER player;
KYOTEN kyoten;
GameSystem;
//メニュー選択画面
SELECTMENU menu1[5] = {
	{400,310,"種をうえる",0,1},
	{400,330,"水をまく",0,0},
	{400,350,"収穫",0,0},
	{400,370,"バッグ",0,0} };
//メニュー種
SELECTMENU menutane[9] = {
	{400,310,"こむぎのたね",0,1,5,true},
	{400,330,"じゃがいものたね",0,0,5,true},
	{400,350,"にんじんのたね",0,0,5,true},
	{400,370,"だいこんのたね",0,0,5,true},
	{400,390,"きゃべつのたね",0,0,5,true},
	{400,410,"さつまいものたね",0,0,5,true},
	{400,430,"ぶろっこりーのたね", 0,0,5,true},
	{400,450,"かぼちゃのたね",0,0,5,true},
	{400,470,"すいかのたね",0,0,5,true} };
YASAIDATA YasaiData_a[9] = {
	{"こむぎ",0,false,6,KOMUGI_MIZU},
	{"じゃがいも",0,false,2,JAGAIMO_MIZU},
	{"にんじん",0,false,3,NINJIN_MIZU},
	{"だいこん",0,false,5,DAIKON_MIZU},
	{"きゃべつ",0,false,8,KYABETU_MIZU},
	{"さつまいも",0,false,6,SATUMAIMO_MIZU},
	{"ぶろっこりー",0,false,5,BUROKORI_MIZU},
	{"かぼちゃ",0,false,12,KABOCYA_MIZU},
	{"すいか",0,false,42,SUIKA_MIZU} };
//拠点戻る選択
SELECTMENU bacselect[3] = {
	{500,350,"はい",0,1},
	{740,350,"いいえ",0,0},
	{520,280,"拠点へ戻りますか？",0,0},
};
YASAI Yasaidata[54];
//*****変数宣言*****
//畑処理用変数
int Key[256]; // キーが押されているフレーム数を格納する
bool dflg = false; //デバックフラグ
bool flg = true; //関数初期化フラグ
//作業選択変数
bool selectflg = false; //作業選択画面フラグ
int pageflg = MENU; //現在の作業フラグ 種植える 水やり 収穫など
int selectNum = 0; //作業選択の現在選択している場所
int selectTane = 0; //種選択の現在選択している場所
int selectExit = 0; //出口の現在選択している場所
bool initflg = false; //選択された文字の色を変える関数の呼び出しフラグ
//初期化変数
int Plantpageflg = MENU;
bool plantflg = false;//植えるときのフラグ
int drawdignum = 10;//描画するときに数字を調整する
int TaneNowyasai = 0;//現在の野菜データを入れるもの
int MizuNowyasai = 0;
int SyukakuNowyasai = 0;
int startkeycount = 0;
int ykeycoun = 0;
///////////////////種用変数
bool taneplantflg = true;
int tanenum = 0;
int tanelimitdata = 0;
int select_tane_num = 9;
int select_tane_backnum = 8;
///////////////////育つ用変数
bool mizuyari = false;
int Mizu_yasainum = 0;//水やりの時の野菜データを保存するやつ
int TimeCount = 0;
int Yasai_Hanbetu;
int Exit_Time;
int Enter_Time = ch.Return_Base_Status(&ch, 2);
int Time_Yasai = ch.Return_Base_Status(&ch, 2);
bool Exitflg = false;
bool Enterflg = false;
//収穫用変数
int syukakunum = 0;//収穫できるかのデータ保存するやつ
//データ保存
int SyukakuData = 0;
//プレイヤーアニメーション用変数
int playerjouro = 0;
int player_animeflg = 1;

//音楽変数
int work_SEcount = 0;
int Yasai_SE = 0;
int Mizu_SE = 0;
int Plant_SE = 0;
int soundflg = 0;
int player_workSE_L = 0;
int player_workSE_R = 0;
//*****プロトタイプ宣言*****
void Game_Hatake(int Width, int Height);
void InitPlayer(void);//プレイヤー初期化
void InitYasaiData(void);
int IsAbleToGo(int x, int y, int muki);//当たり判定処理
void Player(int Width, int Height);//プレイヤー処理
void PlayerDraw();
int gpUpdateKey();//キー更新処理
void DrawFrem();//枠表示描画
void DrawHatake(int Width, int Height);//畑描画
void MoveYasai();//野菜処理
void DrawYasai();//野菜・種など描画
//種処理
void MoveSelectTane();//種選択画面処理
void DrawSelectTane();//種選択画面描画
//void TaneLimit();//種の数を制限
//void Select_TaneLimit();
//作業選択
void MoveSelectMenu();//作業選択メニュー処理
void DrawSelectMenu(); //作業選択メニュー描画
void YasaiMizuMove();
void MoveMizu();//水をあげる処理
void Debag();//デバック描画処理
//育つ処理
void YasaiDainyu(int i);
void Growth();//成長処理
void YasaiCountFlg();
void Count();//カウント
//拠点処理
void DrawKyotenExitSelect();
void KyotenExitSelect();
void KyotenBag();
//収穫処理
void Syukaku();
void SyuukakuMov();
void InitselectColor();
//植える処理
void TanePlant();
void MizuPlant();
void SyukakuPlant();
//バック画面
void Bag();
void YasaiJudgment();
//音楽処理
void InitSE();
//////////////////
void InitSE() {
	Yasai_SE = LoadSoundMem("sounds/yasainuki.mp3");
	Mizu_SE = LoadSoundMem("sounds/mizuyari.mp3");
	Plant_SE = LoadSoundMem("sounds/ueru.mp3");
	player_workSE_L = LoadSoundMem("sounds/walk-gravel1.mp3");
	/*player_workSE_R = LoadSoundMem("sounds/walk_L.mp3");*/
}
//*****処理呼び出し*****
void Game_Hatake(int Width, int Height) {
	SetFontSize(20);//文字サイズ確認

	if (flg) {
		InitYasaiData();
		InitSE();
		InitPlayer(); flg = false;	//一回のみ初期化
	}

	if (Exitflg == true) {
		 for(int i = 0; i < 54; i++) {
			if (Yasaidata[i].flg == true) {
				Yasaidata[i].Exit_Time = ch.Return_Base_Status(&ch, 2);
			}
		}
		Exitflg = false;
	}
	gpUpdateKey();//入力更新
	Player(Width, Height);//プレイヤー処理関数
	DrawHatake(Width, Height);//描画処理
	//作業メニュー開く処理
	//ここから作業する!!
	if (inp.start == true) {
		StopSoundMem(player_workSE_L);
		ykeycoun++;
		if (ykeycoun % 2 == 0) {
			selectflg = false;//作業メニューを閉じる処理
			selectNum = 0; //開いたときに現在選択している場所を初期化
			selectTane = 0;
			pageflg = MENU;
		}
		else
		{
			selectflg = true; //作業メニューを開く処理
			initflg = true;
		}
	}
	//作業メニュー画面処理
	switch (pageflg)
	{
	case MENU:if (selectflg == true)MoveSelectMenu(); break;//作業選択画面
	case MENU2:if (selectflg == true)MoveSelectTane(); break;//種選択画面
	case MENU3: MoveMizu(); break;//水をあげる画面
	case MENU4: Syukaku(); break;//収穫処理
	case MENU5: Bag(); break;
	}
	//植えるとき
	if (pageflg == MENU2) { Plantpageflg = MENU2; } //10
	else if (pageflg == MENU3) { Plantpageflg = MENU3; }//21
	else if (pageflg == MENU4) { Plantpageflg = MENU4; }//32
	else if (pageflg == MENU5) { Plantpageflg = MENU5; }//43
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//種
	/*Select_TaneLimit();*/
	//拠点戻り処理
	KyotenBag();
	//成長処理
	Count();
	Growth();
	YasaiCountFlg();
	//デバック処理
	if (dflg) {
		Debag();
	}
	DrawBox(90, 640, 380, 680, GetColor(0, 0, 0), true);
	DrawBox(90, 640, 380, 680, GetColor(255, 255, 255), false);
	DrawFormatString(100, 650, GetColor(255, 255, 0), "現在のモード[%s]", menu1[Plantpageflg - 1].name);
}
//野菜データの初期化
void InitYasaiData(void) {
	int i = 2;//行
	int j = 2;//列
	//ほしい値↓**************************
	//   行 列
	//2行[2][2]〜[2][16]
	//3行[3][2]〜[3][16]
	//7行[7][2]〜[7][7] [7][12]〜[7][17]
	//8行[8][2]〜[8][7] [8][12]〜[8][17] 合計54
	//***************************************
	for (int s = 0; s < 54; s++) {
		if (i == 2 || i == 3) {//2行と3行の間繰り返す処理
			if (j >= 17) { i++; j = 2; }//17列目に行ったら3行目にして列をリセットする
			Yasaidata[s].x = j++; //列を代入
		}
		if (i == 4) { i = 7; j = 2; }//[7行目にするための調整][列の初期化]
		if (i == 7 || i == 8) {//7列目と8列目の間繰り返す
			if (j > 17) { i++; j = 2; }//17列目に行ったら8行目にして列をリセットする
			Yasaidata[s].x = j++;//列を代入
			if (j == 8) { j = 12; }//列が8列になったら列を12列目に調整する
		}
		Yasaidata[s].Timecount = 0;
		Yasaidata[s].flg = false;
		Yasaidata[s].y = i;//行を代入
		Yasaidata[s].num = 0;
		Yasaidata[s].price = 0;
		Yasaidata[s].Enter_Time = 0;
		Yasaidata[s].Exit_Time = 0;
	}
}

//プレイヤー初期化
void InitPlayer(void) {
	player.x = 576;
	player.y = 576;
	player.speed = 2;
	player.muki = UP;
	player.image_muki = Image_LEFT;
	player.walking_flg = false;
	kyoten.selectflg = false;
	player.image = 0;
	kyoten.mapdata = 0;
}

//プレイヤー処理
void Player(int Width, int Height) {
	MoveYasai();
	if (selectflg == false && kyoten.flg == false) {
		if (player.x % CHIP_SIZE == 0 && player.y % CHIP_SIZE == 0) {
			player.walking_flg = true;
			//コントロール入力
			if (inp.up == true) {
				player.muki = UP;
				PlaySoundMem(player_workSE_L, DX_PLAYTYPE_BACK, TRUE);
			}
			else if (inp.down == true) {
				player.muki = DOWN;
				PlaySoundMem(player_workSE_L, DX_PLAYTYPE_BACK, TRUE);
			}
			else if (inp.left == true) {
				player.muki = LEFT;//左向きフラグ
				PlaySoundMem(player_workSE_L, DX_PLAYTYPE_BACK, TRUE);
			}
			else if (inp.right == true) {
				player.muki = RIGHT;//右向きフラグ
				PlaySoundMem(player_workSE_L, DX_PLAYTYPE_BACK, TRUE);
			}
			else {
				player.walking_flg = false;//歩かないフラグ
				StopSoundMem(player_workSE_L);
			}
			if (IsAbleToGo(player.x, player.y, player.muki) == 1)
				player.walking_flg = false;
		}
		if (player.walking_flg == true) {//歩くフラグが立ったいたら
			if (player.muki == UP) {
				player.y -= player.speed;
			}
			else if (player.muki == DOWN) {
				player.y += player.speed;
			}
			else if (player.muki == LEFT) {
				player.x -= player.speed;
			}
			else if (player.muki == RIGHT) {
				player.x += player.speed;
			}
		
			//if (work_SEcount % 2 == 0) {
			//	PlaySoundMem(player_workSE_L, DX_PLAYTYPE_BACK, TRUE);
			//}
			//else
			//{
			//	PlaySoundMem(player_workSE_R, DX_PLAYTYPE_BACK, TRUE);
			//}
		}
	}
	//画面外歩けない処理
	if (player.x < 0) {
		player.x = 0;
	}
	else if (player.y < 0) {
		player.y = 0;
	}
	/*デバック表示*/
	if (inp.sele == true) {
		startkeycount++;
		if (startkeycount % 2 == 0) {
			dflg = false;
		}
		else {
			dflg = true;
		}
	}
}
void PlayerDraw() {
	//プレイヤーアニメーション処理******************************************************
	if (player.muki == UP) { player.image_muki = Image_UP; }
	else if (player.muki == DOWN) { player.image_muki = Image_DOWN; }
	else if (player.muki == RIGHT) { player.image_muki = Image_RIGHT; }
	else if (player.muki == LEFT) { player.image_muki = Image_LEFT; }
	player.image = ((player.x % CHIP_SIZE + player.y % CHIP_SIZE) / 21) + player.image_muki;
	//**********************************************************************************
	if (player.muki == DOWN) {
		playerjouro = 0;
	}
	else if (player.muki == LEFT) {
		playerjouro = 1;
	}
	else if (player.muki == RIGHT) {
		playerjouro = 2;
	}
	else if (player.muki == UP) {
		playerjouro = 3;
	}

	if (IsAbleToGo(player.x, player.y, player.muki) == 1 && player.fremflg == true && plantflg == true) {
		if (Plantpageflg == MENU3)player_animeflg = 2;
	}
	else {
		player_animeflg = 1;
	}
	//プレイヤー描画 [1プレイヤー] [2じょうろの画像]
	switch (player_animeflg)
	{
	case 1: DrawGraph(player.x, player.y, hatake.testimage[player.image], TRUE); break;
	case 2: DrawGraph(player.x, player.y, hatake.playerjouro[playerjouro], TRUE); break;
	}
}
//*****畑描画処理*****
void DrawHatake(int Width, int Height) {
	if (hatake.flg) { hatake.ImageInput(&hatake); hatake.flg = false; }
	DrawGraph(0, 0, hatake.image, TRUE);
	PlayerDraw();
	DrawYasai();
	//フレーム表示
	DrawFrem();
}
//野菜判定
void MoveYasai() {
	if (inp.space == true) {
		if (IsAbleToGo(player.x, player.y, player.muki) == 1 && player.fremflg == true && plantflg == true) {
			switch (Plantpageflg) {
			case MENU2:TanePlant(); if (Plantpageflg == MENU2) { PlaySoundMem(Plant_SE, DX_PLAYTYPE_BACK, TRUE); } break;//種植える処理
			case MENU3:MizuPlant(); if (Plantpageflg == MENU3) { mizuyari = true; PlaySoundMem(Mizu_SE, DX_PLAYTYPE_BACK, TRUE);}break;//水植える処理
			case MENU4:SyukakuPlant(); if (Plantpageflg == MENU4) {PlaySoundMem(Yasai_SE, DX_PLAYTYPE_BACK, TRUE);} break;}
		}
	}
}
//野菜描画
void DrawYasai() {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (tane[i][j] != 0) {
				if (tane[i][j] >= KOMUGI_TANE && tane[i][j] <= SUIKA_TANE) {//種描画
					DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, hatake.tane[tane[i][j] % drawdignum], FALSE);
				}
				else if (tane[i][j] >= KOMUGI_MIZU && tane[i][j] <= SUIKA_MIZU) {//水やり描画
					DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, hatake.mizu[tane[i][j] % drawdignum], FALSE);
				}
				else if (tane[i][j] >= KOMUGI && tane[i][j] <= SUIKA) {
					DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, hatake.yasai[tane[i][j] % drawdignum], FALSE);//野菜描画 
				}
			}
		}
	}
}
//**************************************選択画面処理**************************************************************************************
//選択されている場所の色初期化
void InitselectColor() {
	//選択作業初期化
	for (int i = 0; i < 4; i++) {
		if (i == 0) {
			menu1[i].colorflg = 1;
		}
		else {
			menu1[i].colorflg = 0;
		}
	}
	//種選択初期化
	for (int i = 0; i < 9; i++) {
		if (i == 0) {
			menutane[i].colorflg = 1;
		}
		else {
			menutane[i].colorflg = 0;
		}
	}
}
//植える・水やり・収穫・バッグ・選択画面処理
void MoveSelectMenu() {
	//選択画面初期化
	if (initflg) {
		InitselectColor();
		initflg = false;
	}
	if (inp.f_down == true) {
		selectNum = (selectNum + 1) % 4;
	}
	if (inp.f_up == true) {
		selectNum = (selectNum + 3) % 4;
	}
	if (inp.f_down == true || inp.f_up == true) {
		for (int i = 0; i < 4; i++) {
			if (i == selectNum) {
				menu1[i].colorflg = 1;
			}
			else {
				menu1[i].colorflg = 0;
			}
		}
	}

	//選択した処理に飛ばす 0は種を植える 1水をやる 2収穫
	if (inp.space == true) {
		switch (selectNum)
		{
		case 0:pageflg = MENU2; break;
		case 1:pageflg = MENU3, selectflg = false, ykeycoun++; break;
		case 2:pageflg = MENU4, selectflg = false, ykeycoun++; break;
		case 3:pageflg = MENU5, selectflg = false, ykeycoun++; break;
		}
	}
	DrawSelectMenu();
}
//選択画面描画
void DrawSelectMenu() {
	DrawBox(390, 300, 610, 420, GetColor(0, 0, 0), true);
	DrawBox(390, 300, 610, 420, GetColor(255, 255, 255), false);

	for (int i = 0; i < 4; i++) {
		if (menu1[i].colorflg == 1) {
			DrawFormatString(menu1[i].x, menu1[i].y, 0x5D99FF, menu1[i].name);
		}
		else {
			DrawFormatString(menu1[i].x, menu1[i].y, GetColor(255, 255, 255), menu1[i].name);
		}
	}
}

//種選択画面処理
void MoveSelectTane() {
	if (inp.f_down == true) {
		selectTane = (selectTane + 1) % select_tane_num;
	}
	if (inp.f_up == true) {
		selectTane = (selectTane + select_tane_backnum) % select_tane_num; //+2 %3
	}
	if (inp.f_down == true || inp.f_up == true) {
		for (int i = 0; i < select_tane_num; i++) {
			if (i == selectTane) {
				menutane[i].colorflg = 1;
			}
			else {
				menutane[i].colorflg = 0;
			}
		}
	}
	//選択された種を処理
	DrawSelectTane();
	if (inp.space == true) {
		if (selectTane == 0) {
			TaneNowyasai = KOMUGI_TANE;
		}
		else if (selectTane == 1) {
			TaneNowyasai = JAGAIMO_TANE;
		}
		else if (selectTane == 2) {
			TaneNowyasai = NINJIN_TANE;
		}
		else if (selectTane == 3) {
			TaneNowyasai = DAIKON_TANE;
		}
		else if (selectTane == 4) {
			TaneNowyasai = KYABETU_TANE;
		}
		else if (selectTane == 5) {
			TaneNowyasai = SATUMAIMO_TANE;
		}
		else if (selectTane == 6) {
			TaneNowyasai = BUROKORI_TANE;
		}
		else if (selectTane == 7) {
			TaneNowyasai = KABOCYA_TANE;
		}
		else if (selectTane == 8) {
			TaneNowyasai = SUIKA_TANE;
		}
		plantflg = true;
		selectflg = false;
		pageflg = MENU;
	}
}
//植える種の制限
//void Select_TaneLimit() {
//	if (selectTane == 0 && menutane[0].num > 0) {
//		DrawFormatString(300, 200, 0x5D99FF, "成功");
//		TaneNowyasai = KOMUGI_TANE;
//	}
//	else if (selectTane == 1 && menutane[1].num > 0) {
//		DrawFormatString(300, 200, 0x5D99FF, "成功");
//		TaneNowyasai = JAGAIMO_TANE;
//	}
//	else if (selectTane == 2 && menutane[2].num > 0) {
//		DrawFormatString(300, 200, 0x5D99FF, "成功");
//		TaneNowyasai = NINJIN_TANE;
//	}
//	else if (selectTane == 3 && menutane[3].num > 0) {
//		DrawFormatString(300, 200, 0x5D99FF, "成功");
//		TaneNowyasai = DAIKON_TANE;
//	}
//	else if (selectTane == 4 && menutane[4].num > 0) {
//		DrawFormatString(300, 200, 0x5D99FF, "成功");
//		TaneNowyasai = KYABETU_TANE;
//	}
//	else if (selectTane == 5 && menutane[5].num > 0) {
//		DrawFormatString(300, 200, 0x5D99FF, "成功");
//		TaneNowyasai = SATUMAIMO_TANE;
//	}
//	else if (selectTane == 6 && menutane[6].num > 0) {
//		DrawFormatString(300, 200, 0x5D99FF, "成功");
//		TaneNowyasai = BUROKORI_TANE;
//	}
//	else if (selectTane == 7 && menutane[7].num > 0) {
//		DrawFormatString(300, 200, 0x5D99FF, "成功");
//		TaneNowyasai = KABOCYA_TANE;
//	}
//	else if (selectTane == 8 && menutane[8].num > 0) {
//		DrawFormatString(300, 200, 0x5D99FF, "成功");
//		TaneNowyasai = SUIKA_TANE;
//	}
//	else {
//		TaneNowyasai = 0;
//	}
//}
void DrawSelectTane() {
	//メニュー背景枠的な
	DrawBox(390, 300, 630, 500, GetColor(0, 0, 0), true);
	DrawBox(390, 300, 630, 500, GetColor(255, 255, 255), false);

	for (int i = 0; i < select_tane_num; i++) {
		if (menutane[i].drawflg == true) {
			if (menutane[i].colorflg == 1) {
				DrawFormatString(menutane[i].x, menutane[i].y, 0x5D99FF, "%s ∞", menutane[i].name);
			}
			else {
				DrawFormatString(menutane[i].x, menutane[i].y, GetColor(255, 255, 255), "%s ∞", menutane[i].name);
			}
		}
	}
}
//残りの種を引いていく処理
//void TaneLimit() {
//	tanelimitdata = TaneNowyasai;
//
//	if (TaneNowyasai==KOMUGI_TANE) {
//		menutane[0].num--;
//	}
//	else if (TaneNowyasai == JAGAIMO_TANE) {
//		menutane[1].num--;
//	}
//	else if (TaneNowyasai == NINJIN_TANE) {
//		menutane[2].num--;
//	}
//	else if (TaneNowyasai == DAIKON_TANE) {
//		menutane[3].num--;
//	}
//	else if (TaneNowyasai == KYABETU_TANE) {
//		menutane[4].num--;
//	}
//	else if (TaneNowyasai == SATUMAIMO_TANE) {
//		menutane[5].num--;
//	}
//	else if (TaneNowyasai == BUROKORI_TANE) {
//		menutane[6].num--;
//	}
//	else if (TaneNowyasai == KABOCYA_TANE) {
//		menutane[7].num--;
//	}
//	else if (TaneNowyasai == SUIKA_TANE) {
//		menutane[8].num--;
//	}
//
//	for (int i = 0; i < 9; i++) {
//		if (menutane[i].num <= 0) {
//			//select_tane_backnum--;
//			//select_tane_num--;
//			menutane[i].drawflg = false;
//		}
//	}
//}
//*********************************　水を上げる処理********************************************************************************
void YasaiMizuMove() {
	if (KOMUGI_TANE == Mizu_yasainum) { MizuNowyasai = KOMUGI_MIZU; }
	else if (JAGAIMO_TANE == Mizu_yasainum) { MizuNowyasai = JAGAIMO_MIZU; }
	else if (NINJIN_TANE == Mizu_yasainum) { MizuNowyasai = NINJIN_MIZU; }
	else if (DAIKON_TANE == Mizu_yasainum) { MizuNowyasai = DAIKON_MIZU; }
	else if (KYABETU_TANE == Mizu_yasainum) { MizuNowyasai = KYABETU_MIZU; }
	else if (SATUMAIMO_TANE == Mizu_yasainum) { MizuNowyasai = SATUMAIMO_MIZU; }
	else if (BUROKORI_TANE == Mizu_yasainum) { MizuNowyasai = BUROKORI_MIZU; }
	else if (KABOCYA_TANE == Mizu_yasainum) { MizuNowyasai = KABOCYA_MIZU; }
	else if (SUIKA_TANE == Mizu_yasainum) { MizuNowyasai = SUIKA_MIZU; }
}
void MoveMizu() {
	MizuNowyasai = Mizu_yasainum;//水更新
	if (IsAbleToGo(player.x, player.y, player.muki) == 1 && player.fremflg == true) {
		if (player.muki == UP) {
			Mizu_yasainum = tane[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE];
		}
		if (player.muki == DOWN) {
			Mizu_yasainum = tane[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE];
		}
		if (player.muki == LEFT) {
			Mizu_yasainum = tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1];
		}
		if (player.muki == RIGHT) {
			Mizu_yasainum = tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1];
		}
	}
	else {
		Mizu_yasainum = 0;
	}
	if (Mizu_yasainum != 0) {
		plantflg = true;
	}
	else {
		plantflg = false;
	}
	YasaiMizuMove();
}

///////////////////////育つ処理(仮)////////////////////////////////////////////////////////////////////////////////////////////////////////////
void YasaiCountFlg() {
	if (mizuyari == true) {
		for (int i = 0; i < 54; i++) {
			if (IsAbleToGo(player.x, player.y, player.muki) == 1) {
				if (player.fremflg == true) {
					if (Yasaidata[i].y == player.y / CHIP_SIZE - 1 && Yasaidata[i].x == player.x / CHIP_SIZE) {//上
						Yasaidata[i].flg = 1;
						Yasaidata[i].num = tane[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE];
					}
					if (Yasaidata[i].y == player.y / CHIP_SIZE + 1 && Yasaidata[i].x == player.x / CHIP_SIZE) {//下
						Yasaidata[i].flg = 1;
						Yasaidata[i].num = tane[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE];
					}
					if (Yasaidata[i].y == player.y / CHIP_SIZE && Yasaidata[i].x == player.x / CHIP_SIZE - 1) {//左
						Yasaidata[i].flg = 1;
						Yasaidata[i].num = tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1];
					}
					if (Yasaidata[i].y == player.y / CHIP_SIZE && Yasaidata[i].x == player.x / CHIP_SIZE + 1) {//右
						Yasaidata[i].flg = 1;
						Yasaidata[i].num = tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1];
					}
				}
			}
		}
		mizuyari = false;
	}
}


///////////////////////////////////(成長カウント関数)////////////////////////////////////////////////////////////////////////////////////////////
//水やり後のカウントしていく
void Count() {
	for (int i = 0; i < 54; i++) {
		
		if (Yasaidata[i].flg == true) {
			Yasaidata[i].Timecount = (Yasaidata[i].Exit_Time / 60) - (Yasaidata[i].Enter_Time / 60);
		}
	}
}
//成長データ
void Growth() {
	//(2G 3G 5G 6G 8G 12G 42G)//野菜の値段
	//経過処理
	Time_Yasai = (Exit_Time / 60) - (Enter_Time / 60);
	//お金の値段に応じて成長スピード処理
	for (int i = 0; i < 54; i++) {
		if (Yasaidata[i].price == 2) { if (Yasaidata[i].Timecount > 18) { YasaiDainyu(i); } } // 3分
		if (Yasaidata[i].price == 3) { if (Yasaidata[i].Timecount > 30) { YasaiDainyu(i); } } // 5分
		if (Yasaidata[i].price == 5) { if (Yasaidata[i].Timecount > 42) { YasaiDainyu(i); } } // 7分
		if (Yasaidata[i].price == 6) { if (Yasaidata[i].Timecount > 60) { YasaiDainyu(i); } } // 10分
	}
	//お金分別
	for (int i = 0; i < 54; i++) {
		if (Yasaidata[i].num == KOMUGI_MIZU) { Yasaidata[i].price = 6; }
		if (Yasaidata[i].num == JAGAIMO_MIZU) { Yasaidata[i].price = 2; }
		if (Yasaidata[i].num == NINJIN_MIZU) { Yasaidata[i].price = 3; }
		if (Yasaidata[i].num == DAIKON_MIZU) { Yasaidata[i].price = 5; }
		if (Yasaidata[i].num == KYABETU_MIZU) { Yasaidata[i].price = 8; }
		if (Yasaidata[i].num == SATUMAIMO_MIZU) { Yasaidata[i].price = 6; }
		if (Yasaidata[i].num == BUROKORI_MIZU) { Yasaidata[i].price = 5; }
		if (Yasaidata[i].num == KABOCYA_MIZU) { Yasaidata[i].price = 12; }
		if (Yasaidata[i].num == SUIKA_MIZU) { Yasaidata[i].price = 42; }
	}
}
void YasaiDainyu(int i) {
	if (Yasaidata[i].num == KOMUGI_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = KOMUGI; }
	if (Yasaidata[i].num == JAGAIMO_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = JAGAIMO; }
	if (Yasaidata[i].num == NINJIN_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = NINJIN; }
	if (Yasaidata[i].num == DAIKON_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = DAIKON; }
	if (Yasaidata[i].num == KYABETU_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = KYABETU; }
	if (Yasaidata[i].num == SATUMAIMO_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = SATUMAIMO; }
	if (Yasaidata[i].num == BUROKORI_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = BUROKORI; }
	if (Yasaidata[i].num == KABOCYA_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = KABOCYA; }
	if (Yasaidata[i].num == SUIKA_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = SUIKA; }
	/*for (int j = 0; j < 9;j++) {
		if (Yasaidata[i].num == YasaiData_a[j].Yasainum) { tane[Yasaidata[i].y][Yasaidata[i].x] = (YasaiData_a[j].Yasainum + 10); }
	}*/
	Yasaidata[i].num = 0;
	Yasaidata[i].price = 0;
	Yasaidata[i].flg = false;
	Yasaidata[i].Timecount = 0;
}

////////////収穫処理////////////////////////////////////////////////////////////////////////////////////////////////////
void Syukaku() {
	if (IsAbleToGo(player.x, player.y, player.muki) == 1 && player.fremflg == true) {
		if (player.muki == UP) {
			syukakunum = tane[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE];
		}
		if (player.muki == DOWN) {
			syukakunum = tane[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE];
		}
		if (player.muki == LEFT) {
			syukakunum = tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1];
		}
		if (player.muki == RIGHT) {
			syukakunum = tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1];
		}
		SyuukakuMov();
	}
	else {
		syukakunum = 0;
	}
}
void SyuukakuMov() {
	if (KOMUGI == syukakunum) {
		SyukakuNowyasai = 0; plantflg = true;
	}
	else if (JAGAIMO == syukakunum) {
		SyukakuNowyasai = 0; plantflg = true;
	}
	else if (NINJIN == syukakunum) {
		SyukakuNowyasai = 0; plantflg = true;
	}
	else if (DAIKON == syukakunum) {
		SyukakuNowyasai = 0; plantflg = true;
	}
	else if (KYABETU == syukakunum) {
		SyukakuNowyasai = 0; plantflg = true;
	}
	else if (SATUMAIMO == syukakunum) {
		SyukakuNowyasai = 0; plantflg = true;
	}
	else if (BUROKORI == syukakunum) {
		SyukakuNowyasai = 0; plantflg = true;
	}
	else if (KABOCYA == syukakunum) {
		SyukakuNowyasai = 0; plantflg = true;
	}
	else if (SUIKA == syukakunum) {
		SyukakuNowyasai = 0; plantflg = true;
	}
	else { plantflg = false; }
}
void YasaiJudgment() {
	SyukakuData = syukakunum;

	if (KOMUGI == SyukakuData) {
		YasaiData_a[0].num++;
	}
	else if (JAGAIMO == SyukakuData) {
		YasaiData_a[1].num++;
	}
	else if (NINJIN == SyukakuData) {
		YasaiData_a[2].num++;
	}
	else if (DAIKON == SyukakuData) {
		YasaiData_a[3].num++;
	}
	else if (KYABETU == SyukakuData) {
		YasaiData_a[4].num++;
	}
	else if (SATUMAIMO == SyukakuData) {
		YasaiData_a[5].num++;
	}
	else if (BUROKORI == SyukakuData) {
		YasaiData_a[6].num++;
	}
	else if (KABOCYA == SyukakuData) {
		YasaiData_a[7].num++;
	}
	else if (SUIKA == SyukakuData) {
		YasaiData_a[8].num++;
	}
}
//バッグ処理
void Bag() {
	DrawBox(190, 15, 400, 200, GetColor(0, 0, 0), true);
	DrawBox(190, 15, 400, 200, GetColor(255, 255, 255), false);
	for (int i = 0; i < 9; i++) {
		DrawFormatString(200, 20 * (i + 1), GetColor(255, 255, 255), "[%s][%d]", YasaiData_a[i].name, YasaiData_a[i].num);
	}
}
//フレーム描画
void DrawFrem() {
	if (IsAbleToGo(player.x, player.y, player.muki) == 1) {
		if (player.fremflg == true) {
			if (player.muki == UP) {
				DrawGraph((player.x / CHIP_SIZE) * CHIP_SIZE, (player.y / CHIP_SIZE - 1) * CHIP_SIZE, hatake.fremimage, TRUE);
			}
			if (player.muki == DOWN) {
				DrawGraph((player.x / CHIP_SIZE) * CHIP_SIZE, (player.y / CHIP_SIZE + 1) * CHIP_SIZE, hatake.fremimage, TRUE);
			}
			if (player.muki == LEFT) {
				DrawGraph((player.x / CHIP_SIZE - 1) * CHIP_SIZE, (player.y / CHIP_SIZE) * CHIP_SIZE, hatake.fremimage, TRUE);
			}
			if (player.muki == RIGHT) {
				DrawGraph((player.x / CHIP_SIZE + 1) * CHIP_SIZE, (player.y / CHIP_SIZE) * CHIP_SIZE, hatake.fremimage, TRUE);
			}
		}
	}
}
//////////////////////拠点　戻る処理//////////////////////////////////////////////////////////////////////////////////////
void KyotenExitSelect() {
	if (inp.f_left == true) {
		selectExit = (selectExit + 1) % 2;
	}
	if (inp.f_right == true) {
		selectExit = (selectExit + 1) % 2;
	}
	if (inp.f_left == true || inp.f_right == true) {
		for (int i = 0; i < 2; i++) {
			if (i == selectExit) {
				bacselect[i].colorflg = 1;
			}
			else {
				bacselect[i].colorflg = 0;
			}
		}
	}
	if (inp.space == true) {
		if (selectExit == 0) {
			for (int i = 0; i < 54; i++) {
				if (Yasaidata[i].flg == true) {
					Yasaidata[i].Enter_Time = ch.Return_Base_Status(&ch, 2);
					Yasaidata[i].TmpCount = Yasaidata[i].Timecount;
				}
			}
			Exitflg = true;
			g_GameState = GAME_HOME;
			InitPlayer();
		}
		else if (selectExit == 1) {
			kyoten.selectflg = false;
			hatakemap[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE] = WALL;//壁データを入れる
			kyoten.mapdata = NUL;//移動できる場所データを入れる
		}
	}
}
//拠点戻る選択画面描画
void DrawKyotenExitSelect() {
	DrawBox(390, 270, 890, 420, GetColor(0, 0, 0), true);
	DrawBox(390, 270, 890, 420, GetColor(255, 255, 255), false);
	for (int i = 0; i < 3; i++) {
		if (bacselect[i].colorflg == 1) {
			DrawFormatString(bacselect[i].x, bacselect[i].y, 0x5D99FF, bacselect[i].name);
		}
		else {
			DrawFormatString(bacselect[i].x, bacselect[i].y, GetColor(255, 255, 255), bacselect[i].name);
		}
	}
}
//拠点戻る処理
void KyotenBag() {
	if (IsAbleToGo(player.x, player.y, player.muki) == 1) {
		//下を向いたとき下の現在マップデータを入れる
		if (player.muki == DOWN) {
			kyoten.mapdata = hatakemap[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE];
		}
	}
	//拠点戻る処理
	//[NUL=0]移動できる場所 [WALL=2}壁データ [EXIT=3]出口データ
	//kyoten.flg [true]プレイヤー移動ON:[false]プレイヤー移動off
	if (kyoten.mapdata == EXIT) {//プレイヤー下の現在のマップデータが出口データだったら
		kyoten.flg = true;//プレイヤー移動OFF
		kyoten.selectflg = true;//選択画面描画ON
		KyotenExitSelect();
	}
	else
	{//キーが押されたら出口データを入れる
		if (inp.left == true || inp.right == true || inp.up == true) {
			hatakemap[10][9] = EXIT;//出口の位置
			hatakemap[10][10] = EXIT;//出口の位置
			kyoten.flg = false;
			kyoten.mapdata = NUL;
		}
	}
	//選択画面描画ON:OFF処理
	if (kyoten.selectflg) { DrawKyotenExitSelect(); }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//当たり判定用処理
int IsAbleToGo(int x, int y, int muki) {
	if (muki == UP) {
		if (hatakemap[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE] == 1) {
			player.fremflg = true;
			return 1;
		}
		else if (hatakemap[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE] == 2 || (hatakemap[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE] == 3)) {
			player.fremflg = false;
			return 1;
		}
	}
	if (muki == DOWN) {
		if (hatakemap[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE] == 1) {
			player.fremflg = true;
			return 1;
		}
		else if (hatakemap[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE] == 2 || (hatakemap[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE] == 3)) {
			player.fremflg = false;
			return 1;
		}
	}
	if (muki == LEFT) {
		if (hatakemap[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1] == 1) {
			player.fremflg = true;
			return 1;
		}
		else if (hatakemap[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1] == 2 || (hatakemap[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1] == 3)) {
			player.fremflg = false;
			return 1;
		}
	}if (muki == RIGHT) {
		if (hatakemap[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1] == 1) {
			player.fremflg = true;
			return 1;
		}
		else if (hatakemap[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1] == 2 || (hatakemap[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1] == 3)) {
			player.fremflg = false;
			return 1;
		}
	}
	return 0;
}
// キーの入力状態を更新する
int gpUpdateKey() {
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			Key[i]++;     // 加算
		}
		else {              // 押されていなければ
			Key[i] = 0;   // 0にする
		}
	}
	return 0;
}
//デバック
void Debag() {
		//if (CheckSoundMem(HatakeSound.Jouro_SE) == false) {
		//PlaySoundMem(Mizu_SE, DX_PLAYTYPE_BACK,TRUE);//テスト用
		//PlaySoundMem(Yasai_SE, DX_PLAYTYPE_BACK,TRUE);//テスト用
		//}
	/*for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			DrawFormatString(j * CHIP_SIZE + 32, i * CHIP_SIZE + 32, GetColor(255, 255, 0), "%d", tane[i][j]);
			DrawBox(j * CHIP_SIZE, i * CHIP_SIZE, (j + 1) * CHIP_SIZE, (i + 1) * CHIP_SIZE, GetColor(255, 255, 255), FALSE);
		}
	}*/
	//for (int i = 0; i < 30; i++) {
	//	DrawFormatString(600, i * 20, GetColor(255, 255, 0), "[%d]Time[%d]", i + 1, Yasaidata[i].Timecount);
	//}
	//for (int i = 30; i < 54; i++) {
	//	DrawFormatString(750, (i % 30) * 20, GetColor(255, 255, 0), "[%d]Time[%d]", i + 1, Yasaidata[i].Timecount);
	//}

	//for (int i = 0; i < 30; i++) {
	//	DrawFormatString(900, i * 20, GetColor(255, 255, 0), "[%d]tmp[%d]", i + 1, Yasaidata[i].TmpCount);
	//}
	//for (int i = 30; i < 54; i++) {
	//	DrawFormatString(1050, (i % 30) * 20, GetColor(255, 255, 0), "[%d]tmp[%d]", i + 1, Yasaidata[i].TmpCount);
	//}
	/*for (int i = 0; i < 9;i++) {
		DrawFormatString(400, (20*i), GetColor(255, 255, 0), "値段[%d]", YasaiData_a[i].price);
		DrawFormatString(200, (20 * i), GetColor(255, 255, 0), "タイム[%d]", YasaiData_a[i].Timecount);
	}*///DrawFormatString(400, 230, GetColor(255, 255, 0), "ページフラグ [%d]", pageflg);
	//DrawFormatString(400, 230, GetColor(255, 255, 0), "作業種 [%d]", selectTane);
	//DrawFormatString(400, 250, GetColor(255, 255, 0), "作業ナンバー [%d]", selectNum);
	//DrawFormatString(400, 270, GetColor(255, 255, 0), "キーカウント[%d]", ykeycoun%2);
	//DrawFormatString(400, 290, GetColor(255, 255, 0), "ON 1 OFF 0");
	DrawFormatString(600, 310, GetColor(255, 255, 0), "更新ページ[%d]", Plantpageflg);
	
	//DrawFormatString(900, 330, GetColor(255, 255, 0), "畑出た時[%d]", Enter_Time / 60);
	//DrawFormatString(900, 350, GetColor(255, 255, 0), "畑を入った時[%d]", Exit_Time / 60);
	//DrawFormatString(900, 370, GetColor(255, 255, 0), "経過時間[%d}", Time_Yasai);
	//DrawFormatString(400, 430, GetColor(255, 255, 0), "player.RIGHT[%d]", Image_RIGHT);
	//DrawFormatString(400, 100, GetColor(255, 255, 0), "上[%d]", tane[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE]);
	//DrawFormatString(400, 150, GetColor(255, 255, 0), "下[%d]", tane[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE]);
	//DrawFormatString(400, 200, GetColor(255, 255, 0), "左[%d]", tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1]);
	//DrawFormatString(400, 250, GetColor(255, 255, 0), "右[%d]", tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1]);
	//DrawFormatString(400, 100, GetColor(255, 0, 0), "plantflg [%d]",plantflg);
	//DrawFormatString(400, 150, GetColor(255, 255, 0), "Nowyasai [%d]", Nowyasai);
	//DrawFormatString(400, 200, GetColor(255, 255, 0), "Mizu_yasainum [%d]", Mizu_yasainum);
	//DrawFormatString(400, 250, GetColor(255, 255, 0), "selectflg [%d]", selectflg);
	//GameSystem::Input_Time(0);//でる時間を入れるやつ　畑処理
}
//植える処理
void TanePlant() {
	//種のデータの中身を取得
	if (IsAbleToGo(player.x, player.y, player.muki) == 1 && player.fremflg == true) {
		if (player.muki == UP) {
			tanenum = tane[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE];
		}
		if (player.muki == DOWN) {
			tanenum = tane[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE];
		}
		if (player.muki == LEFT) {
			tanenum = tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1];
		}
		if (player.muki == RIGHT) {
			tanenum = tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1];
		}
	}
	else {
		tanenum = 0;
	}
	//データが0以外は植えられない
	if (tanenum != 0) {
		taneplantflg = false;
	}
	else {
		taneplantflg = true;
	}
	//データが0なら植えれる
	if (taneplantflg == true) {
		if (player.muki == UP) {
			tane[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE] = TaneNowyasai;
		}
		if (player.muki == DOWN) {
			tane[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE] = TaneNowyasai;
		}
		if (player.muki == LEFT) {
			tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1] = TaneNowyasai;
		}
		if (player.muki == RIGHT) {
			tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1] = TaneNowyasai;
		}
	}
}
void MizuPlant() {
	if (player.muki == UP) {
		tane[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE] = MizuNowyasai;
	}
	if (player.muki == DOWN) {
		tane[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE] = MizuNowyasai;
	}
	if (player.muki == LEFT) {
		tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1] = MizuNowyasai;
	}
	if (player.muki == RIGHT) {
		tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1] = MizuNowyasai;
	}
}
void SyukakuPlant() {
	if (player.muki == UP) {
		tane[player.y / CHIP_SIZE - 1][player.x / CHIP_SIZE] = SyukakuNowyasai;
	}
	if (player.muki == DOWN) {
		tane[player.y / CHIP_SIZE + 1][player.x / CHIP_SIZE] = SyukakuNowyasai;
	}
	if (player.muki == LEFT) {
		tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE - 1] = SyukakuNowyasai;
	}
	if (player.muki == RIGHT) {
		tane[player.y / CHIP_SIZE][player.x / CHIP_SIZE + 1] = SyukakuNowyasai;
	}
	YasaiJudgment();
}