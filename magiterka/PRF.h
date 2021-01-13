#pragma once
#include <iostream>
#include "Event.h"
#include "DFS.h"
#include "WeatherRadar.h"
#include "Enum.h"
#include "Generators.h"

class PRF :public Event
{
public:
	PRF() = default;
	PRF(DFS *dfs, WeatherRadar *weather_radar, Generators *gen, double time_system, double generate_time, TypePRF type_prf);
	~PRF();

	void PowerAndMove();
	virtual void Execute() override;


private:
	DFS *dfs_;
	WeatherRadar *weather_radar_;
	Generators *gen_;

	TypePRF type_prf_;

};

