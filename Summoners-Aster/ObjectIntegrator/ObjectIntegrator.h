#ifndef OBJECT_INTEGRATOR_H
#define OBJECT_INTEGRATOR_H

#include <vector>

#include "Object/Object.h"

namespace summonersaster
{
	/// <summary>
	/// オブジェクトをまとめて動かすクラス
	/// </summary>
	class ObjectIntegrator
	{
	public:
		ObjectIntegrator();
		~ObjectIntegrator();

		/// <summary>
		/// オブジェクトの登録を行う
		/// </summary>
		/// <param name="pObject">登録したいオブジェクト</param>
		void Register(Object* pObject);

		/// <summary>
		/// 管理しているオブジェクトを開放する
		/// </summary>
		void Release();

		/// <summary>
		/// 管理しているオブジェクトを更新する
		/// </summary>
		void Update();

		/// <summary>
		/// 管理しているオブジェクトを奥にある物体から描画する
		/// </summary>
		void Render();

		/// <summary>
		/// 管理しているオブジェクトのロード関数を呼ぶ
		/// </summary>
		void ReloadResources();

	private:
		/// <summary>
		/// 引数のオブジェクトを比較してどちらが遠いか判断する
		/// </summary>
		/// <param name="pCompares">比較する方</param>
		/// <param name="pCompared">比較される方</param>
		/// <returns>遠ければtrue</returns>
		static bool IsFarther(const Object* pCompares, const Object* pCompared);
		std::vector<Object*> m_pObjects;
	};
} // namespace summonersaster

#endif // !OBJECT_INTEGRATOR_H
