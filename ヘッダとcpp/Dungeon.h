#pragma once

#include "GameSys.h"
void Status_Disp(void);
int Return_Item(int item_select);
void Menu_Item(int item_select);
void Use_Equipment_Item(int item_select);		//アイテム装備/使う
void Delete_Item(int item_select);				//アイテム削除

void DungeonMap(int w, int h);

struct Dungeon_Sys {

	int Cool_Time = 0;							//戦闘エンカウントのクールタイム

	int Dungeon_Num = 0;						//ダンジョンの番号

	bool Boss_Flg[3] = { true,true,true };		//各ダンジョンのボスフラグ

	int Enemy_Num = 0;							//ダンジョン内でエンカウントした敵
	int Enemy_Hp = 0;							//敵の体力
	int Enemy_x = 0;							//敵のx座標
	int Enemy_y = 0;							//敵のy座標

	bool Effect_Flg = 0;							//エフェクトのフラグ()

	/*ダンジョン内ボスの表示*/
	void Dungeon_Enemy_Disp() {
		
		/*ボスのあれ*/

		if (Dungeon_Num == 0) {
			if (Boss_Flg[0]) {
				switch (Enemy_Anim_Num)
				{
				case Dungeon::Idle:
					if (Enemy_Anim_Count > dungeon.Enemy_Idle_Lim[3] * 20 - 1) Enemy_Anim_Count = 0;
					DrawExtendGraph(dungeon.Battle_Enemy_Pos[3][0] + dungeon.move,
						-50,
						(dungeon.Battle_Enemy_Pos[3][0] + dungeon.Enemy_Size[3][0]) + dungeon.move,
						(-50 + dungeon.Enemy_Size[3][1]),
						dungeon.Enemy_Idle[3][Enemy_Anim_Count / 20], TRUE);
					break;
				}

				Enemy_Anim_Count += Enemy_Anim_Speed;
			}
		}
		else if (Dungeon_Num == 1) {
			if (Boss_Flg[1]) {
				switch (Enemy_Anim_Num)
				{
				case Dungeon::Idle:
					if (Enemy_Anim_Count > dungeon.Enemy_Idle_Lim[3] * 20 - 1) Enemy_Anim_Count = 0;
					DrawExtendGraph(dungeon.Battle_Enemy_Pos[3][0] + dungeon.move,
						-50,
						(dungeon.Battle_Enemy_Pos[3][0] + dungeon.Enemy_Size[3][0]) + dungeon.move,
						(-50 + dungeon.Enemy_Size[3][1]),
						dungeon.Enemy_Idle[7][Enemy_Anim_Count / 20], TRUE);
					break;
				}

				Enemy_Anim_Count += Enemy_Anim_Speed;
			}
		}
		else if (Dungeon_Num == 2) {
			if (Boss_Flg[2]) {
				switch (Enemy_Anim_Num)
				{
				case Dungeon::Idle:
					if (Enemy_Anim_Count > dungeon.Enemy_Idle_Lim[3] * 20 - 1) Enemy_Anim_Count = 0;
					DrawExtendGraph(dungeon.Battle_Enemy_Pos[3][0] + dungeon.move,
						-50,
						(dungeon.Battle_Enemy_Pos[3][0] + dungeon.Enemy_Size[3][0]) + dungeon.move,
						(-50 + dungeon.Enemy_Size[3][1]),
						dungeon.Enemy_Idle[11][Enemy_Anim_Count / 20], TRUE);
					break;
				}

				Enemy_Anim_Count += Enemy_Anim_Speed;
			}
		}

	}

	/*ダンジョン内ボスの更新*/
	void Dungeon_Enemy_Update() {

		/*コボルトの当たり判定*/
		if (ch.Dungeon_Boss_Encount(&ch, 4600, -50, 4900, 250) == 1 && Dungeon_Num == 0 && Boss_Flg[0]) {
			ch.isBattle = true;
			Enemy_Num = 3;
			ch.x = 100;
			ch.y = 250;
		}

		/*どくろの当たり判定*/
		if (ch.Dungeon_Boss_Encount(&ch, 4600, -50, 4900, 250) == 1 && Dungeon_Num == 1 && Boss_Flg[1]) {
			ch.isBattle = true;
			Enemy_Num = 7;
			ch.x = 100;
			ch.y = 250;
		}

		/*ドラゴンの当たり判定*/
		if (ch.Dungeon_Boss_Encount(&ch, 4600, -50, 4900, 250) == 1 && Dungeon_Num == 2 && Boss_Flg[2]) {
			ch.isBattle = true;
			Enemy_Num = 11;
			ch.x = 100;
			ch.y = 250;
		}

	}

	/*バトル中の敵の表示*/
	void Battle_Draw() {

		/*敵の描画*/
		switch (Enemy_Anim_Num)
		{
		case Dungeon::Idle:
			if (Enemy_Anim_Count > dungeon.Enemy_Idle_Lim[Enemy_Num] * 20 - 1) Enemy_Anim_Count = 0;
			DrawExtendGraph(Enemy_x + dungeon.move, Enemy_y, (Enemy_x + dungeon.Enemy_Size[Enemy_Num][0]) + dungeon.move, (Enemy_y + dungeon.Enemy_Size[Enemy_Num][1]), dungeon.Enemy_Idle[Enemy_Num][Enemy_Anim_Count / 20], TRUE);
			break;
		case Dungeon::Move:
			if (Enemy_Anim_Count > dungeon.Enemy_Move_Lim[Enemy_Num] * 20 - 1) Enemy_Anim_Count = 0;
			DrawExtendGraph(Enemy_x + dungeon.move, Enemy_y, (Enemy_x + dungeon.Enemy_Size[Enemy_Num][0]) + dungeon.move, (Enemy_y + dungeon.Enemy_Size[Enemy_Num][1]), dungeon.Enemy_Move[Enemy_Num][Enemy_Anim_Count / 20], TRUE);
			break;
		case Dungeon::Attack:
			if (Enemy_Anim_Count > dungeon.Enemy_Attack_Lim[Enemy_Num] * 20 - 1) { Enemy_Anim_Count = 0; ch.Add_Chara_Status(&ch, 2, -dungeon.Enemy_Status[Enemy_Num][1]); }
			DrawExtendGraph(Enemy_x + dungeon.move, Enemy_y, (Enemy_x + dungeon.Enemy_Size[Enemy_Num][0]) + dungeon.move, (Enemy_y + dungeon.Enemy_Size[Enemy_Num][1]), dungeon.Enemy_Attack[Enemy_Num][Enemy_Anim_Count / 20], TRUE);

			break;
		}

		Enemy_Anim_Count += Enemy_Anim_Speed;
		
	}

	/*バトルの進行*/
	void Battle_Update() {
		
		switch (Battle_Phase)
		{
			case 0:
				Battle_Turn = GetRand(1);
				//Battle_Turn = 0;
				ch.x = 100;
				ch.y = 1150 + dungeon.up - ch.c_size + 144.5f;
				Enemy_Hp = dungeon.Enemy_Status[Enemy_Num][0];
				if (dungeon.Battle_Enemy_Pos[Enemy_Num][0] != -99) Enemy_x = dungeon.Battle_Enemy_Pos[Enemy_Num][0];
				else Enemy_x = ch.x + ch.c_size + 420 - dungeon.move;
				if (dungeon.Battle_Enemy_Pos[Enemy_Num][1] != -99) Enemy_y = dungeon.Battle_Enemy_Pos[Enemy_Num][1];
				Battle_Init();
				break;

			case 1:
				/*プレイヤーのターン*/
				if (Battle_Turn == 0) {
					str.SuperString(ch.w / 2, ch.h4, "プレイヤーのターン", 0xffffff, 1, 24);
					if (!menu.isMenu && !menu.isGage_Menu && !Effect_Flg) ch.Move(&ch);

					if (inp.x && !Effect_Flg) {
						DrawBox(ch.x + ch.c_Hsize_e, ch.y, (ch.x + ch.c_Hsize_e) + ch.c_size, ch.y + ch.c_size, 0xff0000, false);
						Enemy_Hp -= (ch.Return_Chara_Status(&ch, 3) + ch.Return_Chara_Status(&ch, 4));
						if (wep.serial_num != 0 && wep.serial_num <= 3) Effect_Num = 1;
						else if (wep.serial_num != 0 && wep.serial_num <= 5) Effect_Num = 3;

						Effect_Flg = true;
					}
					if (inp.y && !Effect_Flg) {
						Enemy_Hp -= (ch.Return_Chara_Status(&ch, 3) + ch.Return_Chara_Status(&ch, 4));
						if (wep.serial_num != 0 && wep.serial_num <= 3) Effect_Num = 2;
						else if (wep.serial_num != 0 && wep.serial_num <= 5) Effect_Num = 4;

						Effect_Flg = true;
					}

					if (Effect_Flg) Battle_Attack_Effect_Disp();
				}
				/*敵のターン*/
				if (Battle_Turn == 1) {
					str.SuperString(ch.w / 2, ch.h4, "敵のターン", 0xffffff, 1, 24);
					Battle_Enemy_Update();
				}

				DrawFormatString(100, 100, 0xffffff, "e_num %d\ne_cnt %d", Effect_Num, Effect_Count);
				DrawFormatString(200, 100, 0xffffff, "en_num %d\nene_x %d\nene_y %d\nene_hp %d", Enemy_Num, Enemy_x, Enemy_y, Enemy_Hp);


				SetFontSize(30);
				DrawFormatString(ch.w / 2 - 90, ch.h4 / 2, 0xffffff, "残り%2d秒", battle_Time / 60);
				SetFontSize(16);

				battle_Time -= 1;		//時間を減らす
				if (battle_Time <= 0) {
					Battle_Phase = 2;
				}



				/*敵のHPが0になったら*/
				if (Enemy_Hp < 0) {
					Battle_Finish_Process();
					ch.Add_Exp(&ch, dungeon.Enemy_Status[Enemy_Num][3]);

				}

				/*こっちの体力が0になったら*/
				if (ch.Return_Chara_Status(&ch, 2) < 0) {
					Battle_Finish_Process();
					g_GameState = GAME_BASE;
				}
				break;

			case 2:
				ch.y = 1150 + dungeon.up - ch.c_size + 144.5f;
				Battle_Turn = 1 - Battle_Turn;
				Battle_Init();
				break;

		}

	}

	/*バトルの初期化*/
	void Battle_Init() {
		Enemy_Anim_Count = 0;
		Enemy_Anim_Num = 0;
		Effect_Count = 0;
		Effect_Num = 0;
		Effect_Flg = false;
		ch.Turn = Battle_Turn;
		battle_Time = Battle_Limit[Battle_Turn];
		Battle_Phase = 1;
	}

	/*バトル終了時の処理*/
	void Battle_Finish_Process() {
		Enemy_Anim_Count = 0;
		Enemy_Anim_Num = 0;
		Battle_Phase = 0;
		battle_Time = 0;
		Battle_Turn = 0;
		Effect_Count = 0;
		ch.x = 100;
		ch.y = 250;
		Cool_Time = 0;
		Effect_Flg = false;
		if (Enemy_Num == 3 || Enemy_Num == 7 || Enemy_Num == 11) {
			Boss_Flg[Enemy_Num % 3] = false;
			menu.Inclease_Gage(4, 50);			//ゲージを増やす
		}
		ch.isBattle = false;
	}

	/*バトル中のボスの動き*/
	void Battle_Enemy_Update() {
		//DrawFormatString(100, 100, 0xffffff, "px:%d ex:%d", ch.x + ch.c_Hsize_e, dungeon.Cobolt_x - 50);
		const int Ppos = ch.x + ch.c_Hsize_s - dungeon.move + (ch.c_Hsize_s + ch.c_Hsize_e) / 2;

		if (Ppos <= Enemy_x + dungeon.Enemy_Attacks[Enemy_Num][0]) {
			Enemy_Anim_Num = 1;
			Enemy_x -= dungeon.Enemy_Status[Enemy_Num][2];
		}
		else if (Ppos >= Enemy_x + dungeon.Enemy_Attacks[Enemy_Num][1]) {
			Enemy_Anim_Num = 1;
			Enemy_x += dungeon.Enemy_Status[Enemy_Num][2];
		}
		else {
			Enemy_Anim_Num = 2;
		}
	}

	/*バトル中のエフェクト*/
	void Battle_Attack_Effect_Disp() {
		
		switch(Effect_Num)
		{
			case 1:
				DrawGraph(ch.x + ch.c_Hsize_e, ch.y, dungeon.Sword_Effect1[Effect_Count / dungeon.Effect_Speed[Effect_Num]], TRUE);
				break;

			case 2:
				DrawGraph(ch.x + ch.c_size, ch.y - ch.c_size, dungeon.Sword_Effect2[Effect_Count / dungeon.Effect_Speed[Effect_Num]], TRUE);
				break;

			case 3:
				DrawGraph(Enemy_x + dungeon.move + dungeon.Enemy_Size[Enemy_Num][0] / 2 - 120, Enemy_y + dungeon.Enemy_Size[Enemy_Num][1] / 2 - 120, dungeon.Magic_Effect1[Effect_Count / dungeon.Effect_Speed[Effect_Num]], TRUE);
				//DrawGraph(ch.x + ch.c_Hsize_e, ch.y, dungeon.Magic_Effect1[Effect_Count / dungeon.Effect_Speed[Effect_Num]], TRUE);
				break;

			case 4:
				DrawGraph(ch.x + ch.size, ch.y - 30, dungeon.Magic_Effect2[Effect_Count / dungeon.Effect_Speed[Effect_Num]], TRUE);
				break;
		}

		Effect_Count += Effect_Anim_Speed;
		if (Effect_Count > dungeon.Effect_Anim_Num[Effect_Num] * dungeon.Effect_Speed[Effect_Num] - 1) {
			Effect_Count = 0;
			Effect_Flg = false;
		}

	}

	/*バトル中のヒット時のエフェクト*/
	void Battle_Hit_Effect_Disp() {
		
	}


private:
	int Enemy_Anim_Count = 0;			//敵アニメーションのカウント
	int Enemy_Anim_Num = 0;				//敵アニメーションの行動切り替え
	int Enemy_Anim_Speed = 2;			//敵アニメーションの速度

	
	int Effect_Count = 0;				//エフェクトのカウント
	int Effect_Num = 0;					//攻撃の種類

	int E_Hit_Count = 0;				//ヒットエフェクトのカウント
	int Effect_Anim_Speed = 2;			//エフェクトアニメーションの速度

	int Battle_Phase = 0;				//バトルの進行
	int Battle_Turn = 0;				//バトルのﾀｰﾝ制
	int battle_Time = 0;				//バトルの残り時間
	int Battle_Limit[2] = { 1200,600 };	//ﾀｰﾝの制限時間
};

extern Dungeon_Sys d_sys;