#ifndef KIND_BASE_H
#define KIND_BASE_H

namespace summonersaster
{
	/// <summary>
	/// シーン等の基底クラスの基底
	/// </summary>
	class KindBase
	{
	public:
		virtual ~KindBase();

		/// <summary>
		/// 初期化を行う
		/// </summary>
		virtual void Initialize() = 0;

		/// <summary>
		/// 終了処理を行う
		/// </summary>
		virtual void Finalize() = 0;

		/// <summary>
		/// 更新を行う
		/// </summary>
		virtual void Update() = 0;

		/// <summary>
		/// 描画を行う
		/// </summary>
		virtual void Render() = 0;

	protected:
		KindBase();
	};
} // namespace summonersaster

#endif //!KIND_BASE_H
