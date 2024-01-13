//==============================================================
//
//残機処理[remain.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "remain.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "texture.h"

//マクロ定義
#define WIDTH_REMAIN	(50.0f * 0.5f)		//残機の横幅
#define HEIGHT_REMAIN	(50.0f * 0.5f)		//残機の縦幅
#define NUM_PATTERN		(10)				//パターン数
#define MOVE_SPEED		(3.0f)				//残機の移動速度
#define ANGLE_UP		(0.75f)				//上の角度
#define ANGLE_DOWN		(0.25f)				//下の角度
#define ANGLE_WIDTH		(0.5f)				//横の角度

//静的メンバ変数宣言
int CRemain::m_nNum = 0;		//残機の数

//==============================================================
//コンストラクタ
//==============================================================
CRemain::CRemain()
{
	m_nIdxTexture = -1;		//テクスチャの番号

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	//m_move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);	//移動量
}

//==============================================================
//デストラクタ
//==============================================================
CRemain::~CRemain()
{

}

//==============================================================
//残機の生成処理
//==============================================================
CRemain *CRemain::Create(D3DXVECTOR3 pos, int nIdx)
{
	CRemain *pRemain = NULL;

	if (pRemain == NULL)
	{//メモリが使用されてなかったら

		//残機の生成
		pRemain = new CRemain;
	}

	if (pRemain != NULL)
	{//メモリ確保できてたら

		//初期化処理
		pRemain->Init(pos, D3DXVECTOR3(0.0f,0.0f,0.0f));
	}

	return pRemain;
}

//==============================================================
//残機の初期化処理
//==============================================================
HRESULT CRemain::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;

	CTexture *pTexture = CManager::GetTexture();

	//テクスチャの読み込み
	m_nIdxTexture = pTexture->Regit("data\\TEXTURE\\item000.png");

	//テクスチャの割り当て
	CObject2D::BindTexture(m_nIdxTexture);

	//オブジェクト2Dの初期化処理
	CObject2D::Init(pos, rot);

	//種類の設定
	CObject::SetType(CObject::TYPE_ITEM);

	///残機の初期設定
	//残機の大きさ設定
	CObject2D::SetSize(WIDTH_REMAIN, HEIGHT_REMAIN);

	return S_OK;
}

//==============================================================
//残機の終了処理
//==============================================================
void CRemain::Uninit(void)
{
	//2Dオブジェクトの終了処理
	CObject2D::Uninit();
}

//==============================================================
//残機の更新処理
//==============================================================
void CRemain::Update(void)
{
	//オブジェクト2Dの更新処理
	CObject2D::Update();

	////位置取得
	//m_pos = CObject2D::GetPosition();

	////位置設定
	//CObject2D::SetPosition(CObject::TYPE_ITEM, m_pos, WIDTH_REMAIN, HEIGHT_REMAIN);
}

//==============================================================
//残機の描画処理
//==============================================================
void CRemain::Draw(void)
{
	//2Dオブジェクトの描画処理
	CObject2D::Draw();
}