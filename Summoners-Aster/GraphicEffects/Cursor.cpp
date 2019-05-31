#include "Cursor.h"

namespace gameframework
{
	Cursor::Cursor()
	{
		m_partScheduler.Register(new FollowUpCursorSquare(_T("カーソル"), 60.0f));

		m_isAdditionBlendMode = false;

		//ShowCursor(false);
	}

	Cursor::~Cursor()
	{

	}

	void Cursor::Update()
	{
		UpdateParts();
	}
}
