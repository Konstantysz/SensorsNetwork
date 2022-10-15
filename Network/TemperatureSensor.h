#pragma once
#include "Sensor.h"

#include <random>

namespace NetworkSystem
{
	class TemperatureSensor :
		public Sensor
	{
	public:
		TemperatureSensor(double frequency);

		[[nodiscard]] std::string GetData() const override;
	};
} // namespace NetworkSystem
