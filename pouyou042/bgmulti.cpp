//==============================================================
//
//多重背景処理[bgmulti.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "bgmulti.h"
#include "manager.h"
#include "renderer.h"
#include "object2D.h"
#include "object.h"
#include "texture.h"

//マクロ定義
#define WIDTH_MULTI		(SCREEN_WIDTH * 0.5f)		//横幅
#define HEIGHT_MULTI	(SCREEN_HEIGHT * 0.5f)		//縦幅

//静的メンバ変数宣言
CObject2D *CBgMulti::m_apObject2D[NUM_BG] = {};
LPDIRECT3DTEXTURE9 CBgMulti::m_pTexture[NUM_BG] = {};		//テクスチャ

//==============================================================
//コンストラクタ
//==============================================================
CBgMulti::CBgMulti()
{
	//変数初期化
	//m_pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);		//位置

	for (int nCntBg = 0; nCntBg < NUM_BG; nCntBg++)
	{
		m_nIdxTexture[nCntBg] = -1;		//テクスチャの番号
		m_aTexV[nCntBg] = 0.0f;
		m_aTexU[nCntBg] = 0.0f;
		m_move[nCntBg] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	}
}

//==============================================================
//デストラクタ
//==============================================================
CBgMulti::~CBgMulti()
{

}

//==============================================================
//多重背景のテクスチャの読み込み
//==============================================================
HRESULT CBgMulti::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//デバイスの取得

	if (m_pTexture[0] == NULL || m_pTexture[1] == NULL || m_pTexture[2] == NULL)
	{//テクスチャ設定されてないとき

		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\bg100.png",
			&m_pTexture[0]);

		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\bg101.png",
			&m_pTexture[1]);

		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\bg102.png",
			&m_pTexture[2]);
	}

	return S_OK;
}

//==============================================================
//多重背景のテクスチャの破棄
//==============================================================
void CBgMulti::Unload(void)
{
	//テクスチャの破棄
	for (int nCntBg = 0; nCntBg < NUM_BG; nCntBg++)
	{
		if (m_pTexture[nCntBg] != NULL)
		{
			m_pTexture[nCntBg]->Release();
			m_pTexture[nCntBg] = NULL;
		}
	}
}

//==============================================================
//生成処理
//==============================================================
CBgMulti *CBgMulti::Create(void)
{
	CBgMulti *pBgMulti = NULL;

	if (pBgMulti == NULL)
	{//メモリが使用されてなかったら

		//多重背景の生成
		pBgMulti = new CBgMulti;

		//初期化処理
		pBgMulti->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		//種類設定
		pBgMulti->SetType(TYPE_NONE);
	}

	return pBgMulti;
}

//==============================================================
//多重背景の初期化処理
//==============================================================
HRESULT CBgMulti::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CTexture *pTexture = CManager::GetTexture();

	//テクスチャの読み込み
	m_nIdxTexture[0] = pTexture->Regit("data\\TEXTURE\\bg100.png");
	m_nIdxTexture[1] = pTexture->Regit("data\\TEXTURE\\bg101.png");
	m_nIdxTexture[2] = pTexture->Regit("data\\TEXTURE\\bg102.png");

	//初期化処置
	for (int nCntBg = 0; nCntBg < NUM_BG; nCntBg++)
	{
		if (m_apObject2D[nCntBg] == NULL)
		{//使用されてないとき

			//2Dオブジェクト生成
			m_apObject2D[nCntBg] = CObject2D::Create();

			if (m_apObject2D[nCntBg] != NULL)
			{//生成出来たら

				//大きさ設定
				m_apObject2D[nCntBg]->SetSize(WIDTH_MULTI, HEIGHT_MULTI);

				//テクスチャ割り当て
				m_apObject2D[nCntBg]->BindTexture(m_nIdxTexture[nCntBg]);
			}
		}
	}

	//移動量設定
	m_move[0].x = 0.001f;
	m_move[1].x = 0.005f;
	m_move[2].x = 0.002f;

	m_move[0].y = 0.001f;
	m_move[1].y = 0.005f;
	m_move[2].y = 0.002f;

	//種類設定
	CObject::SetType(CObject::TYPE_NONE);

	return S_OK;
}

//==============================================================
//多重背景の終了処理
//==============================================================
void CBgMulti::Uninit(void)
{
	for (int nCntBg = 0; nCntBg < NUM_BG; nCntBg++)
	{
		if (m_apObject2D[nCntBg] != NULL)
		{//使用されてるとき

			//終了処理
			m_apObject2D[nCntBg]->Uninit();
			m_apObject2D[nCntBg] = NULL;
		}
	}

	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//多重背景の更新処理
//==============================================================
void CBgMulti::Update(void)
{
	for (int nCntBg = 0; nCntBg < NUM_BG; nCntBg++)
	{
		if (m_apObject2D[nCntBg] != NULL)
		{
			m_aTexU[nCntBg] += m_move[nCntBg].x;
			//m_aTexV[nCntBg] += m_move[nCntBg].y;

			//位置の設定
			m_apObject2D[nCntBg]->SetPosition(CObject::TYPE_NONE, D3DXVECTOR3(0.0f,0.0f,0.0f), WIDTH_MULTI, HEIGHT_MULTI);
			m_apObject2D[nCntBg]->SetType(m_aTexU[nCntBg], m_aTexV[nCntBg]);

			//位置超えたら戻す
			if (m_aTexU[nCntBg] > 1.0f)
			{
				m_aTexV[nCntBg] = 0.0f;

			}
			else if (m_aTexV[nCntBg] < 0.0f)
			{
				m_aTexV[nCntBg] = 1.0f;
			}
			else if (m_aTexV[nCntBg] > 1.0f)
			{
				m_aTexV[nCntBg] = 0.0f;

			}
			else if (m_aTexU[nCntBg] < 0.0f)
			{
				m_aTexV[nCntBg] = 1.0f;
			}
		}
	}

}

//==============================================================
//多重背景の描画処理
//==============================================================
void CBgMulti::Draw(void)
{
	
}

//==============================================================
//テクスチャ割り当て処理
//==============================================================
void CBgMulti::BindTexture(LPDIRECT3DTEXTURE9 pTexture, int nCount)
{
	m_pTexture[nCount] = pTexture;		//テクスチャ割り当て
}