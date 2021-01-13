#pragma once
#include <iostream>

#include "Event.h"
#include "DFS.h"
#include "MemoryRadar.h"
#include "Enum.h"
#include "StartTransmission.h"

class EventMemoryRadar :public Event
{
public:
	EventMemoryRadar() = default;
	EventMemoryRadar(DFS *dfs, double time_system, double generate_time, TypeEventMemoryRadar type_event_memory_radar);
	~EventMemoryRadar();

	virtual void Execute() override;

private:
	DFS *dfs_;

	TypeEventMemoryRadar type_event_memory_radar_;

};

