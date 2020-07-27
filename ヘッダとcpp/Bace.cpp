#include "Source.h"
#include "string.h"
#include "Input.h"
#include "header.h"

#include "Menu.h"

/*拠点で使う関数*/
#include "Base_Function.h"

#pragma warning(disable : 6385)

Menu menu;
Base base;


void DrawGameMain(int width, int height) {
	
	/*初期化*/
	if (base.flg) { base.ImageInput(&base); base.flg = false; }

	/*拠点の描画関数*/
	Base_Disp(width, height);										//拠点内の描画

	/*拠点の更新関数*/
	Base_Update(width, height);										//拠点内の移動、その他更新
	

}

/*拠点の表示*/
void Base_Disp(int width, int height) {
	/*背景表示*/
	DrawExtendGraph(base.move, 0, width * 4 + base.move, height, base.background, 1);

	/*キャラの表示*/
	Chara_Disp();

	/*街の影表示*/
	DrawExtendGraph(base.move, 0, width * 4 + base.move, height, base.shadow, 1);


	menu.Draw();
	if (menu.isMenu == true) {  menu.Item_Kind(Return_Item(menu.item_select)); Status_Disp(); }	//メニューのフラグがtrueだったらメニューとステータスの表示
	if (menu.isItem_Menu) { Menu_Item(menu.item_select); }										//アイテムメニューを開く
	if (menu.isItem_Equip) { Use_Equipment_Item(menu.item_select); menu.isItem_Equip = false; }	//アイテムの装備、使用
	if (menu.isItem_Delete) { Delete_Item(menu.item_select); menu.isItem_Delete = false; }		//アイテムの削除
	if (!str.setTex && inp.start) menu.isMenu = !menu.isMenu;		//文字ウィンドウが出てないときにスタートボタンを押すと、メニューフラグの切り替え

	DrawFormatString(5, 5, 0xffffff, "%d", inp.a);

}

/*拠点のシステム*/
void Base_Update(int width, int height) {

	/*キャラの移動など*/
	if (!menu.isMenu && !str.setTex && !menu.isBuilding_Enter)Chara_Update();

	/*建物の判定*/
	Building_Serihu(width, height);

	/*オブジェクトの範囲に入って調べた時*/
	if (str.TexNum != 99 && !menu.isMenu && inp.space == true) {
		if (str.setTex) str.Serihu_Skip_Fin();
		else str.setTex = true;
	}

	/*建物の入り口を調べた時の*/
	if (menu.Enter_Num != 99 && !menu.isMenu && inp.space == true) {
		menu.isBuilding_Enter =!menu.isBuilding_Enter;
		menu.Enter_Select = 0;
	}


	/*セリフを出す*/
	if (str.setTex) str.Serihu(Player_Serihu[str.TexNum], 15, height - (height / 4 - 10), 0xffffff, width / 40);

}

