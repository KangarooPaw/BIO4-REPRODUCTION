#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

//前方宣言
class CRenderer;
class CInputKeyboard;
class CInputJoystick;
class CCamera;
class CLight;
class CFade;
class CPlayer;
class CModel;
class CDebugProc;
class CMode;

//マネージャークラス
class CManager
{
public:
	//画面遷移の列挙型
	typedef enum
	{
		MODE_NONE = 0,
		MODE_TITLE,		//タイトル
		MODE_GAME,		//ゲーム
		MODE_TUTORIAL,	//チュートリアル
		MODE_RESULT,	//リザルト
		MODE_MAX
	}MODE;

	CManager();//インクリメント
	~CManager();//デクリメント
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindouw);//初期化処理
	void Uninit(void);//終了処理
	void Update(void);//更新処理
	void Draw(void);//描画処理

	void LoadAll(void);//テクスチャの読み込みまとめ
	void UnloadAll(void);//テクスチャの破棄まとめ

	void SetMode(MODE mode);	//モードの設定
	
	static void CreateCamera(void);
	static void CreateLight(void);
	static void CreateFade(MODE mode);

	static CRenderer *GetRenderer(void);	//レンダラー
	static CInputKeyboard *GetInputKeyboard(void);	//キーボード
	static CInputJoystick *GetInputJoystick(void);	//ゲームパッド
	static CCamera *GetCamera(void);		//カメラ
	static CLight *GetLight(void);			//ライト
	static CFade *GetFade(void);			//フェード
	static CDebugProc*GetDebug(void);		//デバッグ
	static MODE GetMode(void);				//モード

private:								  
	static CRenderer *m_pRenderer;			//レンダラー
	static CInputKeyboard *m_pInputKeyboard;//キーボード
	static CInputJoystick *m_pInputJoystick;//ゲームパッド
	static CCamera *m_pCamera;				//カメラ
	static CLight *m_pLight;				//ライト
	static CFade *m_pFade;					//フェード
	static CDebugProc*m_pDebugProc;			//デバッグ
	static CMode *m_pMode;					//モードのポインタ
	static MODE m_mode;						//現在のモード
};	

#endif // !_MANAGER_H_
