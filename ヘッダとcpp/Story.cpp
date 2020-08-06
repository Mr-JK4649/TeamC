#define _CRT_SECURE_NO_WARNINGS
#include "string.h"
#include "Input.h"


#define SCROLL_SPEED 1
#define STORY_MAX 10000

int scroll_y = 0;
FILE* fp;
//const char Story_String[STORY_MAX] = "「異世界転移」、「異世界転生」などの言葉が\n流行り出したのは、いつ頃からだろうか。";
char Story_String2[STORY_MAX] = "";

void Story(int width, int height) {
	fp = fopen("story.txt", "r");
	
	fgets(Story_String2, STORY_MAX, fp);

	DrawString(5, 20, Story_String2, 0xffffff, 1);

	str.setTex = true;
	if (str.setTex) {
		scroll_y += SCROLL_SPEED;
		str.Serihu(Story_String2, (float)width / 100.0f * 30, (float)height / 100.0f * 50 - scroll_y, 0xffffff, width / 100 * 2);
		if (inp.space) str.Serihu_Skip_Fin();
	}

	fclose(fp);
}