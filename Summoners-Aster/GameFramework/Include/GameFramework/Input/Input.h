#ifndef INPUT_H
#define INPUT_H

#include "DirectInput.h"
#include "XinputManager.h"
#include "../GameFrameworkFactory.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// 入力関係の統括クラス
	/// </summary>
	class Input
	{
	public:
		Input()
		{
			GameFrameworkFactory::Create(&m_pDirectInput);
		}

		~Input()
		{
			delete m_pDirectInput;
		}

		/// <summary>
		/// マウスとキーボードの入力状態の更新を行う,メッセージループの始まりで呼ぶ
		/// </summary>
		inline void PrepareInFrame()
		{
			m_pDirectInput->PrepareInFrame();
		}

		/// <summary>
		/// マウスとキーボードの入力状態の保存を行う,メッセージループの終わりで呼ぶ
		/// </summary>
		inline void FinishInFrame()
		{
			m_pDirectInput->FinishInFrame();
		}

		/// <summary>
		/// 引数に渡したボタンが押された瞬間か
		/// </summary>
		/// <param name="key">ボタンの列挙体</param>
		/// <returns>押された瞬間ならtrue</returns>
		inline bool MouseIsPressed(int key) const
		{
			return m_pDirectInput->MouseIsPressed(key);
		}

		inline bool MouseIsHeld(int key) const
		{
			return m_pDirectInput->MouseIsHeld(key);
		}

		inline bool MouseIsReleased(int key) const
		{
			return m_pDirectInput->MouseIsReleased(key);
		}

		inline bool MouseIsNeutral(int key) const
		{
			return m_pDirectInput->MouseIsNeutral(key);
		}

		/// <summary>
		/// 何かのボタンが押された瞬間か
		/// </summary>
		/// <returns>押されていたらtrue</returns>
		inline bool MouseAnyKeyIsPressed() const
		{
			return m_pDirectInput->MouseAnyKeyIsPressed();
		}

		/// <summary>
		/// カーソルの位置の取得
		/// </summary>
		/// <param name="pPos">[in]取得したカーソルの位置を入れる構造体のポインタ</param>
		inline void CursorPos(POINT* pPos) const
		{
			m_pDirectInput->CursorPos(pPos);
		}

		/// <summary>
		/// 前フレームからどのくらいスクロールされたか
		/// </summary>
		/// <returns>スクロールされた量</returns>
		inline long MouseWheelScrolling() const
		{
			return m_pDirectInput->MouseWheelScrolling();
		}

		/// <summary>
		/// 引数に渡したキーが押された瞬間か
		/// </summary>
		/// <param name="key">キーの列挙体</param>
		/// <returns>押された瞬間ならtrue</returns>
		inline bool KeyboardIsPressed(int key) const
		{
			return m_pDirectInput->KeyboardIsPressed(key);
		}

		inline bool KeyboardIsHeld(int key) const
		{
			return m_pDirectInput->KeyboardIsHeld(key);
		}

		inline bool KeyboardIsReleased(int key) const
		{
			return m_pDirectInput->KeyboardIsReleased(key);
		}

		inline bool KeyboardIsNeutral(int key) const
		{
			return m_pDirectInput->KeyboardIsNeutral(key);
		}

		/// <summary>
		/// 何かのキーが押された瞬間か
		/// </summary>
		/// <returns>押されていたらtrue</returns>
		inline bool KeyboardAnyKeyIsPressed() const
		{
			return m_pDirectInput->KeyboardAnyKeyIsPressed();
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
			m_XinputManager.SetDeadzone(leftThumbDeadzone, rightThumbDeadzone, leftTriggerDeadzone, rightTriggerDeadzone);
		}

		/// <summary>
		/// PADの接続、入力状態の確認
		/// </summary>
		/// <seealso cref="GetControl"/>
		/// <seealso cref="ButtonCheck"/>
		inline void DeviceUpdate()
		{
			m_XinputManager.DeviceUpdate();
		}

		/// <summary>
		/// 接続状態の取得
		/// </summary>
		/// <param name="num">コントローラ番号</param>
		/// <returns>保存されているXInputGetState関数の戻り値</returns>
		inline HRESULT GetInfo(Xinput::PLAYER_NUM num)
		{
			return m_XinputManager.GetInfo(num);
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
			return m_XinputManager.GetButton(index, num);
		}

		/// <summary>
		/// XinputDeviceでゲームパッドのいずれかのボタン押下確認
		/// </summary>
		/// <param name="num">コントローラ番号</param>
		/// <returns>いずれかのボタンが押下されてればtrue</returns>
		/// <seealso cref="Xinput::PLAYER_NUM"/>
		inline bool PressedAnyButton(Xinput::PLAYER_NUM num)
		{
			return m_XinputManager.PressedAnyButton(num);
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
			return m_XinputManager.GetTriggerValue(trigger, num);
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
			return m_XinputManager.TiltedLeftThumb(thumbTilt, num);
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
			return m_XinputManager.TiltedRightThumb(thumbTilt, num);
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
			return m_XinputManager.GetLeftThumbValue(thumbTilt, num);
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
			return m_XinputManager.GetRightThumbValue(thumbTilt, num);
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
			return m_XinputManager.GetLeftThumbState(thumbTilt, num);
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
			return m_XinputManager.GetRightThumbState(thumbTilt, num);
		}

		/// <summary>
		/// XinputDeviceでゲームパッドの右トリガー入力状態取得
		/// </summary>
		/// <param name="num">コントローラ番号</param>
		/// <returns>押下状態</returns>
		/// <seealso cref="Xinput::PADSTATE"/>
		inline Xinput::PADSTATE GetRightTriggerState(Xinput::PLAYER_NUM num)
		{
			return m_XinputManager.GetRightTriggerState(num);
		}

		/// <summary>
		/// XinputDeviceでゲームパッドの左トリガー入力状態取得
		/// </summary>
		/// <param name="num">コントローラ番号</param>
		/// <returns>押下状態</returns>
		/// <seealso cref="Xinput::PADSTATE"/>
		inline Xinput::PADSTATE GetLeftTriggerState(Xinput::PLAYER_NUM num)
		{
			return m_XinputManager.GetLeftTriggerState(num);
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
			m_XinputManager.RunVibration(num, LeftValue, RightValue);
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
			return m_XinputManager.GetButton(index);
		}

		/// <summary>
		/// すべてのゲームパッドのいずれかのボタン押下確認
		/// </summary>
		/// <returns>いずれかのボタンが押下されてればtrue</returns>
		/// <seealso cref="Xinput::PADSTATE"/>
		/// <remarks>入力はPLAYER_01優先</remarks>	
		inline bool PressedAnyButton()
		{
			return m_XinputManager.PressedAnyButton();
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
			return m_XinputManager.GetTriggerValue(trigger);
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
			return m_XinputManager.TiltedLeftThumb(thumbTilt);
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
			return m_XinputManager.TiltedRightThumb(thumbTilt);
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
			return m_XinputManager.GetLeftThumbValue(thumbTilt);
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
			return m_XinputManager.GetRightThumbValue(thumbTilt);
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
			return m_XinputManager.GetLeftThumbState(thumbTilt);
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
			return m_XinputManager.GetRightThumbState(thumbTilt);
		}

		/// <summary>
		/// すべてのゲームパッドの右トリガー入力状態取得
		/// </summary>
		/// <returns>押下状態</returns>
		/// <seealso cref="Xinput::PADSTATE"/>
		/// <remarks>入力はPLAYER_01優先</remarks>	
		inline Xinput::PADSTATE GetRightTriggerState()
		{
			return m_XinputManager.GetRightTriggerState();
		}

		/// <summary>
		/// すべてのゲームパッドの左トリガー入力状態取得
		/// </summary>
		/// <returns>押下状態</returns>
		/// <seealso cref="Xinput::PADSTATE"/>
		/// <remarks>入力はPLAYER_01優先</remarks>	
		inline Xinput::PADSTATE GetLeftTriggerState()
		{
			return m_XinputManager.GetLeftTriggerState();
		}

		/// <summary>
		/// すべてのゲームパッドの左右のバイブレーションモーターを動作させる
		/// </summary>
		/// <param name="leftValue">バイブレーション値 MAX＝65535　MIN＝0</param>
		/// <param name="rightValue">バイブレーション値 MAX＝65535　MIN＝0</param>
		/// <remarks>右は高周波モーター、左は低周波モーター</remarks>	
		inline void RunVibration(unsigned int leftValue, unsigned int rightValue)
		{
			m_XinputManager.RunVibration(leftValue, rightValue);
		}


	private:
		Input(const Input& rhs) = delete;

		Input& operator=(const Input& rhs) = delete;

		DirectInput* m_pDirectInput = nullptr;

		XinputManager m_XinputManager;
	};
}

#endif //!INPUT_H
