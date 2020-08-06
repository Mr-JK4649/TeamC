#include "Casino.h"



void Casino_Draw(int width, int height) {
	//if (casino.flg) { casino.ImageInput(&casino); casino.flg = false; }
	
	/*”wŒi*/
	if(cas.Dragon_Tiger || cas.Casino_War)
		DrawExtendGraph(0, 0, width, height, casino.Casino_Table, 1);
	else DrawExtendGraph(0, 0, width, height, casino.background, 1);

	/*ƒJƒWƒm‚Ì•`‰æ*/
	cas.Draw();

	

}