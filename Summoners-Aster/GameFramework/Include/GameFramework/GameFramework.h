#ifndef GAME_FRAMEWORK_H
#define GAME_FRAMEWORK_H

#include "../Singleton.h"

#include "Graphic/Graphic.h"
#include "Input/Input.h"
#include "TimerManager.h"
#include "../Collision.h"
#include "Sound/Sound.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	
	class GameFramework :public Singleton<GameFramework>
	{
	public:
		friend class Singleton<GameFramework>;

		~GameFramework() {};

		/// <summary>
		/// フレームでの開始の準備を行う
		/// </summary>
		inline void PrepareInFrame()
		{
			m_graphic.PrepareInFrame();
			m_input.PrepareInFrame();
		}

		/// <summary>
		/// フレームでの終了処理を行う
		/// </summary>
		inline void FinishInFrame()
		{
			m_graphic.FinishInFrame();
			m_input.FinishInFrame();
		}

		/// <summary>
		/// マウスカーソルが矩形の上にあるか
		/// </summary>
		/// <param name="vertices">矩形クラス</param>
		/// <returns>上にあればtrue</returns>
		inline bool IsCursorOnRect(Vertices& vertices)
		{
			POINT cursorPoint;
			CursorPos(&cursorPoint);
			D3DXVECTOR3 cursorPos(static_cast<float>(cursorPoint.x), static_cast<float>(cursorPoint.y), 0.0f);
				
			return collision::IsInner(vertices, cursorPos);
		}

		/// <summary>
		/// マウスカーソルが円の上にあるか
		/// </summary>
		/// <param name="vertices">矩形クラス</param>
		/// <returns>上にあればtrue</returns>
		inline bool IsCursorOnCircle(Vertices& vertices)
		{
			POINT cursorPoint;
			CursorPos(&cursorPoint);
			D3DXVECTOR3 cursorPos(static_cast<float>(cursorPoint.x), static_cast<float>(cursorPoint.y), 0.0f);

			return collision::Collides(vertices, cursorPos);
		}

		/// <summary>
		/// デットゾーンを設定する
		/// </summary>
		/// <param name="leftThumbDeadzone">0-32767の範囲を取る指定の左スティックデッドゾーン値</param>
		/// <param name="rightThumbDeadzone">0-32767の範囲を取る指定の右スティックデッドゾーン値</param>
		/// <param name="leftTriggerDeadzone">0-255の範囲を取る指定の左トリガーデッドゾーン値</param>
		/// <param name="rightTriggerDeadzone">0-255の範囲を取る指定の右トリガーデッドゾーン値</param>
		inline void SetDeadzone(unsigned int leftThumbDeadzone, unsigned int rightThumbDeadzone, unsigned int leftTriggerDeadzone, unsigned int rightTriggerDeadzone)
		{
			m_input.SetDeadzone(leftThumbDeadzone, rightThumbDeadzone, leftTriggerDeadzone, rightTriggerDeadzone);
		}

		/// <summary>
		/// PADの接続、入力状態の確認
		/// </summary>
		/// <seealso cref="GetControl"/>
		/// <seealso cref="ButtonCheck"/>
		inline void DeviceUpdate()
		{
			m_input.DeviceUpdate();
		}

		/// <summary>
		/// 接続状態の取得
		/// </summary>
		/// <param name="num">コントローラ番号</param>
		/// <returns>保存されているXInputGetState関数の戻り値</returns>
		inline HRESULT GetInfo(Xinput::PLAYER_NUM num)
		{
			return m_input.GetInfo(num);
		}

		/// <summary>
		/// XinputDeviceでゲームパッドの入力取得
		/// </summary>
		/// <param name="index">取得したいボタンの配列番号</param>
		/// <param name="num">コントローラ番号</param>
		/// <returns>PADSTATEの値</returns>
		/// <seealso cref="Xinput::PADSTATE"/>
		inline Xinput::PADSTATE GetButton(Xinput::ButtonIndex index, Xinput::PLAYER_NUM num)const
		{
			return m_input.GetButton(index, num);
		}

		/// <summary>
		/// XinputDeviceでゲームパッドのいずれかのボタン押下確認
		/// </summary>
		/// <param name="num">コントローラ番号</param>
		/// <returns>いずれかのボタンが押下されてればtrue</returns>
		/// <seealso cref="Xinput::PLAYER_NUM"/>
		inline bool PressedAnyButton(Xinput::PLAYER_NUM num)
		{
			return m_input.PressedAnyButton(num);
		}

		/// <summary>
		/// XinputDeviceでゲームパッドのトリガーの入力取得
		/// </summary>
		/// <param name="trigger">トリガーの左右認識番号</param>
		/// <param name="num">コントローラ番号</param>
		/// <returns>0～255の値、押してなければ0</returns>
		/// <seealso cref="Xinput::trigger"/>
		inline int GetTriggerValue(Xinput::Trigger trigger, Xinput::PLAYER_NUM num)
		{
			return m_input.GetTriggerValue(trigger,num);
		}

		/// <summary>
		/// XinputDeviceでゲームパッドの左アナログスティック入力取得
		/// </summary>
		/// <param name="thumbTilt">スティックの方向け先番号</param>
		/// <param name="num">コントローラ番号</param>
		/// <returns>傾いていればTrue、そうでなければFalse</returns>
		/// <seealso cref="Xinput::ThumbTilt"/>
		inline bool TiltedLeftThumb(Xinput::ThumbTilt thumbTilt, Xinput::PLAYER_NUM num)
		{
			return m_input.TiltedLeftThumb(thumbTilt,num);
		}

		/// <summary>
		/// XinputDeviceでゲームパッドの右アナログスティック入力取得
		/// </summary>
		/// <param name="thumbTilt">スティックの方向け先番号</param>
		/// <param name="num">コントローラ番号</param>
		/// <returns>傾いていればTrue、そうでなければFalse</returns>
		/// <seealso cref="Xinput::ThumbTilt"/>
		inline bool TiltedRightThumb(Xinput::ThumbTilt thumbTilt, Xinput::PLAYER_NUM num)
		{
			return m_input.TiltedRightThumb(thumbTilt, num);
		}

		/// <summary>
		/// XinputDeviceでゲームパッドの左アナログスティック入力取得
		/// </summary>
		/// <param name="thumbTilt">スティックの方向け先番号</param>
		/// <param name="num">コントローラ番号</param>
		/// <returns>傾き具合の数値　MAX＝32767　MIN＝-32768</returns>
		/// <seealso cref="Xinput::ThumbTilt"/>
		inline int GetLeftThumbValue(Xinput::ThumbTiltAxis thumbTilt, Xinput::PLAYER_NUM num)
		{
			return m_input.GetLeftThumbValue(thumbTilt, num);
		}

		/// <summary>
		/// XinputDeviceでゲームパッドの右アナログスティック入力取得
		/// </summary>
		/// <param name="thumbTilt">スティックの方向け先番号</param>
		/// <param name="num">コントローラ番号</param>
		/// <returns>傾き具合の数値　MAX＝32767　MIN＝-32768</returns>
		/// <seealso cref="Xinput::ThumbTilt"/>
		inline int GetRightThumbValue(Xinput::ThumbTiltAxis thumbTilt, Xinput::PLAYER_NUM num)
		{
			return m_input.GetRightThumbValue(thumbTilt, num);
		}

		/// <summary>
		/// XinputDeviceでゲームパッドの左アナログスティック入力状態取得
		/// </summary>
		/// <param name="thumbTilt">スティックの方向け先番号</param>
		/// <param name="num">コントローラ番号</param>
		/// <returns>方向け状態</returns>
		/// <seealso cref="Xinput::ThumbTilt"/>
		/// <seealso cref="Xinput::PADSTATE"/>
		inline Xinput::PADSTATE GetLeftThumbState(Xinput::ThumbTilt thumbTilt, Xinput::PLAYER_NUM num)
		{
			return m_input.GetLeftThumbState(thumbTilt, num);
		}

		/// <summary>
		/// XinputDeviceでゲームパッドの左アナログスティック入力状態取得
		/// </summary>
		/// <param name="thumbTilt">スティックの方向け先番号</param>
		/// <param name="num">コントローラ番号</param>
		/// <returns>方向け状態</returns>
		/// <seealso cref="Xinput::ThumbTilt"/>
		/// <seealso cref="Xinput::PADSTATE"/>
		inline Xinput::PADSTATE GetRightThumbState(Xinput::ThumbTilt thumbTilt, Xinput::PLAYER_NUM num)
		{
			return m_input.GetRightThumbState(thumbTilt,num);
		}

		/// <summary>
		/// XinputDeviceでゲームパッドの右トリガー入力状態取得
		/// </summary>
		/// <param name="num">コントローラ番号</param>
		/// <returns>押下状態</returns>
		/// <seealso cref="Xinput::PADSTATE"/>
		inline Xinput::PADSTATE GetRightTriggerState(Xinput::PLAYER_NUM num)
		{
			return m_input.GetRightTriggerState(num);
		}

		/// <summary>
		/// XinputDeviceでゲームパッドの左トリガー入力状態取得
		/// </summary>
		/// <param name="num">コントローラ番号</param>
		/// <returns>押下状態</returns>
		/// <seealso cref="Xinput::PADSTATE"/>
		inline Xinput::PADSTATE GetLeftTriggerState(Xinput::PLAYER_NUM num)
		{
			return m_input.GetLeftTriggerState(num);
		}

		/// <summary>
		/// 左右のバイブレーションモーターを動作させる
		/// </summary>
		/// <param name="num">コントローラ番号</param>
		/// <param name="LeftValue">バイブレーション値 MAX＝65535　MIN＝0</param>
		/// <param name="RightValue">バイブレーション値 MAX＝65535　MIN＝0</param>
		/// <remarks>右は高周波モーター、左は低周波モーター</remarks>	
		inline void RunVibration(Xinput::PLAYER_NUM num, unsigned int LeftValue = 0, unsigned int RightValue = 0)
		{
			m_input.RunVibration(num, LeftValue, RightValue );
		}

		/// <summary>
		/// すべてのゲームパッドの入力取得
		/// </summary>
		/// <param name="index">取得したいボタンの配列番号</param>
		/// <returns>PADSTATEの値</returns>
		/// <seealso cref="Xinput::PADSTATE"/>
		/// <remarks>入力はPLAYER_01優先</remarks>	
		inline Xinput::PADSTATE GetButton(Xinput::ButtonIndex index) const
		{
			return m_input.GetButton(index);
		}

		/// <summary>
		/// すべてのゲームパッドのいずれかのボタン押下確認
		/// </summary>
		/// <returns>いずれかのボタンが押下されてればtrue</returns>
		/// <seealso cref="Xinput::PADSTATE"/>
		/// <remarks>入力はPLAYER_01優先</remarks>	
		inline bool PressedAnyButton()
		{
			return m_input.PressedAnyButton();
		}

		/// <summary>
		/// すべてのゲームパッドのトリガーの入力取得
		/// </summary>
		/// <param name="trigger">トリガーの左右認識番号</param>
		/// <returns>0～255の値、押してなければ0</returns>
		/// <seealso cref="Xinput::trigger"/>
		/// <remarks>入力はPLAYER_01優先</remarks>	
		inline int GetTriggerValue(Xinput::Trigger trigger)
		{
			return m_input.GetTriggerValue(trigger);
		}

		/// <summary>
		/// すべてのゲームパッドの左アナログスティック入力取得
		/// </summary>
		/// <param name="thumbTilt">スティックの方向け先番号</param>
		/// <returns>傾いていればTrue、そうでなければFalse</returns>
		/// <seealso cref="Xinput::ThumbTilt"/>
		/// <remarks>入力はPLAYER_01優先</remarks>	
		inline bool TiltedLeftThumb(Xinput::ThumbTilt thumbTilt)
		{
			return m_input.TiltedLeftThumb(thumbTilt);
		}

		/// <summary>
		/// すべてのゲームパッドの右アナログスティック入力取得
		/// </summary>
		/// <param name="thumbTilt">スティックの方向け先番号</param>
		/// <returns>傾いていればTrue、そうでなければFalse</returns>
		/// <seealso cref="Xinput::ThumbTilt"/>
		/// <remarks>入力はPLAYER_01優先</remarks>	
		inline bool TiltedRightThumb(Xinput::ThumbTilt thumbTilt)
		{
			return m_input.TiltedRightThumb(thumbTilt);
		}

		/// <summary>
		/// すべてのゲームパッドの左アナログスティック入力取得
		/// </summary>
		/// <param name="thumbTilt">スティックの方向け先番号</param>
		/// <returns>傾き具合の数値　MAX＝32767　MIN＝-32768</returns>
		/// <seealso cref="Xinput::ThumbTilt"/>
		/// <remarks>入力はPLAYER_01優先</remarks>	
		inline int GetLeftThumbValue(Xinput::ThumbTiltAxis thumbTilt)
		{
			return m_input.GetLeftThumbValue(thumbTilt);
		}

		/// <summary>
		/// すべてのゲームパッドの右アナログスティック入力取得
		/// </summary>
		/// <param name="thumbTilt">スティックの方向け先番号</param>
		/// <returns>傾き具合の数値　MAX＝32767　MIN＝-32768</returns>
		/// <seealso cref="Xinput::ThumbTilt"/>
		/// <remarks>入力はPLAYER_01優先</remarks>	
		inline int GetRightThumbValue(Xinput::ThumbTiltAxis thumbTilt)
		{
			return m_input.GetRightThumbValue(thumbTilt);
		}

		/// <summary>
		/// すべてのゲームパッドの右アナログスティック入力取得
		/// </summary>
		/// <param name="thumbTilt">スティックの方向け先番号</param>
		/// <returns>傾き具合の数値　MAX＝32767　MIN＝-32768</returns>
		/// <seealso cref="Xinput::ThumbTilt"/>
		/// <remarks>入力はPLAYER_01優先</remarks>	
		inline Xinput::PADSTATE GetLeftThumbState(Xinput::ThumbTilt thumbTilt)
		{
			return m_input.GetLeftThumbState(thumbTilt);
		}

		/// <summary>
		/// すべてのゲームパッドの右アナログスティック入力取得
		/// </summary>
		/// <param name="thumbTilt">スティックの方向け先番号</param>
		/// <returns>傾き具合の数値　MAX＝32767　MIN＝-32768</returns>
		/// <seealso cref="Xinput::ThumbTilt"/>
		/// <remarks>入力はPLAYER_01優先</remarks>	
		inline Xinput::PADSTATE GetRightThumbState(Xinput::ThumbTilt thumbTilt)
		{
			return m_input.GetRightThumbState(thumbTilt);
		}

		/// <summary>
		/// すべてのゲームパッドの右トリガー入力状態取得
		/// </summary>
		/// <returns>押下状態</returns>
		/// <seealso cref="Xinput::PADSTATE"/>
		/// <remarks>入力はPLAYER_01優先</remarks>	
		inline Xinput::PADSTATE GetRightTriggerState()
		{
			return m_input.GetRightTriggerState();
		}

		/// <summary>
		/// すべてのゲームパッドの左トリガー入力状態取得
		/// </summary>
		/// <returns>押下状態</returns>
		/// <seealso cref="Xinput::PADSTATE"/>
		/// <remarks>入力はPLAYER_01優先</remarks>	
		inline Xinput::PADSTATE GetLeftTriggerState()
		{
			return m_input.GetLeftTriggerState();
		}

		/// <summary>
		/// すべてのゲームパッドの左右のバイブレーションモーターを動作させる
		/// </summary>
		/// <param name="leftValue">バイブレーション値 MAX＝65535　MIN＝0</param>
		/// <param name="rightValue">バイブレーション値 MAX＝65535　MIN＝0</param>
		/// <remarks>右は高周波モーター、左は低周波モーター</remarks>	
		inline void RunVibration(unsigned int leftValue, unsigned int rightValue)
		{
			m_input.RunVibration(leftValue, rightValue);
		}

		/// <summary>
		/// テクスチャの作成
		/// </summary>
		/// <param name="pTextureKey">テクスチャにつけるキー</param>
		/// <param name="pTexturePath">テクスチャのパス</param>
		inline void CreateTexture(const TCHAR* pTextureKey, const TCHAR* pTexturePath)
		{
			m_graphic.CreateTexture(pTextureKey, pTexturePath);
		}

		/// <summary>
		/// テクスチャを再読み込み
		/// </summary>
		/// <param name="pTextureKey">テクスチャにつけるキー</param>
		/// <param name="pTexturePath">テクスチャのパス</param>
		inline void ResetTexture(const TCHAR* pTextureKey, const TCHAR* pTexturePath)
		{
			m_graphic.ResetTexture(pTextureKey, pTexturePath);
		}

		/// <summary>
		/// 指定したテクスチャの開放
		/// </summary>
		/// <param name="pTextureKey">テクスチャのキー</param>
		inline void ReleaseTexture(const TCHAR* pTextureKey)
		{
			m_graphic.ReleaseTexture(pTextureKey);
		}

		/// <summary>
		/// テクスチャの全開放
		/// </summary>
		inline void ReleaseAllTexture()
		{
			m_graphic.ReleaseAllTexture();
		}

		/// <summary>
		/// テクスチャの取得
		/// </summary>
		/// <param name="pTextureKey">テクスチャのキー</param>
		/// <returns>テクスチャのポインタ</returns>
		inline LPTEXTURE GetTexture(const TCHAR* pTextureKey)
		{
			return m_graphic.GetTexture(pTextureKey);
		}

		/// <summary>
		/// テクスチャのサイズの取得
		/// </summary>
		/// <param name="pTextureKey">テクスチャのキー</param>
		/// <param name="pTextureSize">取得したサイズを入れるサイズ構造体のポインタ</param>
		inline void GetTextureSize(const TCHAR* pTextureKey, RectSize* pTextureSize)
		{
			m_graphic.GetTextureSize(pTextureKey, pTextureSize);
		}

		/// <summary>
		/// テクスチャが存在しているか判断する
		/// </summary>
		/// <param name="pTextureKey">テクスチャのキー</param>
		/// <returns>存在していたらtrue</returns>
		inline bool TextureExists(const TCHAR* pTextureKey)
		{
			return m_graphic.TextureExists(pTextureKey);
		}

		/// <summary>
		/// 色の合成を通常合成に変更する デフォルトでは通常合成になっている
		/// </summary>
		inline void ToDefaultBlendMode() const
		{
			m_graphic.ToDefaultBlendMode();
		}

		/// <summary>
		/// 色の合成を加算合成に変更する
		/// </summary>
		inline void ToAddtionBlendMode() const
		{
			m_graphic.ToAddtionBlendMode();
		}

		/// <summary>
		/// デフォルトの色合成を使用する ウィンドウモードを切り替えた時には再設定する必要がある
		/// </summary>
		inline void SetDefaultColorBlending() const
		{
			m_graphic.SetDefaultColorBlending();
		}

		/// <summary>
		/// フォントの作成
		/// </summary>
		/// <param name="pFontKey">フォントにつけるキー</param>
		/// <param name="pTexturePath">フォントのパス</param>
		inline void CreateFont(const TCHAR* pFontKey, const RectSize& scale, const TCHAR* pFontName, UINT thickness = 0)
		{
			m_graphic.CreateFont(pFontKey, scale, pFontName, thickness);
		}

		/// <summary>
		/// フォントを再読み込み
		/// </summary>
		/// <param name="pFontKey">フォントにつけるキー</param>
		/// <param name="pTexturePath">フォントのパス</param>
		inline void ResetFont(const TCHAR* pFontKey, const RectSize& scale, const TCHAR* pFontName, UINT thickness = 0)
		{
			m_graphic.ResetFont(pFontKey, scale, pFontName, thickness);
		}

		/// <summary>
		/// 指定したフォントの開放
		/// </summary>
		/// <param name="pFontKey">フォントのキー</param>
		inline void ReleaseFont(const TCHAR* pFontKey)
		{
			m_graphic.ReleaseFont(pFontKey);
		}

		/// <summary>
		/// フォントの全開放
		/// </summary>
		inline void ReleaseAllFont()
		{
			m_graphic.ReleaseAllFont();
		}

		/// <summary>
		/// フォントの取得
		/// </summary>
		/// <param name="pFontKey">フォントのキー</param>
		/// <returns>フォントのポインタ</returns>
		inline LPFONT GetFont(const TCHAR* pFontKey)
		{
			return m_graphic.GetFont(pFontKey);
		}

		/// <summary>
		/// フォントのサイズの取得
		/// </summary>
		/// <param name="pFontKey">フォントのキー</param>
		/// <param name="pFontSize">取得したサイズを入れるサイズ構造体のポインタ</param>
		inline void GetFontSize(const TCHAR* pFontKey, RectSize* pFontSize)
		{
			m_graphic.GetFontSize(pFontKey, pFontSize);
		}

		/// <summary>
		/// フォントが存在しているか判断する
		/// </summary>
		/// <param name="pFontKey">フォントのキー</param>
		/// <returns>存在していたらtrue</returns>
		inline bool FontExists(const TCHAR* pFontKey)
		{
			return m_graphic.FontExists(pFontKey);
		}

		/// <summary>
		/// エフェクトの登録
		/// </summary>
		/// <param name="pGraphicEffect">登録するエフェクトのポインタ</param>
		void RegisterGraphicEffect(GraphicEffect* pGraphicEffect)
		{
			m_graphic.RegisterEffect(pGraphicEffect);
		}

		/// <summary>
		/// エフェクトの全開放
		/// </summary>
		void ReleaseAllGraphicEffect()
		{
			m_graphic.ReleaseAllEffect();
		}

		/// <summary>
		/// 全てのエフェクトを更新する
		/// </summary>
		void UpdateGraphicEffects()
		{
			m_graphic.UpdateEffects();
		}

		/// <summary>
		/// 全てのエフェクトを描画する
		/// </summary>
		void RenderGraphicEffects()
		{
			m_graphic.RenderEffects();
		}

		/// <summary>
		/// 引数に渡したボタンが押された瞬間か
		/// </summary>
		/// <param name="key">ボタンの列挙体</param>
		/// <returns>押された瞬間ならtrue</returns>
		inline bool MouseIsPressed(int key) const
		{
			return m_input.MouseIsPressed(key);
		}

		inline bool MouseIsHeld(int key) const
		{
			return m_input.MouseIsHeld(key);
		}

		inline bool MouseIsReleased(int key) const
		{
			return m_input.MouseIsReleased(key);
		}

		inline bool MouseIsNeutral(int key) const
		{
			return m_input.MouseIsNeutral(key);
		}

		/// <summary>
		/// 何かのボタンが押された瞬間か
		/// </summary>
		/// <returns>押されていたらtrue</returns>
		inline bool MouseAnyKeyIsPressed() const
		{
			return m_input.MouseAnyKeyIsPressed();
		}

		/// <summary>
		/// カーソルの位置の取得
		/// </summary>
		/// <param name="pPos">[in]取得したカーソルの位置を入れる構造体のポインタ</param>
		inline void CursorPos(POINT* pPos) const
		{
			m_input.CursorPos(pPos);
		}

		/// <summary>
		/// 前フレームからどのくらいスクロールされたか
		/// </summary>
		/// <returns>スクロールされた量</returns>
		inline long MouseWheelScrolling() const
		{
			return m_input.MouseWheelScrolling();
		}

		/// <summary>
		/// 引数に渡したキーが押された瞬間か
		/// </summary>
		/// <param name="key">キーの列挙体</param>
		/// <returns>押された瞬間ならtrue</returns>
		inline bool KeyboardIsPressed(int key) const
		{
			return m_input.KeyboardIsPressed(key);
		}

		inline bool KeyboardIsHeld(int key) const
		{
			return m_input.KeyboardIsHeld(key);
		}

		inline bool KeyboardIsReleased(int key) const
		{
			return m_input.KeyboardIsReleased(key);
		}

		inline bool KeyboardIsNeutral(int key) const
		{
			return m_input.KeyboardIsNeutral(key);
		}

		/// <summary>
		/// 何かのキーが押された瞬間か
		/// </summary>
		/// <returns>押されていたらtrue</returns>
		inline bool KeyboardAnyKeyIsPressed() const
		{
			return m_input.KeyboardAnyKeyIsPressed();
		}

		/// <summary>
		/// FPSの設定を行う
		/// </summary>
		/// <param name="fPS">設定したい一秒間でのフレーム数</param>
		/// <remarks>FPSを設定していなかった場合60fps</remarks>
		inline void SetFPS(int fPS)
		{
			m_timerManager.SetFPS(fPS);
		}

		/// <summary>
		/// 次のフレームに進んでいいかを判断する
		/// </summary>
		/// <returns>進んでもよければtrue</returns>
		/// <remarks>ここで一フレームにかかった時間を取得する</remarks>
		inline bool CanStartNextFrame()
		{
			return m_timerManager.CanStartNextFrame();
		}

		/// <summary>
		/// 一フレームにかかった時間(秒)を取得する
		/// </summary>
		/// <returns>経過時間(秒)</returns>
		inline float DeltaTime_sec() const
		{
			return m_timerManager.DeltaTime_sec();
		}

		/// <summary>
		/// タイマーの作成を行う
		/// </summary>
		/// <param name="pKey">生成するタイマーにつける識別キー</param>
		inline void CreateTimer(const TCHAR* pKey)
		{
			m_timerManager.Create(pKey);
		}

		/// <summary>
		/// 引数に渡されたキーのタイマーの開放
		/// </summary>
		/// <param name="pKey">開放したいタイマーのキー</param>
		inline void ReleaseTimer(const TCHAR* pKey)
		{
			m_timerManager.Release(pKey);
		}

		/// <summary>
		/// 引数に渡されたキーのタイマーが存在しているか
		/// </summary>
		/// <param name="pKey">調べたいタイマーの識別キー</param>
		/// <returns>存在していればtrue</returns>
		inline bool TimerExists(const TCHAR* pKey) const
		{
			return m_timerManager.Exists(pKey);
		}

		/// <summary>
		/// 時間の計測開始
		/// </summary>
		/// <param name="pKey">計測開始するタイマーのキー</param>
		inline void StartTimer(const TCHAR* pKey)
		{
			m_timerManager.Start(pKey);
		}

		/// <summary>
		/// 時間計測の一時停止
		/// </summary>
		/// <param name="pKey">一時停止するタイマーのキー</param>
		inline void PauseTimer(const TCHAR* pKey)
		{
			m_timerManager.Pause(pKey);
		}

		/// <summary>
		/// 時間計測のリスタート
		/// </summary>
		/// <param name="pKey">計測を再スタートさせるタイマーのキー</param>
		inline void RestartTimer(const TCHAR* pKey)
		{
			m_timerManager.Restart(pKey);
		}

		/// <summary>
		/// 時間計測の初期化
		/// </summary>
		/// <param name="pKey">初期化したいタイマーのキー</param>
		/// <remarks>計測開始時間を現在の開始時間にする</remarks>
		void ResetTimer(const TCHAR* pKey)
		{
			m_timerManager.Reset(pKey);
		}

		/// <summary>
		/// 計測時間を返す(秒)
		/// </summary>
		/// <param name="pKey">タイマーのキー</param>
		inline LONGLONG GetTime_sec(const TCHAR* pKey)
		{
			return m_timerManager.GetTime_sec(pKey);
		}

		/// <summary>
		/// 計測時間を返す(ミリ秒)
		/// </summary>
		/// <param name="pKey">タイマーのキー</param>
		inline LONGLONG GetTime_msec(const TCHAR* pKey)
		{
			return m_timerManager.GetTime_msec(pKey);
		}

		/// <summary>
		/// 計測時間を返す(マイクロ秒)
		/// </summary>
		/// <param name="pKey">タイマーのキー</param>
		inline LONGLONG GetTime_µsec(const TCHAR* pKey)
		{
			return m_timerManager.GetTime_µsec(pKey);
		}

		/// <summary>
		/// 現在計測が止まっているかを返す
		/// </summary>
		/// <param name="pKey">止まっているかを調べるタイマーのキー</param>
		/// <returns>止まっていればtrue</returns>
		inline bool IsTimerRunning(const TCHAR* pKey)
		{
			return m_timerManager.IsRunning(pKey);
		}

		/// <summary>
		/// 音声ファイルを追加する。
		/// </summary>
		/// <param name="pFilePath">ファイルパス</param>
		/// <param name="pKey">音声ファイルを識別するキー</param>
		/// <param name="type">音声に設定する音声種別</param>
		inline void AddFile(const TCHAR* pFilePath, const TCHAR* pKey, Sound::SoundType type)
		{
			m_Sound.AddFile(pFilePath, pKey, type);
		}

		/// <summary>
		/// 音声ファイルを10個分追加する。
		/// </summary>
		/// <param name="pFilePath">ファイルパス</param>
		/// <param name="pKey">音声ファイルを識別するキー</param>
		/// <param name="type">音声に設定する音声種別</param>
		inline void AddSimultaneousFile(const TCHAR* pFilePath, const TCHAR* pKey, Sound::SoundType type)
		{
			m_Sound.AddSimultaneousFile(pFilePath, pKey, type);
		}

		/// <summary>
		/// ファイルの先頭から単発再生を行う。
		/// </summary>
		/// <param name="pKey">音声ファイルを識別するキー</param>
		inline void OneShotSimultaneous(const TCHAR* pKey)
		{
			m_Sound.OneShotSimultaneous(pKey);
		}

		/// <summary>
		/// ファイルの先頭からループ再生を行う。
		/// </summary>
		/// <param name="pKey">音声ファイルを識別するキー</param>
		inline void LoopStart(const TCHAR* pKey)
		{
			m_Sound.LoopStart(pKey);
		}

		/// <summary>
		/// ファイルの先頭から再生を行う。
		/// </summary>
		/// <param name="pKey">音声ファイルを識別するキー</param>
		inline void OneShotStart(const TCHAR* pKey)
		{
			m_Sound.OneShotStart(pKey);
		}

		/// <summary>
		/// 再生を一時停止する。
		/// </summary>
		/// <param name="pKey">音声ファイルを識別するキー</param>
		/// <returns>成否</returns>
		/// <remarks>続きから再生再開するときには<see cref="Resume(const T*)"/>を実行して下さい。</remarks>
		inline void Pause(const TCHAR* pKey)
		{
			m_Sound.Pause(pKey);
		}

		/// <summary>
		/// 一時停止中の音声を続きから再生する。
		/// </summary>
		/// <param name="pKey">音声ファイルを識別するキー</param>
		/// <returns>成否</returns>
		/// <remarks><see cref="Pause(const T*)"/>で一時停止した音声の続きからの再生に使用します。</remarks>
		inline void Resume(const TCHAR* pKey)
		{
			m_Sound.Resume(pKey);
		}

		/// <summary>
		/// 再生を停止する。
		/// </summary>
		/// <param name="pKey">音声ファイルを識別するキー</param>
		/// <returns>成否</returns>
		/// <remarks>後で続きから再生する必要がある場合は、<see cref="Pause(const TCHAR*)"/>を使用して下さい。</remarks>
		inline void Stop(const TCHAR* pKey)
		{
			m_Sound.Stop(pKey);
		}

		/// <summary>
		/// 再生を停止する。
		/// </summary>
		/// <param name="type">音声ファイルを識別する音声種別</param>
		/// <returns>成否</returns>
		/// <remarks>後で続きから再生する必要がある場合は、<see cref="Pause(const TCHAR*)"/>を使用して下さい。</remarks>
		inline void Stop(Sound::SoundType type = Sound::ALL_TYPE)
		{
			m_Sound.Stop(type);
		}

		/// <summary>
		/// 再生状況を示すステータスを取得する。
		/// </summary>
		/// <param name="pKey">音声ファイルを識別するキー</param>
		/// <returns>再生ステータス</returns>
		inline SoundLib::PlayingStatus GetStatus(const TCHAR* pKey) const
		{
			return m_Sound.GetStatus(pKey);
		}

		/// <summary>
		/// ボリュームを取得する。
		/// </summary>
		/// <param name="pKey">音声ファイルを識別するキー</param>
		/// <returns>ボリューム(0:無音　100:音源ボリューム)</returns>
		inline uint8_t GetVolume(const TCHAR* pKey)
		{
			return m_Sound.GetVolume(pKey);
		}

		/// <summary>
		/// 再生速度とピッチの変化率を取得する。
		/// </summary>
		/// <param name="pKey">音声ファイルを識別するキー</param>
		/// <returns>音源からの変化率</returns>
		/// <remarks>
		/// 1.0の場合、音源から変化なし。
		/// 2.0の場合、再生速度2倍で1オクターブ高音。
		/// 0.5の場合、再生速度1/2で1オクターブ低音。
		/// </remarks>
		inline float GetFrequencyRatio(const TCHAR* pKey)
		{
			return m_Sound.GetFrequencyRatio(pKey);
		}

		/// <summary>
		/// 再生速度とピッチの変化率を設定する。
		/// </summary>
		/// <param name="pKey">音声ファイルを識別するキー</param>
		/// <param name="ratio">音源からの変化率</param>
		/// <remarks>
		/// <para>
		/// 1.0の場合、音源から変化なし。
		/// 2.0の場合、再生速度2倍で1オクターブ高音。
		/// 0.5の場合、再生速度1/2で1オクターブ低音。
		/// </para>
		/// <para>設定可能最大値は4。</para>
		/// </remarks>
		inline void SetFrequencyRatio(const TCHAR* pKey, float ratio)
		{
			m_Sound.SetFrequencyRatio(pKey, ratio);
		}

		/// <summary>
		/// 再生速度とピッチの変化率を設定する。
		/// </summary>
		/// <param name="ratio">音源からの変化率</param>
		/// <param name="type">音声ファイルを識別する音声種別</param>
		/// <returns>成否</returns>
		/// <remarks>
		/// <para>
		/// 1.0の場合、音源から変化なし。
		/// 2.0の場合、再生速度2倍で1オクターブ高音。
		/// 0.5の場合、再生速度1/2で1オクターブ低音。
		/// </para>
		/// <para>設定可能最大値は4。</para>
		/// </remarks>
		inline void SetFrequencyRatio(float ratio, Sound::SoundType type = Sound::ALL_TYPE)
		{
			m_Sound.SetFrequencyRatio(ratio, type);
		}

		/// <summary>
		/// ボリュームを設定する。
		/// </summary>
		/// <param name="vol">ボリューム(0:無音　100:音源ボリューム)</param>
		/// <param name="pKey">音声ファイルを識別するキー</param>
		inline void SetVolume(int vol, const TCHAR* pKey)
		{
			m_Sound.SetVolume(vol, pKey);
		}

		/// <summary>
		/// ボリュームを設定する。
		/// </summary>
		/// <param name="vol">ボリューム(0:無音　100:音源ボリューム)</param>
		/// <param name="type">音声ファイルを識別する音声種別</param>
		inline void SetVolume(int vol, Sound::SoundType type = Sound::ALL_TYPE)
		{
			m_Sound.SetVolume(vol, type);
		}

	private:
		GameFramework() :m_timerManager(TimerManager::CreateAndGetRef())
		{};

		GameFramework(const GameFramework& rhs) = delete;

		GameFramework& operator=(const GameFramework& rhs) = delete;

		Graphic m_graphic;
		Input m_input;
		TimerManager& m_timerManager;
		Sound m_Sound;
	};
}

#endif //!GAME_FRAMEWORK_H
