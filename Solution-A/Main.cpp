#include "OutlineExtractor.h"

void Main()
{
	Window::SetTitle(U"Outline Extractor");

	Image image(U"image/image-1.png");
	Texture texture(image);

	while (System::Update())
	{
		texture.draw();
		OutlineExtractor::GetOutlines(image);
	}
}
