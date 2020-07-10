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

Title title;

void DrawGameTitle(int Width, int Height) {

	//ˆê‰ñ‚¾‚¯‰Šú‰»
	if (title.flg) { title.ImageInput(&title); title.flg = false; }

	DrawExtendGraph(0, 0, Width, Height, title.image, 1);
	DrawGraph(50,150,title.logo,1);
	
	DrawBox(Width / 10 * 1, Height / 10 * 7, Width / 10 * 3, Height / 10 * 8,0x0000ff,1);
	
	if (inp.MouseX >= Width / 10 * 1 &&
		inp.MouseX <= Width / 10 * 3 &&
		inp.MouseY >= Height / 10 * 7 &&
		inp.MouseY <= Height / 10 * 8) {
		
		//if (inp.Lclick) g_GameState = GAME_BASE;
		if (inp.Lclick)SuperString(200,200,"ƒV[ƒ“‚ðØ‚è‘Ö‚¦‚Ü‚µ‚½B",0x000000,0,16);
	}

	/*DrawLine(0,Height/2,Width,Height/2,0xffffff,1);
	DrawLine(Width/2,0,Width/2,Height,0xffffff,1);*/
	//SuperString(Width / 3, Height / 4, "‚i‚j“`",0x000000,1,100);
	
}