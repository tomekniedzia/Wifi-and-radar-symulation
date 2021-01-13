
#include "Event.h"



Event::Event(double system_time, double generate_time)
{
	//generator czasu pojawienia siê zdarzenia
	event_time_ = generate_time + system_time;
	//std::cout << "event time = " << event_time_ << std::endl;
}

double Event::ReturnEventTime() const
{
	return event_time_;
}