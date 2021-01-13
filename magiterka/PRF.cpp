#include "PRF.h"




PRF::PRF(DFS * dfs, WeatherRadar *weather_radar, Generators *gen, double time_system, double generate_time, TypePRF type_prf)
	:Event(time_system, generate_time), dfs_(dfs), weather_radar_(weather_radar), gen_(gen), type_prf_(type_prf)
{
}

PRF::~PRF()
{
}

void PRF::PowerAndMove()
{
	double power_x = weather_radar_->PowerFromAngle(dfs_->GetXAP(), weather_radar_->GetXRadar());
	double power_y = weather_radar_->PowerFromAngle(dfs_->GetYAP(), weather_radar_->GetYRadar());
	double path_loss = weather_radar_->PathLoss(dfs_->GetZAP(), true);
	double noise = gen_->GenerateChiSquareDistributionFromGamma(); //Szum
	//Ustawienie obliczonej mocy dla danego punktu
	if ((power_x + power_y - path_loss) > -101)
	{
		weather_radar_->SetActuallyPowerRadar(power_x + power_y - path_loss + noise);
		dfs_->SetActuallPowerRadar(power_x + power_y - path_loss + noise);
		dfs_->SetActuallPowerRadarWithoutNoise(power_x + power_y - path_loss);
			
		//TESTY - prawdopodobenstwo
		if (power_x + power_y - path_loss > -62)
		{ 
			dfs_->IncCountPRF();
			dfs_->SetPowerWithoutNoiseAboveMinus62(true);
		}
		else
		{
			dfs_->SetPowerWithoutNoiseAboveMinus62(false);
			dfs_->IncCountUnder62();
		}
		//KONIEC TESTOW
	}
	else
	{
		dfs_->SetPowerWithoutNoiseAboveMinus62(false); //TESTY - PRAWD.
		dfs_->IncCountUnder62();
		//Poziom szumu
		weather_radar_->SetActuallyPowerRadar(-101);
		dfs_->SetActuallPowerRadar(-101 + noise);
		dfs_->SetActuallPowerRadarWithoutNoise(-101);
	}
	
	dfs_->SetImpulsDetection(false); //TESTY - PRAWD.

	//Przesuniêcie anteny o 0.0327 stopnia
	weather_radar_->SetXRadar(weather_radar_->GetXRadar() + 0.0327);
}

void PRF::Execute()
{
	if (type_prf_ == kStartPRF)
	{
		//koniec impulsu za 2us (dla testów impuls 0.1ms)
		Event *prf_stop = new PRF(dfs_, weather_radar_, gen_, dfs_->ReturnSystemTime(), 1, kStopPRF);
		dfs_->PushCalendar(prf_stop);
		//Obliczenie mocy i ruch anteny
		PowerAndMove();

		if (weather_radar_->GetIndexPRF() == 11000 && weather_radar_->GetIndexElevation() != 9)
		{

			//Dodanie wydarzenia kolejnego zczytania za 25.5s
			Event *prf = new PRF(dfs_, weather_radar_, gen_, dfs_->ReturnSystemTime(), kTimeNextElevationPRF, kStartPRF);
			dfs_->PushCalendar(prf);
			//Dodanie wydarzenia kolejnego impulsu
			Event *prf2 = new PRF(dfs_, weather_radar_, gen_, dfs_->ReturnSystemTime(), 1.818, kStartPRF);
			dfs_->PushCalendar(prf2);
			//Dodanie kolejnej sekwencji pomiarowej za 5 min
			if (weather_radar_->GetIndexElevation() == 0)
			{
				Event *prf3 = new PRF(dfs_, weather_radar_, gen_, dfs_->ReturnSystemTime(), kTimeNextSekvencePRF, kStartPRF);
				dfs_->PushCalendar(prf3);
			}

			weather_radar_->DecIndexPRF();
		}
		else if (weather_radar_->GetIndexPRF() == 0)
		{
			//Obrót o 360 st w poziom - zwiêkszenie elewacji, ustawienie licznika impulsów
			weather_radar_->IncIndexElevation();
			weather_radar_->SetIndexPRF(11000);
			weather_radar_->SetXRadar(-180);
			if (weather_radar_->GetIndexElevation() == 10)
				weather_radar_->SetIndexElevation(0);
		}
		else
		{
			Event *prf = new PRF(dfs_, weather_radar_, gen_, dfs_->ReturnSystemTime(), 1.818, kStartPRF);
			dfs_->PushCalendar(prf);

			weather_radar_->DecIndexPRF();
		}
	}
	else
	{
		//Znikniêcie sygna³u
		dfs_->SetPowerWithoutNoiseAboveMinus62(false); //TESTY - PRAWD.
		weather_radar_->SetActuallyPowerRadar(-101);
		dfs_->SetActuallPowerRadar(-101);
		dfs_->SetActuallPowerRadarWithoutNoise(-101);
	}		
}

