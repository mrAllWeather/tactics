#pragma once

#include "tickable.h"
#include <iostream>

class TickReport : public Tickable {
public:
    TickReport(){}
    void Tick() {
        std::cout << "Tick";
    }    
};