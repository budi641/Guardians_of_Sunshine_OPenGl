#pragma once
#include <chrono>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point lastTime;
    float deltaTime;

public:
    Timer();

    void Update();

    float GetDeltaTime() const;

    float GetCurrentTime() const;
};
