#pragma once
#include "KamataEngine.h"
#include "MyMath.h"

struct AABB;
class Player;
class Goal {
public:
	void Initialize(const KamataEngine::Vector3& position, KamataEngine::Camera* camera, const KamataEngine::Vector3& size, KamataEngine::Model* model);
	void Update();
	void Draw(KamataEngine::Camera* camera);

	// AABB 取得
	AABB GetAABB() const;

	// ゴールしたか？
	bool IsReached() const { return reached_; }

	// 衝突応答
	void GoalOnCollision(const Player* player);

	KamataEngine::Model* model_ = nullptr;   // モデル
	KamataEngine::Camera* camera_ = nullptr; // カメラ
private:
	KamataEngine::Vector3 position_;
	KamataEngine::Vector3 size_;
	KamataEngine::WorldTransform worldTransform_;

	bool reached_ = false;
};