#include "tick_manager.h"

#include "tickable.h"
#include "tick_report.h"

#include <memory>
#include <thread>
#include <chrono>

using namespace std;

int main(int argv, char** argc){
    TickManager::getInstance().toggle_tick(true);
    shared_ptr<Tickable> TR = std::dynamic_pointer_cast<Tickable>(std::make_shared<TickReport>());
    TickManager::getInstance().add(TR);

    // TEST SLEEP FOR 10 SECONDS
    std::this_thread::sleep_for (std::chrono::seconds(10));

    TickManager::getInstance().shut_down();
}