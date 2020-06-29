#pragma once

enum GAME_MODE {
	GAME_TITLE,		//タイトル
	GAME_INIT,		//初期化
	GAME_END,		//エンド
	GAME_MAIN,		//ゲームメイン
	GAME_C_SELECT,	//キャラ選択
	GAME_S_SELECT,	//ステージ選択
	GAME_RESULT,	//リザルト
	GAME_OVER,		//ゲームオーバー(？)
	END = 99		//エンド用変数
};

class State {

public:
	enum GAME_MODE {
		GAME_TITLE,		//タイトル
		GAME_INIT,		//初期化
		GAME_END,		//エンド
		GAME_MAIN,		//ゲームメイン
		GAME_C_SELECT,	//キャラ選択
		GAME_S_SELECT,	//ステージ選択
		GAME_RESULT,	//リザルト
		GAME_OVER,		//ゲームオーバー(？)
		END = 99		//エンド用変数
	};
};