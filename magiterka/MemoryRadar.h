#pragma once
class MemoryRadar
{
public:
	MemoryRadar() = default;
	MemoryRadar(double time_apperance, double time_disapperance);
	~MemoryRadar();

	double GetTimeApperanceRadar();
	double GetTimeDisapperanceRadar();

private:
	double time_apperance_radar_;
	double time_disapperance_radar_;
};

