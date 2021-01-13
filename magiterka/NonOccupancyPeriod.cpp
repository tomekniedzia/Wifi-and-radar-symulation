#include "NonOccupancyPeriod.h"



NonOccupancyPeriod::NonOccupancyPeriod(DFS *dfs, double time_system, double generate_time, TypeOccupancyPeriod type_occupancy_period)
	:Event(time_system, generate_time), dfs_(dfs), type_occupancy_period_(type_occupancy_period)
{
}


NonOccupancyPeriod::~NonOccupancyPeriod()
{
}

void NonOccupancyPeriod::Execute() {
	//std::cout << "Czas przez ktory kanal jest niedostepny po wykryciu radaru" << std::endl;

	if (type_occupancy_period_ == kStartOccupancy)
	{
		//std::cout << "Start Non-Occupancy Period Time" << std::endl;
		//Zaplanowanie zdarzenia zakoñczenie czasu Okupacji
		Event *stop_occupancy = new NonOccupancyPeriod(dfs_, dfs_->ReturnSystemTime(), kTimeNonOccupacyPeriod, kStopOccupancy);
		dfs_->PushCalendar(stop_occupancy);
	}
	else
	{
		//std::cout << "Stop Non-Occupancy Period Time" << std::endl;
		//Jeœli zakoñczenie okupacji to kana³y staj¹ siê Usable i mo¿na wywo³aæ CAC, jeœli nie nast¹pi³a zmiana kana³u
		dfs_->SetChannel(kUsableChannel);
		Event *cac = new CAC(dfs_, dfs_->ReturnSystemTime(), 0.1, kStartCAC, 0);
		dfs_->PushCalendar(cac);
		std::cout << dfs_->ReturnSystemTime() << " ";
		dfs_->GetChannel();
		std::cout << dfs_->GetActuallPowerRadar() << " " << dfs_->GetActuallPowerRadarWithoutNoise();
		std::cout << " " << "NonOcuPer" << std::endl;
	}

}
