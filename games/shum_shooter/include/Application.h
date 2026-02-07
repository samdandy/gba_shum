#pragma once
#include <vector>
#include "layer.h"
#include "layer_stack.h"
#include <string>
#include <functional>
#include <mutex>

namespace shum
{

    class Application
    {
    public:
        void run();
        void push_layer(Layer* push_layer);
        void submit_to_main_thread(const std::function<void()>& function);
    private:
        void execute_main_thread_queue();
    private:


        LayerStack app_layer_stack;
        std::string app_name;
        std::vector<std::function<void()>> main_thread_queue;
		std::mutex main_thread_queue_mutex;
    };
}
