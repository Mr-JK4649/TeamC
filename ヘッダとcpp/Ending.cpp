#include "DxLib.h"
#include "string.h"

int Anim_N = 0;
int Anim_A = 0;
int Anim_Aa = 1;
int Anim_S = 1;

const char Ending_String[11][500] = {
"�X�𔭓W�ɋ��͂��h���S����|�������́A�ӂƍl���Ă����B",
"�l���������Ă���C�z�͂���̂ɁA�Ȃ��X�̐l�͈�l�����Ȃ��̂��B",
"�l�����Ȃ��̂ɂȂ��X�̏��i�͕⋋����Ă����̂��B",
"�d���̏Љ�f���ɂ��̊Ԃɂ�����o����Ă���",
"�����B�������؂�u���Ă����ƁA���̊Ԃɂ���V����ɓ���B",
"�h�����ꂽ�S�D�����l���ŏ��ȗ��p�������Ă��Ȃ��B",
"�݂��Ă��ꂽ�h�͂Ȃ���̋߂��ɂ���̂��B",
"�Ȃ����́A����Ȃɉ��ł��ł��Ă��܂��̂��B",
"�Ƃ��A����Ȏ��͑S�R�l���ĂȂ���",
"���͂����A���җ�ɁA�^�s�I�J�~���N�e�B�[�����݂����B",
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