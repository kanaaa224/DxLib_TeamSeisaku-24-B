﻿/********************************
* ゲームUI処理
* 担当：島袋
********************************/
#pragma once
#include "main.h"

// UIクラス
class GameUI {
private:
	int state, frameCounter;
	int stock, score, highScore;

	int img_playerScore; // Player1 score
	int img_highScore;   // High score
	int img_stock;       // 残機
	int img_gameOver;    // GAMEOVER
	int img_phase;       // PHASE
	int img_number[10];  // 0 - 9

public:
	// コンストラクタ
	GameUI();

	// デストラクタ
	~GameUI();

	// 更新
	void Update();

	// 描画
	void Draw() const;

	// ステートを設定
	void SetState(int State) {
		state = State;
	};

	// 表示するスコアを設定
	void SetScore(int Score) {
		score = Score;
	};

	// 表示するハイスコアを設定
	void SetHighScore(int HighScore) {
		highScore = HighScore;
	};

	// 表示する残機を設定
	void SetStock(int Stock) {
		stock = Stock;
	};
};