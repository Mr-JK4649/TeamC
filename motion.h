#pragma once
//#include "apple.cpp"


//ŠÖ”‚ÌéŒ¾
void HorrorMotion(struct chara *chara,int pl);
int HitCheck();


//•Ï”‚ÌéŒ¾
int g_MotionCount;

void HorrorMotion(struct chara *chara,int pl) {


	if (g_MotionCount <= 20) {
		if(pl == 0)DrawBox(chara->px+120 ,chara->py+80,chara->px+120 + 50,chara->py+120 + 20,0x0000ff,false);
		if(pl == 1)DrawBox(chara->px+80 ,chara->py+80,chara->px+80 - 50,chara->py+120 + 20,0x0000ff,false);
	}


}

int HitCheck() {

}