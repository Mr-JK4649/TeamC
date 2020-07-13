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

Bace bace;

void DrawGameMain(int width, int height) {
	
	if (bace.flg) { bace.ImageInput(&bace); bace.flg = false; }

	DrawExtendGraph(bace.move, 0, width * 4+bace.move, height, bace.background, 1);

	str.SuperString(200,200,"‚±‚ê‚Í‹’“_‚Å‚·",0xffffff,0,48);

	if (inp.right) { bace.move -= 5; }
	if (inp.left) { bace.move += 5; }

}