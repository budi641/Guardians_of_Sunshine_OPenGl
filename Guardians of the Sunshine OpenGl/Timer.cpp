#include "Timer.h"

Timer::Timer() : deltaTime(0.0f) {
    lastTime = std::chrono::high_resolution_clock::now();
}

void Timer::Update() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsedTime = currentTime - lastTime;
    deltaTime = elapsedTime.count();
    lastTime = currentTime;
}

float Timer::GetDeltaTime() const {
    return deltaTime;
}

float Timer::GetCurrentTime() const {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsedTime = currentTime.time_since_epoch();
    return elapsedTime.count();
}
