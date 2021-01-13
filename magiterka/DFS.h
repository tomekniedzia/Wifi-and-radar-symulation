#pragma once

#include <list>
#include <queue>

#include "Event.h"
#include "Enum.h"
#include "Channels.h"
#include "MemoryRadar.h"

class DFS
{
public:
	
	DFS();
	~DFS();

	//void ShowChannels();

	// KALENDARZ
	void PushCalendar(Event *event);	//dodanie do kalendarza
	void PopCalendar();					//usuiniêcie z kalendarza
	void NextCalendar();
	void NextSystemTime();				//zmiana czasu systemowego
	void DestructorCalendar();			//Destruktor zdarzenia w kalendarzu
	double ReturnSystemTime() const;

	// KANALY
	void SetChannel(TypeChannel type_channel);
	int GetChannel();
	int GetChannel5();

	// RADAR
	void SetIfRadar(bool if_radar);
	bool GetRadar();
	void SetActuallPowerRadar(double power);
	double GetActuallPowerRadar();
	void SetActuallPowerRadarWithoutNoise(double power);
	double GetActuallPowerRadarWithoutNoise();

	// TRANSMISJA
	void SetTransmission(bool transmission);
	bool GetTransmission();

	//	PO£O¯ENIE AP
	void SetPossitionAP(double x_ap, double y_ap, double z_ap);
	double GetXAP();
	double GetYAP();
	double GetZAP();

	//CAC
	void SetIfRunCAC(bool CAC);
	bool GetIfRunCAC();

	//PRAWDOPODBIENSTWO DETEKCJI:
	void IncCountPRF();
	int GetCountPRF();
	void IncCountUnder62();
	int GetCountUnder62();
	void IncCountDetectionPRF();
	int GetCountDetectionPRF();
	void IncImpulsSigDetection();
	int GetImpulsSigDetection();
	void IncImpulsNoSigDetection();
	int GetImpulsNoSigDetection();
	void SetImpulsDetection(bool impuls_detection);
	bool GetImpulsDetection();
	void IncSigDetection();
	int GetSigDetection();
	void IncSigNoDetection();
	int GetSigNoDetection();
	void IncNoSigDetection();
	int GetNoSigDetection();
	void IncNoSigNoDetection();
	int GetNoSigNoDetection();
	void IncShouldDetection();
	int GetShouldDetection();
	void IncNoShouldDetection();
	int GetNoShouldDetection();
	void SetPowerWithoutNoiseAboveMinus62(bool x);
	bool GetPowerWithoutNoiseAboveMinus62();
	void SetNumberImpulsObservation(int number);
	int GetNumberImpulsObservation();

	//PAMIÊC RADARU
	double GetTimeFinishObservation();
	void SetTimeApperanceRadar(double time_apperance_radar);
	double GetTimeApperanceRadar();
	void SetTimeDisapperanceRadar(double time_disapperance_radar);
	double GetTimeDisapperanceRadar();
	void PushMemoryRadarQueue(MemoryRadar *memory_radar);
	void PopFrontMemoryRadarQueue();
	void PopBackMemoryRadarQueue();
	bool IfMemoryRadarQueueEmpty();
	double GetTimeApperanceQueue();
	double GetTimeDisapperanceQueue();
	double GetTimeApperanceQueueBack();
	double GetTimeDisapperanceQueueBack();

private:
	bool transmission_; //Czy transmisja jest czy jej nie ma
	int channels_ = -1; //Kana³y: -1 unavailable channel; 0 usable channel; 1 available channel; 2 operating channel

	bool if_radar_;
	double actuall_power_radar_ = -101;
	double actuall_power_radar_without_noise = -101;

	bool if_run_CAC_;

	double system_time_ = 0;
	
	double x_ap_;
	double y_ap_;
	double z_ap_;

	//PRAWDOPODOBIEÑSTWO
	//Detekcja impulsu
	int count_PRF_above_62 = 0; //licznik impulsów powy¿ej -62dB
	int count_PRF_under_62 = 0; //licznik impulsów poni¿ej -62dB
	int count_detection_PRF_above_62 = 0; //Licznik detekcji impulsów powy¿ej -62dB
	int impuls_sig_detection = 0; //impuls by³, dokonano detekcji
	int impuls_no_sig_detection = 0; //impulsu nie by³o, by³a detekcja
	bool impuls_detection_ = false; //Czy dokonano detekcji impulsu (¿eby nie dublowaæ detekcji)
	//Detekcja w punkcie "próbkowania"
	int sig_detection_ = 0; //Sygna³ by³ i zosta³ wykryty (poprawnie)
	int sig_no_detection_ = 0; //Sygna³ by³, ale brak detekcji (niepoprawnie)
	int no_sig_detection_ = 0; //brak sygna³u, detekcja by³a (nieporpawnie)
	int no_sig_no_detection_ = 0; //brak sygna³u, brak detekcji (poprawnie)
	int should_detection_ = 0; //Ile detekcji sygna³u (ponad -62dB)
	int no_should_detection_ = 0; //Ile detekcji szumu (poni¿ej -62dB), czyli ile "braków detekcji"
	bool power_without_noise_above_minus_62_ = false; //Czy sygna³ bez szumu jest powy¿ej -62dB (jak tak to true)

	int number_impuls_observation_ = 0;

	//PAMIÊC RADARU
	double time_finish_observation = 600000;
	double time_apperance_radar_ = 0.0;
	double time_disapperance_radar_ = 0.0;

	const static int tab_channels_length_ = 19;
	Channels *tab_channels_[tab_channels_length_];


	
	std::list<MemoryRadar*> memory_radar_queue_;
	std::list<Event*> calendar_;					//kalendarz zdarzeñ
};

