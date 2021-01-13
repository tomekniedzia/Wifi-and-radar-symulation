#include "StartTransmission.h"



StartTransmission::StartTransmission(DFS *dfs, double time_system, double generate_time)
	:Event(time_system, generate_time), dfs_(dfs)
{

}


StartTransmission::~StartTransmission()
{
}

void StartTransmission::Execute() {
	//std::cout << "Slave rozpoczyna transmisje" << std::endl;

	//Zmiana kana³u na Operating Channel
	dfs_->SetChannel(kOperatingChannel);

	//Ustawienie transmisji
	dfs_->SetTransmission(true);

	//Odpalenie monitorowania
	Event *in_service = new InServiceMonitoring(dfs_, dfs_->ReturnSystemTime(), 0.1, 1.6, 0);
	dfs_->PushCalendar(in_service);

	std::cout << dfs_->ReturnSystemTime() << " ";
	dfs_->GetChannel();
	std::cout << dfs_->GetActuallPowerRadar() << " " << dfs_->GetActuallPowerRadarWithoutNoise();
	std::cout << std::endl;
}