
#include "WorkHouse.h"

Working wk;

void Work_Draw(int width, int height) {
	if (work.flg) { work.ImageInput(&work); work.flg = false; }

	/*�d���Љ�̕`��*/
	wk.Draw(&wk);

	/*�d���Љ�̑���*/
	wk.Update(&wk);

}