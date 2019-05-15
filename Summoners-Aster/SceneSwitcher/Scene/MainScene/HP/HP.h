#ifndef HP_H
#define HP_H

#include <tchar.h>

#include <d3dx9.h>

#include <GameFramework.h>

#include "BattleObject.h"

namespace summonersaster
{
class HP :public BattleObject
{
public:
	HP(const D3DXVECTOR2& texturCenter);
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
	const unsigned int MAX_CAPACITY = 2;//仮数値
	unsigned int m_Hp = MAX_CAPACITY;

	D3DXVECTOR2 m_Center;

	HP(HP& hP) = delete;

	HP& operator=(HP& hP) = delete;

	D3DXVECTOR2	m_topLeft = { 0.0f, 0.0f };
};
}
#endif
