#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "Source.h"
#include "string.h"
#include "Input.h"


#define SCROLL_SPEED 2
#define STORY_MAX 4000
#define SCROOL_END 9000

int flg = true;
int scroll_y = 0;
int bgm = 0;
int alpha = 0;
int add_alpha = 3;

char Story_String[STORY_MAX] =
"　　　  「異世界転生」や「異世界転移」という言葉が \n\n\n\n"
"　　　  流行り出したのは、いつ頃からだっただろうか。\n\n\n\n"
"　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　\n\n\n\n"
"今やマンガや小説、アニメと至る所で転生しているのを見かける。\n\n\n\n"
"　　　 最近ではゲームでも転生や転移をしているらしい。\n\n\n\n"
"　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　\n\n\n\n"
"　  慣れ親しんだ日常が、いきなり消え去った主人公たちは\n\n\n\n"
"　　　一体どのような心境で世界を救っているのだろうか。\n\n\n\n"
"　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　\n\n\n\n"
"　　　 さて、このゲームにも一人、突然見知らぬ世界に\n\n\n\n"
"　　　　　  飛ばされてしまった人間が居るようだ。\n\n\n\n"
"　　 唐突に訪れた日々の変化に対して彼女はどう思うのか。\n\n\n\n"
"　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　\n\n\n\n"
"　　　 しかし、彼女は決してへこたれたりなんかしない。\n\n\n\n"
"　　　　　　 なぜなら彼女はＪＫだからだ。(偏見)\n\n\n\n"
"　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　\n\n\n\n"
"　　　　 主人公によくあるチートが無くても彼女は強い。\n\n\n\n"
"　　　　　　 なぜなら彼女はＪＫだからだ。(偏見)\n\n\n\n"
"　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　\n\n\n\n"
"飛ばされた先で見知らぬ街に出て、優しい住人に家を借りたようだ。\n\n\n\n"
"　　　　 　　　　　　　  運も強い。\n\n\n\n"
"　　　　　  なぜなら彼女はＪＫだからだ。(偏見)\n\n\n\n"
"　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　\n\n\n\n"
"          見たこともない街並みを横目に彼女は言った。\n\n\n\n"
"       「まずは有名にならなきゃ。その為には.....」\n\n\n\n"
"　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　\n\n\n\n"
"どうやら彼女は街を発展させることで有名人になる事にしたようだ。\n\n\n\n"
"　　　　　　　　　　　　　　　　　　　　　　　　　　  　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　\n\n\n\n\n\n\n\n\n\n"
"　　　 この世界で、イケメンの彼氏をゲットするために。\n\n\n\n";