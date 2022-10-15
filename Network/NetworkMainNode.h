#pragma once
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#include "CyclicBuffer.h"
#include "NetworkConstants.h"

#if defined _WIN32 || defined __WIN64
#include <Windows.h>
#endif // _WIN32 || __WIN64
#include <filesystem>
#include <iostream>
#include <queue>
#include <string>
#include <future>
#include <algorithm>
#include <sstream>

namespace NetworkSystem
{
	typedef std::vector<std::pair<NetworkSystem::SensorTypes, double>> NetworkData;

	class NetworkMainNode
	{
	public:
		NetworkMainNode(const NetworkData& sensorsData, size_t cyclicBufforSize);

		bool RunNetwork();

	private:
		bool RunSingleSensor(double frequency, NetworkSystem::SensorTypes type, size_t sensorId);

		[[nodiscard]] std::filesystem::path GetCurrentExecutableDirectory() const;

		void LogSensorData(const std::string& line, size_t sensorId, size_t idStringLength = 6ULL);

		NetworkSystem::CyclicBuffer cyclicBuffer;
		NetworkData sensorsData;
		std::mutex loggerMutex;
	};
}

