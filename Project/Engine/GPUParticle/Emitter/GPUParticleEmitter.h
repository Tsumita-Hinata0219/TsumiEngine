#pragma once

#include "GameObject/GameObject.h"
#include "../Structure/GPUParticleEmitterStructure.h"
#include "BufferResource/BufferResource.h"
#include "../Resources/GPUParticleEmitterResources.h"

#include <limits>


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

			/// <summary>
			/// Particle発生処理
			/// </summary>
			void Emit(std::unique_ptr<GPUParticle>& particle);


		private:

			/// <summary>
			/// BufferResourceの作成
			/// </summary>
			void CreateBufferResource();


		private:

			// バッファーに書き込むデータ
			GPUParticleEmitterDatas datas_{};

			// バッファー
			GPUParticleEmitterResouces buffers_{};

			// ランダム数値を得るためのスコープ
			Scope scope_{};
		};
	}
}

