﻿
/********************************
* ゲームステージギミック処理
* 編集者：
********************************/
#define _USE_MATH_DEFINES
#include "main.h"

GameStageGimmick::GameStageGimmick() {
	LoadDivGraph("Resources/Images/Stage/Stage_BubbleAnimation.png", 4, 4, 1, 64, 64, img_bubble);
	LoadDivGraph("Resources/Images/Stage/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32,32, img_Thunder);
};

GameStageGimmick::~GameStageGimmick() {
	for (int i = 0; i < 4; i++) {
		DeleteGraph(img_bubble[i]);
	};
};

void GameStageGimmick::UpdateBubble() {
	for (int i = 0; i < BUBBLE_MAX; i++) {
		if (bubble[i].flg) {
			bubble[i].frameCounter++;
			if (bubble[i].flg >= 20) bubble[i].flg = 0;
			else if (bubble[i].flg == 10) {
				bubble[i].anim = 3;
				bubble[i].flg = 11;
			}
			else if (bubble[i].flg >= 11) bubble[i].flg++;
			else if (bubble[i].y < -70) bubble[i].flg = 0;
			else {
				bubble[i].y--;

				float swingMax = 100.0f;
				float moveX = swingMax * sin(2 * M_PI * bubble[i].frameCounter / 240.0f);

				if (bubble[i].flg == 1) bubble[i].drawX = bubble[i].x + moveX;
				else bubble[i].drawX = bubble[i].x - moveX;

				if (bubble[i].frameCounter % 30 == 0) {
					if (bubble[i].anim >= 2) bubble[i].anim = 0;
					else bubble[i].anim++;
				};
			};
		};
	};
};

void GameStageGimmick::DrawBubble() const {


}
void GameStageGimmick::UpdateThunder()
{
	
}
void GameStageGimmick::DrawThunder()const
{
	/*DrawGraph(300, 300, img_Thunder[Thunder_anm], TRUE);*/
	DrawFormatString(320, 320, 0xffffff,"sdfjsf");
}

;