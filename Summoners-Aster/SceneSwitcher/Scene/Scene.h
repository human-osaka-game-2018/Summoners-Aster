#ifndef SCENE_H
#define SCENE_H

namespace summonersaster
{
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

		virtual void Initialize() = 0;

		virtual void Finalize() = 0;

		virtual void Update() = 0;

		virtual void Render() = 0;

	protected:
		Scene();
	};
} // namespace summonersaster

#endif //!SCENE_H
