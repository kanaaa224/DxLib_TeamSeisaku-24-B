/********************************
* �V�[���}�l�[�W���[
* ��ҁF����
********************************/
#pragma once

// �f�t�H���g�̒��ۃV�[���N���X
class AbstractScene {
public:
	// �f�X�g���N�^
	virtual ~AbstractScene() {};

	// �`��ȊO�̍X�V������
	virtual AbstractScene* Update() = 0;

	// �`��Ɋւ��邱�Ƃ�����
	virtual void Draw() const = 0;
};