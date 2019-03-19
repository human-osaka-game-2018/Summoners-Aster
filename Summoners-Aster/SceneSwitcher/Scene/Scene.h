#ifndef SCENE_H
#define SCENE_H

namespace summoners_aster
{
	class Scene
	{
	public:
		enum class KINDS
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
}

#endif //!SCENE_H
