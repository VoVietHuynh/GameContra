#include "DrawLine.h"
#include "ObjectManager.h"

DrawLine* DrawLine::_drawLine = nullptr;

DrawLine* DrawLine::GetInstance()
{
	if (nullptr == _drawLine) {
		_drawLine = new DrawLine();
	}
	return _drawLine;
}

DrawLine::DrawLine()
{
}

DrawLine::~DrawLine()
{
}

void DrawLine::Draw(D3DXVECTOR2 lines[], int count)
{
	LPD3DXLINE line;
	D3DXCreateLine(Graphic::GetInstance()->GetDevice(), &line);
	line->SetWidth(2);
	line->Draw(lines, count, D3DCOLOR_XRGB(255, 0, 0));//Màu đỏ
	line->Release();
}

void DrawLine::DrawRect(RECT rect)
{
	Viewport* view = ObjectManager::GetInstance()->GetViewPort();

	D3DXVECTOR2 lines[] = { view->GetPositionViewport(D3DXVECTOR2(rect.left, rect.top)),
		view->GetPositionViewport(D3DXVECTOR2(rect.right, rect.top)),
			view->GetPositionViewport(D3DXVECTOR2(rect.right, rect.bottom)),
				view->GetPositionViewport(D3DXVECTOR2(rect.left, rect.bottom)),
					view->GetPositionViewport(D3DXVECTOR2(rect.left, rect.top))
						};
	Draw(lines, 5);
}