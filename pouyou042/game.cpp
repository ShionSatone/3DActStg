//==============================================================
//
//ゲーム処理[game.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "game.h"
#include "manager.h"
#include "playerModel.h"
#include "enemyModel.h"
#include "model.h"
#include "field.h"
#include "wall.h"
#include "score.h"
#include "edit.h"
#include "input.h"
#include "camera.h"
#include "weapon.h"
#include "bulletRemain.h"
#include "itemModel.h"
#include "switch.h"
#include "ranking.h"
#include "life.h"
#include "pause.h"
#include "fade.h"
#include "sound.h"

//静的メンバ変数宣言
CPlayerModel *CGame::m_pPlayerModel = NULL;	//プレイヤーの情報
CEdit *CGame::m_pEdit = NULL;				//エディットの情報
CBulletRemain *CGame::m_pBulletRemain = NULL;			//残弾数の情報
CScore *CGame::m_pScore = NULL;				//スコアの情報
CLife *CGame::m_pLife = NULL;				//寿命表示の情報
bool CGame::m_bReset = true;					//リセットしたかどうか
bool CGame::m_bPause = false;					//ポーズ画面か
CPause *CGame::m_pPause = NULL;				//ポーズ画面の情報
CGame::GAMEMODE CGame::m_gameMode = GAMEMODE_GROUND;	//ゲームモード

//==============================================================
//コンストラクタ
//==============================================================
CGame::CGame()
{
	m_nCntEnemy = 0;				//敵出現カウント
}

//==============================================================
//デストラクタ
//==============================================================
CGame::~CGame()
{

}

//==============================================================
//初期化処理
//==============================================================
HRESULT CGame::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CCamera *pCamera = CManager::GetCamera();		//カメラの情報取得
	CSound *pSound = CManager::GetSound();

	m_bReset = true;		//リセットしてる状態にする
	m_bPause = false;		//ポーズしてない

	//カメラの初期化処理
	pCamera->Init();

	//エディットの生成
	m_pEdit = CEdit::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//投影スイッチの生成
	CSwitch::Create(D3DXVECTOR3(2488.0f, 185.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CSwitch::Create(D3DXVECTOR3(2790.0f, 190.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CSwitch::Create(D3DXVECTOR3(3440.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CSwitch::Create(D3DXVECTOR3(3876.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CSwitch::Create(D3DXVECTOR3(4934.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CSwitch::Create(D3DXVECTOR3(5356.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CSwitch::Create(D3DXVECTOR3(5650.0f, 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CSwitch::Create(D3DXVECTOR3(6364.0f, 278.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CSwitch::Create(D3DXVECTOR3(6690.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CSwitch::Create(D3DXVECTOR3(7567.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CSwitch::Create(D3DXVECTOR3(9850.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//壁の生成
	for (int nCntWall = 0; nCntWall < 7; nCntWall++)
	{
		//地上の生成
		CWall::Create(D3DXVECTOR3(150.0f + 1500.0f * nCntWall, 100.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	}

	//地上の生成
	CWall::Create(D3DXVECTOR3(-250.0f, 1000.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);

	//水中の生成
	CWall::Create(D3DXVECTOR3(10300.0f, -4900.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);

	//寿命の表示
	m_pLife = CLife::Create(D3DXVECTOR3(10.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//プレイヤーの生成
	m_pPlayerModel = CPlayerModel::Create(D3DXVECTOR3(0.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f));

	//敵の生成
	CEnemyModel::Create(D3DXVECTOR3(445.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), CEnemyModel::ENEMYTYPE_FROG, 2);
	CEnemyModel::Create(D3DXVECTOR3(1420.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), CEnemyModel::ENEMYTYPE_FROG, 2);
	CEnemyModel::Create(D3DXVECTOR3(2230.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), CEnemyModel::ENEMYTYPE_FROG, 2);
	CEnemyModel::Create(D3DXVECTOR3(9100.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), CEnemyModel::ENEMYTYPE_FROG, 2);
	CEnemyModel::Create(D3DXVECTOR3(5700.0f, 280.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), CEnemyModel::ENEMYTYPE_FROG, 2);
	CEnemyModel::Create(D3DXVECTOR3(6500.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), CEnemyModel::ENEMYTYPE_FROG, 2);
	CEnemyModel::Create(D3DXVECTOR3(4480.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), CEnemyModel::ENEMYTYPE_FROG, 2);

	CEnemyModel::Create(D3DXVECTOR3(9700.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemyModel::ENEMYTYPE_AQUATICA, 3);
	CEnemyModel::Create(D3DXVECTOR3(7640.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemyModel::ENEMYTYPE_AQUATICA, 3);

	//魔女生成
	CEnemyModel::Create(D3DXVECTOR3(10740.0f, -4990.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), CEnemyModel::ENEMYTYPE_WITCH, 40);

	//アイテム生成
	CItemModel::Create(D3DXVECTOR3(1540.0f, 68.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_VAPOR);
	CItemModel::Create(D3DXVECTOR3(2060.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_ICE);
	CItemModel::Create(D3DXVECTOR3(3917.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_VAPOR);
	CItemModel::Create(D3DXVECTOR3(4450.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_WATER);
	CItemModel::Create(D3DXVECTOR3(5520.0f, 230.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_ICE);
	CItemModel::Create(D3DXVECTOR3(6400.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_ICE);
	CItemModel::Create(D3DXVECTOR3(3640.0f, 262.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_LIFE);
	CItemModel::Create(D3DXVECTOR3(3640.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_WATER);
	CItemModel::Create(D3DXVECTOR3(4730.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_LIFE);
	CItemModel::Create(D3DXVECTOR3(6770.0f, 266.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_LIFE);
	CItemModel::Create(D3DXVECTOR3(9500.0f, 120.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_ICE);
	CItemModel::Create(D3DXVECTOR3(10200.0f, -500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_LIFE);
	CItemModel::Create(D3DXVECTOR3(8488.0f, 310.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_WATER);

	//魔女の家生成
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\roof.x");
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\wall00.x");
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\wall01.x");
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\wall02.x");
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\floor01.x");
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\floor02.x");
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\floor03.x");
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\floor04.x");
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\well00.x");
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\well01.x");
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\well02.x");

	//武器の種類の表示
	CWeapon::Create(D3DXVECTOR3(450.0f, 70.0f, 0.0f));

	//残弾数の表示
	m_pBulletRemain = CBulletRemain::Create(D3DXVECTOR3(10.0f, 50.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//スコアの生成
	m_pScore = CScore::Create();

	//ポーズ画面の生成
	m_pPause = CPause::Create();

	//BGM再生
	pSound->Play(pSound->SOUND_LABEL_BGM002);

	CObject::SetType(CObject::TYPE_SCENE);

	return S_OK;
}

//==============================================================
//終了処理
//==============================================================
void CGame::Uninit(void)
{
	CSound *pSound = CManager::GetSound();

	//BGMの停止
	pSound->Stop();

	//寿命の破棄
	if (m_pLife != NULL)
	{
		m_pLife->Uninit();
		m_pLife = NULL;
	}

	//残弾数の破棄
	if (m_pBulletRemain != NULL)
	{
		m_pBulletRemain->Uninit();
		m_pBulletRemain = NULL;
	}

	//エディットの破棄
	if (m_pEdit != NULL)
	{
		m_pEdit->Uninit();
		m_pEdit = NULL;
	}

	//プレイヤーの破棄
	if (m_pPlayerModel != NULL)
	{
		m_pPlayerModel->Uninit();
		m_pPlayerModel = NULL;
	}

	//ポーズの破棄
	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		m_pPause = NULL;
	}

	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//更新処理
//==============================================================
void CGame::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//キーボードの情報取得
	CInputJoyPad *pInputJoyPad = CManager::GetInputJoyPad();			//パッドの情報取得
	CFade *pFade = CManager::GetFade();			//フェードの情報取得

	if (pInputKeyboard->GetTrigger(DIK_P) == true || 
		pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_START, 0) == true)
	{//Pキーを押したら

		m_bPause = m_bPause ? false : true;		//ポーズ切り替え
	}

	if (m_bPause == true)
	{//ポーズしてるとき

		if (pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_B, 0) == true)
		{
			m_bPause = false;
		}
	}

}

//==============================================================
//描画処理
//==============================================================
void CGame::Draw(void)
{

}

//==============================================================
//ポーズ画面の設定処理
//==============================================================
void CGame::SetEnablePauseMenu(bool bPouse)
{
	m_bPause = bPouse;
}