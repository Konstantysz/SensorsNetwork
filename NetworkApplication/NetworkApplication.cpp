#include "NetworkMainNode.h"

#include <iostream>

int main(int argc, char** argv)
{
	const auto bufforSize = 100ULL;
	const NetworkSystem::NetworkData sensorsData = { 
		{ NetworkSystem::SensorTypes::Temperature, 5.0 }, 
		{ NetworkSystem::SensorTypes::Temperature, 10.0 }, 
		{ NetworkSystem::SensorTypes::Temperature, 20.0 },
		{ NetworkSystem::SensorTypes::Position, 1.0 },
		{ NetworkSystem::SensorTypes::Position, 2.0 } };

	auto network = NetworkSystem::NetworkMainNode(sensorsData, bufforSize);

	network.RunNetwork();

	return 0;
}