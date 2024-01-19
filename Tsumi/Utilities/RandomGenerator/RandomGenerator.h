#pragma once

#include "Struct.h"
#include <iostream>
#include <random>


/* RandomGeneratorクラス */
class RandomGenerator {

public:

	~RandomGenerator() {};


	static RandomGenerator* GetInstance() {
		static RandomGenerator instance;
		return &instance;
	}


	static float getRandom(Vector2 scope) {

		std::uniform_real_distribution<float>
			distribution(scope.x, scope.y);

		float result = distribution(RandomGenerator::GetInstance()->randomEngine);

		return result;
	}

	static Vector2 getRandom(Vector2 scopeA, Vector2 scopeB) {

		std::uniform_real_distribution<float>
			distributionA(scopeA.x, scopeA.y);
		std::uniform_real_distribution<float>
			distributionB(scopeB.x, scopeB.y);

		Vector2 result = {
			distributionA(RandomGenerator::GetInstance()->randomEngine),
			distributionB(RandomGenerator::GetInstance()->randomEngine),
		};

		return result;
	}

	static Vector3 getRandom(Vector2 scopeA, Vector2 scopeB, Vector2 scopeC) {

		std::uniform_real_distribution<float>
			distributionA(scopeA.x, scopeA.y);
		std::uniform_real_distribution<float>
			distributionB(scopeB.x, scopeB.y);
		std::uniform_real_distribution<float>
			distributionC(scopeC.x, scopeC.y);

		Vector3 result = {
			distributionA(RandomGenerator::GetInstance()->randomEngine),
			distributionB(RandomGenerator::GetInstance()->randomEngine),
			distributionC(RandomGenerator::GetInstance()->randomEngine),
		};

		return result;
	}


private:

	RandomGenerator() {
		std::random_device seedGenerator;
		randomEngine.seed(seedGenerator());
	}

	RandomGenerator(const RandomGenerator&) = delete;
	RandomGenerator& operator= (const RandomGenerator&) = delete;

private:

	std::mt19937 randomEngine;
};