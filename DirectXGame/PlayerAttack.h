#pragma once
#include "KamataEngine.h"
#include "MyMath.h"
#include <array>
#define _USE_MATH_DEFINES
#include <math.h>

class PlayerAttack
{
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3 position);

	void Update();

	void Draw();

	// void IsFinished();

	
	static inline const uint32_t kNumParticlesAttack = 1;

	std::array<KamataEngine::WorldTransform, kNumParticlesAttack> WorldTransforms_;

	// 存続時間
	static inline const float kDuration = 1.0f;

	// 経過時間カウント
	float counter_ = 0.0f;

	// 終了フラグ
	bool isFinishedAttack_ = false;



	// 色変更オブジェクト
	KamataEngine::ObjectColor objectColor_;
	// 色の数値
	KamataEngine::Vector4 color_;

private:
	// ワールド変換データ
	// KamataEngine::WorldTransform worldTransform_;

	// カメラ
	KamataEngine::Camera* camera_;

	// モデル
	KamataEngine::Model* model_;
};
