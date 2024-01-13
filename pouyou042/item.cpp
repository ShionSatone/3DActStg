//==============================================================
//
//アイテム処理[item.h]
//Author:佐藤根詩音
//
//==============================================================
#include "item.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "texture.h"

//マクロ定義
#define WIDTH_ITEM		(50.0f * 0.5f)		//アイテムの横幅
#define HEIGHT_ITEM		(50.0f * 0.5f)		//アイテムの縦幅
#define NUM_PATTERN		(10)				//パターン数
#define MOVE_SPEED		(3.0f)				//アイテムの移動速度
#define ANGLE_UP		(0.75f)				//上の角度
#define ANGLE_DOWN		(0.25f)				//下の角度
#define ANGLE_WIDTH		(0.5f)				//横の角度

//静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CItem::m_pTexture = NULL;		//テクスチャ

//==============================================================
//コンストラクタ
//==============================================================
CItem::CItem()
{
	m_nIdxTexture = -1;		//テクスチャの番号

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	//m_move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);	//移動量
}

//==============================================================
//デストラクタ
//==============================================================
CItem::~CItem()
{

}

//==============================================================
//アイテムのテクスチャの読み込み
//==============================================================
HRESULT CItem::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//デバイスの取得

	if (m_pTexture == NULL)
	{//テクスチャ設定されてないとき

		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\item000.png",
			&m_pTexture);
	}

	return S_OK;
}

//==============================================================
//アイテムのテクスチャの破棄
//==============================================================
void CItem::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==============================================================
//アイテムの生成処理
//==============================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CItem *pItem = NULL;

	if (pItem == NULL)
	{//メモリが使用されてなかったら

		//アイテムの生成
		pItem = new CItem;
	}

	if (pItem != NULL)
	{//メモリ確保できてたら

		//初期化処理
		pItem->Init(pos, rot);
	}

	return pItem;
}

//==============================================================
//アイテムの初期化処理
//==============================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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

	///アイテムの初期設定
	//アイテムの大きさ設定
	CObject2D::SetSize(WIDTH_ITEM, HEIGHT_ITEM);

	return S_OK;
}

//==============================================================
//アイテムの終了処理
//==============================================================
void CItem::Uninit(void)
{
	//2Dオブジェクトの終了処理
	CObject2D::Uninit();
}

//==============================================================
//アイテムの更新処理
//==============================================================
void CItem::Update(void)
{
	//オブジェクト2Dの更新処理
	CObject2D::Update();

	//位置取得
	m_pos = CObject2D::GetPosition();

	//位置設定
	CObject2D::SetPosition(CObject::TYPE_ITEM, m_pos, WIDTH_ITEM, HEIGHT_ITEM);

	//プレイヤーとの当たり判定
	CItem::ColisionPlayer(m_pos);
}

//==============================================================
//アイテムの描画処理
//==============================================================
void CItem::Draw(void)
{
	//2Dオブジェクトの描画処理
	CObject2D::Draw();
}

//==============================================================
//プレイヤーとの当たり判定
//==============================================================
bool CItem::ColisionPlayer(D3DXVECTOR3 pos)
{
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

			if (type == pObj->TYPE_PLAYER)
			{//種類がプレイヤーの場合

				//プレイヤーの位置取得
				D3DXVECTOR3 posPlayer = pObj->GetPosition();

				if (pos.x >= posPlayer.x - WIDTH_PLAYER && pos.x <= posPlayer.x + WIDTH_PLAYER &&
					pos.y >= posPlayer.y - HEIGHT_PLAYER && pos.y <= posPlayer.y)
				{//アイテムとプレイやーが当たった

					//SE再生
					//CSound::Play(CSound::SOUND_LABEL_SE_DAMAGE000);

					//弾の終了処理
					CObject2D::Uninit();

					return true;
				}
			}

		}
	}

	return false;
}