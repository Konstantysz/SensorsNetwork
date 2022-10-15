#include "pch.h"
#include "Sensor.h"

namespace NetworkSystem
{
	Sensor::Sensor(double frequency) : acquisitionFrequency(frequency)
	{
		if (acquisitionFrequency <= 0.0)
		{
			throw std::invalid_argument("Sensor acquisition frequency has to be positive number.");
		}
	}

	double Sensor::GetAcquisitionFrequency() const
	{
		return acquisitionFrequency;
	}
	double Sensor::GetAcquisitionPeriod() const
	{
		return 1.0 / acquisitionFrequency;
	}
} // namespace NetworkSystem

