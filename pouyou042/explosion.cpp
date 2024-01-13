//==============================================================
//
//爆発の処理[explosion.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "texture.h"

//マクロ定義
#define WIDTH_EXPLOSION		(60.0f * 0.5f)		//爆発の横幅
#define HEIGHT_EXPLOSION	(60.0f * 0.5f)		//爆発の縦幅
#define NUM_PATTERN			(10)				//パターン数
#define MOVE_SPEED			(3.0f)				//爆発の移動速度
#define ANGLE_UP			(0.75f)				//上の角度
#define ANGLE_DOWN			(0.25f)				//下の角度
#define ANGLE_WIDTH			(0.5f)				//横の角度
#define DEST_EXPLOSION		(10)				//爆発が消滅するまでの時間

//静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;		//テクスチャ

//==============================================================
//コンストラクタ
//==============================================================
CExplosion::CExplosion()
{
	m_nIdxTexture = -1;		//テクスチャの番号
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_nCntdest = DEST_EXPLOSION;		//爆発消滅の時間
	m_nPatternAnim = 0;
}

//==============================================================
//デストラクタ
//==============================================================
CExplosion::~CExplosion()
{

}

//==============================================================
//爆発のテクスチャの読み込み
//==============================================================
HRESULT CExplosion::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//デバイスの取得

	if (m_pTexture == NULL)
	{//テクスチャ設定されてないとき

		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\explosion000.png",
			&m_pTexture);
	}

	return S_OK;
}

//==============================================================
//爆発のテクスチャの破棄
//==============================================================
void CExplosion::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==============================================================
//爆発の生成処理
//==============================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CExplosion *pExplosion = NULL;

	if (pExplosion == NULL)
	{//メモリが使用されてなかったら

		//爆発の生成
		pExplosion = new CExplosion;
	}

	//初期化処理
	pExplosion->Init(pos, rot);

	return pExplosion;
}

//==============================================================
//爆発の初期化処理
//==============================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CTexture *pTexture = CManager::GetTexture();

	//テクスチャの読み込み
	m_nIdxTexture = pTexture->Regit("data\\TEXTURE\\explosion000.png");

	//テクスチャの割り当て
	CBillboard::BindTexture(m_nIdxTexture);

	//ビルボードの初期化処理
	CBillboard::Init(pos, rot);

	///爆発の初期設定
	//爆発の大きさ設定
	CBillboard::SetSize(WIDTH_EXPLOSION, HEIGHT_EXPLOSION);

	return S_OK;
}

//==============================================================
//爆発の終了処理
//==============================================================
void CExplosion::Uninit(void)
{
	//ビルボードの終了処理
	CBillboard::Uninit();
}

//==============================================================
//爆発の更新処理
//==============================================================
void CExplosion::Update(void)
{
	//位置取得
	m_pos = CBillboard::GetPosition();

	//位置設定
	CBillboard::SetPosition(CObject::TYPE_EXPLOSION, m_pos);

	//ビルボードの更新処理
	CBillboard::Update();

	if ((m_nCounterAnim % 1) == 0)
	{//一定時間経過

		//パターンNo.を更新する
		m_nPatternAnim++;
	
		CBillboard::SetType(TYPE_EXPLOSION, m_nPatternAnim);
	}

	if (m_nPatternAnim == NUM_PATTERN)
	{//パターンの最大に達したら

		//爆発削除
		CExplosion::Uninit();
	}
}

//==============================================================
//爆発の描画処理
//==============================================================
void CExplosion::Draw(void)
{
	//ビルボードの描画処理
	CBillboard::Draw();
}