#pragma once

//キー入力のやつ
void KeyInput(void);

//ゲームシーケンス？
void Story(int width, int height);

// ゲーム初期化処理
void GameInit(void);

//ステージ選択シーン
void GameSSelect(int width, int height);

// 拠点シーン
void DrawGameMain(int width, int height);

/*ゲーム進行に必要な数値を制御する*/
void GameSystem(void);

/*カジノ*/
void Casino_Draw(int width, int height);

//仕事紹介所
void Work_Draw(int width, int height);

//店のシーン
void Shop_Draw(int width, int height);

//自宅
void Home_Draw(int width, int height);

// ゲームタイトル描画処理
void DrawGameTitle(int width, int height);

// エンド描画処理
void DrawEnd(int width, int height);

//ゲームクレジット
void DrawCredit(int width, int height);

// ゲームクリアーの処理
void DrawGameResult(int width, int height);

// ゲームオーバー描画処理
void DrawGameOver(int width, int height);

//構造体の初期化
void Init(void);

//ダンジョン
void DrawGameDungeon(int Width, int Height);