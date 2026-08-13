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
	//Initialize();
}

CMoveSampleScene::~CMoveSampleScene()
{
	//Release();
}

void CMoveSampleScene::Reset()
{
	float fPlayerSpeed = 2;
	float fPlayerJumpHigher = 7;
	float fOpossumSpeed = 3;
	float fEangleSpeed = 5;

	float fAngle = 0;
	{
		CTransform& cTrnasform = m_pPlayerObject->GetTransform();
		SVector2 vPos = cTrnasform.GetTransrate();
		SVector2 vSize = m_pPlayerObject->GetImage()->GetImageSize();
		SVector2 vScale(1, 1);
		cTrnasform.SetTransrate(vPos);
	}

	//
	{
		CTransform& cTrnasform = m_pOpossumObject->GetTransform();
		SVector2 vPos = SVector2(250,0);
		cTrnasform.SetTransrate(vPos);
	}


	{
		CTransform& cTrnasform = m_pEagleObject->GetTransform();
		SVector2 vSize = m_pEagleObject->GetImage()->GetImageSize();
		SVector2 vPos = SVector2(300, 300);
		//SVector2 vScale(1, 1);
		cTrnasform.SetTransrate(vPos);
		//SVector2 vAsix = vSize * 0.5f;
		//cTrnasform.SetAsixPoint(vAsix);
		//cTrnasform.SetTRS(vPos, 0, vScale);
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

	int nSize = 10;
	m_listItems.resize(10);

	for (int i = 0; i < nSize; i++)
	{
		CGameObject* pItem = new CGameObject();
		if( i % 2)
			pItem->Initialize(m_pGemImage, true);
		else
			pItem->Initialize(m_pCherryImage, true);

		//CTransform& cTrnasform = pItem->GetTransform();
		//SVector2 vPos = SVector2(i * 50, 300);
		//cTrnasform.SetTransrate(vPos);

		pItem->GetTransform().SetTransrate(i * 50, 300);
		//pItem->GetTransformPtr()->SetTransrate(SVector2(i * 50, 300));

		m_listItems[i] = pItem;
	}

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

	m_pPlayerObject->Release();
	delete m_pPlayerObject;
	m_pOpossumObject->Release();
	delete m_pOpossumObject;
	m_pEagleObject->Release();
	delete m_pEagleObject;
	m_pCherryObject->Release();
	delete m_pCherryObject;
	m_pGemObject->Release();
	delete m_pGemObject;
	m_pItemEffectObject->Release();
	delete m_pItemEffectObject;
	m_pDeathEffectObject->Release();
	delete m_pDeathEffectObject;

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
	CDebugHelper::OpenConsole();
	//블록을 활용하여 각 오브젝트 처리시 지역변수를 동일한 이름으로 활용가능하도록 함.


	if (CInputManager::GetAsyncKeyStatePress(VK_F1))
	{
		CDebugHelper::LogConsole("GetAsyncKeyStatePress(VK_F1)");
	}

	if (CInputManager::GetAsyncKeyStateRelease(VK_F1))
	{
		CDebugHelper::LogConsole("GetAsyncKeyStateRelease(VK_F1)");
	}

	static float fAngle = 0;
	{
		CTransform& cTrnasform = m_pPlayerObject->GetTransform();
		SVector2 vPos = cTrnasform.GetTransrate();
		SVector2 vSize = m_pOpossumObject->GetImage()->GetImageSize();
		SVector2 vAsix = vSize * 0.5f;
		SVector2 vScale = cTrnasform.GetScale();

		//벡터방식 연산보다는 효률적이다.
		if (CInputManager::GetAsyncKeyStatePress(VK_RIGHT))
			cTrnasform.Transrate(SVector2::right() * m_fPlayerSpeed);//vPlayerPos.x -= fPlayerSpeed;
		if (CInputManager::GetAsyncKeyStatePress(VK_LEFT))
			cTrnasform.Transrate(SVector2::left() * m_fPlayerSpeed);//vPlayerPos.x -= fPlayerSpeed;
		if (CInputManager::GetAsyncKeyStatePress(VK_DOWN))
			cTrnasform.Transrate(SVector2::down() * m_fPlayerSpeed);//vPlayerPos.x -= fPlayerSpeed;
		if (CInputManager::GetAsyncKeyStatePress(VK_UP))
			cTrnasform.Transrate(SVector2::up() * m_fPlayerSpeed);//vPlayerPos.x -= fPlayerSpeed;
		if (CInputManager::GetAsyncKeyStatePress(90))
			cTrnasform.Transrate(SVector2::left() * m_fPlayerSpeed);//vPlayerPos.x -= fPlayerSpeed;

		cTrnasform.SetAsixPoint(vAsix);
		//cTrnasform.Rotate(10);
	}
	m_pPlayerObject->Update();

	{
		CTransform& cTrnasform = m_pOpossumObject->GetTransform();
		SVector2 vSize = m_pOpossumObject->GetImage()->GetImageSize();
		SVector2 vScale = cTrnasform.GetScale();
		SVector2 vAsix = vSize * 0.5f;
		SVector2 vPos = cTrnasform.GetTransrate();

		vPos = vPos + SVector2::left() * m_fOpossumSpeed;

		if (vPos.x <= 0) vPos.x = 250;

		cTrnasform.SetAsixPoint(vAsix);
		cTrnasform.SetTRS(vPos, 0, vScale);
	}
	m_pOpossumObject->Update();
	
	{
		CTransform& cTrnasform = m_pEagleObject->GetTransform();
		SVector2 vPos = m_pEagleObject->GetTransform().GetTransrate();
		SVector2 vTargetPos = m_pPlayerObject->GetTransform().GetTransrate();
		SVector2 vDir = vTargetPos - vPos;
		vDir = vDir.Normalize();
		vPos = vPos + vDir * m_fEangleSpeed;
		cTrnasform.SetTransrate(vPos);	
	}
	m_pEagleObject->Update();
	
	m_pCherryObject->Update();
	m_pCherryObject->GetTransform().SetTransrate(0, 50);

	m_pGemObject->Update();
	m_pGemObject->GetTransform().SetTransrate(0, 80);

	//m_pItemEffectObject->Update();
	//m_pItemEffectObject->GetTransform().SetTransrate(0, 100);

	m_pDeathEffectObject->Update();
	m_pDeathEffectObject->GetTransform().SetTransrate(0, 120);


	SVector2 vPlayerPos = m_pPlayerObject->GetTransform().GetTransrate();
	SVector2 vPlayerSize = m_pPlayerObject->GetImage()->GetImageSize() * 0.5f;
	float fPlayerRad = vPlayerSize.Magnitude();

	for (int i = 0; i < m_listItems.size(); i++)
	{
		CGameObject* pObjItem = m_listItems[i];
		SVector2 vItemPos = pObjItem->GetTransform().GetTransrate();
		SVector2 vItemSize = pObjItem->GetImage()->GetImageSize() * 0.5f;
		float fItemRad = vItemSize.Magnitude();

		SVector2 vDist = (vItemPos - vPlayerPos);
		float fDist = vDist.Magnitude();
		CDebugHelper::LogConsole("PlayerPos[%f](%f,%f) ItemPos[%f](%f,%f) Dist:%f\n", fPlayerRad, vPlayerPos.x, vPlayerPos.y, fItemRad, vItemPos.x, vItemPos.y, fDist);
		
		if (CCollisionCheck::OverlapCircleToCircle(vPlayerPos, fPlayerRad, vItemPos, fItemRad))
		{
			m_pItemEffectObject->GetTransform().SetTransrate(vItemPos);
			m_pItemEffectObject->Update();
		}

		pObjItem->Update();
	}
}

void CMoveSampleScene::Draw()
{
	ID2D1HwndRenderTarget* pRenderTarget = CSingletonRenderTarget::GetRenderTarget();
	CColorBrush* pRedBrush = m_pColorBrushPalettet->GetBrushClass(CColorBrushPalettet::RED);
	CColorBrush* pGreenBrush = m_pColorBrushPalettet->GetBrushClass(CColorBrushPalettet::GREEN);
	CColorBrush* pYellowBrush = m_pColorBrushPalettet->GetBrushClass(CColorBrushPalettet::YELLOW);
	CColorBrush* pBlackBrush = m_pColorBrushPalettet->GetBrushClass(CColorBrushPalettet::BLACK);


	m_pPlayerObject->Draw();
	//CDebugHelper::DrawBox(m_pPlayerObject, CColorBrushPalettet::GetInstance()->GetBrushClass(CColorBrushPalettet::BLACK));
	//CDebugHelper::DrawCircle(m_pPlayerObject,pBlackBrush);

	m_pOpossumObject->Draw();
	CDebugHelper::DrawRect(m_pOpossumObject, pRedBrush);

	m_pEagleObject->Draw();
	CDebugHelper::DrawCircle(m_pEagleObject,pYellowBrush);

	m_pCherryObject->Draw();
	m_pGemObject->Draw();

	m_pItemEffectObject->Draw();
	m_pDeathEffectObject->Draw();

	SVector2 vPlayerPos = m_pPlayerObject->GetTransform().GetTransrate();
	SVector2 vPlayerSize = m_pPlayerObject->GetImage()->GetImageSize() * 0.5f;
	float fPlayerRad = vPlayerSize.Magnitude();

	for (int i = 0; i < m_listItems.size() ; i++)
	{
		m_listItems[i]->Draw();
	}
}