#include "Casino.h"



void Casino_Draw(int width, int height) {
	if (casino.flg) { casino.ImageInput(&casino); casino.flg = false; }

	DrawExtendGraph(0, 0, width, height, casino.background, 1);

	

}