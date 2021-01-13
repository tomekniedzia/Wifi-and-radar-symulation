#include "MemoryRadar.h"



MemoryRadar::MemoryRadar(double time_apperance, double time_disapperance)
	:time_apperance_radar_(time_apperance), time_disapperance_radar_(time_disapperance)
{
}


MemoryRadar::~MemoryRadar()
{
}

double MemoryRadar::GetTimeApperanceRadar()
{
	return time_apperance_radar_;
}

double MemoryRadar::GetTimeDisapperanceRadar()
{
	return time_disapperance_radar_;
}