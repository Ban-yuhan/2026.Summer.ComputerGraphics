#include "MoveSampleScene.h"
#include "DX2DClasses/Driect2DFramework.h"
#include "DX2DClasses/SingletonRenderTarget.h"
#include "DX2DClasses/ColorBrush.h"
#include "DX2DClasses/Vector2.h"
#include "DX2DClasses/Image.h"
#include "DX2DClasses/InputManager.h"
#include "DX2DClasses/CollisionCheck.h"
#include "DX2DClasses/ColorBrushPalettet.h"
#include "DX2DClasses/DebugHelper.h"
#include "DX2DClasses/GameObject.h"
#include <conio.h>
#include <iostream>
#include <string>

using namespace DX2DClasses;

CMoveSampleScene::CMoveSampleScene()
{
}

CMoveSampleScene::~CMoveSampleScene()
{
}

void CMoveSampleScene::Reset()
{
	// 플레이어를 하단 중앙에 배치
	m_pPlayerObject->GetTransform().SetTransrate(SVector2(400, 500));

	// 적들을 화면 상단 바깥으로 배치 (위에서 아래로 떨어지게 설정)
	m_pOpossumObject->GetTransform().SetTransrate(SVector2(250, -50));
	m_pEagleObject->GetTransform().SetTransrate(SVector2(550, -100));

	// 사용하지 않거나 대기 중인 이펙트와 더미 객체를 화면 밖으로 숨김
	m_pCherryObject->GetTransform().SetTransrate(SVector2(-100, -100));
	m_pGemObject->GetTransform().SetTransrate(SVector2(-100, -100));
	m_pItemEffectObject->GetTransform().SetTransrate(SVector2(-100, -100));
	m_pDeathEffectObject->GetTransform().SetTransrate(SVector2(-100, -100));

	// 점수 초기화
	m_nScore = 0;

	// 총알(m_listItems)들 모두 화면 밖 대기 상태로 초기화
	for (int i = 0; i < m_listItems.size(); i++)
	{
		m_listItems[i]->GetTransform().SetTransrate(SVector2(-100, -100));
	}
}

void CMoveSampleScene::Initialize(HWND hWnd, CDriect2DFramwork* pDX2DFramework)
{
	ID2D1HwndRenderTarget* pRenderTarget = CSingletonRenderTarget::GetRenderTarget();

	m_pColorBrushPalettet = new CColorBrushPalettet();
	m_pColorBrushPalettet->Initialize(pRenderTarget);

	m_pPlayerImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 6);
	m_pPlayerImage->ManualLoadImage(hWnd, L"Images\\Player\\player%02d.png");
	m_pPlayerObject = new CGameObject();
	m_pPlayerObject->Initialize(m_pPlayerImage, true);

	m_pOpossumImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 6);
	m_pOpossumImage->ManualLoadImage(hWnd, L"Images\\Enemy\\opossum%02d.png");
	m_pOpossumObject = new CGameObject();
	m_pOpossumObject->Initialize(m_pOpossumImage, true);

	m_pEagleImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 4);
	m_pEagleImage->ManualLoadImage(hWnd, L"Images\\Enemy\\eagle%02d.png");
	m_pEagleObject = new CGameObject();
	m_pEagleObject->Initialize(m_pEagleImage, true);

	m_pCherryImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 7);
	m_pCherryImage->ManualLoadImage(hWnd, L"Images\\Item\\cherry%02d.png");
	m_pCherryObject = new CGameObject();
	m_pCherryObject->Initialize(m_pCherryImage, true);

	m_pGemImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 5);
	m_pGemImage->ManualLoadImage(hWnd, L"Images\\Item\\gem%02d.png");
	m_pGemObject = new CGameObject();
	m_pGemObject->Initialize(m_pGemImage, true);

	m_pItemEffectImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 4);
	m_pItemEffectImage->ManualLoadImage(hWnd, L"Images\\Effect\\itemeffect%02d.png");
	m_pItemEffectObject = new CGameObject();
	m_pItemEffectObject->Initialize(m_pItemEffectImage, true);

	m_pDeathEffectImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 5);
	m_pDeathEffectImage->ManualLoadImage(hWnd, L"Images\\Effect\\death%02d.png");
	m_pDeathEffectObject = new CGameObject();
	m_pDeathEffectObject->Initialize(m_pDeathEffectImage, true);

	// m_listItems를 총알 오브젝트 풀(Pool)로 활용 (10발 제한)
	int nSize = 10;
	m_listItems.resize(nSize);

	for (int i = 0; i < nSize; i++)
	{
		CGameObject* pItem = new CGameObject();
		if (i % 2)
			pItem->Initialize(m_pGemImage, true); // 보석 모양 총알
		else
			pItem->Initialize(m_pCherryImage, true); // 체리 모양 총알

		m_listItems[i] = pItem;
	}

	// 모든 객체 초기 위치 셋팅
	Reset();
}

void CMoveSampleScene::Release()
{
	for (int i = 0; i < (int)m_listItems.size(); i++)
	{
		m_listItems[i]->Release();
		delete m_listItems[i];
	}
	m_listItems.clear();

	m_pPlayerObject->Release(); delete m_pPlayerObject;
	m_pOpossumObject->Release(); delete m_pOpossumObject;
	m_pEagleObject->Release(); delete m_pEagleObject;
	m_pCherryObject->Release(); delete m_pCherryObject;
	m_pGemObject->Release(); delete m_pGemObject;
	m_pItemEffectObject->Release(); delete m_pItemEffectObject;
	m_pDeathEffectObject->Release(); delete m_pDeathEffectObject;

	delete m_pPlayerImage;
	delete m_pOpossumImage;
	delete m_pEagleImage;
	delete m_pCherryImage;
	delete m_pGemImage;
	delete m_pItemEffectImage;
	delete m_pDeathEffectImage;

	m_pColorBrushPalettet->Release();
	delete m_pColorBrushPalettet;

	CDebugHelper::CloseConsole();
}

void CMoveSampleScene::Update()
{
	// CDebugHelper::OpenConsole(); // 필요시 콘솔 활성화

	// 1. 플레이어 이동 처리
	CTransform& playerTrans = m_pPlayerObject->GetTransform();
	if (CInputManager::GetAsyncKeyStatePress(VK_RIGHT))
		playerTrans.Transrate(SVector2::right() * m_fPlayerSpeed);
	if (CInputManager::GetAsyncKeyStatePress(VK_LEFT))
		playerTrans.Transrate(SVector2::left() * m_fPlayerSpeed);
	if (CInputManager::GetAsyncKeyStatePress(VK_DOWN))
		playerTrans.Transrate(SVector2::down() * m_fPlayerSpeed);
	if (CInputManager::GetAsyncKeyStatePress(VK_UP))
		playerTrans.Transrate(SVector2::up() * m_fPlayerSpeed);

	m_pPlayerObject->Update();

	// 2. 총알 발사 처리 (스페이스바)
	static int fireDelay = 0; // 지역 정적 변수로 연사 딜레이 관리
	if (fireDelay > 0) fireDelay--;

	if (CInputManager::GetAsyncKeyStatePress(VK_SPACE) && fireDelay <= 0)
	{
		for (int i = 0; i < m_listItems.size(); i++)
		{
			SVector2 vPos = m_listItems[i]->GetTransform().GetTransrate();
			// 화면 밖에 있는(대기 중인) 총알을 찾아서 발사
			if (vPos.y <= 0 || vPos.x <= 0)
			{
				m_listItems[i]->GetTransform().SetTransrate(playerTrans.GetTransrate());
				fireDelay = 15; // 15프레임 연사 딜레이
				break;
			}
		}
	}

	// 3. 총알 이동 처리 (위로 발사) - m_fPlayerJumpHigher 변수를 총알 속도로 활용
	for (int i = 0; i < m_listItems.size(); i++)
	{
		CTransform& bulletTrans = m_listItems[i]->GetTransform();
		SVector2 vPos = bulletTrans.GetTransrate();

		if (vPos.x > 0 && vPos.y > 0) // 현재 화면에 발사되어 있는 총알만 이동
		{
			bulletTrans.Transrate(SVector2::up() * m_fPlayerJumpHigher);
			// 화면 위로 벗어나면 대기 상태(화면 밖)로 전환하여 풀 반환
			if (vPos.y < -50)
				bulletTrans.SetTransrate(SVector2(-100, -100));
		}
		m_listItems[i]->Update();
	}

	// 4. 적 이동 처리 (위에서 아래로)
	// 주머니쥐
	CTransform& opossumTrans = m_pOpossumObject->GetTransform();
	opossumTrans.Transrate(SVector2::down() * m_fOpossumSpeed);
	if (opossumTrans.GetTransrate().y > 600) // 화면 아래로 나가면 재스폰
		opossumTrans.SetTransrate(SVector2((rand() % 600) + 100, -50));
	m_pOpossumObject->Update();

	// 독수리
	CTransform& eagleTrans = m_pEagleObject->GetTransform();
	eagleTrans.Transrate(SVector2::down() * m_fEangleSpeed);
	if (eagleTrans.GetTransrate().y > 600) // 화면 아래로 나가면 재스폰
		eagleTrans.SetTransrate(SVector2((rand() % 600) + 100, -50));
	m_pEagleObject->Update();


	// 5. 충돌 처리 로직 (총알 vs 적 기체)
	SVector2 vOpossumPos = opossumTrans.GetTransrate();
	float fOpossumRad = m_pOpossumObject->GetImage()->GetImageSize().Magnitude() * 0.5f;

	SVector2 vEaglePos = eagleTrans.GetTransrate();
	float fEagleRad = m_pEagleObject->GetImage()->GetImageSize().Magnitude() * 0.5f;

	for (int i = 0; i < m_listItems.size(); i++)
	{
		SVector2 vBulletPos = m_listItems[i]->GetTransform().GetTransrate();
		// 대기 중인 총알은 충돌 연산에서 제외
		if (vBulletPos.y <= 0) continue;

		float fBulletRad = m_listItems[i]->GetImage()->GetImageSize().Magnitude() * 0.5f;

		// 5-1. 주머니쥐 피격 판정
		if (CCollisionCheck::OverlapCircleToCircle(vBulletPos, fBulletRad, vOpossumPos, fOpossumRad))
		{
			// 피격 이펙트 표시 및 적 재스폰
			m_pDeathEffectObject->GetTransform().SetTransrate(vOpossumPos);
			opossumTrans.SetTransrate(SVector2((rand() % 600) + 100, -50));
			// 총알 회수
			m_listItems[i]->GetTransform().SetTransrate(SVector2(-100, -100));
			m_nScore += 10;
		}
		// 5-2. 독수리 피격 판정
		else if (CCollisionCheck::OverlapCircleToCircle(vBulletPos, fBulletRad, vEaglePos, fEagleRad))
		{
			// 피격 이펙트 표시 및 적 재스폰
			m_pItemEffectObject->GetTransform().SetTransrate(vEaglePos);
			eagleTrans.SetTransrate(SVector2((rand() % 600) + 100, -50));
			// 총알 회수
			m_listItems[i]->GetTransform().SetTransrate(SVector2(-100, -100));
			m_nScore += 20;
		}
	}

	m_pItemEffectObject->Update();
	m_pDeathEffectObject->Update();
}

void CMoveSampleScene::Draw()
{
	// ID2D1HwndRenderTarget* pRenderTarget = CSingletonRenderTarget::GetRenderTarget();

	// 플레이어 및 적 기체 렌더링
	m_pPlayerObject->Draw();
	m_pOpossumObject->Draw();
	m_pEagleObject->Draw();

	// 발사되어 화면에 존재하는 총알만 렌더링
	for (int i = 0; i < m_listItems.size(); i++)
	{
		if (m_listItems[i]->GetTransform().GetTransrate().y > 0)
		{
			m_listItems[i]->Draw();
		}
	}

	// 파괴 이펙트 렌더링
	m_pItemEffectObject->Draw();
	m_pDeathEffectObject->Draw();

	// 필요 시 사용하지 않는 더미 객체도 에러 방지 차원에서 Draw 가능 (화면 밖에 있으므로 안보임)
	m_pCherryObject->Draw();
	m_pGemObject->Draw();
}