#include "Casino.h"



void Casino_Draw(int width, int height) {
	
	/*�w�i*/
	if(cas.Dragon_Tiger || cas.Casino_War)
		DrawExtendGraph(0, 0, width, height, casino.Casino_Table, 1);
	else DrawExtendGraph(0, 0, width, height, casino.background, 1);

	/*�J�W�m�̕`��*/
	cas.Draw();

}