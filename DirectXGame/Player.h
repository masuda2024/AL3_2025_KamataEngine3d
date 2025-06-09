#pragma once
#include "KamataEngine.h"
class Player 
{
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position);

	void Update();

	void Draw();




	const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }

	const KamataEngine::Vector3& GetVelocity() const { return velocity_; }


private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	// モデル
	KamataEngine::Model* model_ = nullptr;
	// KamataEngine::Model* model_ = nullptr;

	KamataEngine::Camera* camera_ = nullptr;

	KamataEngine::Vector3* position_ = nullptr;

	// テクスチャハンドル
	// uint32_t textureHandle_ = 0u;

	KamataEngine::Vector3 velocity_ = {};
	static inline const float kAcceleration = 1.0f;
	static inline const float kAttenuation = 1.0f;
	//プレイヤーの速度
	static inline const float kLimitRunSpeed = 0.3f;

	// 左右
	enum class LRDirection 
	{
		kRight,
		kLeft,
	};
	LRDirection lrDirection_ = LRDirection::kRight;

	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;
	// 旋回時間<秒>
	static inline const float kTimeTurn = 0.3f;

	bool onGround_ = true;

	// 重力加速度(下方向)
	static inline const float kGravityAcceleration = 9.8f;
	// 最大落下速度(下方向)
	static inline const float kLimitFallSpeed = 10.0f;
	// ジャンプ初速(上方向)
	static inline const float kJumpAcceleration = 5.0f;

	
};