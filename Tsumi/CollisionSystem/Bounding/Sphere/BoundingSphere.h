#pragma once

#include "../../Shape/CollisionShape.h"


/* 3D��ԓ��̋��E��\������N���X : AABB */
class BoundingSphere {

public:

	// �R���X�g���N�^�A�f�X�g���N�^
	BoundingSphere() = default;
	~BoundingSphere() {};

	// �p�����[�^�t���R���X�g���N�^
	BoundingSphere(Col::Sphere setData) {
		this->sphere_ = setData;
	}

	// �w��͈̔͂Əd�Ȃ��Ă��邩�ǂ����𔻒�


	// �w��̓_������Bounding���ɂ��邩�ǂ���


private:

	Col::Sphere sphere_{};
};

