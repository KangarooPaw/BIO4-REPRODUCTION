#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

//前方宣言
class CRenderer;
class CInputKeyboard;
class CInputJoystick;
class CCamera;
class CLight;
class CPlayer;
class CModel;
class CDebugProc;

//マネージャークラス
class CManager
{
public:
	CManager();//インクリメント
	~CManager();//デクリメント
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindouw);//初期化処理
	void Uninit(void);//終了処理
	void Update(void);//更新処理
	void Draw(void);//描画処理

	void LoadAll(void);//テクスチャの読み込みまとめ
	void UnloadAll(void);//テクスチャの破棄まとめ

	
	static CRenderer *GetRenderer(void);	//レンダラー
	static CInputKeyboard *GetInputKeyboard(void);	//キーボード
	static CInputJoystick *GetInputJoystick(void);	//ゲームパッド
	static CCamera *GetCamera(void);		//カメラ
	static CLight *GetLight(void);			//ライト
	static CPlayer *GetPlayer(void);		//プレイヤー
	static CModel *GetModel(void);			//モデル
	static CDebugProc*GetDebug(void);		//デバッグ
private:								  
	static CRenderer *m_pRenderer;			//レンダラー
	static CInputKeyboard *m_pInputKeyboard;//キーボード
	static CInputJoystick *m_pInputJoystick;//ゲームパッド
	static CCamera *m_pCamera;				//カメラ
	static CLight *m_pLight;				//ライト
	static CPlayer *m_pPlayer;				//プレイヤー
	static CModel *m_pModel;				//モデル
	static CDebugProc*m_pDebugProc;			//デバッグ
};	

#endif // !_MANAGER_H_
