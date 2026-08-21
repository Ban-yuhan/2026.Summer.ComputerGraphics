#include "GameScene.h"
#include "DX2DClasses/Driect2DFramework.h"
#include "DX2DClasses/Image.h"
#include "DX2DClasses/GameObject.h"
#include "DX2DClasses/InputManager.h"
#include "DX2DClasses/DebugHelper.h"
#include "DX2DClasses/CollisionCheck.h"
#include "DX2DClasses/ColorBrushPalettet.h"
#include "DX2DClasses/SingletonRenderTarget.h"
#include "DX2DClasses/Colliders.h"
#include "DX2DClasses/Rigidbody.h"
#include <algorithm>

using namespace DX2DClasses;

CGameScene::CGameScene()
{

}

CGameScene::~CGameScene()
{

}

void CGameScene::_InitImagesList(HWND hWnd, CDriect2DFramwork* pDX2DFramework)
{
	m_listImages.resize(E_SUNNYLAND_IMAGE::MAX);

	CImage* pPlayerImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 6);
	pPlayerImage->ManualLoadImage(hWnd, L"Images\\Player\\player%02d.png");
	m_listImages[E_SUNNYLAND_IMAGE::Player] = pPlayerImage;

	CImage* pOpossumImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 6);
	pOpossumImage->ManualLoadImage(hWnd, L"Images\\Enemy\\opossum%02d.png");
	m_listImages[E_SUNNYLAND_IMAGE::Opossum] = pOpossumImage;

	CImage* pEagleImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 4);
	pEagleImage->ManualLoadImage(hWnd, L"Images\\Enemy\\eagle%02d.png");
	m_listImages[E_SUNNYLAND_IMAGE::Eagle] = pEagleImage;

	CImage* pCherryImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 7);
	pCherryImage->ManualLoadImage(hWnd, L"Images\\Item\\cherry%02d.png");
	m_listImages[E_SUNNYLAND_IMAGE::Cherry] = pCherryImage;

	CImage* pGemImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 5);
	pGemImage->ManualLoadImage(hWnd, L"Images\\Item\\gem%02d.png");
	m_listImages[E_SUNNYLAND_IMAGE::Gem] = pGemImage;

	CImage* pItemEffectImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 4);
	pItemEffectImage->ManualLoadImage(hWnd, L"Images\\Effect\\itemeffect%02d.png");
	m_listImages[E_SUNNYLAND_IMAGE::ItemEffect] = pItemEffectImage;

	CImage* pDeathEffectImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 5);
	pDeathEffectImage->ManualLoadImage(hWnd, L"Images\\Effect\\death%02d.png");
	m_listImages[E_SUNNYLAND_IMAGE::DeathEffect] = pDeathEffectImage;
}

void CGameScene::Initialize(HWND hWnd, CDriect2DFramwork* pDX2DFramework)
{
	ID2D1HwndRenderTarget* pRenderTarget = CSingletonRenderTarget::GetRenderTarget();

	m_pColorBrushPalettet = new CColorBrushPalettet();
	m_pColorBrushPalettet->Initialize(pRenderTarget);

	CImage* pPlayerImage = new CImage(pDX2DFramework->GetD2DRenderTarget(), pDX2DFramework->GetImagingFactory(), 6);
	pPlayerImage->ManualLoadImage(hWnd, L"Images\\Player\\player%02d.png");
	m_listImages.push_back(pPlayerImage);
	//_InitImagesList(hWnd,pDX2DFramework);

	m_pPlayerObject = new CGameObject();
	m_pPlayerObject->Initialize(m_listImages[E_SUNNYLAND_IMAGE::Player], true);
	SRect sPlayerRect = m_pPlayerObject->GetImage()->GetDrawRect();
	m_pPlayerCollider = new CCircleCollider(m_pPlayerObject->GetTransformPtr(), sPlayerRect.GetCenter(), sPlayerRect.GetRadius());
	m_pPlayerObject->SetCollider(m_pPlayerCollider);

	//int nSize = 10;
	////m_listItem.resize(nSize);

	//for (int i = 0; i < nSize; i++)
	//{
	//	CGameObject* pObjectItem = new CGameObject();
	//	pObjectItem->Initialize(m_listImages[E_SUNNYLAND_IMAGE::Cherry], true);
	//	pObjectItem->GetTransform().SetTransrate(100.0f * i, 100.0f);
	//	m_listEnableItem.push_back(pObjectItem);
	//	m_listItem.push_back(pObjectItem);
	//}

	//m_pRigidBody = new CRigidbody();
}

void CGameScene::Release()
{
	//delete m_pRigidBody;

	//m_pRigidBodyObject->Release();
	//delete m_pRigidBodyObject;
	
	for(auto it = m_listImages.begin(); 
		it != m_listImages.end(); it++)
	{
		delete *it;
	}
	m_listImages.clear();

	for (auto it = m_listItem.begin();
		it != m_listItem.end(); it++)
	{
		delete *it;
	}
	m_listItem.clear();

	delete m_pPlayerCollider;
	m_pPlayerObject->Release();
	delete m_pPlayerObject;

	m_pColorBrushPalettet->Release();
	delete m_pColorBrushPalettet;
}

void CGameScene::Update()
{
	static float fAngle = 0;
	{
		CTransform& refTrnasform = m_pPlayerObject->GetTransform();
		SVector2 vPos = refTrnasform.GetTransrate();
		SVector2 vSize = m_pPlayerObject->GetImage()->GetImageSize();
		SVector2 vAsix = vSize * 0.5f;
		SVector2 vScale = refTrnasform.GetScale();

		//벡터방식 연산보다는 효률적이다.
		if (CInputManager::GetAsyncKeyStatePress(VK_RIGHT))
			refTrnasform.Transrate(SVector2::right() * m_fPlayerSpeed);//vPlayerPos.x -= fPlayerSpeed;
		if (CInputManager::GetAsyncKeyStatePress(VK_LEFT))
			refTrnasform.Transrate(SVector2::left() * m_fPlayerSpeed);//vPlayerPos.x -= fPlayerSpeed;
		if (CInputManager::GetAsyncKeyStatePress(VK_DOWN))
			refTrnasform.Transrate(SVector2::down() * m_fPlayerSpeed);//vPlayerPos.x -= fPlayerSpeed;
		if (CInputManager::GetAsyncKeyStatePress(VK_UP))
			refTrnasform.Transrate(SVector2::up() * m_fPlayerSpeed);//vPlayerPos.x -= fPlayerSpeed;
		if (CInputManager::GetAsyncKeyStatePress(90))
			refTrnasform.Transrate(SVector2::left() * m_fPlayerSpeed);//vPlayerPos.x -= fPlayerSpeed;

		refTrnasform.SetAsixPoint(vAsix);
		refTrnasform.Rotate(10);
	}
	m_pPlayerObject->Update();

	SVector2 vPlayerPos = m_pPlayerObject->GetTransform().GetTransrate();
	SVector2 vPlayerSize = m_pPlayerObject->GetImage()->GetImageSize() * 0.5f;
	SVector2 vPlayerCenterPos = vPlayerPos + vPlayerSize;
	float fPlayerRad = vPlayerSize.Magnitude();

	for (auto it = m_listItem.begin();
		it != m_listItem.end(); it++)
	{
		CGameObject* pObjItem = (*it);

		if (pObjItem->GetActive())
		{
			SVector2 vItemPos = pObjItem->GetTransform().GetTransrate();
			SVector2 vItemSize = pObjItem->GetImage()->GetImageSize();
			SVector2 vItemCenterPos = vItemPos + vItemSize * 0.5f;
			float fItemRad = vItemSize.Magnitude();

			if (CCollisionCheck::OverlapCircleToCircle(vPlayerCenterPos, fPlayerRad, vItemCenterPos, fItemRad))
			{
				CDebugHelper::LogConsole("[%x] PlayerPos[%f](%f,%f) ItemPos[%f](%f,%f)\n", pObjItem, fPlayerRad, vPlayerPos.x, vPlayerPos.y, fItemRad, vItemPos.x, vItemPos.y);
				CGameObject* colItem = *it;
				auto itFind = find(m_listEnableItem.begin(), m_listEnableItem.end(), colItem);
				colItem->SetActive(false);
				m_listDiableItem.push(colItem);
				m_listEnableItem.remove(colItem);
			}
		}
		pObjItem->Update();
	}
}

void CGameScene::Draw()
{
	m_pPlayerObject->Draw();
	CDebugHelper::DrawRect(m_pPlayerObject, m_pColorBrushPalettet->GetBrushClass(CColorBrushPalettet::BLACK));
	CDebugHelper::DrawCircle(m_pPlayerObject, m_pColorBrushPalettet->GetBrushClass(CColorBrushPalettet::RED));
	for (auto it = m_listItem.begin();
		it != m_listItem.end(); it++)
	{
		CGameObject* pItem = (*it);
		pItem->Draw();
		CDebugHelper::DrawCircle(pItem, m_pColorBrushPalettet->GetBrushClass(CColorBrushPalettet::RED));
	}
}