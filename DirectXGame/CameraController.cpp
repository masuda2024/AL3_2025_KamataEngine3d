#include "CameraController.h"
using namespace KamataEngine;
using namespace MathUtility;
#include"Player.h"

void CameraController::Initialize(KamataEngine::Camera* camera) 
{ 
	

	camera_ = camera;
}

void CameraController::Update()
{

}

void CameraController::Reset() 
{
	

	//追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	
	//追従対象とオフセットからカメラの座標を計算
	camera_->translation_ = targetWorldTransform.translation_ + targetOffset_;
}
