#pragma once


/******�E�o�X�e�[�W�Ɏg���ϐ�******/
struct EscVar {
	
	//�S�W����������
	bool Lock1=false, Lock2=true, Lock3=true;		//�E�o���\�ɂ���ׂɕK�v�Ȍ�
	bool isEvent = false;					//�C�x���g�̃t���O(true�̎��̓C�x���g�������B)
	bool isObj = false;						//�I�u�W�F�N�g�̉摜��\������t���O
	bool LoadFlg = true;					//�摜����񂾂��ǂݍ��ނ��߂̃t���O
	int alpha = 0;							//�d�C�̓_�łɎg���ϐ�
	int EveCount = 0;						//�C�x���g�̐i�s�Ɏg���ϐ�
	int VecNum = 0;							//�����̂ǂ��������Ă��邩 (0�F�O�A1�F�E�A2�F���F3�F��)
	int GraphNum = 0;						//�摜��؂�ւ���p�̃i���o�[

	//�z���[�̂�

};