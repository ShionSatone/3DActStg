//==============================================================
//
//ブロックの処理[block.h]
//Author:佐藤根詩音
//
//==============================================================
#include "block.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//マクロ定義
#define NUM_PATTERN		(10)				//パターン数
#define WIDTH_BLOCK		(100.0f)			//ブロックの横幅
#define HEIGHT_BLOCK	(100.0f)			//ブロックの縦幅
#define MOVE_SPEED		(3.0f)				//ブロックの移動速度
#define ANGLE_UP		(0.75f)				//上の角度
#define ANGLE_DOWN		(0.25f)				//下の角度
#define ANGLE_WIDTH		(0.5f)				//横の角度
#define BLOCK_LIFE		(70)				//ブロックが消滅するまでの時間

//静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CBlock::m_pTexture = NULL;		//テクスチャ
D3DXVECTOR3 CBlock::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
float CBlock::m_fWidth = 0.0f;
float CBlock::m_fHeight = 0.0f;

//==============================================================
//コンストラクタ
//==============================================================
CBlock::CBlock()
{
	m_nIdxTexture;		//テクスチャの番号

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	//m_move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);	//移動量
	m_fWidth = WIDTH_BLOCK;			//幅
	m_fHeight = HEIGHT_BLOCK;		//高さ
	m_nType = 0;				//種類
	m_nCounterMove = 0;			//ブロックの動きのカウンター
}

//==============================================================
//デストラクタ
//==============================================================
CBlock::~CBlock()
{

}

//==============================================================
//ブロックのテクスチャの読み込み
//==============================================================
HRESULT CBlock::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//デバイスの取得

	if (m_pTexture == NULL)
	{//テクスチャ設定されてないとき

		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\block000.jpg",
			&m_pTexture);
	}

	return S_OK;
}

//==============================================================
//ブロックのテクスチャの破棄
//==============================================================
void CBlock::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==============================================================
//ブロックの生成処理
//==============================================================
CBlock *CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBlock *pBlock = NULL;

	if (pBlock == NULL)
	{//メモリが使用されてなかったら

		//ブロックの生成
		pBlock = new CBlock;


		if (pBlock != NULL)
		{//メモリ確保できてたら

			//初期化処理
			pBlock->Init(pos, rot);
		}
	}

	return pBlock;
}

//==============================================================
//ブロックの初期化処理
//==============================================================
HRESULT CBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;

	CTexture *pTexture = CManager::GetTexture();

	//テクスチャの読み込み
	m_nIdxTexture = pTexture->Regit("data\\TEXTURE\\block000.jpg");

	//テクスチャの割り当て
	CObject2D::BindTexture(m_nIdxTexture);

	//オブジェクト2Dの初期化処理
	CObject2D::Init(pos, rot);

	//種類の設定
	CObject::SetType(CObject::TYPE_BLOCK);

	///ブロックの初期設定
	//ブロックの大きさ設定
	CObject2D::SetSize(WIDTH_BLOCK, HEIGHT_BLOCK);

	return S_OK;
}

//==============================================================
//ブロックの終了処理
//==============================================================
void CBlock::Uninit(void)
{
	//2Dオブジェクトの終了処理
	CObject2D::Uninit();
}

//==============================================================
//ブロックの更新処理
//==============================================================
void CBlock::Update(void)
{
	//オブジェクト2Dの更新処理
	CObject2D::Update();

	//位置取得
	m_pos = CObject2D::GetPosition();

	//位置設定
	CObject2D::SetPosition(CObject::TYPE_BLOCK, m_pos, WIDTH_BLOCK, HEIGHT_BLOCK);
}

//==============================================================
//ブロックの描画処理
//==============================================================
void CBlock::Draw(void)
{
	//2Dオブジェクトの描画処理
	CObject2D::Draw();
}

//==============================================================
//ブロックの設定処理
//==============================================================
void CBlock::Set(D3DXVECTOR3 pos, int nType, float fWidth, float fHeight)
{
	m_pos = pos;			//位置
	m_nType = nType;		//種類
	m_fWidth = fWidth;		//横幅
	m_fHeight = fHeight;	//縦幅

	//位置設定処理
	CObject2D::SetPosition(CObject::TYPE_BLOCK, pos, m_fWidth, m_fHeight);
}

//==============================================================
//ブロックの当たり判定
//==============================================================
bool CBlock::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight/*, Block **pBlock*/)
{
	CPlayer *pPlayer = CManager::GetPlayer();
	bool bLand = false;

	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		CObject *pObj;

		//オブジェクトを取得
		pObj = GetObject(nCntObj);

		if (pObj != NULL)
		{//メモリが使用されているとき

			CObject::TYPE type;

			//種類を取得
			type = pObj->GetType();

			if (type == pObj->TYPE_BLOCK)
			{//種類がブロックの場合

				//ブロックの位置取得
				D3DXVECTOR3 posBlock = pObj->GetPosition();

				if (pPosOld->y <= posBlock.y && pPos->y > posBlock.y &&
					pPos->x + fWidth > posBlock.x && pPos->x - fWidth < posBlock.x + m_fWidth)
				{//ブロックの上にめり込んだ

					if (pPosOld->x + fWidth <= posBlock.x && pPos->x + fWidth > posBlock.x &&
						pPos->y > posBlock.y && pPos->y - fHeight < posBlock.y + m_fHeight)
					{//ブロックの左にめり込んだ

					}
					else if (pPosOld->x - fWidth >= posBlock.x + m_fWidth && pPos->x - fWidth < posBlock.x + m_fWidth &&
						pPos->y > posBlock.y && pPos->y - fHeight < posBlock.y + m_fHeight)
					{//ブロックの右にめり込んだ

					}
					else
					{//どこにも当たってない場合

						//ブロックの上に移動
						pPos->y = posBlock.y;

						pMove->y = 0.0f;

						//着地した
						bLand = true;
					}
				}

				if (pPosOld->y - fHeight >= posBlock.y + m_fHeight && pPos->y - fHeight < posBlock.y + m_fHeight &&
					pPos->x + fWidth > posBlock.x && pPos->x - fWidth < posBlock.x + m_fWidth)
				{//ブロックの下にめり込んだ

					if (pPosOld->x + fWidth <= posBlock.x && pPos->x + fWidth > posBlock.x &&
						pPos->y > posBlock.y && pPos->y - fHeight < posBlock.y + m_fHeight)
					{//ブロックの左にめり込んだ

					}
					else if (pPosOld->x - fWidth >= posBlock.x + m_fWidth && pPos->x - fWidth < posBlock.x + m_fWidth &&
						pPos->y > posBlock.y && pPos->y - fHeight < posBlock.y + m_fHeight)
					{//ブロックの右にめり込んだ

					}
					else
					{//どこにも当たってない場合

						//ブロックの下に移動
						pPos->y = posBlock.y + m_fHeight + fHeight;

						pMove->y = 0.0f;

						//着地してない
						bLand = false;
					}
				}

				if (pPosOld->x + fWidth <= posBlock.x && pPos->x + fWidth > posBlock.x &&
					pPos->y > posBlock.y && pPos->y - fHeight < posBlock.y + m_fHeight)
				{//ブロックの左にめり込んだ

					if (pPosOld->y <= posBlock.y && pPos->y > posBlock.y &&
						pPos->x + fWidth > posBlock.x && pPos->x - fWidth < posBlock.x + m_fWidth)
					{//ブロックの上にめり込んだ

					}
					else if (pPosOld->y - fHeight >= posBlock.y + m_fHeight && pPos->y - fHeight < posBlock.y + m_fHeight &&
						pPos->x + fWidth > posBlock.x && pPos->x - fWidth < posBlock.x + m_fWidth)
					{//ブロックの下にめり込んだ

					}
					else
					{//どこにも当たってない場合

						//ブロックの左に移動
						pPos->x = posBlock.x - fWidth;

						pMove->x = 0.0f;

						//着地してない
						bLand = false;
					}
				}

				if (pPosOld->x - fWidth >= posBlock.x + m_fWidth && pPos->x - fWidth < posBlock.x + m_fWidth &&
					pPos->y > posBlock.y && pPos->y - fHeight < posBlock.y + m_fHeight)
				{//ブロックの右にめり込んだ

					if (pPosOld->y <= posBlock.y && pPos->y > posBlock.y &&
						pPos->x + fWidth > posBlock.x && pPos->x - fWidth < posBlock.x + m_fWidth)
					{//ブロックの上にめり込んだ

					}
					else if (pPosOld->y - fHeight >= posBlock.y + m_fHeight && pPos->y - fHeight < posBlock.y + m_fHeight &&
						pPos->x + fWidth > posBlock.x && pPos->x - fWidth < posBlock.x + m_fWidth)
					{//ブロックの下にめり込んだ

					}
					else
					{//どこにも当たってない場合

						//ブロックの右に移動
						pPos->x = posBlock.x + m_fWidth + fWidth;

						pMove->x = 0.0f;

						//着地してない
						bLand = false;
					}
				}
			}

		}
	}

	return bLand;
}