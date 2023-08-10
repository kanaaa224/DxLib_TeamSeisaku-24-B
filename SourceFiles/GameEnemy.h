﻿/********************************
* ゲームエネミー処理
* 編集者：
********************************/
#pragma once
#include "main.h"

#define ENEMYMAX  3

class GameEnemy {
private:
	int frameCounter;
	int currentStateDuration;
	int nextStateChange;
	bool isChasingPlayer;

	Person enemy;

	int lagCounter;
	int lagTime;

	int TimeDuration = 60;
	int currenttime = 0;

	struct Vector {
		float x;
		float y;
	};

	enum class EnemyState {
		CHASE,
		CONTINUE_CHASE,
		ESCAPE,
		AVOID
	};

	EnemyState currentState = EnemyState::CHASE;
	int stateTimer;
	int stateDuration;

	float moveSpeedMax = 2.3f;
	//Vector moveSpeed = { 1.0f, 0.5f };
	float moveSpeed;
	float moveSpeedX;
	float moveSpeedY;
	float inertiaCoefficient = 0.5f;

	float XDistance;
	float YDistance;
	

	int anim;

	int r_enemy[18];
	int g_enemy[18];
	int p_enemy[18];
	

	// プレイヤーの左上・右上座標
	Collide playerCollide;

public:
	// コンストラクタ
	GameEnemy();

	// デストラクタ
	~GameEnemy();

	// 初期化
	void Init();

	// 更新
	void Update();

	// 描画
	void Draw() const;

	void SetEnemyState(int State) {
		enemy.state = State;
	}

	int GetEnemyState() {
		return enemy.state;
	}
	// プレイヤーの衝突座標を設定
	void SetPlayerCollide(Collide collide) {
		playerCollide = collide;
	};
	void ChacePlayer();
	void RunAwayfromPlayer();
	void AvoidPlayer();
};
class EnemyFish {
private:
	int frameCounter;


	int img[10];

	int flg, anim;
	int x;
	int y;

public:
	EnemyFish() {
		frameCounter = 0;

		flg = 0;
		anim = 0;
		x = 0;
		y = 0;

		LoadDivGraph("Resources/Images/Enemy/Enemy_FishAnimation.png", 10, 5, 2, 64, 64, img);
	};

	~EnemyFish() {
		for (int i = 0; i < 10; i++) {
			DeleteGraph(img[i]);
		}
	};

	void Update() {
		x = 300;
		y = SCREEN_HEIGHT - 50;

		if (flg) {
			if (frameCounter++ % 7 == 0) {
				if (flg == 1) {
					if (anim < 2) {
						anim++;
					}
				}
				else if (flg == 2) {
					if (anim > 0) {
						anim--;
					}
					else flg = 0;
				};
			}
		}
	};

	void Draw() const {
		if(flg) DrawRotaGraph(x, y, 1.0f, 0, img[anim], TRUE, FALSE);
	};

	void Spawn() {
		if (!flg) flg = 1;
		else if (flg && anim == 2) flg = 2;
	};
};
