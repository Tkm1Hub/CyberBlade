#pragma once
class ShadowManager
{
public:
	void Init();
	void Update(const VECTOR& pos);

	int GetShadowMapHandle() const { return shadowMapHandle; }
	VECTOR GetLightDir()const { return lightDirection; }

private:
	int shadowMapHandle = -1;					// �e�̃��f���n���h��

	VECTOR lightDirection = { 0.0f,0.0f,0.0f };	// ���̕����x�N�g��

	static constexpr int SHADOW_QUALITY = 2048;	// �e�̃N�I���e�B

	float drawShadowRadius = 200.0f;			// �e��`�悷��͈͂̔��a
	float drawShadowHeight = 50.0f;				// �e��`�悷��͈͂̍���
};