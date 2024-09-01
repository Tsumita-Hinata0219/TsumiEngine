#pragma once

#include "../MathStructure/Vector/Vector.h"

/* カラーのサンプル静的変数 */
namespace Smp {

	struct Color final {

		// サンプルカラー : 静的定数メンバ変数
		static const Vector4 RED;
        static const Vector4 GREEN;
        static const Vector4 BLUE;
        static const Vector4 YELLOW;
        static const Vector4 CYAN;
        static const Vector4 MAGENTA;
        static const Vector4 WHITE;
        static const Vector4 BLACK;
	};

}