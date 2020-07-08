#pragma once


/******脱出ステージに使う変数******/
struct EscVar {
	
	//全ジャンル共通
	bool Lock1=false, Lock2=true, Lock3=true;		//脱出を可能にする為に必要な鍵
	bool isEvent = false;					//イベントのフラグ(trueの時はイベント発生中。)
	bool isObj = false;						//オブジェクトの画像を表示するフラグ
	bool LoadFlg = true;					//画像を一回だけ読み込むためのフラグ
	int alpha = 0;							//電気の点滅に使う変数
	int EveCount = 0;						//イベントの進行に使う変数
	int VecNum = 0;							//部屋のどこを向いているか (0：前、1：右、2：後ろ：3：左)
	int GraphNum = 0;						//画像を切り替える用のナンバー

	//ホラーのみ

};