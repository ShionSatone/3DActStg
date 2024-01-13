//==============================================================
//
//フェード処理[fade.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "fade.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//マクロ定義
#define WIDTH_BG		(SCREEN_WIDTH * 0.5f)		//横幅
#define HEIGHT_BG		(SCREEN_HEIGHT * 0.5f)		//縦幅

//==============================================================
//コンストラクタ
//==============================================================
CFade::CFade()
{
	m_nIdxTexture = -1;		//テクスチャの番号

	m_fade = FADE_IN;										//何もしてない状態
	m_modeNext = CScene::MODE_TITLE;						//次の画面（モード）を設定
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);		//黒いポリゴン（不透明）にしておく
}

//==============================================================
//デストラクタ
//==============================================================
CFade::~CFade()
{

}

//==============================================================
//生成処理
//==============================================================
CFade *CFade::Create()
{
	CFade *pCFade = NULL;

	if (pCFade == NULL)
	{//メモリが使用されてなかったら

		//フェードの生成
		pCFade = new CFade();
	}

	//初期化処理
	pCFade->Init(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return pCFade;
}

//==============================================================
//フェードの初期化処理
//==============================================================
HRESULT CFade::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CTexture *pTexture = CManager::GetTexture();
	int mode = CManager::GetMode();		//現在のゲームモード取得

	//テクスチャの割り当て
	CObject2D::BindTexture(NULL);

	//オブジェクト2Dの初期化処理
	CObject2D::Init(pos, rot);

	//種類の設定
	CObject::SetType(CObject::TYPE_FADE);

	///フェードの初期設定
	//フェードの大きさ設定
	CObject2D::SetSize(WIDTH_BG, HEIGHT_BG);

	//位置設定
	CObject2D::SetPosition(CObject::TYPE_NONE, pos, WIDTH_BG, HEIGHT_BG);

	//頂点カラーの設定
	CObject2D::SetColor(CObject::TYPE_FADE, m_colorFade);

	return S_OK;
}

//==============================================================
//フェードの終了処理
//==============================================================
void CFade::Uninit(void)
{
	//2Dオブジェクトの終了処理
	//CObject2D::Uninit();

	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//フェードの更新処理
//==============================================================
void CFade::Update(void)
{
	CScene *pScene = CManager::GetScene();

	if (m_fade != FADE_NONE)
	{//何もしていない状態じゃないとき

		if (m_fade == FADE_IN)
		{//フェードイン状態

			m_colorFade.a -= 0.03f;		//ポリゴンを透明にしていく

			if (m_colorFade.a <= 0.0f)
			{//透明になったら

				m_colorFade.a = 0.0f;
				m_fade = FADE_NONE;		//何もしていない状態に
			}
		}
		else if (m_fade == FADE_OUT)
		{//フェードアウト状態

			m_colorFade.a += 0.03f;		//ポリゴンを不透明にしていく

			if (m_colorFade.a >= 1.0f)
			{//半透明になったら

				m_colorFade.a = 1.0f;
				m_fade = FADE_IN;		//フェードイン状態に

				//モード設定（次の画面に移行）
				CManager::SetMode(m_modeNext);
			}
		}

		//頂点カラーの設定
		CObject2D::SetColor(CObject::TYPE_FADE, m_colorFade);

	}

	//2Dオブジェクトの更新処理
	CObject2D::Update();
}

//==============================================================
//フェードの描画処理
//==============================================================
void CFade::Draw(void)
{
	if (m_fade != FADE_NONE)
	{//何もしてない状態のとき

		//2Dオブジェクトの更新処理
		CObject2D::Draw();
	}
}

//==============================================================
//フェードの設定処理
//==============================================================
void CFade::SetFade(CScene::MODE modeNext)
{
	if (m_fade == FADE_NONE)
	{//何もしていない状態のとき

		m_fade = FADE_OUT;										//フェードアウト状態
		m_modeNext = modeNext;									//次の画面（モード）を設定
		m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//黒いポリゴン（透明）にしておく
	}
}