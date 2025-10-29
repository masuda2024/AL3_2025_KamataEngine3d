#pragma once
#include "KamataEngine.h"
#include "MyMath.h"

struct AABB;
class Player;


class MapChipField;



class Goal {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position, const KamataEngine::Vector3& size);
	void Update();
	void Draw();

	// AABB 取得
	AABB GetAABB() const;

	// ゴールしたか？
	bool IsReached() const { return reached_; }

	// 衝突応答
	void GoalOnCollision(const Player* player);

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }
	
private:
	
	KamataEngine::Vector3 position_;
	KamataEngine::Vector3 size_;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	


	MapChipField* mapChipField_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;


	bool reached_ = false;
};