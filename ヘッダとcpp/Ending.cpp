#include "DxLib.h"
#include "string.h"

int Anim_N = 0;
int Anim_A = 0;
int Anim_Aa = 1;
int Anim_S = 1;

const char Ending_String[11][500] = {
"街を発展に協力しドラゴンを倒した私は、ふと考えていた。",
"人口が増えている気配はするのに、なぜ街の人は一人もいないのか。",
"人も居ないのになぜ店の商品は補給されていたのか。",
"仕事の紹介が掲示板にいつの間にか張り出されていて",
"それを達成した証を置いておくと、いつの間にか報酬が手に入る。",
"宿をくれた心優しい人も最初以来姿を見せていない。",
"貸してくれた宿はなぜ門の近くにあるのか。",
"なぜ私は、こんなに何でもできてしまうのか。",
"とか、そんな事は全然考えてなくて",
"私はただ、今猛烈に、タピオカミルクティーが飲みたい。",
""
};


void DrawEnding(int width, int height) {

	str.SuperString(width / 2, height / 2, Ending_String[Anim_N], 0xffffff, 1, width / 100 * 3);
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Anim_A);
	DrawBox(0, 0, width, height, 0x000000, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	if (Anim_N != 10) {
		if (Anim_A >= 255 || Anim_A < 0) {
			if (Anim_Aa == 1) Anim_N++;
			Anim_Aa *= -1;
		}
	}
	else {
		g_GameState = GAME_CREDIT;
	}

	Anim_A += Anim_S * Anim_Aa;
	

}