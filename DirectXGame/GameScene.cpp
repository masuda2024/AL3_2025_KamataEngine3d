#include"GameScene.h"
#include"MyMath.h"
using namespace KamataEngine;



GameScene::~GameScene()
{
	delete model_;
	//自キャラの解放
	delete player_;


	/*
	for (KamataEngine::WorldTransform* worldTransformBlock : worldTransformBlocks_)
	{
		delete worldTransformBlock;
	}
    */


	
	for (std::vector<KamataEngine::WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) 
	{
		for (KamataEngine::WorldTransform* worldTransformBlock : worldTransformBlockLine) 
		{
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();

	delete debugCamera_;
}



void GameScene::Initialize()
{
	

	textureHandle_ = TextureManager::Load("block.png");

	model_ = Model::Create();//////



	worldTransform_.Initialize();
	camera_.Initialize();


	//自キャラの生成
	player_ = new Player();
	//自キャラの初期化
	player_->Initialize( model_,  textureHandle_, &camera_);

	


	//要素数
	const uint32_t kNumBlockVirtical = 10;
	const uint32_t kNumBlockHorizontal = 20;
	//ブロック1個分の横幅
	const float kBlockWidth = 2.0f;
	// ブロック1個分の縦幅
	const float kBlockHeight = 2.0f;
	//要素数を変更する
	//列数を設定(縦方向のブロック数)
	worldTransformBlocks_.resize(kNumBlockVirtical);
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i)
	{
		//1列の要素数を設定(横方向のブロック数)
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}





	//キューブの生成
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i)
	{
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j)
		{
			worldTransformBlocks_[i][j] = new KamataEngine::WorldTransform();
			worldTransformBlocks_[i][j]->Initialize();
			worldTransformBlocks_[i][j]->translation_.x = (kBlockWidth+2) * j;
			worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * i;
		}
	}

	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);





}

void GameScene::Update()
{
	//自キャラの更新
	player_->Update();



	//ブロックの更新
	for (std::vector<KamataEngine::WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_)
	{
		for (KamataEngine::WorldTransform* worldTransformBlock : worldTransformBlockLine)
		{
			
			if (!worldTransformBlock)
				continue;
		

			// アフィン変換行列の作成
			worldTransformBlock->matWorld_ = MakeAffinMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);
			// worldTransformBlock->matWorld_=アフィン変換行列;

			// 定数バッファに転送する
			worldTransformBlock->TransferMatrix();
		}
	}
	


	//デバッグカメラの更新
	debugCamera_->Update();
	#ifdef _DEBUG
	if (Input::GetInstance()->TriggerKey(DIK_O))
	{
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
	#endif

	//カメラの処理
	if (isDebugCameraActive_)
	{
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;
		// ビュープロジェクション行列の転送
		camera_.TransferMatrix();
	} else
	{
		//ビュープロジェクション行列の更新と転送
		camera_.UpdateMatrix();
	}


}

void GameScene::Draw() 
{
	



	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList());

	// 自キャラの描画
	player_->Draw();
	//model_->Draw(worldTransform_,camera_,textureHandle_);





	//ブロックの描画
	for (std::vector<KamataEngine::WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_)
	{
		for (KamataEngine::WorldTransform* worldTransformBlock : worldTransformBlockLine)
		{
			model_->Draw(*worldTransformBlock, camera_);
		}
	}





	Model::PostDraw();
}