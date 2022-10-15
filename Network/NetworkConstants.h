#pragma once
#include <limits>

namespace NetworkSystem
{
	enum class SensorTypes : unsigned
	{
		Temperature = 0U,
		Position,
		Unknown = std::numeric_limits<unsigned>::max()
	};
}