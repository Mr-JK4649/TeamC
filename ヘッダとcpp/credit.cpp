#include "DxLib.h"
#include "string.h"
#include "header.h"

#define SCROLL_LIMIT 5000

const char Credit_String[4000] =
"���상���o�[\n\n"
"���n�@�ɉ�\n"
"���e�@����\n"
"���_�@�G�l\n"
"��r�@�z�P\n"
"���ēc�@����\n\n"
"���؂肵���f��\n"
"�摜�E�w�i�f��\n\n"
"�^�C�g�����\nhttp://gahag.net/010808-mountain-countryside/�@�l\n\n"
"�^�C�g���V���G�b�g\nhttps://www.silhouette-ac.com/detail.html?id=143575&ct=&sw=�@�l\n\n"
"�G�݉��w�i\nhttps://www.pixiv.net/artworks/75926194\n��������@�l"
"�_���W�������A�w�i\nhttps://www.pixiv.net/artworks/56456004\n�ό����i�݂Â����j�@�l\n\n"
"�_���W�����p�B�w�i\nhttp://teddy-plaza.sakura.ne.jp/?cat=94\nTEDDY-PLAZA�@�l\n\n"
"�_���W�����_�a�w�i\nhttps://publicdomainq.net/jmw-turner-0026231/\n\n"
"�d���Љ�w�i\nhttps://winddorf.net/archives/19041901.html\nWinddorfBlog�@�l\n\n"
"����w�i\nhttps://www.pixiv.net/artworks/79259280\n�O�������d����W���@�l\n\n"
""
"";

void DrawCredit(int width, int height) {
	static int Scroll_y = 0;
	const int size = width / 100 * 3;

	str.SuperString(width / 2, height / 2 - Scroll_y, Credit_String, 0xffffff, 1, size);


	++Scroll_y;

	//�V�[���J��
	if (Scroll_y > SCROLL_LIMIT) {
		g_GameState = GAME_CREAR;
		Scroll_y = 0;
	}
	
}