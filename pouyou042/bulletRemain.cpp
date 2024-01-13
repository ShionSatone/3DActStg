//==============================================================
//
//残弾数表示処理[bulletRemain.h]
//Author:佐藤根詩音
//
//==============================================================
#include "bulletRemain.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "game.h"
#include "life.h"

//マクロ定義
#define WIDTH_BR		(400.0f)		//残弾数の横幅
#define HEIGHT_BR		(50.0f)			//残弾数の縦幅
#define NUM_PATTERN		(10)			//パターン数
#define MOVE_SPEED		(3.0f)			//残弾数の移動速度
#define LIFE_CNT		(60)			//ライフ減らすカウント

//静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CBulletRemain::m_pTexture = NULL;		//テクスチャ

//==============================================================
//コンストラクタ
//==============================================================
CBulletRemain::CBulletRemain()
{
	m_nIdxTexture = -1;		//テクスチャの番号

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	//m_move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);	//移動量

	m_nNumBullet = 0;		//弾消費数
	m_nCntLife = LIFE_CNT;			//体力減らすカウンター
}

//==============================================================
//コンストラクタ(オーバーロード)
//==============================================================
CBulletRemain::CBulletRemain(D3DXVECTOR3 pos)
{
	m_nIdxTexture = -1;		//テクスチャの番号

	m_pos = pos;		//位置

	m_nCntLife = LIFE_CNT;			//体力減らすカウンター
	m_nNumBullet = 0;		//弾消費数
}

//==============================================================
//デストラクタ
//==============================================================
CBulletRemain::~CBulletRemain()
{

}

//==============================================================
//残弾数の生成処理
//==============================================================
CBulletRemain *CBulletRemain::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBulletRemain *pBulletRemain = NULL;

	if (pBulletRemain == NULL)
	{//メモリが使用されてなかったら

		//残弾数の生成
		pBulletRemain = new CBulletRemain(pos);
	}

	if (pBulletRemain != NULL)
	{//メモリ確保できてたら

		//初期化処理
		pBulletRemain->Init(pos, rot);
	}

	return pBulletRemain;
}

//==============================================================
//残弾数の初期化処理
//==============================================================
HRESULT CBulletRemain::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;

	CTexture *pTexture = CManager::GetTexture();

	//テクスチャの読み込み
	m_nIdxTexture = pTexture->Regit("data\\TEXTURE\\BR00.png");

	//テクスチャの割り当て
	CObject2D::BindTexture(m_nIdxTexture);

	//オブジェクト2Dの初期化処理
	CObject2D::Init(m_pos, rot);

	//種類の設定
	CObject::SetType(CObject::TYPE_BLOCK);

	///残弾数の初期設定
	//残弾数の大きさ設定
	CObject2D::SetSize(WIDTH_BR, HEIGHT_BR);

	//位置設定
	CObject2D::SetPosition(CObject::TYPE_BLOCK, m_pos, WIDTH_BR - m_nNumBullet, HEIGHT_BR);

	return S_OK;
}

//==============================================================
//残弾数の終了処理
//==============================================================
void CBulletRemain::Uninit(void)
{
	//2Dオブジェクトの終了処理
	CObject2D::Uninit();

	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//残弾数の更新処理
//==============================================================
void CBulletRemain::Update(void)
{
	CLife *pLife = CGame::GetLife();

	//オブジェクト2Dの更新処理
	CObject2D::Update();

	//位置設定
	CObject2D::SetPosition(CObject::TYPE_BLOCK, m_pos, WIDTH_BR - m_nNumBullet, HEIGHT_BR);

	if (m_nNumBullet >= WIDTH_BR)
	{//弾がなくなったら

		if (m_nCntLife >= LIFE_CNT)
		{
			//体力減らす
			pLife->SetNum(-40);

			m_nCntLife = 0;
		}

		m_nCntLife++;
	}
}

//==============================================================
//残弾数の描画処理
//==============================================================
void CBulletRemain::Draw(void)
{
	//2Dオブジェクトの描画処理
	CObject2D::Draw();
}

//==============================================================
//弾数設定処理
//==============================================================
void CBulletRemain::SetNumBullet(int nNumBullet)
{
	if (nNumBullet < 0)
	{//回復するとき

		if ((m_nNumBullet + nNumBullet) > 0)
		{//弾の上限以内の場合

			m_nNumBullet += nNumBullet;
		}
		else if ((m_nNumBullet + nNumBullet) <= 0)
		{//弾の上限超える場合

			m_nNumBullet = 0;
		}
	}
	else if (nNumBullet >= 0)
	{//消費するとき

		m_nNumBullet += nNumBullet;
	}
}