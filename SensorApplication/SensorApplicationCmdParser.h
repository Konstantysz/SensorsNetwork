#pragma once

#include "NetworkConstants.h"

#include <set>
#include <string>
#include <stdexcept>

namespace ArgumentNames
{
	static const std::string frameRateLong = "--frameRate";
	static const std::string typeLong = "--type";
	static const std::string frameRateShort = "-f";
	static const std::string typeShort = "-t";
}

class SensorApplicationCmdParser
{
public:
	SensorApplicationCmdParser(int argc, char** argv);

	[[nodiscard]] double GetFramerate() const;

	[[nodiscard]] NetworkSystem::SensorTypes GetType() const;

private:
	const std::set<std::string> argumentsNames = { ArgumentNames::frameRateLong, ArgumentNames::typeLong, ArgumentNames::frameRateShort, ArgumentNames::typeShort };
	double frameRate;
	NetworkSystem::SensorTypes type;
};

