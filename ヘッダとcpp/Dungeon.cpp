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
void Use_Equipment_Item(int item_select);		//�A�C�e������/�g��
void Delete_Item(int item_select);				//�A�C�e���폜

Dungeon dungeon;

void DungeonMap(int w, int h);

void DrawGameDungeon(int Width, int Height) {

	//��񂾂�����
	if (dungeon.flg) { dungeon.ImageInput(&dungeon); dungeon.flg = false; }
	/*if (cha.flg) { cha.Init(&cha, Width, Height); cha.flg = false; }*/
	if (ch.flg) { ch.Init(&ch); ch.flg = false; }

	DrawExtendGraph(0, 0, Width, Height, dungeon.background, 1);
	DrawExtendGraph(dungeon.move, dungeon.up, Width*4+dungeon.move, Height*2+dungeon.up, dungeon.stage, 1);

	/*�L�����N�^�[�̕`��ƍX�V*/
	if(!menu.isMenu && !menu.isGage_Menu)
		ch.Disp(&ch);

	/*���j���[���J��*/
	menu.Draw();
	if (menu.isMenu && !menu.isTIPS) { menu.Item_Kind(Return_Item(menu.item_select)); Status_Disp(); }	//���j���[�̃t���O��true�������烁�j���[�ƃX�e�[�^�X�̕\��
	if (menu.isItem_Menu) { Menu_Item(menu.item_select); }										//�A�C�e�����j���[���J��
	if (menu.isItem_Equip) { Use_Equipment_Item(menu.item_select); menu.isItem_Equip = false; }	//�A�C�e���̑����A�g�p
	if (menu.isItem_Delete) { Delete_Item(menu.item_select); menu.isItem_Delete = false; }		//�A�C�e���̍폜
	if (menu.Move_Scene) {
		if (g_GameState != menu.scene_t) {
			//StopSoundMem(base.bgm);
			g_GameState = menu.scene_t;
		}
		menu.Move_Scene = false;
	}
	if (inp.start) menu.isMenu = !menu.isMenu;

	/*�v���C���[�̈ړ�*/
	if (!menu.isMenu && !menu.isGage_Menu)ch.Move(&ch);

	

	DungeonMap(Width, Height);
}

void DungeonMap(int w, int h) {
	
	//DrawBox(w / 5.1 + dungeon.move, h*1.09+ dungeon.up, w/1.09 + dungeon.move, h * 1.81 + dungeon.up, 0xEEE8AA, 1);
	//DrawExtendGraph(w/5+dungeon.move,  h*1.1+dungeon.up, w/1.1 +dungeon.move, h*1.8+ dungeon.up, dungeon.stage, 1);

}

