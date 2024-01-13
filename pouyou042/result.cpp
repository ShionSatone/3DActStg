//==============================================================
//
//リザルト処理[result.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "result.h"
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
#include "fade.h"
#include "sound.h"

//静的メンバ変数宣言
bool CResult::bReset = true;					//リセットしたかどうか

//==============================================================
//コンストラクタ
//==============================================================
CResult::CResult()
{

}

//==============================================================
//デストラクタ
//==============================================================
CResult::~CResult()
{

}

//==============================================================
//初期化処理
//==============================================================
HRESULT CResult::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CSound *pSound = CManager::GetSound();

	CBg::Create();

	//スコアの生成
	CScore::Create();

	//BGM再生
	if (CManager::GetResult() == true)
	{
		pSound->Play(pSound->SOUND_LABEL_BGM003);
	}
	else if (CManager::GetResult() == false)
	{
		pSound->Play(pSound->SOUND_LABEL_BGM004);
	}

	return S_OK;
}

//==============================================================
//終了処理
//==============================================================
void CResult::Uninit(void)
{
	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//更新処理
//==============================================================
void CResult::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//キーボードの情報取得
	CInputJoyPad *pInputJoyPad = CManager::GetInputJoyPad();			//パッドの情報取得
	CFade *pFade = CManager::GetFade();			//フェードの情報取得

	if ((pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_A, 0) == true) && bReset == false)
	{//ENTERキー押したら

		CManager::SetBgm(false);

		//ランキング画面
		//CManager::SetMode(CScene::MODE_RANKING);
		pFade->SetFade(CScene::MODE_RANKING);
		bReset = true;
	}
	else
	{
		bReset = false;
	}

}

//==============================================================
//描画処理
//==============================================================
void CResult::Draw(void)
{

}