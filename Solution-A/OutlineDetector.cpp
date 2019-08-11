#include "OutlineDetector.h"

bool OutlineDetector::IsInsideMap(const Point& position)
{
	return position.x >= 0 && position.y >= 0 && position.x < m_map.size().x && position.y < m_map.size().y;
}

Point OutlineDetector::GetPosition(const int direction)
{
	switch ((direction % 8 + 8) % 8)
	{
	case 0: return Point(1, 0);
	case 1: return Point(1, 1);
	case 2: return Point(0, 1);
	case 3: return Point(-1, 1);
	case 4: return Point(-1, 0);
	case 5: return Point(-1, -1);
	case 6: return Point(0, -1);
	case 7: return Point(1, -1);
	}

	throw Error(U"存在しない方向`{}`が代入されました"_fmt(direction));
}

void OutlineDetector::FillBlock(const Point& position)
{
	Array<Point> points;
	points.emplace_back(position);
	m_map[position.y][position.x] = false;

	for (int i = 0; i < points.size(); ++i)
	{
		for (int j = 0; j <= 7; ++j)
		{
			Point p = points[i] + GetPosition(j);

			if (IsInsideMap(p) && m_map[p.y][p.x])
			{
				points.emplace_back(p.x, p.y); m_map[p.y][p.x] = false;
			}
		}
	}
}

OutlineDetector::OutlineDetector(const Image& image)
{
	m_map.resize(image.size());

	for (auto p : step(image.size()))
		m_map[p.y][p.x] = image[p.y][p.x].grayscale() < 0.5;

	Point	botPosition(0, 0);
	int		botDirection = 0;
	bool	findBlock = false;

	for (;;)
	{
		if (findBlock)
		{
			for (int i = -2; i <= 4; ++i)
			{
				// 始点に戻った場合
				if (m_outlines.back().size() >= 2 && (botDirection + i) % 8 == 0 && botPosition == m_outlines.back().front())
				{
					FillBlock(botPosition);
					findBlock = false;
					break;
				}

				const Point forwardPosition = botPosition + GetPosition(botDirection + i);

				if (IsInsideMap(forwardPosition) && m_map[forwardPosition.y][forwardPosition.x])
				{
					botPosition = forwardPosition;
					botDirection = ((botDirection + i) % 8 + 8) % 8;
					m_outlines.back().emplace_back(botPosition);
					break;
				}

				if (i == 4)
				{
					// 一ブロックの点
					findBlock = false;
					FillBlock(botPosition);
				}
			}
		}
		else
		{
			botPosition.x++;

			if (botPosition.x == m_map.size().x)
			{
				botPosition.x = 0;
				botPosition.y++;

				if (botPosition.y == m_map.size().y)return;
			}

			if (m_map[botPosition.y][botPosition.x])
			{
				botDirection = 0;
				findBlock = true;
				m_outlines.emplace_back();
				m_outlines.back().emplace_back(botPosition);
			}
		}
	}


}
