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

enum Genre {
	HORROR,			//ホラー
	ACTION,			//アクション
	RPG,			//RPG
	NOVEL,			//ノベル
	CARD,			//カード
	STEALTH,		//ステルス
	SIMULATION,		//シミュレーション
	SHOOTING,		//シューティング
	PUZZLE,			//パズル
	MUSIC,			//音楽
	RACE1,			//レース(レーサー)
	RACE2			//レース(レースオフィシャル)
};