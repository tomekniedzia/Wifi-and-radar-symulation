#pragma once
#include <iostream>
#include "Event.h"
#include "DFS.h"
#include "Enum.h"
#include "CAC.h"

class NonOccupancyPeriod :public Event
{
public:
	NonOccupancyPeriod() = default;
	NonOccupancyPeriod(DFS *dfs, double time_system, double generate_time, TypeOccupancyPeriod type_occupancy_period);
	~NonOccupancyPeriod();

	virtual void Execute() override;

private:
	DFS *dfs_;

	const int occupancy_period_time_ = 108000000; //30 minut
	TypeOccupancyPeriod type_occupancy_period_;
};

