#pragma once

enum TypeOccupancyPeriod 
{
	kStartOccupancy = 0,
	kStopOccupancy,
};

enum TypeCAC
{
	kStartCAC = 0,
	kStopCAC,
	kMeasurementCAC,
};

enum TypeTime {
	kTimeRadar = 899900,
	kTimeCAC = 60000, //Normalnie 60s, dla testów 10 min
	kTimeNonOccupacyPeriod = 1800000, //Normalnie 1800 sek
	kTimeMonitoring = 100
};

enum TypeChannel {
	kUnavailableChannel = -1,
	kAvailableChannel = 0,
	kOperatingChannel = 1,
	kUsableChannel = 2,
};

enum TypePRF {
	kStartPRF = 0,
	kStopPRF,
};

enum TimePRF {
	//kTimePRF = 1.818,
	kTimeNextElevationPRF = 25500,
	kTimeNextSekvencePRF = 300000,
};

enum TypeEventMemoryRadar {
	kStartTransmission = 0,
	kStopTransmission,
};