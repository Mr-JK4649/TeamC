#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>
#include <windows.h>

#include "Source.h"
#include "string.h"
#include "Input.h"
#include "header.h"
#include "character.h"

Dungeon dungeon;
Chara cha;
//void DungeonHitHantei(Chara* p);
void DungeonMap(int w, int h);

void DrawGameDungeon(int Width, int Height) {

	//一回だけ処理
	if (dungeon.flg) dungeon.ImageInput(&dungeon); dungeon.flg = false;
	/*if (cha.flg) { cha.Init(&cha, Width, Height); cha.flg = false; }*/
	if (cha.flg) { cha.Init(&cha); cha.flg = false; }
	DrawExtendGraph(0, 0, Width, Height, dungeon.background, 1);
	DrawExtendGraph(dungeon.move, dungeon.up, Width*4+dungeon.move, Height*2+dungeon.up, dungeon.stage, 1);

	/*キャラクターの描画と更新*/
	cha.Disp(&cha);

	/*プレイヤーの移動*/
	if (!str.setTex)cha.Move(&cha);

	DrawFormatString(100, 100, 0xFFFFFF, "x:%4d y:%4d", inp.MouseX, inp.MouseY);

	DungeonMap(Width, Height);
}

void DungeonMap(int w, int h) {
	
	//DrawBox(w / 5.1 + dungeon.move, h*1.09+ dungeon.up, w/1.09 + dungeon.move, h * 1.81 + dungeon.up, 0xEEE8AA, 1);
	//DrawExtendGraph(w/5+dungeon.move,  h*1.1+dungeon.up, w/1.1 +dungeon.move, h*1.8+ dungeon.up, dungeon.stage, 1);

}

