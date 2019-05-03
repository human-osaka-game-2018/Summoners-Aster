#ifndef MOVE_H
#define MOVE_H

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
	class Move :public Behavior
	{
	public:
		Move(const D3DXVECTOR2& destPos, int requireFrameNum);

		virtual ~Move();

		virtual void Impart(Vertices* pVertices)override;

	protected:
		int m_requireFrameNum;
		D3DXVECTOR3 m_oneFrameMovement = { 0.0f, 0.0f, 0.0f };
	};
} // namespace summonersaster

#endif //!MOVE_H
