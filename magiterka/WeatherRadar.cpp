#include "WeatherRadar.h"



WeatherRadar::~WeatherRadar()
{
}

void WeatherRadar::MoveRadar(double move_x, double move_y)
{
	x_radar_ += move_x;
	y_radar_ += move_y;
}

double WeatherRadar::GetXRadar()
{
	return x_radar_;
}

double WeatherRadar::GetYRadar()
{
	//return y_radar_;
	return elevation_[index_elevation_];
}

void WeatherRadar::SetXRadar(double x_radar)
{
	while (x_radar > 180)
		x_radar -= 360;
	x_radar_ = x_radar;
}

void WeatherRadar::SetYRadar(double y_radar)
{
	while (y_radar > 180)
		y_radar -= 360;
	y_radar_ = y_radar;
}

void WeatherRadar::SetIndexPRF(int index)
{
	index_PRF_ = index;
}

int WeatherRadar::GetIndexPRF()
{
	return index_PRF_;
}

void WeatherRadar::DecIndexPRF()
{
	index_PRF_--;
}

int WeatherRadar::GetIndexElevation()
{
	return index_elevation_;
}

void WeatherRadar::SetIndexElevation(int index)
{
	index_elevation_ = index;
}

void WeatherRadar::IncIndexElevation()
{
	index_elevation_++;
}

double WeatherRadar::PowerFromAngle(double possition_ap, double possition_radar)
{
	if (fabs(possition_ap-possition_radar) > 4.5) {
		return power_radar_db - (10 * fabs(possition_ap - possition_radar));//?
	}
	else
	{
		int i = 0;
		while (possition_radar - possition_ap >= characteristic_x[i])
		{
			i++;
		}
		if (AreSame(possition_ap - possition_radar, characteristic_x[i]))
			return power_radar_db + characteristic_y[i];
		return power_radar_db + ((characteristic_y[i - 1] + characteristic_y[i]) / 2);
	}
}

bool WeatherRadar::AreSame(double a, double b)
{
	//Sprawdza czy dwa double s¹ takie same
	return fabs(a - b) < 0.0001;
}

double WeatherRadar::PathLoss(double distance_ap, bool los)
{
	if (los)
		pl_c2 = 40 * log10(distance_ap) + 13.47 - 14 * log10(h_bs) - 14 * log10(h_ms) + 6 * log10(fc / 5);
	else
		pl_c2 = (44.9 - 6.55 * log10(h_bs)) * log10(distance_ap) + 34.46 + 5.83 * log10(h_bs) + 23 * log10(fc / 5);

	return pl_c2 + 17.4 + 0.5 * 5 - 0.8 * h_ms;
}

void WeatherRadar::SetActuallyPowerRadar(double actually_power)
{
	actually_power_radar_db = actually_power;
}

double WeatherRadar::GetActuallyPowerRadarDb()
{
	return actually_power_radar_db;
}

int WeatherRadar::GetNumberIteration()
{
	return number_iteration_;
}

void WeatherRadar::IncrementNumberIteration()
{
	number_iteration_ ++;
}

