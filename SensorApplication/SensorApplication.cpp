#include "SensorApplicationCmdParser.h"
#include "TemperatureSensor.h"
#include "PositionSensor.h"

#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

int main(int argc, char** argv)
{
    std::shared_ptr<NetworkSystem::Sensor> sensor;
    try
    {
        const auto parser = SensorApplicationCmdParser(argc, argv);

        switch (parser.GetType())
        {
        case NetworkSystem::SensorTypes::Temperature:
        {
            sensor = std::make_shared<NetworkSystem::TemperatureSensor>(parser.GetFramerate());
            break;
        }
        case NetworkSystem::SensorTypes::Position:
        {
            sensor = std::make_shared<NetworkSystem::PositionSensor>(parser.GetFramerate());
            break;
        }
        case NetworkSystem::SensorTypes::Unknown:
        {
            std::cout << "Unhandled sensor type parsed by parser." << std::endl;
            return -1;
        }
        default:
        {
            std::cout << "Unhandled sensor type parsed by parser." << std::endl;
            return -1;
        }
        }
    }
    catch (const std::invalid_argument& exception)
    {
        std::cout << exception.what() << std::endl;
        return -1;
    }

    for (;;)
    {
        std::cout << sensor->GetData() << std::endl;

        // Simulation of frequency of acquisition
        std::chrono::duration<double> chrono_seconds{ sensor->GetAcquisitionPeriod() };
        std::this_thread::sleep_for(chrono_seconds);
    }

    return 0;
}