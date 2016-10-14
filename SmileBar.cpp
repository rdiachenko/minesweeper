#include <algorithm>
#include <chrono>
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

SmileBar::SmileBar(int mines) : startTimeSecs(0), curTimeSecs(0), minesInit(mines), minesLeft(mines), smileState(SmileState::INIT)
{
}

size_t SmileBar::now()
{
	return std::chrono::duration_cast<std::chrono::seconds>(
			std::chrono::system_clock::now().time_since_epoch()
			).count();
}

void SmileBar::startTimer()
{
	startTimeSecs = now();
}

void SmileBar::stopTimer()
{
	curTimeSecs = now() - startTimeSecs;
}

void SmileBar::resetTimer()
{
}

void SmileBar::incrMines()
{
	minesLeft++;
}

void SmileBar::decrMines()
{
	minesLeft--;
}

void SmileBar::render(Texture& texture, SDL_Renderer* const renderer)
{
	renderSmile(texture, renderer);
	renderMineCount(texture, renderer);
	renderTimeCount(texture, renderer);
}

void SmileBar::handleEvent(SDL_Event* event, GameField* gameField)
{
	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		if ((event->button).button == SDL_BUTTON_LEFT)
		{
			if (insideSmile((event->button).x, (event->button).y))
			{
				smileState = SmileState::PRESSED;
			}
		}
	}
	else if (event->type == SDL_MOUSEBUTTONUP)
	{
		if ((event->button).button == SDL_BUTTON_LEFT)
		{
			if (smileState == SmileState::PRESSED)
			{
				smileState = SmileState::INIT;
				reset();
				gameField->reset();
			}
		}
	}
}

void SmileBar::renderTimeCount(Texture& texture, SDL_Renderer* const renderer)
{
	size_t digitCount = std::max(toDigits(curTimeSecs).size(), 3UL);
	int xInit = SCREEN_WIDTH - 4 - digitCount * Clip::clip(DIGITS[0])->w;
	renderCount(xInit, 3, curTimeSecs, texture, renderer);
}

void SmileBar::renderMineCount(Texture& texture, SDL_Renderer* const renderer)
{
	int mines = minesLeft > minesInit ? minesInit : minesLeft < 0 ? 0 : minesLeft;
	renderCount(4, 3, mines, texture, renderer);
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
		x += clip->w;
	}
}

void SmileBar::renderSmile(Texture& texture, SDL_Renderer* const renderer)
{
	const SDL_Rect* clip = Clip::clip(static_cast<const int>(smileState));
	texture.render(SCREEN_WIDTH / 2 - clip->w / 2, 2, clip, renderer);
}

void SmileBar::reset()
{
	curTimeSecs = 0;
	minesLeft = minesInit;
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

bool SmileBar::insideSmile(int x, int y)
{
	const SDL_Rect* clip = Clip::clip(static_cast<const int>(SmileState::INIT));
	int x0 = SCREEN_WIDTH / 2 - clip->w / 2;
	int x1 = x0 + clip->w;
	int y0 = 2;
	int y1 = y0 + clip->h;
	return x >= x0 && x <= x1 && y >= y0 && y <= y1;
}

