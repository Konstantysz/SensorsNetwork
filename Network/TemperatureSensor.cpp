#include "pch.h"
#include "TemperatureSensor.h"

namespace NetworkSystem
{
	TemperatureSensor::TemperatureSensor(double frequency) : Sensor(frequency)
	{
	}

	std::string TemperatureSensor::GetData() const
	{
		const auto lowerTemperatureLimit = 15.0;
		const auto higherTemperatureLimit = 25.0;

		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> dist(lowerTemperatureLimit, higherTemperatureLimit);

		return "T: " + std::to_string(dist(mt)) + " [degC]";
	}
} // namespace NetworkSystem

