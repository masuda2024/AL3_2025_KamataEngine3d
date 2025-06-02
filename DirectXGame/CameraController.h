#pragma once
#include"KamataEngine.h"
using namespace MathUtility;


class CameraController
{

	

public:
	

	void Initialize(KamataEngine::Camera* camera);
	

	void Update();
	
	
	class Player;

	Player* target_ = nullptr;
	void SetTarget(Player* target) { target_ = target; }

	void Reset();
	


	//追従対象とカメラの座標の差
	Vector3 targetOffset_ = {0, 0, -15.0f};

	
	

private:

	KamataEngine::Camera* camera_ = nullptr;
	


};