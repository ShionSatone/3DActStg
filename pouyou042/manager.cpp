//==============================================================
//
//マネージャ処理[manager.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "manager.h"
#include "object.h"
#include "renderer.h"
#include "debugproc.h"
#include "input.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "texture.h"
#include "material.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "fade.h"

//静的メンバ変数宣言
CRenderer *CManager::m_pRenderer = NULL;		//レンダラーの情報
CInputKeyboard *CManager::m_pInputKeyboard = NULL;	//キーボードの情報
CInputJoyPad *CManager::m_pInputJoyPad = NULL;		//ゲームパッドの情報
CTexture *CManager::m_pTexture = NULL;			//テクスチャの情報
CMaterial *CManager::m_pMaterial = NULL;		//マテリアルの情報

CPlayer *CManager::m_pPlayer = NULL;			//プレイヤーの情報
CSound *CManager::m_pSound = NULL;				//サウンドの情報
CDebugProc *CManager::m_pDebugProc = NULL;		//デバッグ表示の情報

CCamera *CManager::m_pCamera = NULL;			//カメラの情報
CLight *CManager::m_pLight = NULL;				//ライトの情報
CScene *CManager::m_pScene = NULL;				//シーンの情報
CFade *CManager::m_pFade = NULL;				//フェードの情報

int CManager::m_nScore = 0;						//スコア
bool CManager::m_bBgm = false;					//BGMストップするか
bool CManager::m_bResult = true;				//リザルトの判定

CTitle *CScene::m_pTitle = NULL;			//タイトル画面の情報
CTutorial *CScene::m_pTutorial = NULL;		//チュートリアル画面
CGame *CScene::m_pGame = NULL;				//ゲーム画面の情報
CResult *CScene::m_pResult = NULL;			//リザルト画面の情報
CRanking *CScene::m_pRanking = NULL;		//ランキング画面の情報
//==============================================================
//シーンのコンストラクタ
//==============================================================
CScene::CScene()
{
	m_mode = MODE_TITLE;		//ゲームモード
}

//==============================================================
//シーンのコンストラクタ(オーバーロード)
//==============================================================
CScene::CScene(MODE mode)
{
	m_mode = mode;		//ゲームモード
}

//==============================================================
//シーンのデストラクタ
//==============================================================
CScene::~CScene()
{

}

//==============================================================
//シーンの生成処理
//==============================================================
CScene *CScene::Create(MODE mode)
{
	CScene *pScene = NULL;

	if (pScene == NULL)
	{//メモリが使用されてなかったら

		//指定されたモードを生成
		pScene = new CScene(mode);
	}

	////初期化処理
	//pScene->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return pScene;
}

//==============================================================
//シーンの初期化処理
//==============================================================
HRESULT CScene::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	switch (m_mode)
	{
	case MODE_TITLE:		//タイトル画面

		//タイトル画面の生成
		if (m_pTitle == NULL)
		{
			m_pTitle = new CTitle;

			if (m_pTitle != NULL)
			{
				//ゲーム画面の初期化
				if (FAILED(m_pTitle->Init(pos, rot)))
				{//初期化処理が失敗した場合

					return E_FAIL;
				}
			}
		}

		break;

	case MODE_TUTORIAL:		//チュートリアル画面

		//チュートリアル画面の生成
		if (m_pTutorial == NULL)
		{
			m_pTutorial = new CTutorial;

			if (m_pTutorial != NULL)
			{
				//ゲーム画面の初期化
				if (FAILED(m_pTutorial->Init(pos, rot)))
				{//初期化処理が失敗した場合

					return E_FAIL;
				}
			}
		}

		break;

	case MODE_GAME:			//ゲーム画面

		//ゲーム画面の生成
		if (m_pGame == NULL)
		{
			m_pGame = new CGame;

			if (m_pGame != NULL)
			{
				//ゲーム画面の初期化
				if (FAILED(m_pGame->Init(pos, rot)))
				{//初期化処理が失敗した場合

					return E_FAIL;
				}
			}
		}

		break;

	case MODE_RESULT:		//リザルト画面

		//リザルト画面の生成
		if (m_pResult == NULL)
		{
			m_pResult = new CResult;

			if (m_pResult != NULL)
			{
				//ゲーム画面の初期化
				if (FAILED(m_pResult->Init(pos, rot)))
				{//初期化処理が失敗した場合

					return E_FAIL;
				}
			}
		}

		break;

	case MODE_RANKING:		//ランキング画面

		//ランキング画面の生成
		if (m_pRanking == NULL)
		{
			m_pRanking = new CRanking;

			if (m_pRanking != NULL)
			{
				//ゲーム画面の初期化
				if (FAILED(m_pRanking->Init(pos, rot)))
				{//初期化処理が失敗した場合

					return E_FAIL;
				}
			}
		}

		break;
	}


	return S_OK;
}

//==============================================================
//シーンの終了処理
//==============================================================
void CScene::Uninit(void)
{
	switch (m_mode)
	{
	case MODE_TITLE:		//タイトル画面

		//タイトル画面の破棄
		if (m_pTitle != NULL)
		{
			//終了処理
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}

		break;

	case MODE_TUTORIAL:		//チュートリアル画面

		//チュートリアル画面の破棄
		if (m_pTutorial != NULL)
		{
			//終了処理
			m_pTutorial->Uninit();
			m_pTutorial = NULL;
		}

		break;

	case MODE_GAME:			//ゲーム画面

		//ゲーム画面の破棄
		if (m_pGame != NULL)
		{
			//終了処理
			m_pGame->Uninit();
			m_pGame = NULL;
		}

		break;

	case MODE_RESULT:		//リザルト画面

		//リザルト画面の破棄
		if (m_pResult != NULL)
		{
			//終了処理
			m_pResult->Uninit();
			m_pResult = NULL;
		}

		break;

	case MODE_RANKING:		//ランキング画面

		//ランキング画面の破棄
		if (m_pRanking != NULL)
		{
			//終了処理
			m_pRanking->Uninit();
			m_pRanking = NULL;
		}

		break;
	}

	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//シーンの更新処理
//==============================================================
void CScene::Update(void)
{
	CDebugProc *pDebugProc = CManager::GetDebugProc();

	switch (m_mode)
	{
	case MODE_TITLE:		//タイトル画面

		pDebugProc->Print("<<<<<<タイトル>>>>>>\n");

		break;

	case MODE_TUTORIAL:		//チュートリアル画面

		pDebugProc->Print("<<<<<<チュートリアル>>>>>>\n");

		break;

	case MODE_GAME:			//ゲーム画面

		pDebugProc->Print("<<<<<<ゲーム>>>>>>\n");

		break;

	case MODE_RESULT:		//リザルト画面

		pDebugProc->Print("<<<<<<リザルト>>>>>>\n");

		break;

	case MODE_RANKING:		//ランキング画面

		pDebugProc->Print("<<<<<<ランキング>>>>>>\n");

		break;
	}
}

//==============================================================
//シーンの描画処理
//==============================================================
void CScene::Draw(void)
{

}

//==============================================================
//マネージャのコンストラクタ
//==============================================================
CManager::CManager()
{

}

//==============================================================
//マネージャのデストラクタ
//==============================================================
CManager::~CManager()
{

}

//==============================================================
//マネージャの初期化処理
//==============================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//レンダラーの生成
	if (m_pRenderer == NULL)
	{//メモリが使用されてないとき

		m_pRenderer = new CRenderer;
	}

	//レンダラーの初期化処理
	if (m_pRenderer != NULL)
	{//メモリ確保できてたら

		//レンダラーの初期化
		if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
		{//初期化処理が失敗した場合

			return E_FAIL;
		}
	}

	//デバッグ表示の生成
	if (m_pDebugProc == NULL)
	{//メモリが使用されてないとき

		m_pDebugProc = new CDebugProc;
	}

	if (m_pDebugProc != NULL)
	{//メモリが確保されたとき

		//デバッグ表示の初期化処理
		m_pDebugProc->Init();
	}

	//キーボードの生成
	if (m_pInputKeyboard == NULL)
	{//キーボードが使用されてないとき

		m_pInputKeyboard = new CInputKeyboard;
	}

	if (m_pInputKeyboard != NULL)
	{//メモリ確保できてたら

		//キーボードの初期化
		if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
		{//初期化処理が失敗した場合

			return E_FAIL;
		}
	}

	//ゲームパッドの生成
	if (m_pInputJoyPad == NULL)
	{
		m_pInputJoyPad = new CInputJoyPad;
	}

	if (m_pInputJoyPad != NULL)
	{//メモリ確保できてたら

		//パッドの初期化
		if (FAILED(m_pInputJoyPad->Init(hInstance, hWnd)))
		{//初期化処理が失敗した場合

			return E_FAIL;
		}
	}

	//カメラの生成
	if (m_pCamera == NULL)
	{
		m_pCamera = new CCamera;
	}

	if (m_pCamera != NULL)
	{//メモリ確保できてたら

		//カメラの初期化
		if (FAILED(m_pCamera->Init()))
		{//初期化処理が失敗した場合

			return E_FAIL;
		}
	}

	//ライトの生成
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
	}

	if (m_pLight != NULL)
	{//メモリ確保できてたら

		//ライトの初期化
		if (FAILED(m_pLight->Init()))
		{//初期化処理が失敗した場合

			return E_FAIL;
		}
	}

	//サウンドの生成
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
	}

	if (m_pSound != NULL)
	{//メモリ確保できてたら

		//サウンドの初期化
		if (FAILED(m_pSound->Init(hWnd)))
		{//初期化処理が失敗した場合

			return E_FAIL;
		}
	}

	//テクスチャの生成
	if (m_pTexture == NULL)
	{
		m_pTexture = new CTexture;
	}

	if (m_pTexture != NULL)
	{//メモリ確保できてたら

		//テクスチャの読み込み
		if (FAILED(m_pTexture->Load()))
		{//読み込みが失敗した場合

			return E_FAIL;
		}
	}

	//マテリアルの生成
	if (m_pMaterial == NULL)
	{
		m_pMaterial = new CMaterial;
	}

	if (m_pMaterial != NULL)
	{//メモリ確保できてたら

		//マテリアルの読み込み
		if (FAILED(m_pMaterial->Load()))
		{//読み込みが失敗した場合

			return E_FAIL;
		}
	}

	//シーンの生成処理
	if (m_pScene == NULL)
	{
#if _DEBUG

		m_pScene = CScene::Create(CScene::MODE_TITLE);

#else

		m_pScene = CScene::Create(CScene::MODE_TITLE);

#endif
	}

	if (m_pScene != NULL)
	{//メモリ確保できたら

		//シーンの初期化処理
		if (FAILED(m_pScene->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f))))
		{//読み込みが失敗した場合

			return E_FAIL;
		}
	}

	//フェードの生成処理
	if (m_pFade == NULL)
	{
		m_pFade = CFade::Create();
	}
	
	return S_OK;
}

//==============================================================
//マネージャの終了処理
//==============================================================
void CManager::Uninit(void)
{
	//全てのオブジェクトの破棄
	CObject::ReleaseAll();

	//全てのテクスチャの破棄
	if (m_pMaterial != NULL)
	{
		//テクスチャの終了処理
		m_pMaterial->Unload();

		delete m_pMaterial;
		m_pMaterial = NULL;
	}

	//全てのテクスチャの破棄
	if (m_pTexture != NULL)
	{
		//テクスチャの終了処理
		m_pTexture->Unload();

		delete m_pTexture;
		m_pTexture = NULL;
	}

	//フェードの破棄
	//if (m_pFade != NULL)
	//{
	//	//フェードの終了処理
	//	m_pFade->Uninit();

	//	delete m_pFade;
	//	m_pFade = NULL;
	//}

	//シーンの破棄
	//if (m_pScene != NULL)
	//{
	//	//シーンの終了処理
	//	m_pScene->Uninit();

	//	delete m_pScene;
	//	m_pScene = NULL;
	//}

	//サウンドの破棄
	if (m_pSound != NULL)
	{
		//サウンドの終了処理
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = NULL;
	}

	//キーボードの破棄
	if (m_pInputKeyboard != NULL)
	{
		//キーボードの終了処理
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//ゲームパッドの破棄
	if (m_pInputJoyPad != NULL)
	{
		//ゲームパッドの終了処理
		m_pInputJoyPad->Uninit();

		delete m_pInputJoyPad;
		m_pInputJoyPad = NULL;
	}

	//ライトの破棄
	if (m_pLight != NULL)
	{
		//ライトの終了処理
		m_pLight->Uninit();

		delete m_pLight;
		m_pLight = NULL;
	}

	//カメラの破棄
	if (m_pCamera != NULL)
	{
		//カメラの終了処理
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = NULL;
	}

	//デバッグ表示の破棄
	if (m_pDebugProc != NULL)
	{
		//デバッグ表示の終了処理
		m_pDebugProc->Uninit();

		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}

	//レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		//レンダラーの終了処理
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//==============================================================
//マネージャの更新処理
//==============================================================
void CManager::Update(void)
{
	//キーボードの更新処理
	m_pInputKeyboard->Update();

	//ゲームパッドの更新処理
	m_pInputJoyPad->Update();

	//デバッグ表示の更新処理
	m_pDebugProc->Update();

	//マップの再生成
	CManager::ResetMap();

	//レンダラーの更新処理
	m_pRenderer->Update();

	//カメラの更新処理
	m_pCamera->Update();
}

//==============================================================
//マネージャの描画処理
//==============================================================
void CManager::Draw(void)
{
	//レンダラーの描画処理
	m_pRenderer->Draw();
}

//==============================================================
//ゲームモードの設定処理
//==============================================================
void CManager::SetMode(CScene::MODE mode)
{
	//if (CManager::GetMode() != CScene::MODE_RESULT && )
	//{
	//	//サウンドの停止
	//	m_pSound->Stop();
	//}

	//現在のモードの破棄
	if (m_pScene != NULL)
	{
		//全ての終了処理
		CObject::DeathAll();
	}

	//新しいモードの生成
	m_pScene = CScene::Create(mode);

	//初期化処理
	m_pScene->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//フェードの生成処理
	m_pFade = CFade::Create();
}

//==============================================================
//ゲームモードの取得処理
//==============================================================
CScene::MODE CManager::GetMode(void)
{
	return m_pScene->GetMode();
}

//==============================================================
//マップの配置リセット
//==============================================================
void CManager::ResetMap(void)
{
	//リセット
	if (m_pInputKeyboard->GetPress(DIK_F2) == true)
	{//F2を押したとき

		//マップのオブジェクトのリセット
		CObject::ResetMapAll();

		////オブジェクト3Dの生成
		//CManager::Create3DAll();
	}
}