#include "Source.h"
#include "string.h"
#include "Input.h"
#include "header.h"

#include "Menu.h"

/*拠点で使う関数*/
#include "Base_Function.h"

#pragma warning(disable : 6385)

Menu menu; 

void DrawGameMain(int width, int height) {
	

	/*拠点の描画関数*/
	Base_Disp(width, height);						//拠点内の描画

	/*BGMとシーン移動の処理*/
	/*if (menu.Move_Scene) {
		if (g_GameState != menu.scene_t) {
			StopSoundMem(base.bgm);
			g_GameState = menu.scene_t;
			//Move_Scene_Init_Flg();
		}
		menu.Move_Scene = false;
	}
	else if (CheckSoundMem(base.bgm) == false) {
		PlaySoundMem(base.bgm, DX_PLAYTYPE_BACK, 1);
	}*/

	/*拠点の更新関数*/
	if(!menu.Result_DWork_Flg && !menu.Result_FWork_Flg && !menu.isGage_Menu && !menu.isTutorial && !menu.isDevilsCome)
		Base_Update(width, height);					//拠点内の移動、その他更新
	

	if (menu.isTutorial) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 0, width, height,0x000000,TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		
		const float w100 = (float)width / 100.0f;
		const float h100 = (float)height / 100.0f;

		DrawRoundRect(w100 * 21, h100, w100 * 80, h100 * 90, 10, 10, 0x444444, 1);
		DrawRoundRect(w100 * 21, h100, w100 * 80, h100 * 90, 10, 10, 0xaaaaaa, 0);
		DrawRoundRect(w100 * 21 + 1, h100 + 1, w100 * 80 - 1, h100 * 90 - 1, 10, 10, 0xffffff, 0);

		
		DrawExtendGraph(w100 * 22, h100 * 4, w100 * 79, h100 * 82, base.Tutorial_img[menu.Tutorial_Select], 1);
		DrawFormatString(w100 * 67, h100 * 85, 0xffffff, "Pages %d / %d", menu.Tutorial_Select + 1, 3);

		if (inp.f_left) {
			PlaySoundMem(se.SelectMove_SE,DX_PLAYTYPE_BACK,TRUE);
			if (--menu.Tutorial_Select < 0) menu.Tutorial_Select = 2;
		}
		if (inp.f_right) {
			PlaySoundMem(se.SelectMove_SE, DX_PLAYTYPE_BACK, TRUE);
			if (++menu.Tutorial_Select > 2) menu.Tutorial_Select = 0;
		}

		if (inp.cancel || inp.space) {
			PlaySoundMem(se.Cansel_SE, DX_PLAYTYPE_BACK, TRUE);
			menu.Tutorial_Select = 0;
			menu.isTutorial = false;
		}
		
	}

}

/*拠点の表示*/
void Base_Disp(int width, int height) {
	/*背景表示*/


	if(Return_Base_Status(1) >= 100) DrawExtendGraph(base.move, 0, width * 4 + base.move, height, base.background2, 1);
	else DrawExtendGraph(base.move, 0, width * 4 + base.move, height, base.background, 1);


	/*キャラの表示*/
	Chara_Disp();


	/*街の影表示*/
	DrawExtendGraph(base.move, 0, width * 4 + base.move, height, base.shadow, 1);


	menu.Draw();
	if (menu.isMenu && !menu.isTIPS) {  menu.Item_Kind(Return_Item(menu.item_select)); Status_Disp(); }	//メニューのフラグがtrueだったらメニューとステータスの表示
	if (menu.isItem_Menu) { Menu_Item(menu.item_select); }										//アイテムメニューを開く
	if (menu.isItem_Equip) { Use_Equipment_Item(menu.item_select); menu.isItem_Equip = false; }	//アイテムの装備、使用
	if (menu.isItem_Delete) { Delete_Item(menu.item_select); menu.isItem_Delete = false; }		//アイテムの削除
	if (!str.setTex &&
		inp.start &&
		!menu.Result_DWork_Flg &&
		!menu.Result_FWork_Flg &&
		!menu.isTIPS &&
		!menu.isGage_Menu) menu.isMenu = !menu.isMenu;		//文字ウィンドウが出てないときにスタートボタンを押すと、メニューフラグの切り替え

	/*セリフを出す*/
	if (str.setTex) str.Serihu(Player_Serihu[str.TexNum], 15, height - (height / 4 - 10), 0xffffff, width / 40);

	//DrawFormatString(5, 5, 0xffffff, "%d", inp.a);
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
		if (!menu.isBuilding_Enter) {
			PlaySoundMem(base.BC_window_pop, DX_PLAYTYPE_BACK, TRUE);
			menu.isBuilding_Enter = true;\
		}
		else menu.isBuilding_Enter = false;
		menu.Enter_Select = 0;
	}

}

