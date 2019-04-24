#ifndef MP_H
#define MP_H

#include <GameFramework.h>

#include "BattleObject.h"

namespace summonersaster
{
using gameframework::Vertices;

class MP :public BattleObject
{
public:
	explicit MP(const D3DXVECTOR3& center);
	~MP();
	void Render();

	unsigned int GetUsablePoint() const
	{
		return m_UsablePoint;
	}
	unsigned int GetCapacity() const
	{
		return m_Capacity;
	}

	/// <summary>
	/// 最大値を増やす
	/// </summary>
	/// <remarks>増加最大値は<seealso cref="MAX_CAPACITY"/></remarks>
	void IncreaseCapacity();

	/// <summary>
	/// 値を減らす
	/// </summary>
	/// <param name="paidMp">減らす量</param>
	bool Paid(const int paidMp);

	/// <summary>
	/// 使用可能ポイントを今の容量で更新する
	/// </summary>
	void RenewUsablePoints();
private:
	void LocaleMP();

	void LocaleStream();

	void InitializeStream();

	static const int MAX_CAPACITY = 10;
	int m_UsablePoint = 0;
	int m_Capacity = 0;

	D3DXVECTOR3 m_Center = { 0.0f, 0.0f, 0.0f };

	MP(MP& mP) = delete;

	Vertices* m_pVertices[MAX_CAPACITY];

	MP& operator=(MP& mP) = delete;
};
}
#endif
