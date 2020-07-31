#pragma once

//拠点の描画と更新
void Base_Disp(int width,int height);
void Base_Update(int width, int height);

//セリフの発動とトリガー
void Building_Serihu(int width,int height);

//キャラクターの描画と更新
void Chara_Disp(void);
void Chara_Update(void);
int Return_Base_Status(int num);

/*メニュー用のステータスを取得する関数*/
void Status_Disp(void);
int Return_Item(int item_select);
void Menu_Item(int item_select);
void Use_Equipment_Item(int item_select);		//アイテム装備/使う
void Delete_Item(int item_select);				//アイテム削除


char Player_Serihu[5][200] = { "ここは検問所ね。\n街を出入りする際に怪しい動きをしたら逮捕されちゃうかも。\n、、、、、、、、、、、なんてね。",		//検問所で出るセリフ
							   "カジノ建設予定地と書いてあるわ。\n出来たら一回くらい来てみてもいいかもしれないわね。",						//カジノ(未建設)で出るセリフ
							   "a",																											//カジノ(建設済み)で出るセリフ
							   "これは仕事紹介所の掲示板ね。\n色んな仕事の依頼が貼ってあるわ。",											//仕事紹介所の掲示板で出るセリフ
							   "お店で取り扱ってる商品の値段が書いてあるわ。\n斧が250ゴールド、盾が300ゴールド、回復薬が5ゴールド。\n安いのか高いのか分からないわね・・・・・。" };	//店で出るセリフ

