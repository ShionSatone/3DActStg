//==============================================================
//
//タイトルのテクスチャ処理[titleTexture.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "titleTexture.h"
#include "manager.h"
#include "renderer.h"
#include "object2D.h"
#include "object.h"
#include "texture.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//マクロ定義
#define APPEAR_CNT		(60)			//点滅カウント
#define APPEAR_CNT_MIN	(2)				//点滅カウント(Enter押したとき)

//静的メンバ変数宣言
CObject2D *CTitleTex::m_apObject2D[NUM_TITLE_TEX] = {};

//==============================================================
//コンストラクタ
//==============================================================
CTitleTex::CTitleTex()
{
	//変数初期化
	//m_pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);		//位置

	for (int nCntTex = 0; nCntTex < NUM_TITLE_TEX; nCntTex++)
	{
		m_nIdxTexture[nCntTex] = -1;		//テクスチャの番号
	}

	m_nCntAppear = APPEAR_CNT;			//点滅カウンター
	m_state = STATE_NONE;
	m_bAppear = true;
	m_fAlpha = 1.0f;
}

//==============================================================
//デストラクタ
//==============================================================
CTitleTex::~CTitleTex()
{

}

//==============================================================
//生成処理
//==============================================================
CTitleTex *CTitleTex::Create(void)
{
	CTitleTex *pTitleTex = NULL;

	if (pTitleTex == NULL)
	{//メモリが使用されてなかったら

		//タイトルテクスチャの生成
		pTitleTex = new CTitleTex;

		//初期化処理
		pTitleTex->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		//種類設定
		pTitleTex->SetType(TYPE_NONE);
	}

	return pTitleTex;
}

//==============================================================
//タイトルテクスチャの初期化処理
//==============================================================
HRESULT CTitleTex::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CTexture *pTexture = CManager::GetTexture();

	//テクスチャの読み込み
	m_nIdxTexture[0] = pTexture->Regit("data\\TEXTURE\\title.png");
	m_nIdxTexture[1] = pTexture->Regit("data\\TEXTURE\\enter.png");

	for (int nCntTex = 0; nCntTex < NUM_TITLE_TEX; nCntTex++)
	{
		//初期化処置
		if (m_apObject2D[nCntTex] == NULL)
		{//使用されてないとき

			//2Dオブジェクト生成
			m_apObject2D[nCntTex] = CObject2D::Create();

			if (m_apObject2D[nCntTex] != NULL)
			{//生成出来たら

				//大きさ設定
				m_apObject2D[nCntTex]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

				//テクスチャ割り当て
				m_apObject2D[nCntTex]->BindTexture(m_nIdxTexture[nCntTex]);

				//位置設定
				if (nCntTex == 0)
				{
					m_apObject2D[nCntTex]->SetPosition(CObject::TYPE_EFFECT, D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 200.0f, 0.0f), 400.0f, 100.0f);

				}
				else if (nCntTex == 1)
				{
					m_apObject2D[nCntTex]->SetPosition(CObject::TYPE_EFFECT, D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 600.0f, 0.0f), 120.0f, 60.0f);
				}
			}
		}
	}

	//種類設定
	CObject::SetType(CObject::TYPE_NONE);

	return S_OK;
}

//==============================================================
//タイトルテクスチャの終了処理
//==============================================================
void CTitleTex::Uninit(void)
{
	CSound *pSound = CManager::GetSound();

	if (CManager::GetBgm() == false)
	{
		//BGMの停止
		pSound->Stop();
	}
	for (int nCntTex = 0; nCntTex < NUM_TITLE_TEX; nCntTex++)
	{
		if (m_apObject2D[nCntTex] != NULL)
		{//使用されてるとき

			//終了処理
			m_apObject2D[nCntTex]->Uninit();
			m_apObject2D[nCntTex] = NULL;
		}
	}

	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//タイトルテクスチャの更新処理
//==============================================================
void CTitleTex::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//キーボードの情報取得
	CInputJoyPad *pInputJoyPad = CManager::GetInputJoyPad();			//パッドの情報取得
	CFade *pFade = CManager::GetFade();		//フェードの情報取得

	switch (m_state)
	{
	case STATE_NONE:		//通常状態

		if ((m_nCntAppear % APPEAR_CNT) == 0)
		{//一定時間たったら

			m_bAppear = m_bAppear ? false : true;

		}

		if (m_bAppear == true)
		{
			m_fAlpha += 1.0f / APPEAR_CNT;
			m_apObject2D[0]->SetPosition(CObject::TYPE_EFFECT, 
				D3DXVECTOR3(m_apObject2D[0]->GetPosition().x, m_apObject2D[0]->GetPosition().y + 0.1f, m_apObject2D[0]->GetPosition().z), 400.0f, 100.0f);
		}
		else if (m_bAppear == false)
		{
			m_fAlpha -= 1.0f / APPEAR_CNT;
			m_apObject2D[0]->SetPosition(CObject::TYPE_EFFECT, 
				D3DXVECTOR3(m_apObject2D[0]->GetPosition().x, m_apObject2D[0]->GetPosition().y - 0.1f, m_apObject2D[0]->GetPosition().z), 400.0f, 100.0f);

		}

		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
			pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_A, 0) == true)
		{//Enterキーを押したら

			CSound *pSound = CManager::GetSound();

			//SE再生
			pSound->Play(pSound->SOUND_LABEL_SE_ENTER000);
			pSound->Play(pSound->SOUND_LABEL_SE_ENTER002);

			m_state = STATE_APPEAR;
			m_nCntAppear = 0;		//点滅カウンター
		}

		break;

	case STATE_APPEAR:

		if ((m_nCntAppear % APPEAR_CNT_MIN) == 0)
		{//一定時間たったら

			m_bAppear = m_bAppear ? false : true;
		}

		if (m_nCntAppear >= 60)
		{//一定時間たったら

			CManager::SetBgm(false);

			pFade->SetFade(CScene::MODE_TUTORIAL);
		}

		break;
	}

	//点滅させる
	if (m_bAppear == true && m_state == STATE_APPEAR)
	{
		m_apObject2D[1]->SetColor(CObject::TYPE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	}
	else if (m_bAppear == false && m_state == STATE_APPEAR)
	{
		m_apObject2D[1]->SetColor(CObject::TYPE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	}
	else
	{
		m_apObject2D[1]->SetColor(CObject::TYPE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha));

	}

	m_nCntAppear++;
}

//==============================================================
//タイトルテクスチャの描画処理
//==============================================================
void CTitleTex::Draw(void)
{
	
}