#pragma once

//���_�̕`��ƍX�V
void Base_Disp(int width,int height);
void Base_Update(int width, int height);

//�Z���t�̔����ƃg���K�[
void Building_Serihu(int width,int height);

//�L�����N�^�[�̕`��ƍX�V
void Chara_Disp(void);
void Chara_Update(void);
int Return_Base_Status(int num);

/*���j���[�p�̃X�e�[�^�X���擾����֐�*/
void Status_Disp(void);
int Return_Item(int item_select);
void Menu_Item(int item_select);
void Use_Equipment_Item(int item_select);		//�A�C�e������/�g��
void Delete_Item(int item_select);				//�A�C�e���폜


char Player_Serihu[5][200] = { "�����͌��⏊�ˁB\n�X���o���肷��ۂɉ�����������������ߕ߂��ꂿ�Ⴄ�����B\n�A�A�A�A�A�A�A�A�A�A�A�Ȃ�ĂˁB",		//���⏊�ŏo��Z���t
							   "�J�W�m���ݗ\��n�Ə����Ă����B\n�o�������񂭂炢���Ă݂Ă�������������Ȃ���ˁB",						//�J�W�m(������)�ŏo��Z���t
							   "a",																											//�J�W�m(���ݍς�)�ŏo��Z���t
							   "����͎d���Љ�̌f���ˁB\n�F��Ȏd���̈˗����\���Ă����B",											//�d���Љ�̌f���ŏo��Z���t
							   "���X�Ŏ�舵���Ă鏤�i�̒l�i�������Ă����B\n����250�S�[���h�A����300�S�[���h�A�񕜖�5�S�[���h�B\n�����̂������̂�������Ȃ���ˁE�E�E�E�E�B" };	//�X�ŏo��Z���t

