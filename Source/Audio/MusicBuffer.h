#ifndef _MUSIC_BUFFER_H_
#define _MUSIC_BUFFER_H_

#include "../Common.h"
#include "../LogSystem.h"
#include <AL/al.h>
#include <sndfile.h>

class MusicBuffer {
public:
    void play();
    void pause();
    void stop();
    void resume();

    ALint getSource();

    void updateBufferStream();
    bool isPlaying();
    MusicBuffer(const char* file);
    ~MusicBuffer();

private:

    ALuint  ptr_Source;
    static const int bufferSamples = 8192;
    static const int numBuffers = 4;
    ALuint  ptr_Buffers[numBuffers];
    SNDFILE* ptr_sndFile;
    SF_INFO ptr_sfInfo;
    short* ptr_MemBuf;
    ALenum ptr_Format;

    MusicBuffer() = delete;
};

#endif