#pragma once
//=============================================================================
//
// サウンド処理 [sound.h]
// Author : HOGE FUGA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <xaudio2.h>

class CSound
{
public:
	CSound();
	~CSound();
	//*****************************************************************************
	// サウンドファイル
	//*****************************************************************************
	typedef enum
	{
		SOUND_LABEL_SE_SHOT = 0,		// 発射音テスト
		SOUND_LABEL_BGM_TEST, //BGMテスト
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
private:
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDPARAM;
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;								    // XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;			    // マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ

	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];

};

#endif
