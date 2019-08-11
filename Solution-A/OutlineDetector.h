#pragma once

class OutlineDetector
{
	Image	m_image;
	Grid<bool>	m_map;
	Array<Array<Point>>	m_outlines;

	bool	IsInsideMap(const Point& position);
	Point	GetPosition(const int direction);
	void	FillBlock(const Point& position);

public:
	OutlineDetector(const Image& image);

	const Array<Array<Point>>& GetOutlines() const { return m_outlines; }
};

