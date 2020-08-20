#include "DxLib.h"
#include "string.h"
#include "header.h"

#define SCROLL_LIMIT 5000

const char Credit_String[4000] =
"制作メンバー\n\n"
"下地　遼河\n"
"座覇　龍一\n"
"崎濱　秀人\n"
"二瓶　陽輝\n"
"眞榮田　美樹\n\n"
"お借りした素材\n"
"画像・背景素材\n\n"
"タイトル画面\nhttp://gahag.net/010808-mountain-countryside/　様\n\n"
"タイトルシルエット\nhttps://www.silhouette-ac.com/detail.html?id=143575&ct=&sw=　様\n\n"
"雑貨屋背景\nhttps://www.pixiv.net/artworks/75926194\n綾瀬いよ　様"
"ダンジョン洞窟背景\nhttps://www.pixiv.net/artworks/56456004\n観月藍（みづきらん）　様\n\n"
"ダンジョン廃坑背景\nhttp://teddy-plaza.sakura.ne.jp/?cat=94\nTEDDY-PLAZA　様\n\n"
"ダンジョン神殿背景\nhttps://publicdomainq.net/jmw-turner-0026231/\n\n"
"仕事紹介所背景\nhttps://winddorf.net/archives/19041901.html\nWinddorfBlog　様\n\n"
"自宅背景\nhttps://www.pixiv.net/artworks/79259280\n三國＠お仕事募集中　様\n\n"
""
"";

void DrawCredit(int width, int height) {
	static int Scroll_y = 0;
	const int size = width / 100 * 3;

	str.SuperString(width / 2, height / 2 - Scroll_y, Credit_String, 0xffffff, 1, size);


	++Scroll_y;

	//シーン遷移
	if (Scroll_y > SCROLL_LIMIT) {
		g_GameState = GAME_CREAR;
		Scroll_y = 0;
	}
	
}