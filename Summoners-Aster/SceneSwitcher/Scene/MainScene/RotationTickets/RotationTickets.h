#ifndef ROTATION_TICKETS_H
#define ROTATION_TICKETS_H

#include <vector>

#include <Gameframework.h>

#include "Object.h"

namespace summonersaster
{
	using gameframework::Vertices;
	using gameframework::Stream;

	class RotationTickets :public Object
	{
	public:
		explicit RotationTickets(const D3DXVECTOR2& baseCenterWindowMulti);

		~RotationTickets();

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize()override;

		/// <summary>
		/// 終了処理
		/// </summary>
		void Finalize()override;

		/// <summary>
		/// テクスチャ読み込み
		/// </summary>
		void LoadResource()override;

		/// <summary>
		/// 回転権の描画
		/// </summary>
		void Render()override;

		inline int RetentionNum()const
		{
			return m_retentionNum;
		}

		inline void RetentionNum(int rhs)
		{
			m_retentionNum = min(rhs, RETENTION_MAX);
		}

		inline RotationTickets& operator=(int rhs)
		{
			m_retentionNum = rhs;

			return *this;
		}

		inline bool operator==(int rhs)const
		{
			return (m_retentionNum == rhs);
		}

		inline RotationTickets& operator++()
		{
			++m_retentionNum;

			return *this;
		}

		inline RotationTickets& operator--()
		{
			--m_retentionNum;

			return *this;
		}

		inline bool operator<(int rhs)const
		{
			return (m_retentionNum < rhs);
		}

		inline bool operator>(int rhs)const
		{
			return (m_retentionNum > rhs);
		}

		inline bool operator<=(int rhs)const
		{
			return (m_retentionNum <= rhs);
		}

		inline bool operator>=(int rhs)const
		{
			return (m_retentionNum >= rhs);
		}

		static const int RETENTION_MAX = 3;

	private:
		RotationTickets(RotationTickets& rotationTickets) = delete;
		RotationTickets& operator=(RotationTickets& rotationTickets) = delete;

		gameframework::Vertices* m_pVertices = nullptr;

		D3DXVECTOR3 m_baseCenter = { 0.0f, 0.0f, 0.0f };

		int m_retentionNum = 0;
	};
} // namespace summonersaster

#endif // !ROTATION_TICKETS_H
