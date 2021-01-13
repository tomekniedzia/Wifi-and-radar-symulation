#pragma once
#include <iostream>

#include "Event.h"
#include "DFS.h"
#include "MemoryRadar.h"
#include "EventMemoryRadar.h"

class Observation :public Event
{
public:
	Observation() = default;
	Observation(DFS *dfs, double time_system, double generate_time, int impuls_observed);
	~Observation();

	virtual void Execute() override;

private:
	DFS *dfs_;

	int count_impuls_observed_;
	bool observed_equal_observation_ = false;
	double sampling_ = 0.9;
};

