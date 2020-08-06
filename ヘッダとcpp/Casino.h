#pragma once

#include "character.h"

//Casino casino;

struct Casino_System {
	bool Dragon_Tiger = false;		//�h���S���^�C�K�[���v���C
	bool DT_Info = false;			//�h���S���^�C�K�[�̐���
	int DT_Phase = 0;				//�h���S���^�C�K�[�̃t�F�C�Y
	int DT_Result = 0;				//�h���S���^�C�K�[�̌���
	char DT_Result_Sting[4][20] = {	//�h���S���^�C�K�[�̌��ʕ�����
		"�h���S���̏���",
		"�^�C�K�[�̏���",
		"�^�C",
		"�X�[�e�b�h�^�C"
	};
	int DT_Result_Money = 0;		//�h���S���^�C�K�[�̕ԋ��z

	bool Casino_War = false;		//�J�W�m�E�H�[���v���C
	bool CW_Info = false;			//�J�W�m�E�H�[�̐���
	int CW_Phase = 0;				//�J�W�m�E�H�[�̃t�F�C�Y
	int CW_Tie_Bet = 0;				//�J�W�m�E�H�[��TIE�x�b�g�̂��(1�Ȃ�TIE�x�b�g)
	int CW_Tie_Select = 0;			//�^�C�̏ꍇ�̑I��(�T�����_�[�A�E�H�[)
	int CW_Result = 0;				//�J�W�m�E�H�[�̌���
	char CW_Result_String[3][20] = {//�J�W�m�E�H�[�̌��ʕ�����
		"����̏���",
		"���Ȃ��̏���",
		"�^�C"
	};
	char CW_TieBet_String[2][20] = { "���Ȃ�","����" };
	char CW_Tie_Select_String[2][20] = { "�T�����_�[","�E�H�[" };
	int CW_Result_Money = 0;		//�J�W�m�E�H�[�̕ԋ��z

	/*�J�[�h�̏�����*/
	void Card_Init() {
		for (int i = 0; i < 2; i++) {
			
			Card_Status[i][0] = 55;		//��������
			Card_Status[i][1] = -30;	//��������
			Card_Status[i][2] = 10;		//��������
			Card_Status[i][3] = 30;		//����������
			Card_Status[i][4] = GetRand(51);	//�J�[�h�̔ԍ��ƃ}�[�N
			Back_or_Front[i] = 0;				//�ŏ��̃J�[�h�͗�
		}
	}

	void Draw() {
		const float w = (float)scale.Width / 100.0f;
		const float h = (float)scale.Height / 100.0f;
		const int size = scale.Width / 100;

		/*�Z���t�ƑI��g*/
		if (Casino_War) {
			/*�Z���t�g*/
			DrawRoundRect(w * 1, h * 50, w * 35, h * 99, 10, 10, 0x444444, 1);
			DrawRoundRect(w * 1, h * 50, w * 35, h * 99, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w * 1 + 1, h * 50 + 1, w * 35 - 1, h * 99 - 1, 10, 10, 0xffffff, 0);

			/*�I�����g*/
			DrawRoundRect(w * 71, h * 70, w * 99, h * 99, 10, 10, 0x444444, 1);
			DrawRoundRect(w * 71, h * 70, w * 99, h * 99, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w * 71 + 1, h * 70 + 1, w * 99 - 1, h * 99 - 1, 10, 10, 0xffffff, 0);
		}
		else {
			/*�Z���t�g*/
			DrawRoundRect(w * 1, h * 70, w * 70, h * 99, 10, 10, 0x444444, 1);
			DrawRoundRect(w * 1, h * 70, w * 70, h * 99, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w * 1 + 1, h * 70 + 1, w * 70 - 1, h * 99 - 1, 10, 10, 0xffffff, 0);

			/*�I�����g*/
			DrawRoundRect(w * 71, h * 70, w * 99, h * 99, 10, 10, 0x444444, 1);
			DrawRoundRect(w * 71, h * 70, w * 99, h * 99, 10, 10, 0xaaaaaa, 0);
			DrawRoundRect(w * 71 + 1, h * 70 + 1, w * 99 - 1, h * 99 - 1, 10, 10, 0xffffff, 0);
		}


		/*�J�W�m�̃Q�[���̐���*/
		Casino_Game_Info(w, h, size);

		/*�������͒ʏ푀��s��*/
		if (!Dragon_Tiger && !Casino_War) {
			for (int i = 0; i < 2; i++) {
				if (Depth_Select[Depth] == i) color = blue_color;
				str.SuperString(w * 85, h * (75 + 10 * i), Depth_Select_String[Depth][i], color, 1, size * 3);
				color = white_color;
			}

			
			if(Depth == 0)str.SuperString(w * 2, h * 71, "�ǂ����悤������", 0xffffff, 0, size * 2);
			if(Depth == 1)str.SuperString(w * 2, h * 71, "���ŗV�ڂ�������", 0xffffff, 0, size * 2);
			if(Depth == 2)str.SuperString(w * 2, h * 71, "�h���S���^�C�K�[������Ă݂悤������", 0xffffff, 0, size * 2);
			if(Depth == 3)str.SuperString(w * 2, h * 71, "�J�W�m�E�H�[������Ă݂悤������", 0xffffff, 0, size * 2);

			/*�J�W�m�ł̑���*/
			Update();
		}

		

		/*�Q�[���v���C*/
		GamePlay(w,h,size);

	}

	void Update() {
		if (inp.f_up) {
			if (--Depth_Select[Depth] < 0) Depth_Select[Depth] = 1;
		}
		if (inp.f_down) {
			if (++Depth_Select[Depth] > 1) Depth_Select[Depth] = 0;
		}

		if (inp.space) {
			switch (Depth) {
				case 0:
					if (Depth_Select[0] == 0) Depth = 1;
					if (Depth_Select[0] == 1) g_GameState = GAME_BASE;
					Depth_Select[0] = 0;
					break;

				case 1:
					if (Depth_Select[1] == 0) Depth = 2;
					if (Depth_Select[1] == 1) Depth = 3;
					Depth_Select[1] = 0;
					break;

				case 2:
					if (Depth_Select[2] == 0) { Dragon_Tiger = true; Card_Init(); }
					if (Depth_Select[2] == 1) { DT_Info = true; Depth = 4; }
					Depth_Select[2] = 0;
					break;

				case 3:
					if (Depth_Select[3] == 0) { Casino_War = true; Card_Init(); }
					if (Depth_Select[3] == 1) { CW_Info = true; Depth = 5; }
					Depth_Select[3] = 0;
					break;

				case 4:
					if (inp.space) Depth = 2;
					DT_Info = false;
					break;

				case 5:
					if (inp.space) Depth = 3;
					CW_Info = false;
					break;
			}
		}

		if (inp.cancel) {
			if (Depth < 4) {
				Depth_Select[Depth] = 0;
				if (--Depth < 0) Depth = 0;
			}
		}
	}

	void GamePlay(float w,float h,int size) {

		SetFontSize(size * 2);

		/*�h���S���^�C�K�[*/
		if (Dragon_Tiger) {

			DrawExtendGraph(w * 20, h * 30, w * 40, h * 60, casino.Dragon_img, 1);			//�h���S���̊G
			DrawExtendGraph(w * 60, h * 30, w * 80, h * 60, casino.Tiger_img, 1);			//�g���̊G

			/*����̃J�[�h�̕`��*/
			if (Back_or_Front[0] == 0) {
				DrawExtendGraph(w * Card_Status[0][0],								//�����W
								h * Card_Status[0][1],								//�����W
								(w * Card_Status[0][0] + w * Card_Status[0][2]),	//��
								(h * Card_Status[0][1] + h * Card_Status[0][3]),	//����
								casino.Card_Back, 1);
			}
			else {
				DrawExtendGraph(w * Card_Status[0][0],								//�����W
								h * Card_Status[0][1],								//�����W
								(w * Card_Status[0][0] + w * Card_Status[0][2]),	//��
								(h * Card_Status[0][1] + h * Card_Status[0][3]),	//����
								casino.Cards[Card_Status[0][4]], 1);
				
			}

			/*�����̃J�[�h�̕`��*/
			if (Back_or_Front[1] == 0) {
				DrawExtendGraph(w * Card_Status[1][0],								//�����W
								h * Card_Status[1][1],								//�����W
								(w * Card_Status[1][0] + w * Card_Status[1][2]),	//��
								(h * Card_Status[1][1] + h * Card_Status[1][3]),	//����
								casino.Card_Back, 1);
			}
			else {
				DrawExtendGraph(w * Card_Status[1][0],								//�����W
								h * Card_Status[1][1],								//�����W
								(w * Card_Status[1][0] + w * Card_Status[1][2]),	//��
								(h * Card_Status[1][1] + h * Card_Status[1][3]),	//����
								casino.Cards[Card_Status[1][4]], 1);
			}



			switch (DT_Phase) {
				case 0:																		//�J�[�h��z��܂��B
					DrawString(w * 2, h * 71, "�ł́A�J�[�h���h���S���ƃ^�C�K�[�ɔz��܂�", 0xffffff, 1);
					++Anime_Count;
					if (Anime_Count < 50) {
						if (Card_Status[0][0] >= 25) Card_Status[0][0] -= 2;
						if (Card_Status[1][0] <= 55) Card_Status[1][0] += 2;
						if (Card_Status[0][1] <= 30) Card_Status[0][1] += 2;
						if (Card_Status[1][1] <= 30) Card_Status[1][1] += 2;
					}
					if (Anime_Count > 100) {
						DT_Phase = 1;
						Anime_Count = 0;
						Bet_Select = 0;
						Bet_Money = 0;
					}
					break;

				case 1:																		//�a�d�s�^�C��
					DrawString(w * 2, h * 71, "���ɓq���܂����H", 0xffffff, 1);
					for (int i = 0; i < 4; i++) {
						if (Bet_Select == i) color = blue_color;
						str.SuperString(w * 85, h * (73 + (size / 2) * i), Bet_Select_String[i], color, 1, size * 2);
						color = white_color;
					}
					if (inp.f_up) {
						if (--Bet_Select < 0) Bet_Select = 3;
					}
					if (inp.f_down) {
						if (++Bet_Select > 3) Bet_Select = 0;
					}
					if (inp.space) {
						DT_Phase = 2;
					}
					break;

				case 2:
					DrawString(w * 2, h * 71, "������a�d�s���܂���\n��F�@�P�f���Z\n���F�@�P�f���Z\n�E�F�@�P�O�f���Z\n���F�@�P�O�f���Z\n�{�^�������ła�d�s�m��", 0xffffff, 1);
					DrawFormatString(w * 85, h * 71, 0xffffff, "BET���z�F\n%9d\n\n�������F\n%9d", Bet_Money, ch.Return_Base_Status(&ch, 0));
					if (inp.f_up) {
						Bet_Money += 1;
					}
					if (inp.f_down) {
						Bet_Money -= 1;
					}
					if (inp.f_right) {
						Bet_Money += 10;
					}
					if (inp.f_left) {
						Bet_Money -= 10;
					}

					if (Bet_Money < 0)Bet_Money = 0;
					if (Bet_Money > ch.Return_Base_Status(&ch, 0)) Bet_Money = ch.Return_Base_Status(&ch, 0);

					if (inp.space) {
						ch.Add_Base_Status(&ch, 0, -Bet_Money);
						DT_Phase = 3;
					}

					break;

				case 3:
					DrawString(w * 2, h * 71, "�ł́A�J�[�h���߂���܂��B", 0xffffff, 1);
					++Anime_Count;
					if (Anime_Count < 100) {
						;
					}
					else if (Anime_Count < 200) {
						Back_or_Front[0] = 1;
						Back_or_Front[1] = 1;
					}
					if (Anime_Count > 200) {
						Anime_Count = 0;
						DT_Phase = 4;
					}
					break;

				case 4:
					DrawString(w * 2, h * 71, "���ʂ�..............\n", 0xffffff, 1);
					if ((Card_Status[0][4] % 13 + 1) > (Card_Status[1][4] % 13 + 1)) DT_Result = 0;
					if ((Card_Status[0][4] % 13 + 1) < (Card_Status[1][4] % 13 + 1)) DT_Result = 1;
					if ((Card_Status[0][4] % 13 + 1) == (Card_Status[1][4] % 13 + 1)) DT_Result = 2;
					if ((Card_Status[0][4]) == (Card_Status[1][4])) DT_Result = 3;

					if (Bet_Select == 0) {							//�h���S���ɓq���Ă��Ƃ�
						switch (DT_Result) {
							case 0:
								DT_Result_Money = Bet_Money * 2;
								break;

							case 1:
								DT_Result_Money = 0;
								break;

							case 2:
								DT_Result_Money = Bet_Money / 2;
								break;

							case 3:
								DT_Result_Money = Bet_Money / 2;
								break;
						}
					}
					if (Bet_Select == 1) {
						switch (DT_Result) {
							case 0:
								DT_Result_Money = 0;
								break;

							case 1:
								DT_Result_Money = Bet_Money * 2;
								break;

							case 2:
								DT_Result_Money = Bet_Money / 2;
								break;

							case 3:
								DT_Result_Money = Bet_Money / 2;
								break;
						}
					}
					if (Bet_Select == 2) {
						switch (DT_Result) {
							case 0:
								DT_Result_Money = 0;
								break;

							case 1:
								DT_Result_Money = 0;
								break;

							case 2:
								DT_Result_Money = Bet_Money * 11;
								break;

							case 3:
								DT_Result_Money = Bet_Money * 11;
								break;
						}
					}
					if (Bet_Select == 3) {
						switch (DT_Result) {
							case 0:
								DT_Result_Money = 0;
								break;

							case 1:
								DT_Result_Money = 0;
								break;

							case 2:
								DT_Result_Money = Bet_Money * 50;
								break;

							case 3:
								DT_Result_Money = Bet_Money * 50;
								break;
						}
					}
					DrawFormatString(w * 2, h * 75, 0xffffff, "�u%s�v�ł��B%9d�f�̕����߂��ɂȂ�܂��B", DT_Result_Sting[DT_Result], DT_Result_Money);
					

					str.SuperString(w * 85, h * 80, "�߂�", 0xff0000, 1, size * 3);
					if (inp.space) {
						ch.Add_Base_Status(&ch, 0, DT_Result_Money);
						Depth = 0;
						DT_Phase = 0;
						Dragon_Tiger = false;
						DT_Result = 0;
						Bet_Money = 0;
						DT_Result_Money = 0;
					}

					break;
			}
		}

		/*�J�W�m�E�H�[���v���C*/
		if (Casino_War) {

			/*����̃J�[�h�̕`��*/
			if (Back_or_Front[0] == 0) {
				DrawExtendGraph(w * Card_Status[0][0],					//�����W
					h * Card_Status[0][1],								//�����W
					(w * Card_Status[0][0] + w * Card_Status[0][2]),	//��
					(h * Card_Status[0][1] + h * Card_Status[0][3]),	//����
					casino.Card_Back, 1);
			}
			else {
				DrawExtendGraph(w * Card_Status[0][0],					//�����W
					h * Card_Status[0][1],								//�����W
					(w * Card_Status[0][0] + w * Card_Status[0][2]),	//��
					(h * Card_Status[0][1] + h * Card_Status[0][3]),	//����
					casino.Cards[Card_Status[0][4]], 1);

			}

			/*�����̃J�[�h�̕`��*/
			if (Back_or_Front[1] == 0) {
				DrawExtendGraph(w * Card_Status[1][0],					//�����W
					h * Card_Status[1][1],								//�����W
					(w * Card_Status[1][0] + w * Card_Status[1][2]),	//��
					(h * Card_Status[1][1] + h * Card_Status[1][3]),	//����
					casino.Card_Back, 1);
			}
			else {
				DrawExtendGraph(w * Card_Status[1][0],					//�����W
					h * Card_Status[1][1],								//�����W
					(w * Card_Status[1][0] + w * Card_Status[1][2]),	//��
					(h * Card_Status[1][1] + h * Card_Status[1][3]),	//����
					casino.Cards[Card_Status[1][4]], 1);
			}

			switch (CW_Phase) {
				case 0:
					DrawString(w * 2, h * 51, "�ł́A�J�[�h��z��܂��B", 0xffffff, 1);
					++Anime_Count;
					if (Anime_Count < 50) {
						if (Card_Status[0][0] >= 45) Card_Status[0][0] -= 1;
						if (Card_Status[1][0] >= 45) Card_Status[1][0] -= 1;
						if (Card_Status[0][1] <= 7) Card_Status[0][1] += 1;
						if (Card_Status[1][1] <= 50) Card_Status[1][1] += 2;
					}
					if (Anime_Count > 100) {
						CW_Phase = 1;
						Anime_Count = 0;
						Bet_Select = 0;
					}
					break;

				case 1:
					DrawString(w * 2, h * 51, "����ł͂a�d�s�^�C���Ɉڂ�܂��B\n������a�d�s���܂���\n��F�@�P�f���Z\n���F�@�P�f���Z\n�E�F�@�P�O�f���Z\n���F�@�P�O�f���Z\n�{�^�������ła�d�s�m��", 0xffffff, 1);
					DrawFormatString(w * 85, h * 71, 0xffffff, "BET���z�F\n%9d\n\n�������F\n%9d", Bet_Money, ch.Return_Base_Status(&ch, 0));
					if (inp.f_up) {
						Bet_Money += 1;
					}
					if (inp.f_down) {
						Bet_Money -= 1;
					}
					if (inp.f_right) {
						Bet_Money += 10;
					}
					if (inp.f_left) {
						Bet_Money -= 10;
					}

					if (Bet_Money < 0)Bet_Money = 0;
					if (Bet_Money > ch.Return_Base_Status(&ch, 0)) Bet_Money = ch.Return_Base_Status(&ch, 0);

					if (inp.space) {
						ch.Add_Base_Status(&ch, 0, -Bet_Money);
						CW_Phase = 2;
					}
					break;

				case 2:
					DrawString(w * 2, h * 51, "�uTIE�x�b�g�v���܂����H", 0xffffff, 1);
					for (int i = 0; i < 2; i++) {
						if (CW_Tie_Bet == i) color = blue_color;
						str.SuperString(w * 85, h * (73 + (size / 2) * i), CW_TieBet_String[i], color, 1, size * 2);
						color = white_color;
					}
					if (inp.f_up) {
						if (--CW_Tie_Bet < 0) CW_Tie_Bet = 1;
					}
					if (inp.f_down) {
						if (++CW_Tie_Bet > 1) CW_Tie_Bet = 0;
					}
					if (inp.space) {
						CW_Phase = 3;
					}
					break;

				case 3:
					DrawString(w * 2, h * 51, "�ł́A�J�[�h���߂���܂��B", 0xffffff, 1);
					++Anime_Count;
					if (Anime_Count < 100) {
						;
					}
					else if (Anime_Count < 200) {
						Back_or_Front[0] = 1;
						Back_or_Front[1] = 1;
					}
					if (Anime_Count > 200) {
						Anime_Count = 0;
						CW_Phase = 4;
					}
					break;

				case 4:
					
					if (CW_Tie_Bet == 1) {
						if ((Card_Status[0][4] % 13 + 1) > (Card_Status[1][4] % 13 + 1)) { CW_Phase = 5; CW_Result = 0; CW_Result_Money = 0; }
						if ((Card_Status[0][4] % 13 + 1) < (Card_Status[1][4] % 13 + 1)) { CW_Phase = 5; CW_Result = 0; CW_Result_Money = 0; }
						if ((Card_Status[0][4] % 13 + 1) == (Card_Status[1][4] % 13 + 1)) {
							CW_Phase = 5;
							CW_Result = 1;
							CW_Result_Money = Bet_Money * 11;
						}
					}
					else {
						if ((Card_Status[0][4] % 13 + 1) > (Card_Status[1][4] % 13 + 1)) { CW_Phase = 5; CW_Result = 0; CW_Result_Money = 0; }
						if ((Card_Status[0][4] % 13 + 1) < (Card_Status[1][4] % 13 + 1)) { CW_Phase = 5; CW_Result = 1; CW_Result_Money = Bet_Money * 2; }
						if ((Card_Status[0][4] % 13 + 1) == (Card_Status[1][4] % 13 + 1)) { CW_Result = 2; CW_Phase = 6; }
					}

					break;

				case 5:
					DrawString(w * 2, h * 51, "���ʂ�..............\n", 0xffffff, 1);
					DrawFormatString(w * 2, h * 75, 0xffffff, "�u%s�v�ł��B\n%9d�f\n�̕����߂��ɂȂ�܂��B", CW_Result_String[CW_Result], CW_Result_Money);

					

					str.SuperString(w * 85, h * 80, "�߂�", 0xff0000, 1, size * 3);
					if (inp.space) {
						ch.Add_Base_Status(&ch, 0, CW_Result_Money);
						Bet_Money = 0;
						CW_Tie_Select = 0;
						CW_Result = 0;
						CW_Phase = 0;
						CW_Result_Money = 0;
						CW_Tie_Bet = 0;
						CW_Tie_Select = 0;
						Casino_War = false;
						Depth = 0;
					}
					break;

				case 6:
					DrawString(w * 2, h * 51, "���ʂ�..............\n", 0xffffff, 1);
					DrawFormatString(w * 2, h * 75, 0xffffff, "�u%s�v�ł��B\n�u�T�����_�[(�~�Q)�v\n��\n�u�E�H�[(���z�x�b�g�ōĐ�)�v\n�̂����ꂩ��I�����Ă�������", CW_Result_String[CW_Result]);
					for (int i = 0; i < 2; i++) {
						if (CW_Tie_Select == i) color = blue_color;
						str.SuperString(w * 85, h * (73 + (size / 2) * i), CW_Tie_Select_String[i], color, 1, size * 2);
						color = white_color;
					}
					if (inp.f_up) {
						if (--CW_Tie_Select < 0) CW_Tie_Select = 1;
					}
					if (inp.f_down) {
						if (++CW_Tie_Select > 1) CW_Tie_Select = 0;
					}
					if (inp.space) {
						if (CW_Tie_Select == 0) {					//�~�Q�B�x�b�g�z�̔������x����
							ch.Add_Base_Status(&ch, 0, Bet_Money / 2);
							Bet_Money = 0;
							CW_Tie_Select = 0;
							CW_Result = 0;
							CW_Phase = 0;
							CW_Result_Money = 0;
							CW_Tie_Bet = 0;
							CW_Tie_Select = 0;
							Casino_War = false;
							Depth = 0;
						}
						if (CW_Tie_Select == 1) {
							Bet_Money *= 2;
							Card_Init();
							CW_Phase = 0;
						}
					}
					
					break;
			}
		}
	}

	void Casino_Game_Info(float w,float h,int size) {
		
		/*�h���S���^�C�K�[�̐���*/
		if (DT_Info) {
			DrawExtendGraph(w * 10, h * 5, w * 90, h * 65, casino.Dragon_Tiger_img, 1);
			str.SuperString(w * 2, h * 71, "�h���S���^�C�K�[�̃��[���͈ȉ��̒ʂ肾�B\n�E��̃h���S���ƃ^�C�K�[�Ɉꖇ���J�[�h���z����\n�E�u�h���S���v�u�^�C�K�[�v�u�^�C�v�u�X�[�e�b�h�^�C�v\n�@�̂����ꂩ��BET���邱�Ƃ��ł���\n�E�q���ɏ����Ƃ��o����Ή摜�̔z������������", 0xffffff, 0, size * 2);
		
			str.SuperString(w * 85, h * 80, "�߂�", 0xff0000, 1, size * 3);
		}

		/*�J�W�m�E�H�[�̐���*/
		if (CW_Info) {
			DrawExtendGraph(w * 10, h * 5, w * 90, h * 65, casino.Casino_War_img, 1);
			str.SuperString(w * 2, h * 71, "�J�W�m�E�H�[�̃��[���͈ȉ��̒ʂ肾�B\n�E�f�B�[���[�ƃv���C���[�ɃJ�[�h���ꖇ���z����\n�E�������m�F���đ傫�����̏����ƂȂ�B�������A�^�C�̏ꍇ��\n�@�u�T�����_�[(�~�Q)�v���u�E�H�[(���zBET�ł������)�v\n�@��I�Ԃ��Ƃ��ł���\n�ETIE�x�b�g�������ꍇ��TIE�ȊO�͕����ƂȂ�\n�E�q���ɏ����Ƃ��o����Ή摜�̔z������������", 0xffffff, 0, size * 2);

			str.SuperString(w * 85, h * 80, "�߂�", 0xff0000, 1, size * 3);
		}

	}

private:
	int Depth = 0;								//�J�W�m���j���[�̂�ׂ�
	int Depth_Select[4] = { 0 };				//Depth���Ƃ̑I��
	unsigned int color = 0xffffff;				//�����̐F
	unsigned int white_color = 0xffffff;		//���F
	unsigned int blue_color = 0x6666aa;			//�F
	char Depth_Select_String[4][2][20] = {		//Depth���Ƃ̑I����
		{"�V��","�X�ɖ߂�"},
		{"�h���S���^�C�K�[","�J�W�m�E�H�["},
		{"���","�����𕷂�"},
		{"���","�����𕷂�"}
	};

	int Bet_Money = 0;							//�|����
	int Bet_Select = 0;							//�|���I��
	char Bet_Select_String[4][20] = {			//�I����
		"�h���S��",
		"�^�C�K�[",
		"�^�C",
		"�X�[�e�b�h�^�C"
	};
	int Anime_Count = 0;						//�Q�[���̃A�j���[�V�����J�E���g
	int Card_Status[2][5] = { 0 };				//����Ǝ����̃J�[�h�X�e�[�^�X(�����W�A�����W�A���A�����A�����ƃ}�[�N)
	int Back_or_Front[2] = { 0 };				//����Ǝ����̃J�[�h�������\��(0�F���A1�F�\)
};

Casino_System cas;