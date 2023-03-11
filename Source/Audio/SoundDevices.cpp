#include "SoundDevices.h"

SoundDevices* SoundDevices::get() {
    static SoundDevices* device = new SoundDevices();
    return device;
}

SoundDevices::SoundDevices() {
    ptr_ALCdevice = alcOpenDevice(nullptr);
    if(!ptr_ALCdevice) logError("Error: Failed to get sound device!");

    ptr_ALCcontext = alcCreateContext(ptr_ALCdevice, nullptr);
    if(!ptr_ALCcontext) logError("Error: Failed to create ALC context!");

    if(!alcMakeContextCurrent(ptr_ALCcontext)) logError("Error: Failed to make ALC context!");

    const ALCchar* name = nullptr;
    if(alcIsExtensionPresent(ptr_ALCdevice, "ALC_ENUMERATE_ALL_EXT")) {
        name = alcGetString(ptr_ALCdevice, ALC_ALL_DEVICES_SPECIFIER);
    }
    if(!name || alcGetError(ptr_ALCdevice) != ALC_NO_ERROR) {
        name = alcGetString(ptr_ALCdevice, ALC_DEVICE_SPECIFIER);
    }
    logMessage("Success! Opened ", name);
    deviceName = std::string(name);
}

SoundDevices::~SoundDevices() {
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(ptr_ALCcontext);
    alcCloseDevice(ptr_ALCdevice);
}