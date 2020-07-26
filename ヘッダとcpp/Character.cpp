#include "DxLib.h"

#include "character.h"

Chara ch;									
Weapon Hand = { 1.0f,-99,-99,"","なし",0};													//空気の剣。手ごたえ？忘れてきました。
Weapon Wood_Sword = { 1.2f,20,30,"images/タピオカミルクティー.jpg" ,"木の剣",1};				//木の剣
Weapon Iron_Sword = { 1.4f,50,75,"images/タピオカミルクティー.jpg" ,"鉄の剣",2};				//鉄の剣
Weapon Exca_Sword = { 2.0f,100,150,"images/タピオカミルクティー.jpg" ,"エクスカリバー",3};	//エクスカリバー
Weapon Wood_Rod = { 0.5f,200,300,"images/タピオカミルクティー.jpg" ,"木のロッド",4};			//木のロッド
Weapon Iron_Rod = { 1.0f,600,900,"images/タピオカミルクティー.jpg","鉄のロッド" ,5};			//鉄のロッド
Weapon wep = Hand;																			//武器構造体のあれ
Weapon wep_work;																			//武器避難用のあれ

Shield Air = { 1.0f,-99,-99,"","なし",0 };													//空気の盾。これで防げると思ったら大間違いです。
Shield Wood_Shield = { 3.0f,100,200,"images/タピオカミルクティー.jpg","木の盾" ,6};			//木の盾
Shield Iron_Shield = { 8.0f,400,800,"images/タピオカミルクティー.jpg","鉄の盾" ,7};			//鉄の盾
Shield Tapi_Shield = { 20.0f,2000,4000,"images/タピオカミルクティー.jpg","タピオカの盾" ,8};	//タピオカの盾　強い(確信)
Shield shi = Air;																			//盾構造体のあれ
Shield shi_work;																			//盾避難用のあれ

/*キャラの表示*/
void Chara_Disp() {
	if (ch.flg) { ch.Init(&ch); ch.flg = false; }
	
	/*キャラクターの描画*/
	ch.Disp(&ch);
}

/*キャラの移動*/
void Chara_Update() {

	/*プレイヤーの移動*/
	ch.Move(&ch);

	/*経過時間*/
	ch.Add_Time(&ch);
}

/*ステータスの表示*/
void Status_Disp() {
	ch.Menu_Status_Disp(&ch);
}

/*アイテム一覧の表示*/
void Menu_Item(int item_select) {

	char item_name[51];
	unsigned int color = 0xffffff;

	for (int i = 0; i < 10; i++) {
		
		SetFontSize(ch.size * 2);

		switch (ch.Menu_Items_Disp(&ch, i))
		{
			case Chara::Wood_Sword:		strcpy_s(item_name,Wood_Sword.Weapon_name);		break;
			case Chara::Iron_Sword:		strcpy_s(item_name,Iron_Sword.Weapon_name);		break;
			case Chara::Excalibur:		strcpy_s(item_name,Exca_Sword.Weapon_name);		break;
			case Chara::Wood_Rod:		strcpy_s(item_name,Wood_Rod.Weapon_name);		break;
			case Chara::Iron_Rod:		strcpy_s(item_name,Iron_Rod.Weapon_name);		break;
			case Chara::Wood_Shield:	strcpy_s(item_name,Wood_Shield.Shield_name);	break;
			case Chara::Iron_Shield:	strcpy_s(item_name,Iron_Shield.Shield_name);	break;
			case Chara::Tapi_Shield:	strcpy_s(item_name,Tapi_Shield.Shield_name);	break;
			case Chara::Portion:		strcpy_s(item_name,"ポーション");				break;
			case Chara::Tapi_MT:		strcpy_s(item_name,"タピオカＭＴ");				break;
			default:					strcpy_s(item_name, "　　　　　　　　ーーー　　　　　　　　");		break;
		}

		if (i == item_select) color = 0x6666ff;

		DrawString(ch.w5 * 1 + 11, ch.h4 + 6 + (ch.size * 3) * i, item_name, color, 1);

		color = 0xffffff;
	}
}

/*選択したアイテムの種類*/
int Return_Item(int item_select) {
	
	return ch.Menu_Items_Disp(&ch, item_select);
}

int Return_Base_Status(int num) {
	return ch.Return_Base_Status(&ch, num);
}

/*アイテム装備い使用*/
void Use_Equipment_Item(int item_select) {

	int item = ch.Menu_Items_Disp(&ch, item_select);
	
	if (item > 0 && item <= Chara::Iron_Rod) {				//装備品なら装備
		wep_work = wep;							//武器の避難
		switch (item)
		{
			case Chara::Wood_Sword:	wep = Wood_Sword;	break;
			case Chara::Iron_Sword:	wep = Iron_Sword;	break;
			case Chara::Excalibur:	wep = Exca_Sword;	break;
			case Chara::Wood_Rod:	wep = Wood_Rod;		break;
			case Chara::Iron_Rod:	wep = Iron_Rod;		break;
			default:	ch.Delete_Item(&ch,item_select);	break;
		}

		ch.Input_Item(&ch, item_select, wep_work.serial_num);
	}
	else if (item <= Chara::Tapi_Shield) {
		shi_work = shi;
		switch (item)
		{
			case Chara::Wood_Shield:	shi = Wood_Shield;	break;
			case Chara::Iron_Shield:	shi = Iron_Shield;	break;
			case Chara::Tapi_Shield:	shi = Tapi_Shield;	break;
			default:	ch.Delete_Item(&ch,item_select);	break;
		}

		ch.Input_Item(&ch, item_select, shi_work.serial_num);
	}
	else if (item <= Chara::Tapi_MT) {
		
		switch (item) 
		{
		case Chara::Portion: ch.Healing_Life(&ch, Chara::Portion); break;
		case Chara::Tapi_MT: ch.Healing_Life(&ch, Chara::Tapi_MT); break;
		}

		ch.Delete_Item(&ch, item_select);
	}

	
	
}

/*アイテム削除*/
void Delete_Item(int item_select) {
	ch.Delete_Item(&ch,item_select);
}