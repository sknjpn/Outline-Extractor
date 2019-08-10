#pragma once

namespace OutlineExtractor
{
	bool		IsInsideImage(const Point& position, const Size& imageSize);
	Point		GetPosition(const int direction);
	Array<Point>	GetOutline(const Image& image, const double threshold = 140);
	Array<Array<Point>>	GetOutlines(const Image& image, const double threshold = 140);
};

