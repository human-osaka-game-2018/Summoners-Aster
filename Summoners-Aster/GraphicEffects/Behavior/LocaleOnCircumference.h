#ifndef LOCALE_ON_CIRCUMFERENCE_H
#define LOCALE_ON_CIRCUMFERENCE_H

#include <d3dx9.h>

#include <GameFramework.h>

namespace summonersaster
{
	using gameframework::Behavior;
	using gameframework::Degree;
	using gameframework::Vertices;

	/// <summary>
	/// 移動
	/// </summary>
	class LocaleOnCircumference :public Behavior
	{
	public:
		LocaleOnCircumference(const D3DXVECTOR3& basePos, float radius, float radiusDifference, float startDegreeOnRightVec, float degreeWidth);

		virtual ~LocaleOnCircumference();

		virtual void Impart(Vertices* pVertices)override;

	protected:
		D3DXVECTOR3 m_pos = { 0.0f, 0.0f, 0.0f };
	};
} // namespace summonersaster

#endif //!LOCALE_ON_CIRCUMFERENCE_H
