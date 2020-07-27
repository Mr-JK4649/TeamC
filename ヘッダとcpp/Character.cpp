#include "DxLib.h"

#include "character.h"

Chara ch;									
Weapon Hand = { 1.0f,-99,-99,"","�Ȃ�",0};													//��C�̌��B�育�����H�Y��Ă��܂����B
Weapon Wood_Sword = { 1.2f,20,30,"images/�^�s�I�J�~���N�e�B�[.jpg" ,"�؂̌�",1};				//�؂̌�
Weapon Iron_Sword = { 1.4f,50,75,"images/�^�s�I�J�~���N�e�B�[.jpg" ,"�S�̌�",2};				//�S�̌�
Weapon Exca_Sword = { 2.0f,100,150,"images/�^�s�I�J�~���N�e�B�[.jpg" ,"�G�N�X�J���o�[",3};	//�G�N�X�J���o�[
Weapon Wood_Rod = { 0.5f,200,300,"images/�^�s�I�J�~���N�e�B�[.jpg" ,"�؂̃��b�h",4};			//�؂̃��b�h
Weapon Iron_Rod = { 1.0f,600,900,"images/�^�s�I�J�~���N�e�B�[.jpg","�S�̃��b�h" ,5};			//�S�̃��b�h
Weapon wep = Hand;																			//����\���̂̂���
Weapon wep_work;																			//������p�̂���

Shield Air = { 1.0f,-99,-99,"","�Ȃ�",0 };													//��C�̏��B����Ŗh����Ǝv�������ԈႢ�ł��B
Shield Wood_Shield = { 3.0f,100,200,"images/�^�s�I�J�~���N�e�B�[.jpg","�؂̏�" ,6};			//�؂̏�
Shield Iron_Shield = { 8.0f,400,800,"images/�^�s�I�J�~���N�e�B�[.jpg","�S�̏�" ,7};			//�S�̏�
Shield Tapi_Shield = { 20.0f,2000,4000,"images/�^�s�I�J�~���N�e�B�[.jpg","�^�s�I�J�̏�" ,8};	//�^�s�I�J�̏��@����(�m�M)
Shield shi = Air;																			//���\���̂̂���
Shield shi_work;																			//�����p�̂���

/*�L�����̕\��*/
void Chara_Disp() {
	if (ch.flg) { ch.Init(&ch); ch.flg = false; }
	
	/*�L�����N�^�[�̕`��*/
	ch.Disp(&ch);
}

/*�L�����̈ړ�*/
void Chara_Update() {

	/*�v���C���[�̈ړ�*/
	ch.Move(&ch);

	/*�o�ߎ���*/
	ch.Add_Time(&ch);
}

/*�X�e�[�^�X�̕\��*/
void Status_Disp() {
	ch.Menu_Status_Disp(&ch);
}

/*�A�C�e���ꗗ�̕\��*/
void Menu_Item(int item_select) {

	char item_name[51];
	unsigned int color = 0xffffff;

	for (int i = 0; i < 10; i++) {
		
		SetFontSize(ch.size * 2);

		switch (ch.Menu_Items_Disp(&ch, i))
		{
			case Chara::Wood_Sword:		strcpy_s(item_name,Wood_Sword.Weapon_name);		break;
			case Chara::Iron_Sword:		strcpy_s(item_name,Iron_Sword.Weapon_name);		break;
			case Chara::Excalibur:		strcpy_s(item_name,Exca_Sword.Weapon_name);		break;
			case Chara::Wood_Rod:		strcpy_s(item_name,Wood_Rod.Weapon_name);		break;
			case Chara::Iron_Rod:		strcpy_s(item_name,Iron_Rod.Weapon_name);		break;
			case Chara::Wood_Shield:	strcpy_s(item_name,Wood_Shield.Shield_name);	break;
			case Chara::Iron_Shield:	strcpy_s(item_name,Iron_Shield.Shield_name);	break;
			case Chara::Tapi_Shield:	strcpy_s(item_name,Tapi_Shield.Shield_name);	break;
			case Chara::Portion:		strcpy_s(item_name,"�|�[�V����");				break;
			case Chara::Tapi_MT:		strcpy_s(item_name,"�^�s�I�J�l�s");				break;
			default:					strcpy_s(item_name, "�@�@�@�@�@�@�@�@�[�[�[�@�@�@�@�@�@�@�@");		break;
		}

		if (i == item_select) color = 0x6666ff;

		DrawString(ch.w5 * 1 + 11, ch.h4 + 6 + (ch.size * 3) * i, item_name, color, 1);

		color = 0xffffff;
	}
}

/*�I�������A�C�e���̎��*/
int Return_Item(int item_select) {
	
	return ch.Menu_Items_Disp(&ch, item_select);
}

int Return_Base_Status(int num) {
	return ch.Return_Base_Status(&ch, num);
}

/*�A�C�e���������g�p*/
void Use_Equipment_Item(int item_select) {

	int item = ch.Menu_Items_Disp(&ch, item_select);
	
	if (item > 0 && item <= Chara::Iron_Rod) {				//�����i�Ȃ瑕��
		wep_work = wep;							//����̔��
		switch (item)
		{
			case Chara::Wood_Sword:	wep = Wood_Sword;	break;
			case Chara::Iron_Sword:	wep = Iron_Sword;	break;
			case Chara::Excalibur:	wep = Exca_Sword;	break;
			case Chara::Wood_Rod:	wep = Wood_Rod;		break;
			case Chara::Iron_Rod:	wep = Iron_Rod;		break;
			default:	ch.Delete_Item(&ch,item_select);	break;
		}

		ch.Input_Item(&ch, item_select, wep_work.serial_num);
	}
	else if (item <= Chara::Tapi_Shield) {
		shi_work = shi;
		switch (item)
		{
			case Chara::Wood_Shield:	shi = Wood_Shield;	break;
			case Chara::Iron_Shield:	shi = Iron_Shield;	break;
			case Chara::Tapi_Shield:	shi = Tapi_Shield;	break;
			default:	ch.Delete_Item(&ch,item_select);	break;
		}

		ch.Input_Item(&ch, item_select, shi_work.serial_num);
	}
	else if (item <= Chara::Tapi_MT) {
		
		switch (item) 
		{
		case Chara::Portion: ch.Healing_Life(&ch, Chara::Portion); break;
		case Chara::Tapi_MT: ch.Healing_Life(&ch, Chara::Tapi_MT); break;
		}

		ch.Delete_Item(&ch, item_select);
	}

	
	
}

/*�A�C�e���폜*/
void Delete_Item(int item_select) {
	ch.Delete_Item(&ch,item_select);
}