#pragma once

#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <string>
#include <unordered_map>
#include <vector>

class SoundManager {
public:
    static SoundManager& GetInstance();
    
    // Initialize and cleanup
    bool Initialize();
    void Cleanup();
    
    // Sound loading and management
    unsigned int LoadSound(const std::string& filename);
    void UnloadSound(unsigned int buffer);
    
    // Playback control
    unsigned int PlaySound(unsigned int buffer, float volume = 1.0f, bool loop = false);
    void StopSound(unsigned int source);
    void PauseSound(unsigned int source);
    void ResumeSound(unsigned int source);
    
    // Volume control
    void SetVolume(unsigned int source, float volume);
    
private:
    SoundManager() = default;  // Private constructor for singleton
    ~SoundManager();
    
    // Prevent copying
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;
    
    // OpenAL device and context
    ALCdevice* device = nullptr;
    ALCcontext* context = nullptr;
    
    // Sound resources
    std::unordered_map<std::string, unsigned int> soundBuffers;
    std::vector<unsigned int> sources;
    
    // Helper functions
    bool CheckALError(const char* operation);
    unsigned int CreateSource();
};
