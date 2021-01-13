#pragma once

#include <iostream>
#include <fstream>
#include "Event.h"
#include "DFS.h"
#include "Enum.h"
#include "StartTransmission.h"
#include "NonOccupancyPeriod.h"

class CAC :public Event
{
public:
	CAC() = default;
	CAC(DFS *dfs, double time_system, double generate_time, TypeCAC type_cac, int impuls_observed);
	~CAC();

	virtual void Execute() override;

private:
	DFS *dfs_;
	TypeCAC type_cac_;

	int count_impuls_observed_;
	bool observed_equal_observation_ = false;
	bool radar_;

};

