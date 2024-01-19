struct VertexShaderOutput {
    float32_t4 position : SV_POSITION;
    float32_t2 texcoord : TEXCOORD0;
    float32_t3 normal : NORMAL0;
    float32_t3 worldPosition : WORLDPOSITION0;
};

struct TransformationViewMatrix {
	float32_t4x4 view;
	float32_t4x4 viewProjection;
	float32_t4x4 orthoGraphic;
	float32_t3 cameraPosition;
};
