

void Main()
{
	Window::SetTitle("Outline Extractor");

	Image image(U"image/image-1.png");
	Texture texture(image);

	while (System::Update())
	{
		texture.draw();
	}
}
