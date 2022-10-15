#include "pch.h"
#include "NetworkMainNode.h"

namespace NetworkSystem
{
	NetworkMainNode::NetworkMainNode(const NetworkData& sensorsData, size_t cyclicBufforSize) : cyclicBuffer(cyclicBufforSize), sensorsData(sensorsData)
	{
	}
	
	bool NetworkMainNode::RunNetwork()
	{
        auto sensorProcessCalls = std::vector<std::future<bool>>(sensorsData.size());
        for (int sensorId = 0; sensorId < sensorsData.size(); sensorId++)
        {
            sensorProcessCalls[sensorId] = std::async(
                std::launch::async,
                [&](size_t sensorId) -> bool
                {
                    if (!RunSingleSensor(sensorsData[sensorId].second, sensorsData[sensorId].first, sensorId))
                    {
                        std::cout << "Failed to run process for sensor: " + std::to_string(sensorId) << std::endl;
                        return false;
                    }

                    return true;
                },
                sensorId);
        }

        return true;
	}

    bool NetworkMainNode::RunSingleSensor(double frequency, NetworkSystem::SensorTypes type, size_t sensorId)
    {
        // Different commands for Linux and Windows
#if defined _WIN32 || defined __WIN64
        const auto execPath = GetCurrentExecutableDirectory() / "SensorApplication.exe";
        const auto command = std::string("\"\"") + execPath.string() + "\" -f " + std::to_string(frequency) + " -t " + std::to_string(static_cast<unsigned>(type)) + " 2>&1\"";
#define popen _popen
#define pclose _pclose
#else
        const auto execPath = std::filesystem::canonical("/proc/self/exe") / "SensorApplication.exe";
        const auto command = std::string("\"") + execPath.string() + "\" -f " + std::to_string(frequency) + " -t " + std::to_string(static_cast<unsigned>(type)) + " 2>&1";
#endif // _WIN32 || __WIN64

        try
        {
            const auto pipe = popen(command.c_str(), "r");
            if (pipe == nullptr)
            {
                std::cout << "Failed to create pipe to run command: " + command << std::endl;
                return false;
            }

            std::string commandResult;
            char lineBuffer[100ULL];

            while (!feof(pipe))
            {
                if (fgets(lineBuffer, 100ULL, pipe) != nullptr)
                {
                    LogSensorData(lineBuffer, sensorId);
                    commandResult += lineBuffer;
                }
            }

            if (pclose(pipe) != EXIT_SUCCESS)
            {
                std::cout << "Execution of command (" + command + ") failed. The command returned such output: " + commandResult << std::endl;
                return false;
            }
        }
        catch (std::exception& error)
        {
            std::cout << error.what() << std::endl;
            return false;
        }

        return true;

    }

    std::filesystem::path NetworkMainNode::GetCurrentExecutableDirectory() const
    {
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        std::string::size_type pos = std::string(buffer).find_last_of("\\/");

        return std::filesystem::path(std::string(buffer).substr(0, pos));
    }

    void NetworkMainNode::LogSensorData(const std::string& line, size_t sensorId, size_t idStringLength)
    {
        std::lock_guard<std::mutex> guard(loggerMutex);

        // Get time
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
        std::string formattedTime = ss.str();

        // Format sensor id
        std::string sensorIdString = std::to_string(sensorId);
        size_t precision = idStringLength - std::min<size_t>(idStringLength, sensorIdString.size());
        std::string sensorIdStringFormatted = std::string(precision, '0').append(sensorIdString);

        std::string formattedLog = "[" + formattedTime + "][" + sensorIdStringFormatted + "] " + line;
        std::cout << formattedLog << std::endl;

        cyclicBuffer.Push(formattedLog);
    }
}