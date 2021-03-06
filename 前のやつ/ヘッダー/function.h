#pragma once
//キー入力のやつ
void KeyInput(void);

// ゲーム初期化処理
void GameInit(void);

// キャラ選択シーン
void GameCSelect(int width, int height);

//ステージ選択シーン
void GameSSelect(int width, int height);

// 戦闘シーン
void DrawGameMain(int width, int height);
//void PlayerMove(int genre,struct chara *chara,int pl);

// ゲームタイトル描画処理
void DrawGameTitle(int width, int height);

// エンド描画処理
void DrawEnd(int width, int height);

// ゲームクリアーの処理
void DrawGameResult(int width, int height);

// ゲームオーバー描画処理
void DrawGameOver(int width, int height);

// 画像読み込み
int LoadImages();

//サウンド
int LoadSounds(void);


//デバッグ用
void DebugMode(int w, int h,int x,int y);