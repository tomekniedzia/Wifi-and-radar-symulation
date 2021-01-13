#include "InServiceMonitoring.h"



InServiceMonitoring::InServiceMonitoring(DFS *dfs, double time_system, double generate_time, double sampling, int impuls_observed)
	:Event(time_system, generate_time), dfs_(dfs), sampling_(sampling), count_impuls_observed_(impuls_observed)
{
}


InServiceMonitoring::~InServiceMonitoring()
{
}

void InServiceMonitoring::Execute() {

	if (dfs_->GetTransmission())
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

				if (dfs_->GetImpulsDetection() == false)
				{
					dfs_->IncCountDetectionPRF();
					dfs_->SetImpulsDetection(true);
					if (dfs_->GetPowerWithoutNoiseAboveMinus62() == true)
						dfs_->IncImpulsSigDetection();
					else
						dfs_->IncImpulsNoSigDetection();
				}
				//std::cout << "In-Service Monitoring - jest radar" << std::endl;
				//Zerwanie transmisji
				dfs_->SetTransmission(false);
				//UStawienie kana³u na Unavailable Channel
				dfs_->SetChannel(kUnavailableChannel);
				//odpalenie NonOccupacy Period Time
				Event *start_occupacy = new NonOccupancyPeriod(dfs_, dfs_->ReturnSystemTime(), 1, kStartOccupancy);
				dfs_->PushCalendar(start_occupacy);
				std::cout << dfs_->ReturnSystemTime() << " ";
				dfs_->GetChannel();
				std::cout << dfs_->GetActuallPowerRadar() << " " << dfs_->GetActuallPowerRadarWithoutNoise();
				std::cout << std::endl;
			}
			else
			{
				Event *in_service = new InServiceMonitoring(dfs_, dfs_->ReturnSystemTime(), sampling_, sampling_, count_impuls_observed_); //kTimeMoinitoring (oryginalnie).
				dfs_->PushCalendar(in_service);
			}
		}
		else
		{
			//std::cout << "In-Service Monitoring - nie ma radar" << std::endl;
			Event *in_service = new InServiceMonitoring(dfs_, dfs_->ReturnSystemTime(), sampling_, sampling_, count_impuls_observed_); //kTimeMoinitoring (oryginalnie)
			dfs_->PushCalendar(in_service);
		}
	}
}
