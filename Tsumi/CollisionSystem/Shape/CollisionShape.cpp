#include "CollisionShape.h"
#include "../Tree/Octree/Octree.h"


// 境界ボックスから空間レベルと所属空間を求める
void CollisionShape::CalcSpaceLevel()
{
	/* ===================================================== */

	// 座標から左上と右下を求める
	std::pair<Vector2, Vector2> pos;
	pos.first = { // 左上
		bounding_.center.x + bounding_.min.x,
		bounding_.center.y + bounding_.max.y,
	};
	pos.second = { // 右下
		bounding_.center.x + bounding_.max.x,
		bounding_.center.y + bounding_.min.y,
	};

	// 座標と孫空間の一辺で割りintでキャストしたもの
	float U = float(ROOT_EDGE_LENGTH / std::pow(2, 3));
	std::pair<uint32_t, uint32_t> leftTop = {
		static_cast<uint32_t>(pos.first.x / U),
		static_cast<uint32_t>(pos.first.y / U),
	};
	std::pair<uint32_t, uint32_t> rightDown = {
		static_cast<uint32_t>(pos.second.x / U),
		static_cast<uint32_t>(pos.second.y / U),
	};

	// AABBの二頂点の所属空間
	vertexSpaceID_ = {
		Get2DMortonNumber(leftTop.first, leftTop.second),	  // 左上
		Get2DMortonNumber(rightDown.first, rightDown.second), // 右下
	};

	/* ===================================================== */  // TODO : 現状2Dなので後で3D用に変える


	// 二頂点のXOR
	int XOR = vertexSpaceID_.first ^ vertexSpaceID_.second;

	// 最上位ビット位置
	int highestBitPos = findHighestBitPosition(XOR);

	// 空間レベル
	levelIndex_ = 3 - highestBitPos / 2;

	// 所属空間
	spaceIndex_ = vertexSpaceID_.first >> highestBitPos;
}
