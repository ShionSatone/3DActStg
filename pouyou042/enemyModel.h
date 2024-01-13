//==============================================================
//
//モデル処理[enemyModel.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _ENEMYMODEL_H_		//このマクロ定義がされていなかったら
#define _ENEMYMODEL_H_		//2重インクルード防止のマクロを定義する

#include"objectX.h"

//マクロ定義
#define MAX_ENEMY_MODEL			(128)		//モデルの数

//前方宣言
class CModelHier;			//モデルの階層構造
class CMotion;				//モーション

//敵クラスの定義
class CEnemyModel : public CObject
{
public:

	//敵の種類の列挙の定義
	typedef enum
	{
		ENEMYTYPE_FROG = 0,			//カエル
		ENEMYTYPE_AQUATICA,			//ロリッパアクアテイカ

		ENEMYTYPE_JELLY,			//クラゲ
		ENEMYTYPE_NUDI,				//ウミウシ

		ENEMYTYPE_WITCH,			//魔女
		ENEMYTYPE_MAX
	} ENEMYTYPE;

	CEnemyModel();		//コンストラクタ
	CEnemyModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);		//コンストラクタ(オーバーロード)
	~CEnemyModel();		//デストラクタ

	//static HRESULT Load(const char *pFilename);		//テクスチャの読み込み
	//static void Unload(void);		//テクスチャの破棄
	static CEnemyModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ENEMYTYPE type, int nLife);		//生成処理

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot) = 0;
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Hit(void) = 0;
	D3DXVECTOR3 GetSizeMin(void) { return m_min; }
	D3DXVECTOR3 GetSizeMax(void) { return m_max; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			//位置の取得
	void SetRotaition(D3DXVECTOR3 rot) { m_rot = rot; }		//向きの設定
	D3DXVECTOR3 GetRotation(void) { return m_rot; }			//向きの取得

protected:
	static CEnemyModel *m_apEnemyModel[MAX_ENEMY_MODEL];			//敵のモデル
	CMotion *m_pMotion;		//モーション情報
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_posOld;	//前回の位置
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_rot;		//向き
	D3DXVECTOR3 m_max;		//最大値
	D3DXVECTOR3 m_min;		//最小値
	int m_nLife;			//寿命
	int m_nCntDamage;		//ダメージカウンター
	int m_nCntAttack;		//攻撃カウンター
	STATE m_state;			//敵の状態

protected:

	bool m_bAction;			//攻撃したか
	bool m_bJump;			//ジャンプしたか
	bool m_bLand;			//着地したか

private:
	static LPD3DXMESH m_pMesh;						//メッシュ（頂点情報）へのポインタ
	static LPD3DXBUFFER m_pBuffMat;					//マテリアルへのポインタ
	static DWORD m_dwNumMat;						//マテリアルの数
	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス

	int m_nIdxTexture;			//テクスチャの番号
	static int m_nNumAll;		//敵の総数
	int m_nID;					//敵の番号

	ENEMYTYPE m_type;		//敵の種類
};

//カエルの敵クラスの定義
class CEnemyFrog : public CEnemyModel
{
public:

	//敵のパーツ
	typedef enum
	{
		PARTS_BODY = 0,		//[0]体
		PARTS_LU,			//[1]左腕上
		PARTS_LD,			//[2]左腕下
		PARTS_HAND_L,		//[3]左手
		PARTS_RU,			//[4]右腕上
		PARTS_RD,			//[5]右腕下
		PARTS_HAND_R,		//[6]右手
		PARTS_LEG_LU,		//[7]左太もも
		PARTS_LEG_LD,		//[8]左ふくらはぎ
		PARTS_ANKLE_L,		//[9]左足首
		PARTS_SHOE_L,		//[10]左靴
		PARTS_LEG_RU,		//[11]右太もも
		PARTS_LEG_RD,		//[12]右ふくらはぎ
		PARTS_ANKLE_R,		//[13]右足首
		PARTS_SHOE_R,		//[14]右靴
		PARTS_MAX
	} PARTS;

	CEnemyFrog();		//コンストラクタ
	CEnemyFrog(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);		//コンストラクタ(オーバーロード)
	~CEnemyFrog();		//デストラクタ

	void LoadFile(void);	//モデルファイル読み込み

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);

private:

	static char *m_apFileName[PARTS_MAX];		//ファイル名
	CModelHier *m_apModel[PARTS_MAX];		//モデル(パーツ)へのポインタ


};

//ロリッパアクアティカの敵クラスの定義
class CEnemyAquatica : public CEnemyModel
{
public:

	//敵のパーツ
	typedef enum
	{
		PARTS_BODY = 0,		//[0]体
		//PARTS_HEAD,			//[1]頭
		//PARTS_HAIR,			//[2]お下げ
		//PARTS_ARMUP_L,		//[3]左腕上
		//PARTS_ARMDOWN_L,	//[4]左腕下
		//PARTS_HAND_L,		//[5]左手
		//PARTS_ARMUP_R,		//[6]右腕上
		//PARTS_ARMDOWN_R,	//[7]右腕下
		//PARTS_HAND_R,		//[8]右手
		//PARTS_WAIST,		//[9]腰
		//PARTS_SKIRT,		//[10]スカート
		//PARTS_LEG_L,		//[11]左太もも
		//PARTS_CALF_L,		//[12]左ふくらはぎ
		//PARTS_FOOT_L,		//[13]左靴
		//PARTS_LEG_R,		//[14]右太もも
		//PARTS_CALF_R,		//[15]右ふくらはぎ
		//PARTS_FOOT_R,		//[16]右靴
		//PARTS_WEAPON,		//[17]武器(ッテッポウウオ)
		PARTS_MAX
	} PARTS;

	CEnemyAquatica();		//コンストラクタ
	CEnemyAquatica(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);		//コンストラクタ(オーバーロード)
	~CEnemyAquatica();		//デストラクタ

	void LoadFile(void);	//モデルファイル読み込み

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);

private:

	static char *m_apFileName[PARTS_MAX];		//ファイル名
	CModelHier *m_apModel[PARTS_MAX];		//モデル(パーツ)へのポインタ

};

//魔女の敵クラスの定義
class CEnemWitch : public CEnemyModel
{
public:

	//敵のパーツ
	typedef enum
	{
		PARTS_BODY = 0,		//[0]体
		PARTS_HEAD,			//[1]頭
		PARTS_ARMUP_L,		//[2]左腕上
		PARTS_ARMDOWN_L,	//[3]左腕下
		PARTS_HAND_L,		//[4]左手
		PARTS_ARMUP_R,		//[5]右腕上
		PARTS_ARMDOWN_R,	//[6]右腕下
		PARTS_HAND_R,		//[7]右手
		PARTS_WAIST,		//[8]腰
		PARTS_SKIRT,		//[9]スカート
		PARTS_LEG_L,		//[10]左太もも
		PARTS_CALF_L,		//[11]左ふくらはぎ
		PARTS_FOOT_L,		//[12]左靴
		PARTS_LEG_R,		//[13]右太もも
		PARTS_CALF_R,		//[14]右ふくらはぎ
		PARTS_FOOT_R,		//[15]右靴
		PARTS_MAX
	} PARTS;

	//魔女の形態
	typedef enum
	{
		FORM_FIRST = 0,		//第1形態
		FORM_SECOND,		//第２形態
		FORM_MAX
	} FORM;

	//攻撃の種類
	typedef enum
	{
		ATTACK_GROUND = 0,		//地面
		ATTACK_FLY,				//空中
		ATTACK_3D,				//立体
		ATTACK_MAX
	} ATTACK;

	CEnemWitch();		//コンストラクタ
	CEnemWitch(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);		//コンストラクタ(オーバーロード)
	~CEnemWitch();		//デストラクタ

	void LoadFile(void);	//モデルファイル読み込み

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);

	int GetForm(void) { return m_form; }		//魔女の形態取得
	static int GetAttack(void) { return m_attack; }

private:

	static char *m_apFileName[PARTS_MAX];		//ファイル名
	CModelHier *m_apModel[PARTS_MAX];		//モデル(パーツ)へのポインタ

	FORM m_form;		//形態
	static ATTACK m_attack;	//攻撃の種類
	int m_nCntSwitch;	//切り替えカウント
	bool m_bBgm;		//BGMが鳴ったか
	bool m_bItem;		//アイテム出現していいのか
	int m_nCntEnemy;	//敵出現までのカウント
	int m_nCntItem;		//アイテム出現カウント
	float m_fAngle;		//角度
};

#endif
