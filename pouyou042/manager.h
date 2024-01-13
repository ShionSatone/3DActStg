//==============================================================
//
//マネージャ処理[manager.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _MANAGER_H_		//このマクロ定義がされていなかったら
#define _MANAGER_H_		//2重インクルード防止のマクロを定義する

#include "main.h"
#include "object.h"

//前方宣言
class CRenderer;		//レンダラー
class CInputKeyboard;	//キーボード入力
class CInputJoyPad;		//ゲームパッドの入力
class CPlayer;			//プレイヤー
class CEnemy;			//敵
class CSound;			//サウンド
class CCamera;			//カメラ
class CLight;			//ライト
class CDebugProc;		//デバッグ表示
class CTexture;			//テクスチャ
class CMaterial;		//マテリアル
class CTitle;			//タイトル画面
class CTutorial;		//チュートリアル画面
class CGame;			//ゲーム画面
class CResult;			//リザルト画面
class CRanking;			//ランキング画面
class CFade;			//フェード

//シーンクラスの定義
class CScene : public CObject
{
public:

	//ゲームモード
	typedef enum
	{
		MODE_TITLE = 0,		//タイトル画面
		MODE_TUTORIAL,		//チュートリアル画面
		MODE_GAME,			//ゲーム画面
		MODE_RESULT,		//リザルト画面
		MODE_RANKING,		//ランキング画面

	} MODE;

	CScene();
	CScene(MODE mode);
	~CScene();

	static CScene *Create(MODE mode);		//生成処理

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//初期化処理
	virtual void Uninit(void);			//終了処理
	virtual void Update(void);			//更新処理
	virtual void Draw(void);			//描画処理
	MODE GetMode(void) { return m_mode; }			//モード取得
	void SetMode(MODE mode) { m_mode = mode; }		//モード設定

	static CGame *GetGame(void) { return m_pGame; }		//ゲーム画面取得
	static CRanking *GetRanking(void) { return m_pRanking; }		//ランキング画面取得

private:
	MODE m_mode;			//ゲームモード

	static CTitle *m_pTitle;			//タイトル画面の情報
	static CTutorial *m_pTutorial;		//チュートリアル画面
	static CGame *m_pGame;				//ゲーム画面の情報
	static CResult *m_pResult;			//リザルト画面の情報
	static CRanking *m_pRanking;		//ランキング画面の情報
};

//マネージャクラスの定義
class CManager
{
public:

	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance,
		HWND hWnd,
		BOOL bWindow);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	void ResetMap(void);	//マップの再生成

	static CRenderer *GetRenderer(void) { return m_pRenderer; }		//レンダラーの取得
	static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }		//キーボードの取得
	static CInputJoyPad *GetInputJoyPad(void) { return m_pInputJoyPad; }			//ゲームパッドの取得
	static CTexture *GetTexture(void) { return m_pTexture; }		//テクスチャの取得
	static CMaterial *GetMaterial(void) { return m_pMaterial; }		//マテリアルの取得

	static CPlayer *GetPlayer(void) { return m_pPlayer; }			//プレイヤーの取得
	static CEnemy *GetEnemy(void) { return m_pEnemy; }				//敵の情報
	static CDebugProc *GetDebugProc(void) { return m_pDebugProc; }	//デバッグ表示の取得
	static CSound *GetSound(void) { return m_pSound; }				//サウンドの取得

	static CCamera *GetCamera(void) { return m_pCamera; }			//カメラの情報
	static CLight *GetLight(void) { return m_pLight; }				//ライトの情報
	static CScene *GetScene(void) { return m_pScene; }				//シーンの情報
	static CFade *GetFade(void) { return m_pFade; }					//フェードの情報

	static void SetMode(CScene::MODE mode);		//ゲームモード設定
	static CScene::MODE GetMode(void);			//ゲームモード取得
	static void SetNumScore(int nNum) { m_nScore = nNum; }		//スコアの設定
	static int GetNumScore(void) { return m_nScore; }			//スコアの取得
	static void SetBgm(bool bBgm) { m_bBgm = bBgm; }		//BGMの設定
	static bool GetBgm(void) { return m_bBgm; }				//BGMの取得
	static void SetResult(bool bResult) { m_bResult = bResult; }	//リザルトの判定の設定
	static bool GetResult(void) { return m_bResult; }				//リザルトの判定取得

private:
	static CRenderer *m_pRenderer;		//レンダラーの情報
	static CInputKeyboard *m_pInputKeyboard;	//キーボードの情報
	static CInputJoyPad *m_pInputJoyPad;		//ゲームパッドの情報
	static CTexture *m_pTexture;				//テクスチャの情報
	static CMaterial *m_pMaterial;		//マテリアルの情報

	static CPlayer *m_pPlayer;			//プレイヤーの情報
	static CEnemy *m_pEnemy;			//敵の情報
	static CSound *m_pSound;			//サウンドの情報
	static CDebugProc *m_pDebugProc;	//デバッグ表示の情報

	static CCamera *m_pCamera;			//カメラの情報
	static CLight *m_pLight;			//ライトの情報
	static CScene *m_pScene;			//シーンの情報
	static CFade *m_pFade;				//フェードの情報

	static int m_nScore;				//スコア
	static bool m_bBgm;					//BGMストップするか
	static bool m_bResult;				//リザルトの判定
};

#endif
