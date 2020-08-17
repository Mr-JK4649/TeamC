#include "Dungeon.h"

Dungeon_Sys d_sys;

void DrawGameDungeon(int Width, int Height) {

	////一回だけ処理
	//if (dungeon.flg) { dungeon.ImageInput(&dungeon); dungeon.flg = false; }
	///*if (cha.flg) { cha.Init(&cha, Width, Height); cha.flg = false; }*/
	//if (ch.flg) { ch.Init(&ch); ch.flg = false; }


	DrawExtendGraph(0, 0, Width, Height, dungeon.background, 1);
	if (!ch.isBattle) {
		DrawExtendGraph(dungeon.move, dungeon.up, Width * 4 + dungeon.move, Height * 2 + dungeon.up, dungeon.stage, 1);
	}


	/*キャラクターの描画と更新*/
	ch.Disp(&ch);
	/*プレイヤーの移動*/
	if (!menu.isMenu && !menu.isGage_Menu && !ch.isBattle && !d_sys.Effect_Flg)ch.Move(&ch);

	/*雑魚的エンカウント*/
	if (!ch.isBattle && ++d_sys.Cool_Time > 300) {
		if (GetRand(10) == 0) {
			d_sys.Enemy_Num = GetRand(2) + 4 * d_sys.Dungeon_Num;
			//d_sys.Enemy_Num = 9;
			ch.isBattle = true;
			d_sys.Cool_Time = 0;
		}
	}

	/*敵の描画と更新*/
	if (!ch.isBattle) {
		d_sys.Dungeon_Enemy_Disp();
		d_sys.Dungeon_Enemy_Update();
	}
	else {
		d_sys.Battle_Draw();
		d_sys.Battle_Update();
	}
	

	/*メニューを開く*/
	menu.Draw();
	if (menu.isMenu && !menu.isTIPS) { menu.Item_Kind(Return_Item(menu.item_select)); Status_Disp(); }	//メニューのフラグがtrueだったらメニューとステータスの表示
	if (menu.isItem_Menu) { Menu_Item(menu.item_select); }										//アイテムメニューを開く
	if (menu.isItem_Equip) { Use_Equipment_Item(menu.item_select); menu.isItem_Equip = false; }	//アイテムの装備、使用
	if (menu.isItem_Delete) { Delete_Item(menu.item_select); menu.isItem_Delete = false; }		//アイテムの削除
	if (menu.Move_Scene) {
		if (g_GameState != menu.scene_t) {
			//StopSoundMem(dungeon.bgm);
			g_GameState = menu.scene_t;
			ch.init_flg = true;
			ch.isBattle = false;
			d_sys.Cool_Time = 0;
			d_sys.Battle_Finish_Process();
		}
		menu.Move_Scene = false;
	}
	/*else if (CheckSoundMem(dungeon.bgm) == false) {
		PlaySoundMem(dungeon.bgm,DX_PLAYTYPE_BACK,1);
	}*/
	if (inp.start) menu.isMenu = !menu.isMenu;

	
	
	

	DungeonMap(Width, Height);
}

void DungeonMap(int w, int h) {
	
	//DrawBox(w / 5.1 + dungeon.move, h*1.09+ dungeon.up, w/1.09 + dungeon.move, h * 1.81 + dungeon.up, 0xEEE8AA, 1);
	//DrawExtendGraph(w/5+dungeon.move,  h*1.1+dungeon.up, w/1.1 +dungeon.move, h*1.8+ dungeon.up, dungeon.stage, 1);

}

