#include "OutlineExtractor.h"

bool OutlineExtractor::IsInsideImage(const Point& position, const Size& imageSize)
{
	return  position.x >= 0 && position.y >= 0 && position.x < imageSize.x && position.y < imageSize.y;
}

Point OutlineExtractor::GetPosition(const int direction)
{
	switch (direction % 8)
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

Array<Array<Point>> OutlineExtractor::GetOutlines(const Image& image, const double threshold)
{
	Array<Array<Point>> result;

	Point	botPosition(0, 0);
	int		botDirection = 0;
	bool	findBlock = false;

	for (;;)
	{
		if (findBlock)
		{
			for (int i = -1; i <= 4; ++i)
			{
				const Point forwardPosition = botPosition + GetPosition(botDirection + i);

				if (IsInsideImage(forwardPosition, image.size()) && image[forwardPosition.y][forwardPosition.x].grayscale0_255() <= threshold)
				{
					botPosition = forwardPosition;
					result.back().emplace_back(botPosition);
				}

				// 始点に戻った場合
				if (result.back().size() >= 2 && botDirection + i == 0 && botPosition == result.back().front())
				{
					findBlock = false;
				}
			}

			// 一ブロックの点
			findBlock = false;
		}
		else
		{
			botPosition.x++;

			if (botPosition.x == image.size().x)
			{
				botPosition.x = 0;
				botPosition.y++;

				if (botPosition.y == image.size().y) return result;
			}

			if (image[botPosition.y][botPosition.x].grayscale0_255() <= threshold)
			{
				botDirection = 0;
				findBlock = true;
				result.emplace_back();
				result.back().emplace_back(botPosition);
			}
		}
	}


}
