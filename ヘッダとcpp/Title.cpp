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

	const float w = (float)Width * 4.0 / 100.0;
	const float h = (float)Height / 100.0;

	//��񂾂�������
	if (title.flg) { title.ImageInput(&title); title.flg = false; }

	DrawExtendGraph(0, 0, Width, Height, title.image, 1);
	
	SetFontSize(20);

	DrawString(5, 5, "�r���h���t�F2020�N7��17��", 0xff0000, 1);

	SetFontSize(16);

	/*DrawFormatString(0, 0, 0x0000ff,"x=%d y=%d",inp.MouseX,inp.MouseY);*/
	
	if (inp.MouseX >= 750 &&
		inp.MouseX <= 1000 &&
		inp.MouseY >= 400 &&
		inp.MouseY <= 450 ) {
		
		if (inp.Lclick)
		{
			g_GameState = GAME_HATAKE;//title�̎n�߂���������ꍇ�A�Q�[�����C���֐i��
		}   
		
	}

	if (inp.MouseX >= 760 &&
		inp.MouseX <= 900 &&
		inp.MouseY >= 500 &&
		inp.MouseY <= 540) {

		if (inp.Lclick) {
			DxLib_End(); // title�̏I�����������ꍇ�A�Q�[��DX���C�u�����g�p�̏I�������I���֐i��
		}
		
	}
	
}