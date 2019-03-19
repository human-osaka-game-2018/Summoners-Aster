#ifndef SCENE_H
#define SCENE_H

namespace summonersaster
{
	/// <summary>
	/// シーンの基底クラス
	/// </summary>
	class Scene
	{
	public:
		enum class KIND
		{
			TITLE,
			HOME,
			BATTLE,
			RESULT
		};

		virtual ~Scene();

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
		Scene();
	};
} // namespace summonersaster

#endif //!SCENE_H
