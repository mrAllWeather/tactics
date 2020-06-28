#include "tick_manager.h"
#include "tick_report.h"

#include <memory>
#include <thread>
#include <chrono>

using namespace std;

int main(int argv, char** argc){
    TickManager::getInstance().toggle_tick(true);
    shared_ptr<Tickable> TR = shared_ptr<TickReport>();

    TickManager::getInstance().add(TR);

    for (int i=10; i>0; --i) {
        std::this_thread::sleep_for (std::chrono::seconds(1));
    }

    TickManager::getInstance().shut_down();
}