#include "DrawPhase.h"

namespace summonersaster
{
	DrawPhase::DrawPhase()
	{

	}

	DrawPhase::~DrawPhase()
	{

	}

	void DrawPhase::Initialize()
	{
		
	}

	void DrawPhase::Finalize()
	{
		
	}

	void DrawPhase::Update()
	{
		////ドローフェイズの処理が完了しているならばメインフェイズへ移行
		//if (Players.Update(_T("DRAW")))
		//{
		//	SwitchEventMediatorBase<Phase>::GetRef().SendSwitchEvent(_T("MAIN"));
		//}

		//Field.Update(_T("DRAW"));
	}

	void DrawPhase::Render()
	{
		//Players.Render(_T("DRAW"));
		//Field.Render(_T("DRAW"));
	}
} // namespace summonersaster
