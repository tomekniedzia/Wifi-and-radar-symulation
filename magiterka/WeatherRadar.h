#pragma once
#include <cmath>
class WeatherRadar
{
public:
	WeatherRadar() = default;
	~WeatherRadar();

	void MoveRadar(double move_x, double move_y);

	double GetXRadar();
	double GetYRadar();
	void SetXRadar(double x_radar);
	void SetYRadar(double y_radar);
	int GetIndexPRF();
	void SetIndexPRF(int index);
	void DecIndexPRF();
	int GetIndexElevation();
	void SetIndexElevation(int index);
	void IncIndexElevation();
	

	double PowerFromAngle(double possition_ap, double possition_radar);
	bool AreSame(double a, double b);
	double PathLoss(double distance_ap, bool los);
	void SetActuallyPowerRadar(double actually_power);
	double GetActuallyPowerRadarDb();

	int GetNumberIteration();
	void IncrementNumberIteration();

private:

	double x_radar_ = -180.0;
	double y_radar_ = -180.0;
	const double elevation_[10] = { 0.5, 1.4, 2.4, 3.4, 5.3, 7.7, 10.6, 14.1, 18.5, 23.8 };
	int index_PRF_ = 11000;
	int index_elevation_ = 0;

	const double power_radar_w = 250000;
	const double power_radar_db = (53.979 + 30) / 2; //+30, bo dBm Przez dwa bo sumuje dB
	double actually_power_radar_db = -101;

	int number_iteration_ = 0;

	double h_bs = 35;	//wysokosc radaru
	double h_ms = 1.5;	//wysokosc odbiornika
	int fc = 5650;		//czestotliwosc
	double pl_c2;
	
	const double characteristic_x[91] = { -4.5, -4.4, -4.3, -4.2, -4.1, -4.0, -3.9, -3.8, -3.7, -3.6, -3.5, -3.4, -3.3, -3.2, -3.1, -3.0, -2.9, -2.8, -2.7, -2.6, -2.5, -2.4, -2.3, -2.2, -2.1, -2.0, -1.9, -1.8, -1.7, -1.6, -1.5, -1.4, -1.3, -1.2, -1.1, -1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0, 4.1, 4.2, 4.3, 4.4, 4.5 };
	const double characteristic_y[91] = { -40, -40, -40, -40, -40, -40, -40, -40, -38.2, -37, -36.8, -36.8, -36.2, -35.2, -33.6, -32.4, -32, -32.4, -33.8, -37, -40, -38.2, -34.2, -32.2, -30.6, -30.4, -31, -31.2, -30.4, -29.2, -28.5, -29.8, -40, -33.8, -24.4, -18, -13.2, -10.2, -7.4, -5.6, -3, -2.2, -1.2, -0.6, -0.2, 0, -0.2, -0.6, -1.2, -2.2, -3, -4.8, -6.8, -9, -11.8, -15.6, -20.8, -27.4, -37.8, -34, -31.2, -30.8, -31.4, -32, -32.4, -32.8, -33.8, -35.6, -37.6, -38.1, -35.4, -33.4, -32, -31.4, -31.4, -32.2, -33.6, -35, -36.2, -37, -37.2, -37.4, -38.6, -40, -40, -40, -40, -38.4, -37.6, -37.6, -38.2 };
};

