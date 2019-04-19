#ifndef HP_H
#define HP_H
namespace summonersaster
{

class HP
{
public:
	HP();
	~HP();
	void Render();

	/// <summary>
	/// HPを減らす
	/// </summary>
	/// <param name="damage">減らす量</param>
	void Damaged(unsigned int damage);

	/// <summary>
	/// HPを増やす
	/// </summary>
	/// <param name="heal">増やす量</param>
	/// <remarks>初期値よりも増えない</remarks>
	void Recover(unsigned int heal);
	unsigned int GetRemain() {
		return m_Hp;
	}
private:
	const unsigned int MAX_CAPACITY = 10;//仮数値
	unsigned int m_Hp = MAX_CAPACITY;
	HP(HP& hP) = delete;

	HP& operator=(HP& hP) = delete;
};
}
#endif
