#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>
#include <windows.h>

#include "GameSys.h"
void Status_Disp(void);
int Return_Item(int item_select);
void Menu_Item(int item_select);
void Use_Equipment_Item(int item_select);		//アイテム装備/使う
void Delete_Item(int item_select);				//アイテム削除

Dungeon dungeon;

void DungeonMap(int w, int h);

void DrawGameDungeon(int Width, int Height) {

	//一回だけ処理
	if (dungeon.flg) { dungeon.ImageInput(&dungeon); dungeon.flg = false; }
	/*if (cha.flg) { cha.Init(&cha, Width, Height); cha.flg = false; }*/
	if (ch.flg) { ch.Init(&ch); ch.flg = false; }

	DrawExtendGraph(0, 0, Width, Height, dungeon.background, 1);
	DrawExtendGraph(dungeon.move, dungeon.up, Width*4+dungeon.move, Height*2+dungeon.up, dungeon.stage, 1);

	/*キャラクターの描画と更新*/
	if(!menu.isMenu && !menu.isGage_Menu)
		ch.Disp(&ch);

	/*メニューを開く*/
	menu.Draw();
	if (menu.isMenu && !menu.isTIPS) { menu.Item_Kind(Return_Item(menu.item_select)); Status_Disp(); }	//メニューのフラグがtrueだったらメニューとステータスの表示
	if (menu.isItem_Menu) { Menu_Item(menu.item_select); }										//アイテムメニューを開く
	if (menu.isItem_Equip) { Use_Equipment_Item(menu.item_select); menu.isItem_Equip = false; }	//アイテムの装備、使用
	if (menu.isItem_Delete) { Delete_Item(menu.item_select); menu.isItem_Delete = false; }		//アイテムの削除
	if (menu.Move_Scene) {
		if (g_GameState != menu.scene_t) {
			//StopSoundMem(base.bgm);
			g_GameState = menu.scene_t;
		}
		menu.Move_Scene = false;
	}
	if (inp.start) menu.isMenu = !menu.isMenu;

	/*プレイヤーの移動*/
	if (!menu.isMenu && !menu.isGage_Menu)ch.Move(&ch);

	

	DungeonMap(Width, Height);
}

void DungeonMap(int w, int h) {
	
	//DrawBox(w / 5.1 + dungeon.move, h*1.09+ dungeon.up, w/1.09 + dungeon.move, h * 1.81 + dungeon.up, 0xEEE8AA, 1);
	//DrawExtendGraph(w/5+dungeon.move,  h*1.1+dungeon.up, w/1.1 +dungeon.move, h*1.8+ dungeon.up, dungeon.stage, 1);

}

