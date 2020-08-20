#include "DxLib.h"
#include "string.h"
#include "header.h"

#define SCROLL_LIMIT 5000

const char Credit_String[4000] =
"§ìƒƒ“ƒo[\n\n"
"‰º’n@—É‰Í\n"
"À”e@—´ˆê\n"
"èà_@Gl\n"
"“ñ•r@—z‹P\n"
"áÁžÄ“c@”üŽ÷\n\n"
"‚¨ŽØ‚è‚µ‚½‘fÞ\n"
"‰æ‘œE”wŒi‘fÞ\n\n"
"ƒ^ƒCƒgƒ‹‰æ–Ê\nhttp://gahag.net/010808-mountain-countryside/@—l\n\n"
"ƒ^ƒCƒgƒ‹ƒVƒ‹ƒGƒbƒg\nhttps://www.silhouette-ac.com/detail.html?id=143575&ct=&sw=@—l\n\n"
"ŽG‰Ý‰®”wŒi\nhttps://www.pixiv.net/artworks/75926194\nˆ»£‚¢‚æ@—l"
"ƒ_ƒ“ƒWƒ‡ƒ““´ŒA”wŒi\nhttps://www.pixiv.net/artworks/56456004\nŠÏŒŽ—•i‚Ý‚Ã‚«‚ç‚ñj@—l\n\n"
"ƒ_ƒ“ƒWƒ‡ƒ“”pB”wŒi\nhttp://teddy-plaza.sakura.ne.jp/?cat=94\nTEDDY-PLAZA@—l\n\n"
"ƒ_ƒ“ƒWƒ‡ƒ“_“a”wŒi\nhttps://publicdomainq.net/jmw-turner-0026231/\n\n"
"ŽdŽ–Ð‰îŠ”wŒi\nhttps://winddorf.net/archives/19041901.html\nWinddorfBlog@—l\n\n"
"Ž©‘î”wŒi\nhttps://www.pixiv.net/artworks/79259280\nŽOš —‚¨ŽdŽ–•åW’†@—l\n\n"
""
"";

void DrawCredit(int width, int height) {
	static int Scroll_y = 0;
	const int size = width / 100 * 3;

	str.SuperString(width / 2, height / 2 - Scroll_y, Credit_String, 0xffffff, 1, size);


	++Scroll_y;

	//ƒV[ƒ“‘JˆÚ
	if (Scroll_y > SCROLL_LIMIT) {
		g_GameState = GAME_CREAR;
		Scroll_y = 0;
	}
	
}