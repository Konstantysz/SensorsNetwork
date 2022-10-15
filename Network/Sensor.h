#pragma once
#include <string>
#include <stdexcept>

namespace NetworkSystem
{
	class Sensor
	{
	public:
		Sensor(double frequency);

		virtual std::string GetData() const = 0;

		[[nodiscard]] double GetAcquisitionFrequency() const;

		[[nodiscard]] double GetAcquisitionPeriod() const;

	private:
		double acquisitionFrequency;
	};
} // namespace NetworkSystem

