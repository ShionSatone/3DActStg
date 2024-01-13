//==============================================================
//
//ゲーム処理[game.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _GAME_H_		//このマクロ定義がされていなかったら
#define _GAME_H_		//2重インクルード防止のマクロを定義する

#include "manager.h"

//前方宣言
class CScore;			//スコアの情報
class CPlayerModel;		//プレイヤーの情報
class CEnemyModel;		//敵の情報
class CModel;			//モデルの情報
class CWall;			//壁の情報
class CField;			//床の情報
class CEdit;			//エディットの情報
class CBulletRemain;	//残弾数の情報
class CLife;			//寿命表示の情報
class CPause;			//ポーズ画面の情報
class CFade;			//フェード

//ゲーム画面クラスの定義
class CGame : public CScene
{
public:

	//ゲームモードの種類
	typedef enum
	{
		GAMEMODE_START = 0,			//開始
		GAMEMODE_GROUND,			//地上
		GAMEMODE_UNDER,				//水中
		GAMEMODE_BOSS,				//ボス戦
		GAMEMODE_OVER,				//終了

	} GAMEMODE;

	CGame();
	~CGame();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetEnablePauseMenu(bool bPouse);			//ポーズ切り替え

	static CPlayerModel *GetPlayerModel(void) { return m_pPlayerModel; }				//プレイヤーの情報
	static CBulletRemain *GetBulletRemain(void) { return m_pBulletRemain; }				//残弾数の情報
	static CScore *GetScore(void) { return m_pScore; }			//スコアの情報
	static CLife *GetLife(void) { return m_pLife; }				//寿命表示の情報
	static void SetGameMode(GAMEMODE gameMode) { m_gameMode = gameMode; }		//ゲームモードの設定
	static GAMEMODE GetGameMode(void) { return m_gameMode; }					//ゲームモードの設定
	static CPause *GetPause(void) { return m_pPause; }			//ポーズ画面の情報
	static bool GetPauseDisp(void) { return m_bPause; }			//ポーズしてるか取得

private:
	static CScore *m_pScore;		//スコアの情報
	static CPlayerModel *m_pPlayerModel;	//プレイヤーの情報
	static CEnemyModel *m_pEnemyModel;		//敵の情報
	static CModel *m_pModel;		//モデルの情報
	static CWall *m_pWall;			//壁の情報
	static CField *m_pField;		//床の情報
	static CEdit *m_pEdit;			//エディットの情報
	static CBulletRemain *m_pBulletRemain;		//残弾数の情報
	static CLife *m_pLife;			//寿命表示の情報
	static CPause *m_pPause;		//ポーズ画面の情報

	static bool m_bReset;				//リセットしたか
	static bool m_bPause;				//ポーズ画面か

	static GAMEMODE m_gameMode;		//ゲームモード
	int m_nCntEnemy;				//敵出現カウント
};

#endif

