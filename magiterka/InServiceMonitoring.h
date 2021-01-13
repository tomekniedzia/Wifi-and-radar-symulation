#pragma once
#include <iostream>
#include "Event.h"
#include "DFS.h"
#include "Enum.h"
#include "NonOccupancyPeriod.h"

class InServiceMonitoring :public Event
{
public:
	InServiceMonitoring() = default;
	InServiceMonitoring(DFS *dfs, double time_system, double generate_time, double sampling, int impuls_observed);
	~InServiceMonitoring();

	virtual void Execute() override;

private:
	DFS *dfs_;

	int count_impuls_observed_;
	bool observed_equal_observation_ = false;
	double sampling_;
};

