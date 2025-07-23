#pragma once
#include "KamataEngine.h"
#include "Player.h"
/**/
class TitleScene
{
public:


	//終了フラグ
	bool finished_ = false;
	//デスフラグのgetter
	bool IsFinished() const { return finished_; }


	void Initialize();
	void Update();
	void Draw();
	//void ChangeScene();
	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_; // stdでエラーが起きたらKamataEngine::をいれる

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;





	// モデルプレイヤー
	KamataEngine::Model* modelPlayer_ = nullptr;


	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::WorldTransform worldTransformPlayer_;

	// カメラ
	KamataEngine::Camera camera_;
	
	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;

	// 3Dモデルデータ
	KamataEngine::Model* model_ = nullptr;

	// 自キャラ
	Player* player_ = nullptr;

	// マップチップフィールド
	MapChipField* mapChipField_;

private:
};