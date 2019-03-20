#include <GameFramework.h>

#ifndef OBJECT_H
#define OBJECT_H

namespace summonersaster
{
	/// <summary>
	/// オブジェクトの基底クラス
	/// </summary>
	class Object
	{
	public:
		virtual ~Object();

		/// <summary>
		/// 初期化を行う
		/// </summary>
		virtual void Initialize() = 0;

		/// <summary>
		/// 外部からのファイル読み込みを行う
		/// </summary>
		virtual void LoadResource() = 0;

		/// <summary>
		/// 終了処理を行う
		/// </summary>
		virtual void Finalize() = 0;

		/// <summary>
		/// 更新を行う
		/// </summary>
		virtual void Update();

		/// <summary>
		/// 描画を行う
		/// </summary>
		virtual void Render() = 0;

		inline float GetZ() const
		{
			return m_z;
		}

	protected:
		Object(float z);

		/// <summary>
		/// 描画順を決める際に扱う変数
		/// </summary>
		float m_z = 1.0f;

		gameframework::RectSize m_windowSize;
		D3DXVECTOR2 m_windowCenter = { 0.0f,0.0f };

		gameframework::GameFramework& m_rGameFramework = gameframework::GameFramework::GetRef();
	};
} // namespace summonersaster

#endif //!OBJECT_H
