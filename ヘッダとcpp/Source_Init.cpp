#include "Source.h"
#include "header.h"
#include "string.h"

SoundE se;
Title title;
Stage stage;
Base base;
Casino casino;
Work work;
Shop shop;
Home home;


void Init() {
	static float Loading_Par = 0;
	static int count = 0;
	const float w100 = (float)scale.Width / 100.0f;
	const float h100 = (float)scale.Height / 100.0f;
	const int size = scale.Width / 100;

	if(Loading_Par != 80.0f)
		str.SuperString(w100 * 50, h100 * 40, "“Ç‚Ýž‚Ý‚ñ‚®!", 0xffffff, 1, size * 2);
	DrawBox(w100 * 10, h100 * 55, w100 * 10 + w100 * Loading_Par, h100 * 60, 0x00ff00, true);
	DrawBox(w100 * 10, h100 * 55, w100 * 90, h100 * 60, 0xffff00, false);

	if (se.flg) { se.Init(&se); se.flg; se.flg = false; Loading_Par = 10.0f; }
	else if (title.flg) { title.ImageInput(&title); title.flg = false; Loading_Par = 20.0f; }
	else if (stage.flg) { stage.ImageInput(&stage); stage.flg = false; Loading_Par = 30.0f; }
	else if (base.flg) { base.ImageInput(&base); base.flg = false; Loading_Par = 40.0f; }
	else if (casino.flg) { casino.ImageInput(&casino); casino.flg = false; Loading_Par = 50.0f; }
	else if (work.flg) { work.ImageInput(&work); work.flg = false; Loading_Par = 60.0f; }
	else if (home.flg) { home.ImageInput(&home); home.flg = false; Loading_Par = 70.0f; }
	else if (shop.flg) { shop.ImageInput(&shop); shop.flg = false; Loading_Par = 80.0f; }

	if (Loading_Par >= 80.0f) {
		str.SuperString(w100 * 50, h100 * 40, "“Ç‚Ýž‚ÝŠ®—¹!", 0xffffff, 1, size * 2);
		if(++count >= 100)g_GameState = GAME_TITLE;
	}
}