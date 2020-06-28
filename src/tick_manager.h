#pragma once

#include "singleton.h"
#include "tickable.h"
#include "tsqueue.h"

#include <set>
#include <memory>
#include <thread>

class TickManager {
public:
    static TickManager& getInstance()
    {
        static TickManager instance; // Guaranteed to be destroyed.
                                // Instantiated on first use.
        return instance;
    }

    void toggle_tick(bool tick);
    void tick_rate(int delay_ms);
    void add(std::shared_ptr<Tickable> T);
    void remove(std::shared_ptr<Tickable> T);
private:
    TickManager();
    ~TickManager();
    // Runs as thread, killed via ticking == false, shutdown == true
    void _internal_tick();
    void _internal_add();
    void _internal_remove();
    void _internal_loop();

    std::thread tick_loop;
    bool shutdown = false;
    bool ticking = false;
    double tick_delay_ms = 250;
    Tsqueue<std::shared_ptr<Tickable>> add_queue;
    Tsqueue<std::shared_ptr<Tickable>> remove_queue;
    std::set<std::shared_ptr<Tickable>> registered_ticks;
public:
    TickManager(TickManager const&)     = delete;
    void operator=(TickManager const&)  = delete;
};