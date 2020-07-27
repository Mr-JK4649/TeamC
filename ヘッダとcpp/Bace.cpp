#include "Source.h"
#include "string.h"
#include "Input.h"
#include "header.h"

#include "Menu.h"

/*���_�Ŏg���֐�*/
#include "Base_Function.h"

#pragma warning(disable : 6385)

Menu menu;
Base base;


void DrawGameMain(int width, int height) {
	
	/*������*/
	if (base.flg) { base.ImageInput(&base); base.flg = false; }

	/*���_�̕`��֐�*/
	Base_Disp(width, height);										//���_���̕`��

	/*���_�̍X�V�֐�*/
	Base_Update(width, height);										//���_���̈ړ��A���̑��X�V
	

}

/*���_�̕\��*/
void Base_Disp(int width, int height) {
	/*�w�i�\��*/
	DrawExtendGraph(base.move, 0, width * 4 + base.move, height, base.background, 1);

	/*�L�����̕\��*/
	Chara_Disp();

	/*�X�̉e�\��*/
	DrawExtendGraph(base.move, 0, width * 4 + base.move, height, base.shadow, 1);


	menu.Draw();
	if (menu.isMenu == true) {  menu.Item_Kind(Return_Item(menu.item_select)); Status_Disp(); }	//���j���[�̃t���O��true�������烁�j���[�ƃX�e�[�^�X�̕\��
	if (menu.isItem_Menu) { Menu_Item(menu.item_select); }										//�A�C�e�����j���[���J��
	if (menu.isItem_Equip) { Use_Equipment_Item(menu.item_select); menu.isItem_Equip = false; }	//�A�C�e���̑����A�g�p
	if (menu.isItem_Delete) { Delete_Item(menu.item_select); menu.isItem_Delete = false; }		//�A�C�e���̍폜
	if (!str.setTex && inp.start) menu.isMenu = !menu.isMenu;		//�����E�B���h�E���o�ĂȂ��Ƃ��ɃX�^�[�g�{�^���������ƁA���j���[�t���O�̐؂�ւ�

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
		menu.isBuilding_Enter =!menu.isBuilding_Enter;
		menu.Enter_Select = 0;
	}


	/*�Z���t���o��*/
	if (str.setTex) str.Serihu(Player_Serihu[str.TexNum], 15, height - (height / 4 - 10), 0xffffff, width / 40);

}

