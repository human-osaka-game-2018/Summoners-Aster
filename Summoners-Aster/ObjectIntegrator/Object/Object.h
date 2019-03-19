#ifndef OBJECT_H
#define OBJECT_H

namespace summonersaster
{
	class Object
	{
	public:
		virtual ~Object();

		virtual bool Initialize() = 0;
		virtual bool LoadResource() = 0;

		virtual void Finalize() = 0;

		virtual void Update() = 0;
		virtual void Render() = 0;

		inline float GetZ() const
		{
			return m_z;
		}

	protected:
		Object(float z);

		//描画順を決める際に扱う変数
		float m_z = 1.0f;
	};
} // namespace summonersaster

#endif //!OBJECT_H
