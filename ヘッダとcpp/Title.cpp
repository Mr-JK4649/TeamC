#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <wingdi.h>
#include <windows.h>

#include "Source.h"

extern int g_GameState;



Title title;

Chara chara1;
Chara chara2;

void DrawGameTitle(int Width, int Height) {
	if (title.flg) { title.ImageInput(&title); title.flg = false; }

	DrawGraph(0, 0, title.image, 1);
}