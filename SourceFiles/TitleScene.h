﻿/********************************
* タイトルシーン
* 担当：島袋
********************************/
#pragma once
#include "AbstractScene.h"
#include "main.h"

class Title : public AbstractScene {
private:
	int state, frameCounter;

	bool ctrl;

	int img_logo;
	int img_mode;
	int img_credit;
	int img_cursor[4];

public:
	// コンストラクタ
	Title();

	// デストラクタ
	~Title();

	// 更新
	virtual AbstractScene* Update() override;

	// 描画
	virtual void Draw() const override;
};