//==============================================================
//
//投影スイッチ処理[switch.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "switch.h"
#include "game.h"
#include "model.h"
#include "playerModel.h"
#include "material.h"
#include "sound.h"

//マクロ定義
#define SWITCH_NAME		"data\\MODEL\\map\\switch.x"		//スイッチのファイル名

//静的メンバ変数宣言
LPD3DXMESH CSwitch::m_pMesh = NULL;				//メッシュ（頂点情報）へのポインタ
LPD3DXBUFFER CSwitch::m_pBuffMat = NULL;		//マテリアルへのポインタ
DWORD CSwitch::m_dwNumMat = NULL;
const char *CSwitch::m_pFilename = {}; 			//ファイルの名前

//==============================================================
//コンストラクタ
//==============================================================
CSwitch::CSwitch()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	m_nIdx = -1;				//モデルの番号
}

//==============================================================
//コンストラクタ(オーバーロード)
//==============================================================
CSwitch::CSwitch(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;		//位置
	m_rot = rot;		//向き
	m_nIdx = -1;		//モデルの番号
}

//==============================================================
//デストラクタ
//==============================================================
CSwitch::~CSwitch()
{

}

//==============================================================
//投影スイッチの生成処理
//==============================================================
CSwitch *CSwitch::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CSwitch *pSwitch = NULL;

	if (pSwitch == NULL)
	{//メモリが使用されてなかったら

		//投影スイッチの生成
		pSwitch = new CSwitch(pos, rot);
	}

	//初期化処理
	pSwitch->Init(pos, rot);

	return pSwitch;
}

//==============================================================
//投影スイッチの初期化処理
//==============================================================
HRESULT CSwitch::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CMaterial *pMaterial = CManager::GetMaterial();

	//モデルの読み込み
	m_nIdx = pMaterial->Regit(SWITCH_NAME);

	//マテリアルの割り当て
	CObjectX::BindMaterial(m_nIdx);

	//オブジェクトXの初期化処理
	CObjectX::Init(pos, rot);

	//種類の設定
	CObject::SetType(CObject::TYPE_SWITCH);

	return S_OK;
}

//==============================================================
//投影スイッチの終了処理
//==============================================================
void CSwitch::Uninit(void)
{
	//オブジェクトXの終了処理
	CObjectX::Uninit();
}

//==============================================================
//投影スイッチの更新処理
//==============================================================
void CSwitch::Update(void)
{
	//オブジェクトXの更新処理
	CObjectX::Update();
}

//==============================================================
//投影スイッチの描画処理
//==============================================================
void CSwitch::Draw(void)
{
	//オブジェクトXの描画処理
	CObjectX::Draw();
}

//==============================================================
//投影スイッチのヒット処理
//==============================================================
void CSwitch::Hit(void)
{
	CPlayerModel *pPlayer = CGame::GetPlayerModel();

	//武器の種類変更する
	pPlayer->SetWeaponType(m_type);

	//終了処理
	CSwitch::Uninit();
}