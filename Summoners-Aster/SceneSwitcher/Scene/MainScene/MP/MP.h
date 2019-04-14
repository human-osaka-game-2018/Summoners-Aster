#ifndef MP_H
#define MP_H
namespace summonersaster
{

class MP
{
public:
	MP();
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
	bool Paid(const unsigned int paidMp);

	/// <summary>
	/// 使用可能ポイントを今の容量で更新する
	/// </summary>
	void RenewUsablePoints();
private:
	const unsigned int MAX_CAPACITY = 10;
	unsigned int m_UsablePoint = 0;
	unsigned int m_Capacity = 0;

	MP(MP& mP) = delete;

	MP& operator=(MP& mP) = delete;

};
}
#endif
