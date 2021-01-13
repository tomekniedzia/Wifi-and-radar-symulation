#pragma once
#include <iostream>
#include "Event.h"
#include "DFS.h"
#include "InServiceMonitoring.h"
#include "Enum.h"

class StartTransmission :public Event
{
public:
	StartTransmission() = default;
	StartTransmission(DFS *dfs, double time_system, double generate_time);
	~StartTransmission();

	virtual void Execute() override;

private:
	DFS *dfs_;
};

