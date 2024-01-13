//==============================================================
//
//タイトル処理[title.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "title.h"
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
#include "bg.h"
#include "sound.h"
#include "fade.h"
#include "texture.h"
#include "titleTexture.h"
#include "ranking.h"

//マクロ定義
#define TRANS_TIME		(60 * 10)			//遷移するまでの時間

//静的メンバ変数宣言
CEdit *CTitle::m_pEdit = NULL;				//エディットの情報
bool CTitle::bReset = true;				//リセットしたかどうか

//==============================================================
//コンストラクタ
//==============================================================
CTitle::CTitle()
{
	for (int nCntTex = 0; nCntTex < NUM_TITLE_TEX; nCntTex++)
	{
		m_nIdxTexture[nCntTex] = -1;		//テクスチャ番号
	}

	m_nCntTrans = 0;				//遷移するまでの時間
}

//==============================================================
//デストラクタ
//==============================================================
CTitle::~CTitle()
{

}

//==============================================================
//初期化処理
//==============================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CCamera *pCamera = CManager::GetCamera();		//カメラの情報取得
	CSound *pSound = CManager::GetSound();
	CTexture *pTexture = CManager::GetTexture();

	//カメラの初期化処理
	pCamera->Init();

	//エディットの生成
	m_pEdit = CEdit::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//壁の生成
	CWall::Create(D3DXVECTOR3(350.0f, 100.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

	//タイトルのテクスチャ
	CTitleTex::Create();

	if (CManager::GetBgm() == false)
	{

		//BGM再生
		pSound->Play(pSound->SOUND_LABEL_BGM000);
	}

	return S_OK;
}

//==============================================================
//終了処理
//==============================================================
void CTitle::Uninit(void)
{
	//エディット
	if (m_pEdit != NULL)
	{
		m_pEdit->Uninit();
		m_pEdit = NULL;
	}

	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//更新処理
//==============================================================
void CTitle::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//キーボードの情報取得
	CFade *pFade = CManager::GetFade();		//フェードの情報取得

	if (m_nCntTrans >= TRANS_TIME)
	{//遷移する時間になったら

		CManager::SetBgm(true);
		pFade->SetFade(CScene::MODE_RANKING);

		//CRanking *pRanking = CScene::GetRanking();		//ランキングの情報取得
		//pRanking->SetSound(true);
	}

	m_nCntTrans++;
}

//==============================================================
//描画処理
//==============================================================
void CTitle::Draw(void)
{
	
}