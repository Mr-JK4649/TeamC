#include "Shopping.h"

Shopping shopping;

void Shop_Draw(int width,int height) {
	if (sh.flg) { sh.ImageInput(&sh); sh.flg = false; }

	shopping.Draw(&shopping);

	if (shopping.Confirm_Buy || shopping.Confirm_Sell)
		shopping.Confirm_Window_String(&shopping);
	
	shopping.Update(&shopping);

}