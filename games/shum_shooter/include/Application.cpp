#pragma once
#include "Application.h"

namespace shum
{
    void Application::run()
    {
        // Application run logic
    }


    void Application::execute_main_thread_queue()
    {
        std::scoped_lock<std::mutex> lock(main_thread_queue_mutex);

        for (auto& function : main_thread_queue)
        {
            function();
        }

        main_thread_queue.clear();
    }

    void Application::submit_to_main_thread(const std::function<void()>& function)
	{
		std::scoped_lock<std::mutex> lock(main_thread_queue_mutex);

		main_thread_queue.emplace_back(function);
	}

    void Application::push_layer(Layer* layer)
    {
        app_layer_stack.PushLayer(layer);
    }
}
