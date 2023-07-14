﻿/********************************
* ゲームメインシーン
* 担当：島袋、
********************************/
#pragma once
#include "AbstractScene.h"
#include "main.h"

class Game : public AbstractScene {
private:
	int btn_flg;
	int state;
	int img_bg;

	GamePlayer player;
	GameStage stage;

	// 仮
	Collide blockData;
	int blockIndex;
	int block[2][4];
public:
	// コンストラクタ
	Game();

	// デストラクタ
	~Game();

	// 描画以外の更新を実装
	virtual AbstractScene* Update() override;

	// 描画に関することを実装
	virtual void Draw() const override;


	// 当たり判定 - 島袋
	static int CheckCollideSquares(int s1X1, int s1Y1, int s1X2, int s1Y2, int s2X1, int s2Y1, int s2X2, int s2Y2) {
		// s1がs2の左側にある場合
		if (s1X2 < s2X1) {
			return 0;
		};
		// s1がs2の右側にある場合
		if (s1X1 > s2X2) {
			return 0;
		};
		// s1がs2の上側にある場合
		if (s1Y2 < s2Y1) {
			return 0;
		};
		// s1がs2の下側にある場合
		if (s1Y1 > s2Y2) {
			return 0;
		};
		// 上記の条件に当てはまらない場合、二つの四角形は重なっている
		return 1;
	};

	// 当たり判定 - 島袋
	static int CheckCollideSquares2(int ret, int s1X1, int s1Y1, int s1X2, int s1Y2, int s2X1, int s2Y1, int s2X2, int s2Y2) {
		// s1がs2の左側にある場合
		if (s1X2 <= s2X1) {
			return 0;
		};
		// s1がs2の右側にある場合
		if (s1X1 >= s2X2) {
			return 0;
		};
		// s1がs2の上側にある場合
		if (s1Y2 <= s2Y1) {
			return 0;
		};
		// s1がs2の下側にある場合
		if (s1Y1 >= s2Y2) {
			return 0;
		};
		// 上記の条件に当てはまらない場合、二つの四角形は重なっている
		return ret;
	};

	// 当たり判定 - 島袋
	static int CheckCollideSquares3(int s1X1, int s1Y1, int s1X2, int s1Y2, int s2X1, int s2Y1, int s2X2, int s2Y2) {
		if (s1X2 < s2X1 || s1X1 > s2X2 || s1Y2 < s2Y1 || s1Y1 > s2Y2) {
			return 0;
		};
		if (s1Y2 == s2Y1) {
			return 1;
		}
		else if (s1Y1 == s2Y2) {
			return 2;
		}
		else if (s1X2 == s2X1) {
			return 3;
		}
		else if (s1X1 == s2X2) {
			return 4;
		}
		else {
			return 0;
		};
	};

	// 当たり判定 - 島袋
	static int CheckCollideBox(int s1X1, int s1Y1, int s1X2, int s1Y2, int s2X1, int s2Y1, int s2X2, int s2Y2) {
		if (s1X2 < s2X1 || s1X1 > s2X2 || s1Y2 < s2Y1 || s1Y1 > s2Y2) {
			return 0;
		};
		if (fabsf(s1Y2 - s2Y1) < 10) {
			return 1;
		}
		else if (fabsf(s1Y1 - s2Y2) < 10) {
			return 2;
		}
		else if (fabsf(s1X2 - s2X1) < 10) {
			return 3;
		}
		else if (fabsf(s1X1 - s2X2) < 10) {
			return 4;
		}
		else {
			return 0;
		};
	};
};
