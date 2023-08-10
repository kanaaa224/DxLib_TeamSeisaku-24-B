﻿/********************************
* ゲームエネミー処理
* 編集者：
********************************/
#include "main.h"

GameEnemy::GameEnemy() {
	Init();
	LoadDivGraph("Resources/Images/Enemy/Enemy_R_Animation.png", 18, 6, 3, 64, 64, r_enemy);
	LoadDivGraph("Resources/Images/Enemy/Enemy_G_Animation.png", 18, 6, 3, 64, 64, g_enemy);
	LoadDivGraph("Resources/Images/Enemy/Enemy_P_Animation.png", 18, 6, 3, 64, 64, p_enemy);

	isChasingPlayer = false;
	nextStateChange = rand() % 300 + 180;
	currentStateDuration = 0;

	anim = 8;
};

GameEnemy::~GameEnemy() {
	for (int i = 0; i < 18; i++) {
		DeleteGraph(r_enemy[i]);//黄色の敵
		DeleteGraph(g_enemy[i]);//緑色の敵
		DeleteGraph(p_enemy[i]);//ピンクの敵
	}
}

void GameEnemy::Init() {

	enemy.hp = 1;
	enemy.position.x = 50 + 15;
	enemy.position.y = 405 - 200;
	enemy.size.width = 15;
	enemy.size.height = 25;

	
};

void GameEnemy::Update() {

	frameCounter++;

	if (frameCounter % 3 == 0) anim++;
	if (anim >= 12) anim = 8;

	XDistance = playerCollide.ul.x - enemy.position.x;
	YDistance = playerCollide.ul.y - enemy.position.y;

	float Distance = sqrt(XDistance * XDistance + YDistance * YDistance);

	const float escapeThreshold = 50.0f;
	bool isPlayerneaby = (fabs(XDistance) < escapeThreshold) && (YDistance < 0) && (fabs(YDistance) < escapeThreshold);

	currenttime++;

	// 距離による判定の閾値
	const float closeDistance = 50.0f; // プレイヤーとの近距離の閾値
	const float farDistance = 200.0f; // プレイヤーとの遠距離の閾値

	/*const float escapeThreshold = 50.0f;
	bool isPlayernearby = (fabs(XDistance) < escapeThreshold) && (YDistance < 0) && (fabs(YDistance) < escapeThreshold);*/

	// タイマーの値が持続時間を超えたら、新しい行動ステートをランダムに選択する
	if (currenttime >= TimeDuration) {
		int randomValue = rand() % 100;
		if (randomValue < 40) { // 40%の確率で追いかける
			currentState = EnemyState::CHASE;
		}
		else if (randomValue < 70) { // 30%の確率で避ける
			currentState = EnemyState::AVOID;
		}
		else { // 30%の確率で逃げる
			currentState = EnemyState::ESCAPE;
		}
		currenttime = 0; // タイマーリセット
	}
	// 距離による判定と行動の実行
	if (YDistance < 0 && Distance < closeDistance) { // プレイヤーが上から近い場合
		currentState = EnemyState::CONTINUE_CHASE; // 追いかけ続ける行動を実行
	}
	else if (Distance < closeDistance) { // プレイヤーが近い場合
		currentState = EnemyState::AVOID; // 避ける行動を実行
	}
	else if (Distance > farDistance) { // プレイヤーが遠い場合
		currentState = EnemyState::CHASE; // 追いかける行動を実行
	}

	// 各行動ステートに応じた行動を実行
	switch (currentState) {
	case EnemyState::CHASE:
		ChacePlayer();
		break;
	case EnemyState::ESCAPE:
		RunAwayfromPlayer();
		break;
	case EnemyState::AVOID:
		AvoidPlayer();
		break;
	}

	bool wallHit = false;

	//画面上の判定
	if (enemy.position.y - enemy.size.height / 2 <= 0) {
		wallHit = true;
	}

	if (wallHit) inertia.y *= -1;

	wallHit = false;

	//地面


	// 天井
	if (enemy.state == 2) {
		enemy.position.y = collideData.lr.y + enemy.size.height + 1;

		wallHit = true;
	};

	if (wallHit) inertia.y *= -1;

	wallHit = false;

	if (enemy.state == 3) {
		enemy.position.x = collideData.ul.x - enemy.size.width - 1;

		wallHit = true;
	}
	if (enemy.state == 4) {
		//player.position.x++;
		enemy.position.x = collideData.lr.x + enemy.size.width + 1;

		wallHit = true;
	};

	if (wallHit) inertia.x = -inertia.x;

	if (enemy.position.x <= 0) enemy.position.x = SCREEN_WIDTH - 1;      // 画面左端時
	else if (SCREEN_WIDTH <= enemy.position.x) enemy.position.x = 0 + 1; // 画面右端時
}

void GameEnemy::Draw() const{
	//int anim = 0;

	////anim = frameCounter / 7 % 5;

	////if (speed[MOVE] == 0) { // 待機 8~12
	//anim += frameCounter / 25 % 2;
	////anim +=  14;		
	////}  

	DrawRotaGraph2((int)enemy.position.x, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, r_enemy[anim], TRUE);
	DrawRotaGraph2((int)enemy.position.x - SCREEN_WIDTH, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, r_enemy[anim], TRUE);
	DrawRotaGraph2((int)enemy.position.x + SCREEN_WIDTH, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, r_enemy[anim], TRUE);
	//仮当たり判定の座標
	DrawBox(enemy.position.x, enemy.position.y, 85, 235, 0xffffff, FALSE);
	DrawBox(45, 175, 85, 200, 0xffffff, FALSE);

	DrawRotaGraph2((int) + 30, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, g_enemy[anim], TRUE);
	DrawRotaGraph2((int)enemy.position.x - SCREEN_WIDTH, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, g_enemy[anim], TRUE);
	DrawRotaGraph2((int)enemy.position.x + SCREEN_WIDTH, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, g_enemy[anim], TRUE);

	DrawRotaGraph2((int)enemy.position.x + 60, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, p_enemy[anim], TRUE);
	DrawRotaGraph2((int)enemy.position.x - SCREEN_WIDTH, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, p_enemy[anim], TRUE);
	DrawRotaGraph2((int)enemy.position.x + SCREEN_WIDTH, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, p_enemy[anim], TRUE);
}

void GameEnemy::ChacePlayer() {
	const float ChaseSpeedMax = 0.8f;

	float ChaseSpeedX = (enemy.position.x - playerCollide.ul.x) * 0.1f;
	moveSpeed = moveSpeed * inertiaCoefficient + ChaseSpeedX * (1.0f - inertiaCoefficient);

	float ChaseSpeedY = (enemy.position.y - playerCollide.ul.y) * 0.1f;
	moveSpeed = moveSpeed * inertiaCoefficient + ChaseSpeedY * (1.0f - inertiaCoefficient);

	ChaseSpeedX = ChaseSpeedX;
	ChaseSpeedY = ChaseSpeedY;

	if (lagCounter <= lagTime) {
		float Progress = static_cast<float>(lagCounter) / lagTime;
		moveSpeedX = moveSpeedX * inertiaCoefficient + ChaseSpeedX * (1.0f - inertiaCoefficient);
		moveSpeedY = moveSpeedY * inertiaCoefficient + ChaseSpeedY * (1.0f - inertiaCoefficient);
		lagCounter++;
	}
	else {
		moveSpeedX = -ChaseSpeedX;
		moveSpeedY = -ChaseSpeedY;
	}

	float currentSpeed = sqrt(moveSpeedX * moveSpeedX + moveSpeedY * moveSpeedY);
	if (currentSpeed > ChaseSpeedMax) {
		float ratio = ChaseSpeedMax / currentSpeed;
		moveSpeedX *= ratio;
		moveSpeedY *= ratio;
	}

	enemy.position.x += moveSpeedX;
	enemy.position.y += moveSpeedY;
}

void GameEnemy::RunAwayfromPlayer()
{
	const float RunawaySpeedMax = 0.5f;

	float EscapeSpeedX = (enemy.position.x - playerCollide.ul.x) * 0.1f;
	moveSpeed = moveSpeed * inertiaCoefficient + EscapeSpeedX * (1.0f - inertiaCoefficient);

	float EscapeSpeedY = (enemy.position.y - playerCollide.ul.y) * 0.1f;
	moveSpeed = moveSpeed * inertiaCoefficient + EscapeSpeedY * (1.0f - inertiaCoefficient);

	EscapeSpeedX = EscapeSpeedX;
	EscapeSpeedY = EscapeSpeedY;

	if (lagCounter <= lagTime) {
		float Progress = static_cast<float>(lagCounter) / lagTime;
		moveSpeedX = moveSpeedX * inertiaCoefficient + EscapeSpeedX * (1.0f - inertiaCoefficient);
		moveSpeedY = moveSpeedY * inertiaCoefficient + EscapeSpeedY * (1.0f - inertiaCoefficient);
		lagCounter++;
	}
	else {
		moveSpeedX = EscapeSpeedX;
		moveSpeedY = EscapeSpeedY;
	}

	float currentSpeed = sqrt(moveSpeedX * moveSpeedX + moveSpeedY * moveSpeedY);
	if (currentSpeed > RunawaySpeedMax) {
		float ratio = RunawaySpeedMax / currentSpeed;
		moveSpeedX *= ratio;
		moveSpeedY *= ratio;
	}

	enemy.position.x += moveSpeedX;
	enemy.position.y += moveSpeedY;
}

void GameEnemy::AvoidPlayer() {

	float moveAmountX = (float)(rand() % 11 - 5); // -5から5までのランダムな値
	float moveAmountY = (float)(rand() % 11 - 5); // -5から5までのランダムな値

	// 移動速度を制限する
	const float maxMoveSpeed = 1.0f;
	float moveSpeed = sqrt(moveAmountX * moveAmountX + moveAmountY * moveAmountY);
	if (moveSpeed > maxMoveSpeed) {
		float ratio = maxMoveSpeed / moveSpeed;
		moveAmountX *= ratio;
		moveAmountY *= ratio;
	}

	// 敵の位置を更新
	enemy.position.x += moveAmountX;
	enemy.position.y += moveAmountY;
}