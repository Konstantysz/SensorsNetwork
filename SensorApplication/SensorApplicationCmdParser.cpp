#include "SensorApplicationCmdParser.h"

SensorApplicationCmdParser::SensorApplicationCmdParser(int argc, char** argv) : frameRate(0.0), type(NetworkSystem::SensorTypes::Unknown)
{
    if (argc != 5)
    {
        throw std::invalid_argument("Command line arguments must be equal to three.");
    }

    // First argument is application name so we start from second
    for (size_t i = 1; i < argc; ++i)
    {
        std::string argName = argv[i];
        std::string argValue = argv[i + 1];

        if (argumentsNames.count(argName) != 1)
        {
            throw std::invalid_argument("Argument named: " + argName +" is not handled by parser.");
        }

        if (argName == ArgumentNames::frameRateLong || argName == ArgumentNames::frameRateShort)
        {
            try
            {
                frameRate = std::stod(argValue);
            }
            catch (const std::exception& exception)
            {
                throw std::invalid_argument("Argument named: " + argName + " while converting to double returned exception: " + exception.what());
            }
        }

        if (argName == ArgumentNames::typeLong || argName == ArgumentNames::typeShort)
        {
            try
            {
                type = static_cast<NetworkSystem::SensorTypes>(std::stoul(argValue));
            }
            catch (const std::exception& exception)
            {
                throw std::invalid_argument("Argument named: " + argName + " while converting to unsigned returned exception: " + exception.what());
            }
        }

        i++;
    }
}

double SensorApplicationCmdParser::GetFramerate() const
{
    return frameRate;
}

NetworkSystem::SensorTypes SensorApplicationCmdParser::GetType() const
{
    return type;
}
