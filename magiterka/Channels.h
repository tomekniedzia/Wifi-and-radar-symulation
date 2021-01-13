#pragma once
#include "Enum.h"
class Channels
{
public:
	Channels() = default;
	Channels(int number, int min_freq, int max_freq);
	~Channels();

	int GetNumber();
	int GetMinFreq();
	int GetMaxFreq();
	int GetType(); //Zwraca stan kana³u
	void SetType(TypeChannel type);

private:
	int number_;
	int min_freq_;
	int max_freq_;
	TypeChannel type_;
};

