#include "SoundManager.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

SoundManager& SoundManager::GetInstance() {
    static SoundManager instance;
    return instance;
}

bool SoundManager::Initialize() {
    // Open the default audio device
    device = alcOpenDevice(nullptr);
    if (!device) {
        std::cerr << "Failed to open audio device" << std::endl;
        return false;
    }

    // Create and set the audio context
    context = alcCreateContext(device, nullptr);
    if (!context) {
        std::cerr << "Failed to create audio context" << std::endl;
        alcCloseDevice(device);
        return false;
    }

    if (!alcMakeContextCurrent(context)) {
        std::cerr << "Failed to make audio context current" << std::endl;
        alcDestroyContext(context);
        alcCloseDevice(device);
        return false;
    }

    // Set default listener properties
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    float orientation[] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };
    alListenerfv(AL_ORIENTATION, orientation);

    return !CheckALError("Initialization");
}

void SoundManager::Cleanup() {
    // Stop and delete all sources
    for (auto source : sources) {
        alSourceStop(source);
        alDeleteSources(1, &source);
    }
    sources.clear();

    // Delete all buffers
    for (const auto& pair : soundBuffers) {
        alDeleteBuffers(1, &pair.second);
    }
    soundBuffers.clear();

    // Cleanup OpenAL context and device
    if (context) {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(context);
        context = nullptr;
    }
    
    if (device) {
        alcCloseDevice(device);
        device = nullptr;
    }
}

SoundManager::~SoundManager() {
    Cleanup();
}

bool SoundManager::CheckALError(const char* operation) {
    ALenum error = alGetError();
    if (error != AL_NO_ERROR) {
        std::cerr << "OpenAL error during " << operation << ": " << error << std::endl;
        return true;
    }
    return false;
}

unsigned int SoundManager::CreateSource() {
    unsigned int source;
    alGenSources(1, &source);
    
    if (!CheckALError("source generation")) {
        sources.push_back(source);
        // Set default source properties for 2D sound
        alSource3f(source, AL_POSITION, 0.0f, 0.0f, 0.0f);
        alSource3f(source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
        alSourcei(source, AL_SOURCE_RELATIVE, AL_TRUE);  // Make the source relative to listener
        return source;
    }
    
    return 0;
}

// WAV file header structure
struct WAVHeader {
    char riff[4];          // "RIFF"
    unsigned int size;     // Size of the file minus 8 bytes
    char wave[4];          // "WAVE"
    char fmt[4];          // "fmt "
    unsigned int fmtSize;  // Size of the format chunk (16 for PCM)
    unsigned short format; // Audio format (1 for PCM)
    unsigned short channels; // Number of channels
    unsigned int sampleRate; // Sample rate
    unsigned int byteRate;   // Bytes per second
    unsigned short blockAlign; // Bytes per sample * number of channels
    unsigned short bitsPerSample; // Bits per sample
};

unsigned int SoundManager::LoadSound(const std::string& filename) {
    // Open the WAV file
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open sound file: " << filename << std::endl;
        return 0;
    }

    // Check if we already loaded this sound
    auto it = soundBuffers.find(filename);
    if (it != soundBuffers.end()) {
        return it->second;
    }

    // Read the WAV header
    WAVHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(WAVHeader));

    // Verify that it's a valid WAV file
    if (strncmp(header.riff, "RIFF", 4) != 0 || strncmp(header.wave, "WAVE", 4) != 0) {
        std::cerr << "Invalid WAV file: " << filename << std::endl;
        return 0;
    }

    // Find the data chunk
    char chunkID[4];
    unsigned int chunkSize;
    while (true) {
        file.read(chunkID, 4);
        file.read(reinterpret_cast<char*>(&chunkSize), 4);
        
        if (strncmp(chunkID, "data", 4) == 0) {
            break;
        }
        
        // Skip this chunk
        file.seekg(chunkSize, std::ios::cur);
    }

    // Read the sound data
    std::vector<char> data(chunkSize);
    file.read(data.data(), chunkSize);

    // Create OpenAL buffer
    unsigned int buffer;
    alGenBuffers(1, &buffer);

    // Determine format
    ALenum format;
    if (header.channels == 1) {
        format = (header.bitsPerSample == 8) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
    } else {
        format = (header.bitsPerSample == 8) ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
    }

    // Load data into buffer
    alBufferData(buffer, format, data.data(), chunkSize, header.sampleRate);
    
    if (CheckALError("buffer creation")) {
        alDeleteBuffers(1, &buffer);
        return 0;
    }

    // Store and return the buffer ID
    soundBuffers[filename] = buffer;
    return buffer;
}

void SoundManager::UnloadSound(unsigned int buffer) {
    // Find and remove the buffer from our map
    for (auto it = soundBuffers.begin(); it != soundBuffers.end(); ++it) {
        if (it->second == buffer) {
            alDeleteBuffers(1, &buffer);
            soundBuffers.erase(it);
            break;
        }
    }
}

unsigned int SoundManager::PlaySound(unsigned int buffer, float volume, bool loop) {
    // Create a new source
    unsigned int source = CreateSource();
    if (source == 0) {
        return 0;
    }

    // Set source properties
    alSourcei(source, AL_BUFFER, buffer);
    alSourcef(source, AL_GAIN, volume);
    alSourcei(source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
    
    // Play the sound
    alSourcePlay(source);
    
    if (CheckALError("sound playback")) {
        alDeleteSources(1, &source);
        return 0;
    }

    return source;
}

void SoundManager::StopSound(unsigned int source) {
    alSourceStop(source);
}

void SoundManager::PauseSound(unsigned int source) {
    alSourcePause(source);
}

void SoundManager::ResumeSound(unsigned int source) {
    alSourcePlay(source);
}

void SoundManager::SetVolume(unsigned int source, float volume) {
    alSourcef(source, AL_GAIN, volume);
}
