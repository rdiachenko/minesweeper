#include <algorithm>
#include "SmileBar.h"
#include "Config.h"

static const int DIGITS[10] =
{
	Clip::DIGIT_0,
	Clip::DIGIT_1,
	Clip::DIGIT_2,
	Clip::DIGIT_3,
	Clip::DIGIT_4,
	Clip::DIGIT_5,
	Clip::DIGIT_6,
	Clip::DIGIT_7,
	Clip::DIGIT_8,
	Clip::DIGIT_9
};

SmileBar::SmileBar(int mines) : timeSecs(0), minesInit(mines), minesLeft(mines), smileState(SmileState::INIT)
{
}

void SmileBar::incrTime()
{
	timeSecs++;
}

void SmileBar::incrMines()
{
	minesLeft++;
}

void SmileBar::decrMines()
{
	minesLeft--;
}

void SmileBar::setSmileState(SmileState state)
{
	smileState = state;
}

void SmileBar::render(Texture& texture, SDL_Renderer* const renderer)
{
	renderSmile(texture, renderer);
	renderTimeCount(texture, renderer);
	renderMineCount(texture, renderer);
}

void SmileBar::reset()
{
	timeSecs = 0;
	minesLeft = minesInit;
}

bool SmileBar::insideSmile(int x, int y)
{
	const SDL_Rect* clip = Clip::clip(static_cast<const int>(SmileState::INIT));
	int x0 = SCREEN_WIDTH / 2 - clip->w / 2;
	int x1 = x0 + clip->w;
	int y0 = 2;
	int y1 = y0 + clip->h;
	return x >= x0 && x <= x1 && y >= y0 && y <= y1;
}

void SmileBar::renderTimeCount(Texture& texture, SDL_Renderer* const renderer)
{
	renderCount(4, 3, timeSecs, texture, renderer);
}

void SmileBar::renderMineCount(Texture& texture, SDL_Renderer* const renderer)
{
	size_t digitCount = std::max(toDigits(minesLeft).size(), 3UL);
	int xInit = SCREEN_WIDTH - 4 - digitCount * Clip::clip(DIGITS[0])->w - (digitCount - 1);
	renderCount(xInit, 3, minesLeft, texture, renderer);
}

void SmileBar::renderCount(int xInit, int yInit, int count, Texture& texture, SDL_Renderer* const renderer)
{
	std::deque<int> digits = toDigits(count);
	size_t digitCount = std::max(digits.size(), 3UL);
	int x = xInit;

	for (size_t i = 0, j = 0; i < digitCount; i++)
	{
		const SDL_Rect* clip;
		if ((digitCount - i) > digits.size()) clip = Clip::clip(DIGITS[0]);
		else clip = Clip::clip(DIGITS[digits[j++]]);
		texture.render(x, yInit, clip, renderer);
		x += clip->w + 1;
	}
}

void SmileBar::renderSmile(Texture& texture, SDL_Renderer* const renderer)
{
	const SDL_Rect* clip = Clip::clip(static_cast<const int>(smileState));
	texture.render(SCREEN_WIDTH / 2 - clip->w / 2, 2, clip, renderer);
}

std::deque<int> SmileBar::toDigits(int val)
{
	std::deque<int> reversedVal;
	while (val > 0)
	{
		reversedVal.push_front(val % 10);
		val /= 10;
	}
	return std::move(reversedVal);
}
