#include"PlayerAttack.h"
#include"KamataEngine.h"
#include"Player.h"
#include"GameScene.h"
#include"cassert"
#include<numbers>
#include<algorithm>

#define NOMINMAX
#include "MapChipField.h"
#include <algorithm>
using namespace KamataEngine;
using namespace MathUtility;

void PlayerAttack::Initialize(Model* model, Camera* camera, KamataEngine::Vector3 position) {
	// NULLポイントチェック
	assert(model);

	model_ = model;

	// textureHandle_ = textureHandle;
	for (KamataEngine::WorldTransform& worldTransform : WorldTransforms_)
	{
		worldTransform.translation_ = position;
		worldTransform.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	}

	camera_ = camera;

	// worldTransform_.Initialize();

	// ワールド変換の初期化
	for (KamataEngine::WorldTransform& worldTransform : WorldTransforms_)
	{
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}
	objectColor_.Initialize();
	color_ = {1, 1, 1, 1};
}

void PlayerAttack::Update()
{

	for (KamataEngine::WorldTransform& worldTransform : WorldTransforms_)
	{
		// アフィン変換行列
		worldTransform.matWorld_ = MakeAffineMatrix(worldTransform.scale_, worldTransform.rotation_, worldTransform.translation_);
		worldTransform.TransferMatrix(); // プレイヤーの座標の計算
	}

	
	// カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;

	color_.w = std::clamp(1.0f - counter_ / kDuration, 0.0f, 1.0f);
	// 色変更オブジェクトに色の数値を設定する
	objectColor_.SetColor(color_);

	// 存続時間の上限に達したら
	if (counter_ >= kDuration) 
	{
		counter_ = kDuration;
		// 終了扱いにする
		isFinishedAttack_ = true;
	}
	// 終了なら何もしない
	if (isFinishedAttack_)
	{
		return;
	}
}

void PlayerAttack::Draw()
{

	for (KamataEngine::WorldTransform& worldTransform : WorldTransforms_) {
		model_->Draw(worldTransform, *camera_, &objectColor_);
	}

	// 終了なら何もしない
	if (isFinishedAttack_)
	{
		return;
	}
}
