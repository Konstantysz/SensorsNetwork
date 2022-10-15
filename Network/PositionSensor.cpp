#include "pch.h"
#include "PositionSensor.h"

namespace NetworkSystem
{
	PositionSensor::PositionSensor(double frequency) : Sensor(frequency)
	{
	}

	std::string PositionSensor::GetData() const
	{
		const auto lowerPositionLimit = 15.0;
		const auto higherPositionLimit = 25.0;

		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> dist(lowerPositionLimit, higherPositionLimit);

		return "X: " + std::to_string(dist(mt)) + ", Y: " + std::to_string(dist(mt)) + ", Z: " + std::to_string(dist(mt)) + " [mm]";
	}
} // namespace NetworkSystem
