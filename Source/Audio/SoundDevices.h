#ifndef _SOUND_DEVICES_H_
#define _SOUND_DEVICES_H_

#include "../Common.h"
#include "../LogSystem.h"
#include <AL/alc.h>

class SoundDevices {
public:
    static SoundDevices* get();
    std::string getName() {
        return deviceName;
    }
private:
    SoundDevices();
    ~SoundDevices();

    ALCdevice* ptr_ALCdevice;
    ALCcontext* ptr_ALCcontext;
    std::string deviceName;
};

#endif