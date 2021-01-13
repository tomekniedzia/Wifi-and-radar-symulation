#include "Observation.h"

Observation::Observation(DFS *dfs, double time_system, double generate_time, int impuls_observed)
	:Event(time_system, generate_time), dfs_(dfs), count_impuls_observed_(impuls_observed)
{
}


Observation::~Observation()
{
}

void Observation::Execute() {
	//Koniec obserwacji
	if (dfs_->GetTimeFinishObservation() > dfs_->ReturnSystemTime())
	{
		if (dfs_->GetActuallPowerRadar() > -101)
		{
			if (dfs_->GetActuallPowerRadar() >= -62)
				count_impuls_observed_++;
			else
				count_impuls_observed_ = 0;

			if (count_impuls_observed_ == dfs_->GetNumberImpulsObservation())
				observed_equal_observation_ = true;
			else
				observed_equal_observation_ = false;
		}
		if (dfs_->GetActuallPowerRadar() >= -62)
		{
			if (observed_equal_observation_)
			{
				count_impuls_observed_ = 0;

				//WYKRYCIE RADARU
				MemoryRadar *memory_radar = new MemoryRadar(dfs_->ReturnSystemTime() - 10000, dfs_->ReturnSystemTime() + 10000);
				
				if(dfs_->IfMemoryRadarQueueEmpty())
					dfs_->PushMemoryRadarQueue(memory_radar);
				else
				{
					if ((memory_radar->GetTimeDisapperanceRadar() - 10000 - 1000) < dfs_->ReturnSystemTime())
					{
						MemoryRadar *memory_radar_new = new MemoryRadar(dfs_->GetTimeApperanceQueueBack(), dfs_->ReturnSystemTime() + 10000);
						dfs_->PopBackMemoryRadarQueue();
						dfs_->PushMemoryRadarQueue(memory_radar_new);
					}
					else
					{
						dfs_->PushMemoryRadarQueue(memory_radar);
					}
				}
				Event *observation = new Observation(dfs_, dfs_->ReturnSystemTime(), sampling_, count_impuls_observed_);
				dfs_->PushCalendar(observation);
			}
			else
			{
				//DZIA£A SOBIE DALEJ
				Event *observation = new Observation(dfs_, dfs_->ReturnSystemTime(), sampling_, count_impuls_observed_); 
				dfs_->PushCalendar(observation);
			}
		}
		else
		{
			//DZIA£A SOBIE DALEJ
			Event *observation = new Observation(dfs_, dfs_->ReturnSystemTime(), sampling_, count_impuls_observed_);
			dfs_->PushCalendar(observation);
		}
	}
	else
	{
		//ZDARZENIE ROZPCZÊCIA TRANSMISJI Z PAMIÊCI¥ RADARU
		Event *event_memory = new EventMemoryRadar(dfs_, dfs_->ReturnSystemTime(), 0.001, kStartTransmission);
		dfs_->PushCalendar(event_memory);
	}
}