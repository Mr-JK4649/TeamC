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
"���상���o�[\n\n\n"
"���n�@�ɉ�\n\n"
"���e�@����\n\n"
"���_�@�G�l\n\n"
"��r�@�z�P\n\n"
"���ēc�@����\n\n\n"
"���؂肵���f��\n\n\n"
"�摜�E�w�i�f��\n\n"
"�u�^�C�g����ʁv\nhttp://gahag.net/010808-mountain-countryside/�@�l\n\n"
"�u�^�C�g���V���G�b�g�v\nhttps://www.silhouette-ac.com/detail.html?id=143575&ct=&sw=�@�l\n\n"
"�u�G�݉��w�i�v\nhttps://www.pixiv.net/artworks/75926194\n��������@�l\n\n"
"�u�_���W�������A�w�i�v\nhttps://www.pixiv.net/artworks/56456004\n�ό����i�݂Â����j�@�l\n\n"
"�u�_���W�����p�B�w�i�v\nhttp://teddy-plaza.sakura.ne.jp/?cat=94\nTEDDY-PLAZA�@�l\n\n"
"�u�_���W�����_�a�w�i�v\nhttps://publicdomainq.net/jmw-turner-0026231/\n\n"
"�u�d���Љ�w�i�v\nhttps://winddorf.net/archives/19041901.html\nWinddorfBlog�@�l\n\n"
"�u����w�i�v\nhttps://www.pixiv.net/artworks/79259280\n�O�������d����W���@�l\n\n"
"�u�J�W�m�w�i�v\nhttps://matome.naver.jp/odai/2141653739086970101/2141653886490344803�@�l\n\n"
"�u������@�Q�[���p�b�h�摜�v\nhttp://www.etaro.net/archives/1731\n�t���[�f�ނ̊G���Y�@�l\n\n"
"�u�G�݉��A�C�e���|�[�V�����v\nhttps://seiga.nicovideo.jp/seiga/im8495955\nsiwasiwa�@�l\n\n�u�^�s�I�J�~���N�e�B�[�v\nhttp://niceillust.com/���p�t���[�E�����C���X�g_�^�s�I�J�~���N�e�B�[_/�@�l\n\n"
"�u�J�W�m�g�����v�v\nhttps://seiga.nicovideo.jp/seiga/im1453557\n��c�H�[�A�j�\���J���I�P���쎺�@�l\n\n"
"�u�J�W�m���[���v\nhttps://www.casinolobby.info/game/trump/�@�l\n\n"
"�u�����X�^�[�v\nhttps://booth.pm/ja/items/1268365\n���[�Y�~���N�e�B�[�@�l\n\n"
"�u�U���G�t�F�N�g�v\nhttps://pipoya.net/sozai/\n�҂ۂ�q�Ɂ@�l\n\n\n\n"
"���؂肵�����y\n\n"
"�u�^�C�g��BGM�v\nhttp://classical-sound.seesaa.net/article/474840757.html\n�w�u���[���X�F�����ȑ�1�� �n�Z�� Op.68 ��3�y�́x\n�N���V�b�N���ȃT�E���h���C�u�����[�@�l\n\n"
"�u�N���W�b�gBGM�v\nhttp://classical-sound.seesaa.net/article/174477599.html\n�w�����F���F�{�����x\n�N���V�b�N���ȃT�E���h���C�u�����[�@�l\n\n"
"�u����BGM�v\nhttp://classical-sound.seesaa.net/article/474922849.html\n�w�h���H���U�[�N�F������ ��9�� �z�Z�� Op.95 �u�V���E���v ��2�y�́x\n�N���V�b�N���ȃT�E���h���C�u�����[�@�l\n\n"
"�u���炷��BGM�v\nhttps://dova-s.jp/bgm/play13233.html\n�w��V���l�̃e�[�}�x\nDova-Syndrome�@�l\n\n"
"�u�G�݉�BGM�v\nhttps://dova-s.jp/bgm/play13219.html\n�wTake a Break�x\nDova-Syndrome�@�l\n\n"
"�u�d���ЉBGM�v\nhttps://dova-s.jp/bgm/play12942.html\n�w�C�^���A�̂��ƒ�ɂāx\nDova-Syndrome�@�l\n\n"
"�u�J�W�mBGM�v\nhttps://dova-s.jp/bgm/play11231.html\n�wFirst Tune�x\nDova-Syndrome�@�l\n\n"
"�u�_���W�������ABGM�v\n\n"
"�u�_���W�����p�BBGM�v\n\n"
"�u�_���W�����_�aBGM�v\n\n"
"�u���_BGM�v\nhttps://dova-s.jp/bgm/play13203.html\n�w�Y�ޒ����͂�x\nDova-Syndrome�@�l\n\n"
"�u����x�b�g�x�e�v\nhttps://dova-s.jp/bgm/play11720.html\n�w���̊Ԃ̋x���x\nDova-Syndrome �l\n\n\n\n"
"�u���؂肵�����ʉ��v\n\n"
"�u���j���[�ړ����v\nhttps://soundeffect-lab.info/sound/button/\n�w�J�[�\���ړ�1�x\n���ʉ����{�@�l\n\n"
"�u���j���[���艹�v\nhttps://soundeffect-lab.info/sound/button/\n�w����A�{�^������3�x\n���ʉ����{�@�l\n\n"
"�u���j���[�L�����Z�����v\nhttps://soundeffect-lab.info/sound/button/\n�w�L�����Z��2�x\n���ʉ����{�@�l\n\n"
"�u�L���������v\nhttps://soundeffect-lab.info/sound/various/\n�w�����̏������x\n���ʉ����{�@�l\n\n"
"�u�Q�[���X�^�[�g�v\nhttps://soundeffect-lab.info/sound/anime/\n�w�ˌ����b�p�x\n���ʉ����{�@�l\n\n"
"�u�A�C�e���o�b�O�J���v\nhttps://soundeffect-lab.info/sound/various/various3.html\n�w�W�b�p�[�x\n���ʉ����{�@�l\n\n"
"�u�A�C�e���{�b�N�X���J�����v\nhttps://soundeffect-lab.info/sound/various/various3.html\n�w�A�^�b�V���P�[�X���J����x\n���ʉ����{�@�l\n\n"
"�u�A�C�e���{�b�N�X����鉹�v\nhttps://soundeffect-lab.info/sound/various/various3.html\n�w�A�^�b�V���P�[�X�����x\n���ʉ����{�@�l\n\n"
"�u�G�݉��ł̎x�������v\nhttps://soundeffect-lab.info/sound/anime/\n�w���z�\���x\n���ʉ����{�@�l\n\n"
"�u�����̊m�F���v\nhttps://soundeffect-lab.info/sound/button/\n�w����A�{�^������22�x\n���ʉ����{�@�l\n\n"
"�u�J�W�m�ŃJ�[�h��z��v\nhttps://soundeffect-lab.info/sound/various/various3.html\n�w����̎�D�𔲂����x\n���ʉ����{�@�l\n\n"
"�u�J�W�m�ŃJ�[�h���߂���v\nhttps://soundeffect-lab.info/sound/various/various3.html\n�w�J�[�h����ɊJ���x\n���ʉ����{�@�l\n\n"
"�u�J�W�m�ŏ����v\nhttps://soundeffect-lab.info/sound/various/various3.html\n�w�吨�Ŕ���2�x\n���ʉ����{�@�l\n\n"
"�u�J�W�m�Ŕs�k�v\nhttps://soundeffect-lab.info/sound/anime/\n�w�F�ŏ΂�3�x\n���ʉ����{�@�l\n\n"
"�u�͎d���̌��ʉ��v\nhttps://dova-s.jp/se/play1101.html\n�w�H������x\nDova-Syndrome�@�l\n\n"
"�u�H���d���̌��ʉ��v\nhttps://dova-s.jp/se/play425.html\n�w���J�x\nDova-Syndrome�@�l\n\n\n"
"�u�W�����v���ʉ��v\n\n"
"�u�U��1���ʉ��v\n\n"
"�u�U��2���ʉ��v\n\n"
"�u���@1���ʉ��v\n\n"
"�u���@2���ʉ��v\n\n";

const char Title_Strings[10] = "�i�j�`";

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

	//�V�[���J��
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