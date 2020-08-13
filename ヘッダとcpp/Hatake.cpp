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
enum Tane { KOMUGI_TANE = 10, JAGAIMO_TANE, NINJIN_TANE };
enum MIZU { KOMUGI_MIZU = 20, JAGAIMO_MIZU, NINJIN_MIZU };
enum eYASAI { KOMUGI = 30, JAGAIMO, NINJIN };
enum Page { MENU, MENU2, MENU3 ,MENU4,MENU5};
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
	int image=0;
};
struct YASAI{
	int x, y;//座標
	int count;//秒数
	int num = 0;//今の野菜データ保存するやつ
	bool flg;//増えているか
};
struct SELECTMENU {
	int x, y;
	char name[128];
	bool flg;
	bool colorflg;
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
//メニュー選択画面
SELECTMENU menu1[4] = {
	{400,310,"種をうえる",0,1},
	{400,330,"水をまく",0,0},
	{400,350,"収穫",0,0},
	{400,370,"バッグ",0,0} };
//メニュー種
SELECTMENU menutane[3] = {
	{400,310,"こむぎのたね",0,1},
	{400,330,"じゃがいものたね",0,0},
	{400,350,"にんじんのたね",0,0}};
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
int Plantpageflg = MENU3;
bool plantflg = false;//植えるときのフラグ
int drawdignum = 10;//描画するときに数字を調整する
int TaneNowyasai = 0;//現在の野菜データを入れるもの
int MizuNowyasai = 0;
int SyukakuNowyasai = 0;
///////////////////育つ用変数
bool mizuyari = false;
int Mizu_yasainum = 0;//水やりの時の野菜データを保存するやつ
//収穫用変数
int syukakunum = 0;//収穫できるかのデータ保存するやつ
//*****プロトタイプ宣言*****
void Game_Hatake(int Width, int Height);
void InitPlayer(void);//プレイヤー初期化
int IsAbleToGo(int x, int y, int muki);//当たり判定処理
void Player(int Width, int Height);//プレイヤー処理
int gpUpdateKey();//キー更新処理
void DrawFrem();//枠表示描画
void DrawHatake(int Width, int Height);//畑描画
void MoveYasai();//野菜処理
void DrawYasai();//野菜・種など描画
void MoveSelectTane();//種選択画面処理
void DrawSelectTane();//種選択画面描画
void MoveSelectMenu();//作業選択メニュー処理
void DrawSelectMenu(); //作業選択メニュー描画
void YasaiMizuMove();
void MoveMizu();//水をあげる処理
void Debag();//デバック描画処理
//育つ処理
void Growth();//成長処理
void YasaiCountFlg();
void Count();//カウント
//拠点処理
void DrawKyotenExitSelect();
void KyotenExitSelect();
void KyotenBag();
//収穫処理
void Syukaku();
void SyuukakuMove();
void InitselectColor();
//野菜データ
void InitYasaiData();
//植える処理
void TanePlant();
void MizuPlant();
void SyukakuPlant();
//バック画面
//void Bag();//ここまで8/06
//*****処理呼び出し*****
void Game_Hatake(int Width, int Height) {
	SetFontSize(20);//文字サイズ確認
	if (flg) {
		InitPlayer(); flg = false;	//一回のみ初期化
		InitYasaiData();
	}
	gpUpdateKey();//入力更新
	Player(Width, Height);//プレイヤー処理関数
	DrawHatake(Width, Height);//描画処理
	//作業セレクトメニュー開く処理
	if (Key[KEY_INPUT_A] == 1) {
		selectNum = 0; //開いたときに現在選択している場所を初期化
		selectTane = 0;
		selectflg = true; //Aを押したとき作業選択画面開く
		initflg = true;
	}else if (Key[KEY_INPUT_S] == 1) {
		selectflg = false; //Sを押したとき作業選択画面閉じる
		pageflg = MENU;
	}
	//処理セレクトフラグONならセレクト画面開く
	switch (pageflg)
	{
	case MENU:if (selectflg == true)MoveSelectMenu(); break;//作業選択画面
	case MENU2:if (selectflg == true)MoveSelectTane(); break;//種選択画面
	case MENU3: MoveMizu(); break;//水をあげる画面
	case MENU4: Syukaku(); break;//収穫処理
	/*case MENU5: Bag(); break;*/
	}
	if (pageflg == MENU2) { Plantpageflg = MENU2; }
	else if (pageflg == MENU3) { Plantpageflg = MENU3; }
	else if (pageflg == MENU4) { Plantpageflg = MENU4; }
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
}
//野菜データの初期化
void InitYasaiData(void) {
	int i = 2;//行
	int j = 2;//列
	//ほしい値↓**************************
	//   行 列
	//2行[2][2]～[2][16]
	//3行[3][2]～[3][16]
	//7行[7][2]～[7][7] [7][12]～[7][17]
	//8行[8][2]～[8][7] [8][12]～[8][17] 合計54
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
		Yasaidata[s].count = 0;
		Yasaidata[s].flg = false;
		Yasaidata[s].y = i;//行を代入
		Yasaidata[s].num = 0;
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
	if (selectflg == false && kyoten.flg == false) {
		if (player.x % CHIP_SIZE == 0 && player.y % CHIP_SIZE == 0) {
			player.walking_flg = true;
			if (Key[KEY_INPUT_UP] > 1) {
				player.muki = UP;//上向きフラグ
			}
			else if (Key[KEY_INPUT_DOWN] > 1) {
				player.muki = DOWN;//下向きフラグ
			}
			else if (Key[KEY_INPUT_LEFT] > 1) {
				player.muki = LEFT;//左向きフラグ
			}
			else if (Key[KEY_INPUT_RIGHT] > 1) {
				player.muki = RIGHT;//右向きフラグ
			}
			else {
				player.walking_flg = false;//歩かないフラグ
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
		}
		MoveYasai();
	}
	//画面外歩けない処理
	if (player.x < 0) {
		player.x = 0;
	}
	else if (player.y < 0) {
		player.y = 0;
	}

	//デバック表示
	if (Key[KEY_INPUT_D] == 1) {
		dflg = true;
	}else if (Key[KEY_INPUT_B] == 1) {
		dflg = false;
	}
}
//*****畑描画処理*****
void DrawHatake(int Width, int Height) {
	if (hatake.flg) { hatake.ImageInput(&hatake); hatake.flg = false; }
	//プレイヤーアニメーション処理******************************************************
	if (player.muki == UP) { player.image_muki = Image_UP; }
	else if (player.muki == DOWN) { player.image_muki = Image_DOWN; }
	else if (player.muki == RIGHT) { player.image_muki = Image_RIGHT;}
	else if (player.muki == LEFT) { player.image_muki = Image_LEFT;}
	player.image = ((player.x % CHIP_SIZE + player.y % CHIP_SIZE) / 21) + player.image_muki;
	//**********************************************************************************
	DrawGraph(0, 0, hatake.image, TRUE);
	DrawGraph(player.x, player.y, hatake.testimage[player.image], TRUE);
	DrawYasai();
	//フレーム表示
	DrawFrem();
}
//野菜判定
void MoveYasai() {
	if (Key[KEY_INPUT_X] == 1) {
		if (IsAbleToGo(player.x, player.y, player.muki) == 1 && player.fremflg == true && plantflg == true) {
			switch (Plantpageflg) {
			case MENU2:TanePlant(); break;//種植える処理
			case MENU3:MizuPlant(); if (Plantpageflg == MENU3)mizuyari = true; break;//水植える処理
			case MENU4:SyukakuPlant(); break;
			}
		}
	}
}
//野菜描画
void DrawYasai(){
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (tane[i][j] != 0) {
				if (tane[i][j] >= KOMUGI_TANE && tane[i][j] <= NINJIN_TANE) {//種描画
					DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, hatake.tane[tane[i][j] % drawdignum], FALSE);
				}
				else if (tane[i][j] >= KOMUGI_MIZU && tane[i][j] <= NINJIN_MIZU){//水やり描画
					DrawGraph(j* CHIP_SIZE, i* CHIP_SIZE, hatake.mizu[tane[i][j] % drawdignum], FALSE);
				}
				else if(tane[i][j] >= KOMUGI && tane[i][j] <= NINJIN) {
					DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE, hatake.yasai[tane[i][j] % drawdignum], FALSE);//野菜描画 
				}
			}
		}
	}
}
//**************************************選択画面処理**************************************************************************************
//選択されている場所の色初期化
void InitselectColor() {
	for (int i = 0; i < 4; i++) {
		if (i == 0) {
			menu1[i].colorflg = 1;
		}
		else {
			menu1[i].colorflg = 0;
		}
	}
}
//植える・水やり・収穫・バッグ・選択画面処理
void MoveSelectMenu(){
	//選択画面初期化
	if (initflg) {
		InitselectColor();
		initflg = false;
	}
	if (Key[KEY_INPUT_DOWN] == 1) {
		selectNum = (selectNum + 1) % 4;
	}
	if (Key[KEY_INPUT_UP] == 1) {
		selectNum = (selectNum + 3) % 4;
	}
	if (Key[KEY_INPUT_DOWN] == 1 || Key[KEY_INPUT_UP] == 1) {
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
	if (Key[KEY_INPUT_X] == 1) {
		if (selectNum == 0) {
			pageflg = MENU2;
		}
		else if (selectNum == 1) {
			pageflg = MENU3;
			selectflg = false;
		}
		else if (selectNum == 2) {
			pageflg = MENU4;
			selectflg = false;
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
				DrawFormatString(menu1[i].x, menu1[i].y, GetColor(0, 0, 255), menu1[i].name);
		}
		else {
			DrawFormatString(menu1[i].x, menu1[i].y, GetColor(255, 255, 255), menu1[i].name);
		}
	}
}

//種選択画面処理
void MoveSelectTane() {
	if (Key[KEY_INPUT_DOWN] == 1) {
		selectTane = (selectTane + 1) % 3;
	}
	if (Key[KEY_INPUT_UP] == 1) {
		selectTane = (selectTane + 2) % 3;
	}
	if (Key[KEY_INPUT_DOWN] == 1 || Key[KEY_INPUT_UP] == 1) {
		for (int i = 0; i < 3; i++) {
			if (i == selectTane) {
				menu1[i].colorflg = 1;
			}
			else {
				menu1[i].colorflg = 0;
			}
		}
	}
	//選択された種を処理
	DrawSelectTane();
	if (Key[KEY_INPUT_X] == 1) {
		if (selectTane == 0) {
			TaneNowyasai = KOMUGI_TANE;
		}
		else if (selectTane == 1) {
			TaneNowyasai = JAGAIMO_TANE;
		}
		else if (selectTane == 2) {
			TaneNowyasai = NINJIN_TANE;
		}
		plantflg = true;
		selectflg = false;
		pageflg = MENU;
	}
}
void DrawSelectTane() {
	DrawBox(390, 300, 610, 420, GetColor(0, 0, 0), true);
	DrawBox(390, 300, 610, 420, GetColor(255, 255, 255), false);

	for (int i = 0; i < 3; i++) {
		if (menu1[i].colorflg == 1) {
			DrawFormatString(menutane[i].x, menutane[i].y, GetColor(0, 0, 255), menutane[i].name);
		}
		else {
			DrawFormatString(menutane[i].x, menutane[i].y, GetColor(255, 255, 255), menutane[i].name);
		}
	}
}
//*********************************　水を上げる処理********************************************************************************
void YasaiMizuMove() {
	if (KOMUGI_TANE == Mizu_yasainum) { MizuNowyasai = KOMUGI_MIZU; }
	else if (JAGAIMO_TANE == Mizu_yasainum) { MizuNowyasai = JAGAIMO_MIZU; }
	else if (NINJIN_TANE == Mizu_yasainum) { MizuNowyasai = NINJIN_MIZU;}
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
	if(mizuyari == true){
		for (int i = 0; i < 54; i++) {
			if (IsAbleToGo(player.x, player.y, player.muki) == 1) {
				if (player.fremflg == true) {
					if (Yasaidata[i].y == player.y/CHIP_SIZE - 1 && Yasaidata[i].x == player.x / CHIP_SIZE) {//上
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
void Count(){
	for (int i = 0; i < 54;i++) {
		if (Yasaidata[i].flg == true) {
			Yasaidata[i].count++;
		}
	}
}
//成長データ
void Growth() {
	for (int i = 0; i < 54; i++) {//1分
		if (Yasaidata[i].count >= 3600) {
			if (Yasaidata[i].num == KOMUGI_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = KOMUGI;}
			if (Yasaidata[i].num == JAGAIMO_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = JAGAIMO;}
			if (Yasaidata[i].num == NINJIN_MIZU) { tane[Yasaidata[i].y][Yasaidata[i].x] = NINJIN;}
			Yasaidata[i].num = 0;//numのデータ初期化
			Yasaidata[i].count = 0;
			Yasaidata[i].flg = false;
		}
	}
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
		SyuukakuMove();
	}
}
void SyuukakuMove() {
	if (KOMUGI == syukakunum) {
		SyukakuNowyasai = 0; plantflg = true;
	}
	else if (JAGAIMO == syukakunum) {
		SyukakuNowyasai = 0; plantflg = true;
	}
	else if (NINJIN == syukakunum) {
		SyukakuNowyasai = 0; plantflg = true;
	}
	else { plantflg = false; }
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
	if (Key[KEY_INPUT_LEFT] == 1) {
		selectExit = (selectExit + 1) % 2;
	}
	if (Key[KEY_INPUT_RIGHT] == 1) {
		selectExit = (selectExit + 1) % 2;
	}
	if (Key[KEY_INPUT_LEFT] == 1 || Key[KEY_INPUT_RIGHT] == 1) {
		for (int i = 0; i < 2; i++) {
			if (i == selectExit) {
				bacselect[i].colorflg = 1;
			}
			else {
				bacselect[i].colorflg = 0;
			}
		}
	}
	if (Key[KEY_INPUT_X] == 1) {
		if (selectExit == 0) {
			g_GameState = GAME_HOME;
			/*GameSystem::Input_Time(1);*/
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
	for (int i = 0; i <3; i++) {
		if (bacselect[i].colorflg == 1) {
			DrawFormatString(bacselect[i].x, bacselect[i].y, GetColor(0, 0, 255), bacselect[i].name);
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
	}else
	{//キーが押されたら出口データを入れる
		if (Key[KEY_INPUT_LEFT] == 1 || Key[KEY_INPUT_RIGHT] == 1 || Key[KEY_INPUT_UP] == 1) {
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
int IsAbleToGo(int x,int y,int muki){
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
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			DrawFormatString(j * CHIP_SIZE + 32, i * CHIP_SIZE + 32, GetColor(255, 255, 0), "%d", tane[i][j]);
			DrawBox(j * CHIP_SIZE, i * CHIP_SIZE, (j + 1) * CHIP_SIZE, (i + 1) * CHIP_SIZE, GetColor(255, 255, 255), FALSE);
		}
	}
	//for (int i = 0; i < 30; i++) {
	//	DrawFormatString(100, i * 20, GetColor(255, 255, 0), "[%d]flg[%d]", i + 1, Yasaidata[i].num);
	//}
	//for (int i = 30; i < 54; i++) {
	//	DrawFormatString(300, (i % 30) * 20, GetColor(255, 255, 0), "[%d]flg[%d]", i + 1, Yasaidata[i].num);
	//}
	//DrawFormatString(400, 210, GetColor(255, 255, 0), "植える時のページフラグ [%d]", Plantpageflg);
	//DrawFormatString(400, 230, GetColor(255, 255, 0), "ページフラグ [%d]", pageflg);
	//DrawFormatString(400, 250, GetColor(255, 255, 0), "収穫用保存 [%d]", syukakunum);
	//DrawFormatString(400, 270, GetColor(255, 255, 0), "現在の種 [%d]", TaneNowyasai);
	/*DrawFormatString(400, 310, GetColor(255, 255, 0), "現在の収穫[%d]", SyukakuNowyasai);*/
	//DrawFormatString(400, 370, GetColor(255, 255, 0), "player.DOWN[%d]", Image_DOWN);
	//DrawFormatString(400, 390, GetColor(255, 255, 0), "player.UP[%d]", Image_UP);
	//DrawFormatString(400, 410, GetColor(255, 255, 0), "player.LEFT[%d]", Image_LEFT);
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
}