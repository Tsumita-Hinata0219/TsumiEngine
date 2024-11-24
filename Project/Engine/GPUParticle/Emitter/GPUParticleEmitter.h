#pragma once

#include "GameObject/GameObject.h"
#include "../Structure/GPUParticleEmitterStructure.h"
#include "BufferResource/BufferResource.h"


namespace Particle {
	namespace Emit {

		/* GPUParticleのEmitterクラス */
		class GPUParticleEmitter {

		public:

			/// <summary>
			/// コンストラクタ
			/// </summary>
			GPUParticleEmitter() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~GPUParticleEmitter() = default;

			/// <summary>
			/// 初期化処理
			/// </summary>
			void Init();

			/// <summary>
			/// 更新処理
			/// </summary>
			void Update();

			/// <summary>
			/// 描画処理
			/// </summary>
			void Draw();


		private:

			// バッファーに書き込むデータ
			SphereEmitter emitData_{};

			// バッファー
			BufferResource<SphereEmitter> emitBuffer_;
		};
	}
}

