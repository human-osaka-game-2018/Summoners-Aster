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
		/// <param name="retentionMax">保持数</param>
		RotationTickets(int retentionMax);

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

		inline int RetentionNum(int rhs)
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

		const int RETENTION_MAX;

	private:
		RotationTickets(RotationTickets& rotationTickets) = delete;
		RotationTickets& operator=(RotationTickets& rotationTickets) = delete;

		std::vector<Vertices*> m_pVertices;

		int m_retentionNum = 0;
	};
} // namespace summonersaster

#endif // !ROTATION_TICKETS_H
