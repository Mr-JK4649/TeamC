
#include "WorkHouse.h"

Working wk;

void Work_Draw(int width, int height) {
	if (work.flg) { work.ImageInput(&work); work.flg = false; }

	/*d–Ğ‰îŠ‚Ì•`‰æ*/
	wk.Draw(&wk);

	/*d–Ğ‰îŠ‚Ì‘€ì*/
	wk.Update(&wk);

}