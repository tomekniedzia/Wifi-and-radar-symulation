#pragma once

class Event				//klasa reprezentuj¹ca zdarzenia
{
public:

	Event(double system_time, double generate_time);
	
	virtual ~Event() = default;

	virtual void Execute() = 0;
	double ReturnEventTime() const;

private:

	double event_time_ = 0;
};

