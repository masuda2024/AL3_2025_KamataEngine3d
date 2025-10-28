#include "Goal.h"
#include "MyMath.h"

void Goal::Initialize(const KamataEngine::Vector3& position, KamataEngine::Camera* camera, const KamataEngine::Vector3& size, KamataEngine::Model* model) {

	model_ = model;
	camera_ = camera;
	position_ = position;
	size_ = size;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position_;
}

void Goal::Update() {
	worldTransform_.translation_ = position_;
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Goal::Draw(KamataEngine::Camera* camera) { model_->Draw(worldTransform_, *camera); }

void Goal::GoalOnCollision(const Player* player) { (void)player; }

AABB Goal::GetAABB() const {
	return AABB{
	    {position_.x - size_.x * 0.5f, position_.y - size_.y * 0.5f, position_.z - size_.z * 0.5f},

	    {position_.x + size_.x * 0.5f, position_.y + size_.y * 0.5f, position_.z + size_.z * 0.5f}
    };
}
// 衝突判定はプレイヤー側で実施