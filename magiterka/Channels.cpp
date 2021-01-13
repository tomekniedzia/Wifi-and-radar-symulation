#include "Channels.h"


Channels::Channels(int number, int min_freq, int max_freq):
	number_(number), min_freq_(min_freq), max_freq_(max_freq)
{
	type_ = kUsableChannel;
}

Channels::~Channels()
{
}

int Channels::GetNumber()
{
	return number_;
}

int Channels::GetMinFreq()
{
	return min_freq_;
}

int Channels::GetMaxFreq()
{
	return max_freq_;
}

int Channels::GetType()
{
	return type_;
}

void Channels::SetType(TypeChannel type)
{
	type_ = type;
}
