//==============================================================
//
//体力表示処理[life.h]
//Author:佐藤根詩音
//
//==============================================================
#include "life.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "particle.h"
#include "playerModel.h"
#include "game.h"

//マクロ定義
#define WIDTH_LIFE		(400.0f)		//体力表示の横幅
#define HEIGHT_LIFE		(20.0f)			//体力表示の縦幅

//静的メンバ変数宣言
CObject2D *CLife::m_apObject2D[NUM_LIFE_FRAME] = {};		//オブジェクト2Dの情報

//==============================================================
//コンストラクタ
//==============================================================
CLife::CLife()
{
	for (int nCntTex = 0; nCntTex < NUM_LIFE_FRAME; nCntTex++)
	{
		m_nIdxTexture[nCntTex] = -1;		//テクスチャの番号
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	//m_move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);	//移動量

	m_nNumCon = 0;		//体力消費数
}

//==============================================================
//コンストラクタ(オーバーロード)
//==============================================================
CLife::CLife(D3DXVECTOR3 pos)
{
	for (int nCntTex = 0; nCntTex < NUM_LIFE_FRAME; nCntTex++)
	{
		m_nIdxTexture[nCntTex] = -1;		//テクスチャの番号
	}

	m_pos = pos;		//位置

	m_nNumCon = 0;		//体力消費数
}

//==============================================================
//デストラクタ
//==============================================================
CLife::~CLife()
{

}

//==============================================================
//体力表示の生成処理
//==============================================================
CLife *CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CLife *pLife = NULL;

	if (pLife == NULL)
	{//メモリが使用されてなかったら

		//体力表示の生成
		pLife = new CLife(pos);
	}

	if (pLife != NULL)
	{//メモリ確保できてたら

		//初期化処理
		pLife->Init(pos, rot);
	}

	return pLife;
}

//==============================================================
//体力表示の初期化処理
//==============================================================
HRESULT CLife::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;

	CTexture *pTexture = CManager::GetTexture();

	//テクスチャの読み込み
	m_nIdxTexture[0] = pTexture->Regit("data\\TEXTURE\\life.jpg");
	m_nIdxTexture[1] = pTexture->Regit("data\\TEXTURE\\life01.png");

	//初期化処置
	for (int nCntLife = 0; nCntLife < NUM_LIFE_FRAME; nCntLife++)
	{
		if (m_apObject2D[nCntLife] == NULL)
		{//使用されてないとき

			//2Dオブジェクト生成
			m_apObject2D[nCntLife] = CObject2D::Create();

			if (m_apObject2D[nCntLife] != NULL)
			{//生成出来たら

				//大きさ設定
				m_apObject2D[nCntLife]->SetSize(WIDTH_LIFE, HEIGHT_LIFE);

				//テクスチャ割り当て
				m_apObject2D[nCntLife]->BindTexture(m_nIdxTexture[nCntLife]);

				//位置設定
				m_apObject2D[nCntLife]->SetPosition(CObject::TYPE_BLOCK, m_pos, WIDTH_LIFE - m_nNumCon, HEIGHT_LIFE);
			}
		}
	}

	//種類の設定
	CObject::SetType(CObject::TYPE_BLOCK);

	return S_OK;
}

//==============================================================
//体力表示の終了処理
//==============================================================
void CLife::Uninit(void)
{
	for (int nCntLife = 0; nCntLife < NUM_LIFE_FRAME; nCntLife++)
	{
		if (m_apObject2D[nCntLife] != NULL)
		{
			m_apObject2D[nCntLife]->Uninit();
			m_apObject2D[nCntLife] = NULL;
		}
	}

	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//体力表示の更新処理
//==============================================================
void CLife::Update(void)
{
	for (int nCntLife = 0; nCntLife < NUM_LIFE_FRAME; nCntLife++)
	{
		//オブジェクト2Dの更新処理
		m_apObject2D[nCntLife]->Update();

		//位置更新
		m_apObject2D[0]->SetPosition(CObject::TYPE_BLOCK, m_pos, float(m_nMaxLife - m_nNumCon), HEIGHT_LIFE);
	}
}

//==============================================================
//体力表示の描画処理
//==============================================================
void CLife::Draw(void)
{
	for (int nCntLife = 0; nCntLife < NUM_LIFE_FRAME; nCntLife++)
	{
		//2Dオブジェクトの描画処理
		m_apObject2D[nCntLife]->Draw();
	}
}

//==============================================================
//体力表示の設定処理
//==============================================================
void CLife::SetNum(int nNumBullet)
{
	CPlayerModel *pPlayer = CGame::GetPlayerModel();

	if (nNumBullet > 0)
	{//回復の場合

		if ((m_nMaxLife - m_nNumCon) < m_nMaxLife - nNumBullet)
		{//回復量が体力より少ない場合

			m_nNumCon -= nNumBullet;
		}
		else
		{
			m_nNumCon = 0;
		}

		//パーティクル生成
		CParticle::Create(pPlayer->GetPosition(), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), PARTICLETYPE_LIFE, 30, 15.0f);
	}
	else if ((m_nMaxLife - m_nNumCon) > 0)
	{//体力があったら

		m_nNumCon -= nNumBullet;

	}
	else
	{
		//プレイヤーを死亡状態にする
		pPlayer->SetState(STATE_DEATH);
	}
}