#pragma once
#include "DX2DClasses/SceneManager.h"
#include "DX2DClasses/Vector2.h"
#include <vector>
#include <list>
#include <queue>

namespace DX2DClasses
{
	class CImage;
	class CColorBrushPalettet;
	class CGameObject;
	class CCircleCollider;
	class CRigidbody;

	class CGameScene : public ISceneManager
	{
		//색상정보가 설정된 객체 디버그도우미와 함께 사용한다.
		CColorBrushPalettet* m_pColorBrushPalettet;

		enum E_SUNNYLAND_IMAGE
		{ 
			Player, 
			Opossum, 
			Eagle, 
			Cherry, 
			Gem, 
			ItemEffect, 
			DeathEffect, 
			MAX
		};
		
		//게임이 필요한 이미지를 가져오는 객체
		std::vector<CImage*> m_listImages;
		
		std::vector<CGameObject*> m_listItem;
		std::list<CGameObject*> m_listEnableItem;
		std::queue<CGameObject*> m_listDiableItem;

		std::vector<CGameObject*> m_listBullet;
		std::queue<CGameObject*> m_queueEnableBullet;
		std::queue<CGameObject*> m_queueDisableBullet;

		//실제로 로드된 이미지를 토대로 애니메이션 및 변형을 수행한다.
		//게임오브젝트는 실제복제된 객체도 포함도므로 더 많은게 일반적이다.
		CGameObject* m_pPlayerObject;

		std::vector<CGameObject*> m_listOpossumObject;
		std::vector<CGameObject*> m_listEagleObject;

		std::vector<CGameObject*> m_listItemEffectObject;
		std::vector<CGameObject*> m_listpDeathEffectObject;

		CCircleCollider* m_pPlayerCollider;
		CCircleCollider* m_pItemCollider;

		CGameObject* m_pRigidBodyObject;
		CRigidbody* m_pRigidBody;

		float m_fPlayerSpeed = 2;
		float m_fPlayerJumpHigher = 7;
		float m_fOpossumSpeed = 3;
		float m_fEangleSpeed = 5;

		int m_nScore;

		void _InitImagesList(HWND hWnd, CDriect2DFramwork* pDX2DFramework);
	public:
		CGameScene();
		~CGameScene();

		void Initialize(HWND hWnd, CDriect2DFramwork* pDX2DFramework) override; //초기화
		void Release() override; //동적객체 제거

		void Update() override; //정보변경
		void Draw() override; //객체 그리기
	};
}