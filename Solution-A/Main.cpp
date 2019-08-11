#include "OutlineDetector.h"

void Main()
{
	Window::SetTitle(U"Outline Detector");

	double s = 16;
	Image image(U"image/image-3.png");
	DynamicTexture texture(image);

	Scene::Resize(image.size() * int(s));
	Window::Resize(Scene::Size());

	while (System::Update())
	{
		auto t = Transformer2D(Mat3x2::Scale(s), true);

		if (MouseL.pressed()) Line(Cursor::PreviousPos(), Cursor::Pos()).overwrite(image, Palette::Black, false);
		if (MouseR.pressed()) Line(Cursor::PreviousPos(), Cursor::Pos()).overwrite(image, Palette::White, false);

		OutlineDetector detector(image);
		ClearPrint();
		Print << U"図形の数" << detector.GetOutlines().size();

		texture.fill(image);
		texture.draw();
		for (auto& outline : detector.GetOutlines())
		{
			for (int i = 0; i < outline.size() - 1; ++i)
			{
				auto p1 = Vec2::One() * 0.5 + outline[i];
				auto p2 = Vec2::One() * 0.5 + outline[i + 1];

				Line(p1, p2).draw(0.5, ColorF(HSV(i), 0.5));
			}
		}
	}
}
