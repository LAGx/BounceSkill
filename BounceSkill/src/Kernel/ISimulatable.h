#pragma once
#include "Time.h"

// :)
struct ISimulatable {
	virtual void simulate(const TimeInfo&) = 0;
};