#include "Source.h"
#include "string.h"
#include "Input.h"
#include "header.h"

#include "Menu.h"

/*���_�Ŏg���֐�*/
#include "Base_Function.h"

#pragma warning(disable : 6385)

Menu menu;


void DrawGameMain(int width, int height) {
	

	/*���_�̕`��֐�*/
	Base_Disp(width, height);						//���_���̕`��

	/*BGM�ƃV�[���ړ��̏���*/
	if (menu.Move_Scene) {
		if (g_GameState != menu.scene_t) {
			StopSoundMem(base.bgm);
			g_GameState = menu.scene_t;
		}
		menu.Move_Scene = false;
	}
	else if (CheckSoundMem(base.bgm) == false) {
		PlaySoundMem(base.bgm, DX_PLAYTYPE_BACK, 1);
	}

	/*���_�̍X�V�֐�*/
	if(!menu.Result_DWork_Flg && !menu.Result_FWork_Flg && !menu.isGage_Menu)
		Base_Update(width, height);					//���_���̈ړ��A���̑��X�V
	

}

/*���_�̕\��*/
void Base_Disp(int width, int height) {
	/*�w�i�\��*/


	if(Return_Base_Status(1) >= 100) DrawExtendGraph(base.move, 0, width * 4 + base.move, height, base.background2, 1);
	else DrawExtendGraph(base.move, 0, width * 4 + base.move, height, base.background, 1);


	/*�L�����̕\��*/
	Chara_Disp();


	/*�X�̉e�\��*/
	DrawExtendGraph(base.move, 0, width * 4 + base.move, height, base.shadow, 1);


	menu.Draw();
	if (menu.isMenu && !menu.isTIPS) {  menu.Item_Kind(Return_Item(menu.item_select)); Status_Disp(); }	//���j���[�̃t���O��true�������烁�j���[�ƃX�e�[�^�X�̕\��
	if (menu.isItem_Menu) { Menu_Item(menu.item_select); }										//�A�C�e�����j���[���J��
	if (menu.isItem_Equip) { Use_Equipment_Item(menu.item_select); menu.isItem_Equip = false; }	//�A�C�e���̑����A�g�p
	if (menu.isItem_Delete) { Delete_Item(menu.item_select); menu.isItem_Delete = false; }		//�A�C�e���̍폜
	if (!str.setTex &&
		inp.start &&
		!menu.Result_DWork_Flg &&
		!menu.Result_FWork_Flg &&
		!menu.isTIPS &&
		!menu.isGage_Menu) menu.isMenu = !menu.isMenu;		//�����E�B���h�E���o�ĂȂ��Ƃ��ɃX�^�[�g�{�^���������ƁA���j���[�t���O�̐؂�ւ�

	DrawFormatString(5, 5, 0xffffff, "%d", inp.a);
}

/*���_�̃V�X�e��*/
void Base_Update(int width, int height) {
	
	/*�L�����̈ړ��Ȃ�*/
	if (!menu.isMenu && !str.setTex && !menu.isBuilding_Enter)Chara_Update();

	/*�����̔���*/
	Building_Serihu(width, height);

	/*�I�u�W�F�N�g�͈̔͂ɓ����Ē��ׂ���*/
	if (str.TexNum != 99 && !menu.isMenu && inp.space == true) {
		if (str.setTex) str.Serihu_Skip_Fin();
		else str.setTex = true;
	}

	/*�����̓�����𒲂ׂ�����*/
	if (menu.Enter_Num != 99 && !menu.isMenu && inp.space == true) {
		if (!menu.isBuilding_Enter) {
			PlaySoundMem(base.BC_window_pop, DX_PLAYTYPE_BACK, TRUE);
			menu.isBuilding_Enter = true;\
		}
		else menu.isBuilding_Enter = false;
		menu.Enter_Select = 0;
	}


	/*�Z���t���o��*/
	if (str.setTex) str.Serihu(Player_Serihu[str.TexNum], 15, height - (height / 4 - 10), 0xffffff, width / 40);

}

