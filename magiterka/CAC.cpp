#include "CAC.h"

CAC::CAC(DFS *dfs, double time_system, double generate_time, TypeCAC type_cac, int impuls_observed)
	:Event(time_system, generate_time), dfs_(dfs), type_cac_(type_cac), count_impuls_observed_(impuls_observed)
{

}

CAC::~CAC()
{
}

void CAC::Execute() {

	//TESTY - d³uzszy czas obserwacji
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
	//Przeszukanie czy jest sygna³ radarowy czy go nie ma
	if (dfs_->GetActuallPowerRadar() > -62)
	{
		if (observed_equal_observation_)
		{
			//Zwraca true, co znaczy, ¿e jest sygna³ radarowy, wiêc trzeba przejsc do wykrycia radaru
			//UStawienie kana³u na Unavailable Channel
			dfs_->SetChannel(kUnavailableChannel);

			std::cout << dfs_->ReturnSystemTime() << " ";
			dfs_->GetChannel();
			std::cout << dfs_->GetActuallPowerRadar() << " " << dfs_->GetActuallPowerRadarWithoutNoise();
			std::cout << std::endl;
			//po 1us wywo³uje czas okupacji
			Event *det_radar = new NonOccupancyPeriod(dfs_, dfs_->ReturnSystemTime(), 0.001, kStartOccupancy);
			dfs_->PushCalendar(det_radar);

			radar_ = false;
		}
		else
		{
			Event *cac_measurement = new CAC(dfs_, dfs_->ReturnSystemTime(), 0.9, kMeasurementCAC, count_impuls_observed_); //Normalnie 1us
			dfs_->PushCalendar(cac_measurement);
		}	
	}
	else 
	{
		//Jeœli go nie ma to przechodzi dalej
		if (type_cac_ == kStartCAC)
		{
			//std::cout << "Rozpoczecie CAC" <<  std::endl;
			//Zaplanowanie zdarzenia koñca CAC
			Event *cac = new CAC(dfs_, dfs_->ReturnSystemTime(), kTimeCAC, kStopCAC, count_impuls_observed_);
			dfs_->PushCalendar(cac);
			Event *cac_measurement = new CAC(dfs_, dfs_->ReturnSystemTime(), 0.001, kMeasurementCAC, count_impuls_observed_);
			dfs_->PushCalendar(cac_measurement);
			dfs_->SetIfRunCAC(true);

			radar_ = true;
		}
		else if (type_cac_ == kMeasurementCAC && dfs_->GetIfRunCAC() == true)
		{
			Event *cac_measurement = new CAC(dfs_, dfs_->ReturnSystemTime(), 0.9, kMeasurementCAC, count_impuls_observed_); //Normalnie 1us
			dfs_->PushCalendar(cac_measurement);

			radar_ = true;
		}
		else if (type_cac_ == kStopCAC)
		{
			//Jeœli nie wykry³ radaru przez ten czas to ustawia kana³y z CAC na "availble"
			if (dfs_->GetChannel5() == kUsableChannel)
			{
				//std::cout << "Zakonczenie CAC" << std::endl;
				dfs_->SetChannel(kAvailableChannel);
				//Zaplanuje transmisje za 1 sek
				Event *transmission = new StartTransmission(dfs_, dfs_->ReturnSystemTime(), 1000);
				dfs_->PushCalendar(transmission);
				dfs_->SetIfRunCAC(false);

				std::cout << dfs_->ReturnSystemTime() << " ";
				dfs_->GetChannel();
				std::cout << dfs_->GetActuallPowerRadar() << " " << dfs_->GetActuallPowerRadarWithoutNoise();
				std::cout << std::endl;
			}		
		}
	}
	
}
