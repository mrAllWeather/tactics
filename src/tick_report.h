#pragma once

#include "tickable.h"
#include <iostream>
#include <chrono>  // chrono::system_clock
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time
#include <string>  // string

class TickReport : public Tickable {
public:
    TickReport(){}
    void Tick() {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
        std::cerr << ss.str() << "\tTickReport::Tick\tTick\n";
    }    
};