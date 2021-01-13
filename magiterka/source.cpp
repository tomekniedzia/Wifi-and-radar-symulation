#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <random>

#include "DFS.h"
#include "Event.h"
#include "CAC.h"
#include "StartTransmission.h"
#include "WeatherRadar.h"
#include "PRF.h"
#include "InServiceMonitoring.h"
#include "Generators.h"
#include "Observation.h"
#include "EventMemoryRadar.h"

//CZAS W ms!

int main() {

	srand((unsigned) time(NULL));

	bool work = true;

	//std::cout << "Czy praca krokowa? Wciscnij 1 jesli praca krokowa, 0 jesli praca ciagla " << std::endl;
	//std::cin >> work;

	//pêtla po z
	//for (int i = 0; i < 20; i++) {
		//pêtla po próbkowaniu
		//for (int j = 0; j < 10; j++) {
			//pêtla po mocy szumu
			//for (int k = 0; k < 10; k++)
			//{
				double z = 200;//50 + 75.0 * i;
				double sampling = 1.6;//0.08 + 0.02 * j;
				double noise_sigma = 5.0; //1.0 + k * 1.0;

				// Chi-square distribtion
				typedef std::chrono::high_resolution_clock myclock;
				myclock::time_point beginning = myclock::now();

				myclock::duration d = myclock::now() - beginning;
				unsigned seed2 = d.count();

				std::default_random_engine generator;
				generator.seed(seed2);

				std::gamma_distribution<double> distribution(1.0, noise_sigma);

				Generators *gen = new Generators(distribution, generator);

				work = true;
				DFS *dfs = new DFS();

				dfs->SetNumberImpulsObservation(6);

				WeatherRadar *weather = new WeatherRadar();
				dfs->SetPossitionAP(30.0, 7.0, z);

				Event *prf = new PRF(dfs, weather, gen, dfs->ReturnSystemTime(), 0.005, kStartPRF);
				dfs->PushCalendar(prf);

				std::fstream f1;
				f1.open("!sygnal_szum_sigma_5_odl_200_czas_obserwacji6_kalendarz_30min.txt", std::ios::app);

				double in_service_time = 1.0 * ((rand() % 3000));
				in_service_time /= 1000;
				//Event *cac = new CAC(dfs, dfs->ReturnSystemTime(), in_service_time, kStartCAC, 0);
				//dfs->PushCalendar(cac);
				//Event *in_service = new InServiceMonitoring(dfs, dfs->ReturnSystemTime(), in_service_time, sampling, 0);
				//dfs->PushCalendar(in_service);
				int count = 0;

				//PAMIÊC RADAROWA
				Event *observ = new Observation(dfs, dfs->ReturnSystemTime(), 0.001, 0);
				dfs->PushCalendar(observ);

				while (work)
				{
					dfs->NextSystemTime();
					dfs->NextCalendar();
					dfs->DestructorCalendar();
					dfs->PopCalendar();
					if (dfs->ReturnSystemTime() > 1800000)//86400000)
					{
						work = false;
						std::cout << dfs->ReturnSystemTime() << " ";
						dfs->GetChannel();
						std::cout << dfs->GetActuallPowerRadar() << " " << dfs->GetActuallPowerRadarWithoutNoise();
						std::cout << std::endl;
						std::cout << 123456789 << " " << z << std::endl;
					}
					if (count == 21)
					{
						f1 << dfs->ReturnSystemTime() << " ";
						f1 << dfs->GetChannel();
						f1 << " " << dfs->GetActuallPowerRadar() << " " << dfs->GetActuallPowerRadarWithoutNoise();
						f1 << std::endl;
						count = 0;
					}
					count++;
				}

				f1.close();
				delete dfs;
				delete weather;
	return 0;
}