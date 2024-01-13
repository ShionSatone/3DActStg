//==============================================================
//
//アイテム処理[itemModel.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _ITEMMODEL_H_		//このマクロ定義がされていなかったら
#define _ITEMMODEL_H_		//2重インクルード防止のマクロを定義する

#include"objectX.h"

//モデル配置クラスの定義
class CItemModel : CObjectX
{
public:

	//アイテムの種類
	typedef enum
	{
		TYPEITEM_NONE = 0,
		TYPEITEM_WATER,			//水
		TYPEITEM_ICE,			//氷
		TYPEITEM_VAPOR,			//蒸気
		TYPEITEM_LIFE,			//体力回復
		//TYPEITEM_KEY,			//ボス第２形態のためのキーアイテム
		TYPE_MAX
	} TYPEITEM;

	CItemModel();		//コンストラクタ
	CItemModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPEITEM type);		//コンストラクタ(オーバーロード)
	~CItemModel();		//デストラクタ

	static CItemModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPEITEM type);		//生成処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);

	int GetItemType(void) { return m_type; }

private:

	static int m_nNumAll;			//モデルの種類

	static LPD3DXMESH m_pMesh;			//メッシュ（頂点情報）へのポインタ
	static LPD3DXBUFFER m_pBuffMat;		//マテリアルへのポインタ
	static DWORD m_dwNumMat;			//マテリアルの数
	static const char *m_pFilename[TYPE_MAX];		//ファイル名

	D3DXVECTOR3 m_pos;			//位置
	D3DXVECTOR3 m_rot;			//向き
	int m_nMaxModel;			//モデルの設置数
	int m_nIdx;					//モデルの番号

	int m_type;			//アイテムの種類
};

#endif