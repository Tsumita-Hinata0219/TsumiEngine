#pragma once
#include<cstdint>


struct ObjectFileter {
	static const uint32_t None = 0xfffff;
	static const uint32_t Player = 0b00001;
	static const uint32_t Enemy = 0b00011;
	static const uint32_t Terrain = 0b00101;
};

struct ObjectBit {
	static const uint32_t None = 0xfffff;
	static const uint32_t Player = 0b00001;
	static const uint32_t PlayerBullet = 0b00010;
	static const uint32_t Enemy = 0b00011;
	static const uint32_t EnemyBullet = 0b00100;
	static const uint32_t Terrain = 0b00101;
};
