//==============================================================
//
//敵の処理[enemy.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "explosion.h"
#include "particle.h"
#include "texture.h"

//マクロ定義
#define NUM_PATTERN		(10)				//パターン数
#define MOVE_SPEED		(3.0f)				//敵の移動速度
#define ANGLE_UP		(0.75f)				//上の角度
#define ANGLE_DOWN		(0.25f)				//下の角度
#define ANGLE_WIDTH		(0.5f)				//横の角度
#define DEST_ENEMY		(70)				//敵が消滅するまでの時間

//静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;		//テクスチャ

//==============================================================
//コンストラクタ
//==============================================================
CEnemy::CEnemy()
{
	m_nIdxTexture = -1;		//テクスチャの番号

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	//m_move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);	//移動量
}

//==============================================================
//デストラクタ
//==============================================================
CEnemy::~CEnemy()
{

}

//==============================================================
//敵のテクスチャの読み込み
//==============================================================
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//デバイスの取得

	if (m_pTexture == NULL)
	{//テクスチャ設定されてないとき

		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\enemy000.png",
			&m_pTexture);
	}

	return S_OK;
}

//==============================================================
//敵のテクスチャの破棄
//==============================================================
void CEnemy::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==============================================================
//敵の生成処理
//==============================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy *pEnemy = NULL;

	if (pEnemy == NULL)
	{//メモリが使用されてなかったら

		//敵の生成
		pEnemy = new CEnemy;

		if (pEnemy != NULL)
		{//メモリ確保できてたら

			//初期化処理
			pEnemy->Init(pos, rot);
		}
	}

	return pEnemy;
}

//==============================================================
//敵の初期化処理
//==============================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;

	CTexture *pTexture = CManager::GetTexture();

	//テクスチャの読み込み
	m_nIdxTexture = pTexture->Regit("data\\TEXTURE\\enemy000.png");

	//テクスチャの割り当て
	CObject2D::BindTexture(m_nIdxTexture);

	//オブジェクト2Dの初期化処理
	CObject2D::Init(pos, rot);

	//種類の設定
	CObject::SetType(CObject::TYPE_ENEMY);

	///敵の初期設定
	//敵の大きさ設定
	CObject2D::SetSize(WIDTH_ENEMY, HEIGHT_ENEMY);

	return S_OK;
}

//==============================================================
//敵の終了処理
//==============================================================
void CEnemy::Uninit(void)
{
	//2Dオブジェクトの終了処理
	CObject2D::Uninit();
}

//==============================================================
//敵の更新処理
//==============================================================
void CEnemy::Update(void)
{
	//オブジェクト2Dの更新処理
	CObject2D::Update();

	//位置取得
	m_pos = CObject2D::GetPosition();

	//位置設定
	CObject2D::SetPosition(CObject::TYPE_ENEMY, m_pos, WIDTH_ENEMY, HEIGHT_ENEMY);
}

//==============================================================
//敵の描画処理
//==============================================================
void CEnemy::Draw(void)
{
	//2Dオブジェクトの描画処理
	CObject2D::Draw();
}