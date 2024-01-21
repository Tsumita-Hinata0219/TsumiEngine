#pragma once
#include<cstdint>

enum class ObjectFilter {
	None = 0xfffff,
	Player  = 0b00001,
	Enemy   = 0b00010,
	Terrain = 0b00011,
};
enum class ObjectBit {
	None = 0xfffff,
	Player = 0b00001,
	PlayerBullet = 0b00010,
	Enemy = 0b00011,
	EnemyBullet = 0b00100,
	Terrain = 0b00101,
};

const uint32_t kCollisionAttributePlayer = 0b0001;
const uint32_t kCollisionAttributeEnemy = 0b0010;

const uint32_t kCollisionMaskPlayer = 0b1110;
const uint32_t kCollisionMaskEnemy = 0b1101;

