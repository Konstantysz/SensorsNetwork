#pragma once
#include "Sensor.h"

#include <random>

namespace NetworkSystem
{
    class PositionSensor :
        public Sensor
    {
    public:
        PositionSensor(double frequency);

        [[nodiscard]] std::string GetData() const override;
    };
} // namespace NetworkSystem
