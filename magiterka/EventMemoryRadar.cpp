#include "EventMemoryRadar.h"


EventMemoryRadar::EventMemoryRadar(DFS * dfs, double time_system, double generate_time, TypeEventMemoryRadar type_event_memory_radar)
	:Event(time_system, generate_time), dfs_(dfs), type_event_memory_radar_(type_event_memory_radar)
{
}

EventMemoryRadar::~EventMemoryRadar()
{
}

void EventMemoryRadar::Execute()
{
	if (type_event_memory_radar_ == kStartTransmission)
	{
		//rozpoczêcie transmisji
		Event *transmission = new StartTransmission(dfs_, dfs_->ReturnSystemTime(), 0.1);
		dfs_->PushCalendar(transmission);
		if (dfs_->IfMemoryRadarQueueEmpty() == false)
		{
			//zaplanowanie kolejnego zdarzenia stopu i startu transmisji
			Event *event_memory_stop = new EventMemoryRadar(dfs_, dfs_->ReturnSystemTime(), dfs_->GetTimeApperanceQueue(), kStopTransmission);
			dfs_->PushCalendar(event_memory_stop);
			Event *event_memory_start = new EventMemoryRadar(dfs_, dfs_->ReturnSystemTime(), dfs_->GetTimeDisapperanceQueue(), kStartTransmission);
			dfs_->PushCalendar(event_memory_start);
			//przesuniêcie pierwszego na koniec
			//utowrzenie nowego
			MemoryRadar *memory_radar = new MemoryRadar(dfs_->GetTimeApperanceQueue(), dfs_->GetTimeDisapperanceQueue());
			//dodanie do kolejki na koniec
			dfs_->PushMemoryRadarQueue(memory_radar);
			//usuniêcie pierwszego
			dfs_->PopFrontMemoryRadarQueue();
		}
	}
	else
	{
		//Wy³¹czenie transmisji
		dfs_->SetTransmission(false);
		dfs_->SetChannel(kAvailableChannel);
	}
}
