#include "tick_manager.h"

#include <chrono>


TickManager::TickManager(){
    this->tick_loop = std::thread(&TickManager::_internal_loop, this);
}

TickManager::TickManager(){
    ticking = false;
    shutdown = true;
    this->tick_loop.join();
}

void TickManager::add(std::shared_ptr<Tickable> T){
    this->add_queue.push(T);
}

void TickManager::remove(std::shared_ptr<Tickable> T){
    this->remove_queue.push(T);
}

void TickManager::toggle_tick(bool tick){
    this->ticking = tick;
}

void TickManager::_internal_add(){
    this->registered_ticks.insert(this->add_queue.pop());
}

void TickManager::_internal_remove(){
    if(this->remove_queue.empty()) return;
    this->registered_ticks.insert(this->remove_queue.pop());
}

void TickManager::_internal_loop(){
    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;
    std::chrono::duration<double, std::milli> delta;

    while(!shutdown){
        
        while(ticking){
            t1 = std::chrono::high_resolution_clock::now();

            for(auto elem : this->registered_ticks){
                elem->Tick();
            }
            
            while(!this->remove_queue.empty()){
                this->_internal_remove();
            }

            while(!this->add_queue.empty()){
                this->_internal_add();
            }

            t2 = std::chrono::high_resolution_clock::now();
            delta = t2 - t1;
            std::this_thread::sleep_for(std::chrono::milliseconds(tick_delay_ms - delta.count()));
        }
    }
}