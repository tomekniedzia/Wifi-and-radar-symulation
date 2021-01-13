#include "DFS.h"
#include <iostream>

DFS::DFS()
{
	transmission_ = false;

	//Stworzenie kana³ów
	int min_freq, max_freq;
	for (int i = 0; i < tab_channels_length_; i++) {
		if (i < 8)
		{
			min_freq = 5180 + (i * 20);
			max_freq = 5180 + (i * 20) + 20;
		}
		else
		{
			min_freq = 5500 + ((i - 8) * 20);
			max_freq = 5500 + ((i - 8) * 20) + 20;
		}
		
		tab_channels_[i] = new Channels(i, min_freq, max_freq);
		//std::cout << "Kanal: " << i << " number: " << tab_channels_[i]->GetNumber() << " Freq: " << tab_channels_[i]->GetMinFreq() << "-" << tab_channels_[i]->GetMaxFreq() << " Type: " << tab_channels_[i]->GetType() << std::endl;
	}
		//channels_ = -1; //Po w³¹czeniu kana³y jako nie aktywne
	//}
}


DFS::~DFS()
{
}

/*void DFS::ShowChannels()
{
	for (int i = 0; i < 12; i++)
	{
		std::cout << channels_[i];
	}
	std::cout << std::endl;
}*/

////  FUNKCJE DOTYCZ¥CE KALENDARZA ZDARZEÑ /////

void DFS::PushCalendar(Event *event) //Dodanie zdarzenia
{
	if (calendar_.empty())
		calendar_.push_front(event);
	else
	{
		for (std::list<Event*>::iterator it = calendar_.begin(); it != calendar_.end(); ++it)
		{
			if ((*it)->ReturnEventTime() > event->ReturnEventTime())
			{
				calendar_.insert(it, event);
				return;
			}
		}
		calendar_.push_back(event);
	}
}

void DFS::PopCalendar() //Usuniêcie zdarzenia
{
	calendar_.pop_front();	//usuniêcie zdarzenia obs³u¿onego
}

void DFS::NextCalendar() //kolejne zdarzenie z kalendarza
{
	calendar_.front()->Execute(); //Wywo³anie funkcji;
}

void DFS::NextSystemTime() // Zmiana czasu systemowego
{
	system_time_ = calendar_.front()->ReturnEventTime(); // zmiana czasu systemowego
}

void DFS::DestructorCalendar()
{
	delete calendar_.front();
}

double DFS::ReturnSystemTime() const
{
	return system_time_;
}

////	FUNKCJE OD KANALOW	////

void DFS::SetChannel(TypeChannel type_channel)
{
	for (int i = 0; i < tab_channels_length_; i++)
		tab_channels_[i]->SetType(type_channel);
}

int DFS::GetChannel()
{
	//for (int i = 0; i < tab_channels_length_; i++)
		//std::cout << tab_channels_[i]->GetType() << " ";
	return tab_channels_[5]->GetType();
}

int DFS::GetChannel5()
{
	return tab_channels_[5]->GetType();
}


////	FUNKCJE OD RADARU	////

void DFS::SetIfRadar(bool if_radar)
{
	if_radar_ = if_radar;
}

bool DFS::GetRadar()
{
	return if_radar_;
}

void DFS::SetActuallPowerRadar(double power)
{
	actuall_power_radar_ = power;
}

double DFS::GetActuallPowerRadar()
{
	return actuall_power_radar_;
}

void DFS::SetActuallPowerRadarWithoutNoise(double power)
{
	actuall_power_radar_without_noise = power;
}

double DFS::GetActuallPowerRadarWithoutNoise()
{
	return actuall_power_radar_without_noise;
}

////	FUNKCJE DO TRANSMISJI	////

void DFS::SetTransmission(bool transmission)
{
	transmission_ = transmission;
}

bool DFS::GetTransmission()
{
	return transmission_;
}

////	FUNKCJE PO£O¯ENIE AP	////

void DFS::SetPossitionAP(double x_ap, double y_ap, double z_ap)
{
	x_ap_ = x_ap;
	y_ap_ = y_ap;
	z_ap_ = z_ap;
}

double DFS::GetXAP()
{
	return x_ap_;
}

double DFS::GetYAP()
{
	return y_ap_;
}

double DFS::GetZAP()
{
	return z_ap_;
}

void DFS::SetIfRunCAC(bool CAC)
{
	if_run_CAC_ = CAC;
}

bool DFS::GetIfRunCAC()
{
	return if_run_CAC_;
}

//PRAWDOPODBIENSTWO DETEKCJI

void DFS::IncCountPRF()
{
	count_PRF_above_62++;
}

int DFS::GetCountPRF()
{
	return count_PRF_above_62;
}

void DFS::IncCountUnder62()
{
	count_PRF_under_62++;
}

int DFS::GetCountUnder62()
{
	return count_PRF_under_62;
}

void DFS::IncCountDetectionPRF()
{
	count_detection_PRF_above_62++;
}

int DFS::GetCountDetectionPRF()
{
	return count_detection_PRF_above_62;
}

void DFS::IncImpulsSigDetection()
{
	impuls_sig_detection++;
}

int DFS::GetImpulsSigDetection()
{
	return impuls_sig_detection;
}

void DFS::IncImpulsNoSigDetection()
{
	impuls_no_sig_detection++;
}

int DFS::GetImpulsNoSigDetection()
{
	return impuls_no_sig_detection;
}

void DFS::SetImpulsDetection(bool impuls_detection)
{
	impuls_detection_ = impuls_detection;
}

bool DFS::GetImpulsDetection()
{
	return impuls_detection_;
}

void DFS::IncSigDetection()
{
	sig_detection_++;
}

int DFS::GetSigDetection()
{
	return sig_detection_;
}

void DFS::IncSigNoDetection()
{
	sig_no_detection_++;
}

int DFS::GetSigNoDetection()
{
	return sig_no_detection_;
}

void DFS::IncNoSigDetection()
{
	no_sig_detection_++;
}

int DFS::GetNoSigDetection()
{
	return no_sig_detection_;
}

void DFS::IncNoSigNoDetection()
{
	no_sig_no_detection_++;
}

int DFS::GetNoSigNoDetection()
{
	return no_sig_no_detection_;
}

void DFS::IncShouldDetection()
{
	should_detection_++;
}

int DFS::GetShouldDetection()
{
	return should_detection_;
}

void DFS::IncNoShouldDetection()
{
	no_should_detection_++;
}

int DFS::GetNoShouldDetection()
{
	return no_should_detection_;
}

void DFS::SetPowerWithoutNoiseAboveMinus62(bool x)
{
	power_without_noise_above_minus_62_ = x;
}

bool DFS::GetPowerWithoutNoiseAboveMinus62()
{
	return power_without_noise_above_minus_62_;
}

void DFS::SetNumberImpulsObservation(int number)
{
	number_impuls_observation_ = number;
}

int DFS::GetNumberImpulsObservation()
{
	return number_impuls_observation_;
}

double DFS::GetTimeFinishObservation()
{
	return time_finish_observation;
}

void DFS::SetTimeApperanceRadar(double time_apperance_radar)
{
	time_apperance_radar_ = time_apperance_radar;
}

double DFS::GetTimeApperanceRadar()
{
	return time_apperance_radar_;
}

void DFS::SetTimeDisapperanceRadar(double time_disapperance_radar)
{
	time_disapperance_radar_ = time_disapperance_radar;
}

double DFS::GetTimeDisapperanceRadar()
{
	return time_disapperance_radar_;
}

void DFS::PushMemoryRadarQueue(MemoryRadar * memory_radar)
{
	memory_radar_queue_.push_back(memory_radar);
}

void DFS::PopFrontMemoryRadarQueue()
{
	memory_radar_queue_.pop_front();
}

void DFS::PopBackMemoryRadarQueue()
{
	memory_radar_queue_.pop_back();
}

bool DFS::IfMemoryRadarQueueEmpty()
{
	if (memory_radar_queue_.empty())
		return true;
	else
		return false;
}

double DFS::GetTimeApperanceQueue()
{
	return memory_radar_queue_.front()->GetTimeApperanceRadar();
}

double DFS::GetTimeDisapperanceQueue()
{
	return memory_radar_queue_.front()->GetTimeDisapperanceRadar();
}

double DFS::GetTimeApperanceQueueBack()
{
	return memory_radar_queue_.back()->GetTimeApperanceRadar();
}

double DFS::GetTimeDisapperanceQueueBack()
{
	return memory_radar_queue_.back()->GetTimeDisapperanceRadar();
}



