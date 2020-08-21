#include "DxLib.h"
#include "string.h"
#include "header.h"
#include "Input.h"
#include "Source.h"

#define SCROLL_LIMIT 7000

Credit credit;

int Scroll_y = 0;
const int Scroll_Speed = 1;

int Anim_Count = 0;
int Anim_Speed = 2;


const char Credit_String[5000] =
"制作メンバー\n\n\n"
"下地　遼河\n\n"
"座覇　龍一\n\n"
"崎濱　秀人\n\n"
"二瓶　陽輝\n\n"
"眞榮田　美樹\n\n\n"
"お借りした素材\n\n\n"
"画像・背景素材\n\n"
"「タイトル画面」\nhttp://gahag.net/010808-mountain-countryside/　様\n\n"
"「タイトルシルエット」\nhttps://www.silhouette-ac.com/detail.html?id=143575&ct=&sw=　様\n\n"
"「雑貨屋背景」\nhttps://www.pixiv.net/artworks/75926194\n綾瀬いよ　様\n\n"
"「ダンジョン洞窟背景」\nhttps://www.pixiv.net/artworks/56456004\n観月藍（みづきらん）　様\n\n"
"「ダンジョン廃坑背景」\nhttp://teddy-plaza.sakura.ne.jp/?cat=94\nTEDDY-PLAZA　様\n\n"
"「ダンジョン神殿背景」\nhttps://publicdomainq.net/jmw-turner-0026231/\n\n"
"「仕事紹介所背景」\nhttps://winddorf.net/archives/19041901.html\nWinddorfBlog　様\n\n"
"「自宅背景」\nhttps://www.pixiv.net/artworks/79259280\n三國＠お仕事募集中　様\n\n"
"「カジノ背景」\nhttps://matome.naver.jp/odai/2141653739086970101/2141653886490344803　様\n\n"
"「操作方法ゲームパッド画像」\nhttp://www.etaro.net/archives/1731\nフリー素材の絵太郎　様\n\n"
"「雑貨屋アイテムポーション」\nhttps://seiga.nicovideo.jp/seiga/im8495955\nsiwasiwa　様\n\n「タピオカミルクティー」\nhttp://niceillust.com/商用フリー・無料イラスト_タピオカミルクティー_/　様\n\n"
"「カジノトランプ」\nhttps://seiga.nicovideo.jp/seiga/im1453557\n野田工房アニソンカラオケ制作室　様\n\n"
"「カジノルール」\nhttps://www.casinolobby.info/game/trump/　様\n\n"
"「モンスター」\nhttps://booth.pm/ja/items/1268365\nローズミルクティー　様\n\n"
"「攻撃エフェクト」\nhttps://pipoya.net/sozai/\nぴぽや倉庫　様\n\n\n\n"
"お借りした音楽\n\n"
"「タイトルBGM」\nhttp://classical-sound.seesaa.net/article/474840757.html\n『ブラームス：交響曲第1番 ハ短調 Op.68 第3楽章』\nクラシック名曲サウンドライブラリー　様\n\n"
"「クレジットBGM」\nhttp://classical-sound.seesaa.net/article/174477599.html\n『ラヴェル：ボレロ』\nクラシック名曲サウンドライブラリー　様\n\n"
"「自宅BGM」\nhttp://classical-sound.seesaa.net/article/474922849.html\n『ドヴォルザーク：交響曲 第9番 ホ短調 Op.95 「新世界より」 第2楽章』\nクラシック名曲サウンドライブラリー　様\n\n"
"「あらすじBGM」\nhttps://dova-s.jp/bgm/play13233.html\n『吟遊詩人のテーマ』\nDova-Syndrome　様\n\n"
"「雑貨屋BGM」\nhttps://dova-s.jp/bgm/play13219.html\n『Take a Break』\nDova-Syndrome　様\n\n"
"「仕事紹介所BGM」\nhttps://dova-s.jp/bgm/play12942.html\n『イタリアのご家庭にて』\nDova-Syndrome　様\n\n"
"「カジノBGM」\nhttps://dova-s.jp/bgm/play11231.html\n『First Tune』\nDova-Syndrome　様\n\n"
"「ダンジョン洞窟BGM」\n\n"
"「ダンジョン廃坑BGM」\n\n"
"「ダンジョン神殿BGM」\n\n"
"「拠点BGM」\nhttps://dova-s.jp/bgm/play13203.html\n『悩む昼ごはん』\nDova-Syndrome　様\n\n"
"「自宅ベット休憩」\nhttps://dova-s.jp/bgm/play11720.html\n『束の間の休息』\nDova-Syndrome 様\n\n\n\n"
"「お借りした効果音」\n\n"
"「メニュー移動音」\nhttps://soundeffect-lab.info/sound/button/\n『カーソル移動1』\n効果音ラボ　様\n\n"
"「メニュー決定音」\nhttps://soundeffect-lab.info/sound/button/\n『決定、ボタン押下3』\n効果音ラボ　様\n\n"
"「メニューキャンセル音」\nhttps://soundeffect-lab.info/sound/button/\n『キャンセル2』\n効果音ラボ　様\n\n"
"「キャラ足音」\nhttps://soundeffect-lab.info/sound/various/\n『砂利の上を歩く』\n効果音ラボ　様\n\n"
"「ゲームスタート」\nhttps://soundeffect-lab.info/sound/anime/\n『突撃ラッパ』\n効果音ラボ　様\n\n"
"「アイテムバッグ開閉音」\nhttps://soundeffect-lab.info/sound/various/various3.html\n『ジッパー』\n効果音ラボ　様\n\n"
"「アイテムボックスを開く音」\nhttps://soundeffect-lab.info/sound/various/various3.html\n『アタッシュケースを開ける』\n効果音ラボ　様\n\n"
"「アイテムボックスを閉じる音」\nhttps://soundeffect-lab.info/sound/various/various3.html\n『アタッシュケースを閉じる』\n効果音ラボ　様\n\n"
"「雑貨屋での支払い音」\nhttps://soundeffect-lab.info/sound/anime/\n『金額表示』\n効果音ラボ　様\n\n"
"「建物の確認音」\nhttps://soundeffect-lab.info/sound/button/\n『決定、ボタン押下22』\n効果音ラボ　様\n\n"
"「カジノでカードを配る」\nhttps://soundeffect-lab.info/sound/various/various3.html\n『相手の手札を抜き取る』\n効果音ラボ　様\n\n"
"「カジノでカードをめくる」\nhttps://soundeffect-lab.info/sound/various/various3.html\n『カードを扇状に開く』\n効果音ラボ　様\n\n"
"「カジノで勝利」\nhttps://soundeffect-lab.info/sound/various/various3.html\n『大勢で拍手2』\n効果音ラボ　様\n\n"
"「カジノで敗北」\nhttps://soundeffect-lab.info/sound/anime/\n『皆で笑う3』\n効果音ラボ　様\n\n"
"「力仕事の効果音」\nhttps://dova-s.jp/se/play1101.html\n『工事現場』\nDova-Syndrome　様\n\n"
"「食料仕事の効果音」\nhttps://dova-s.jp/se/play425.html\n『霧笛』\nDova-Syndrome　様\n\n\n"
"「ジャンプ効果音」\n\n"
"「攻撃1効果音」\n\n"
"「攻撃2効果音」\n\n"
"「魔法1効果音」\n\n"
"「魔法2効果音」\n\n";

const char Title_Strings[10] = "ＪＫ伝";

void DrawCredit(int width, int height) {
	if (credit.flg) { credit.Input_bgm(&credit); credit.flg = false; }

	const int size = width / 100 * 2;

	//BGM
	if (CheckSoundMem(credit.bgm) == false) PlaySoundMem(credit.bgm, DX_PLAYTYPE_BACK, TRUE);

	str.SuperString(width / 2, height - Scroll_y, Credit_String, 0xffffff, 1, size);
	str.SuperString(width / 2, height / 10 * 4 + SCROLL_LIMIT - Scroll_y, Title_Strings, 0xffffff, 1, size*4);

	if(Scroll_y < SCROLL_LIMIT)
		Scroll_y += Scroll_Speed;

	if (inp.space) {
		Scroll_y = SCROLL_LIMIT;
	}

	//シーン遷移
	if (Scroll_y >= SCROLL_LIMIT) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Anim_Count);
		DrawBox(0, 0, width, height, 0x000000, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		if (Anim_Count > 255) {

			g_GameState = GAME_CREAR;
			Scroll_y = 0;
			Anim_Count = 0;
			StopSoundMem(credit.bgm);
		}
		Anim_Count += Anim_Speed;
	}
	
}