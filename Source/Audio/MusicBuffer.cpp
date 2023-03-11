#include "MusicBuffer.h"
#include <cstddef>
#include <AL/alext.h>
#include <malloc.h>

void MusicBuffer::play() {
    ALsizei i;

    alGetError();

    alSourceRewind(ptr_Source);
    alSourcei(ptr_Source, AL_BUFFER, 0);

    for(i = 0; i < numBuffers; i++) {
        sf_count_t slen = sf_readf_short(ptr_sndFile, ptr_MemBuf, bufferSamples);
        if(slen < 1) break;
        slen *= ptr_sfInfo.channels * (sf_count_t)sizeof(short);
        alBufferData(ptr_Buffers[i], ptr_Format, ptr_MemBuf, (ALsizei)slen, ptr_sfInfo.samplerate);
    }

    if(alGetError() != AL_NO_ERROR) {
        logError("Error: Failed buffering for playback");
    }

    alSourceQueueBuffers(ptr_Source, i, ptr_Buffers);
    alSourcePlay(ptr_Source);
    if(alGetError() != AL_NO_ERROR) {
        logError("Error: Failed starting playback");
    }
 
 }

 void MusicBuffer::updateBufferStream() {
    ALint processed, state;

    alGetError();

    alGetSourcei(ptr_Source, AL_SOURCE_STATE, &state);
    alGetSourcei(ptr_Source, AL_BUFFERS_PROCESSED, &processed);
    if(alGetError() != AL_NO_ERROR) {
        logError("Error: Failed checking music source state");
    }

    while(processed > 0) {
        ALuint  bufferID;
        sf_count_t slen;

        alSourceUnqueueBuffers(ptr_Source, 1, &bufferID);
        processed--;

        slen = sf_readf_short(ptr_sndFile, ptr_MemBuf, bufferSamples);
        if(slen > 0) {
            slen *= ptr_sfInfo.channels * (sf_count_t)sizeof(short);
            alBufferData(bufferID, ptr_Format, ptr_MemBuf, (ALsizei)slen, ptr_sfInfo.samplerate);
            alSourceQueueBuffers(ptr_Source, 1, &bufferID);
        }
        if(alGetError() != AL_NO_ERROR) {
            logError("Error: Failed buffering music data");
        }
    }

    if(state != AL_PLAYING && state != AL_PAUSED) {
        ALint quered;

        alGetSourcei(ptr_Source, AL_BUFFERS_QUEUED, &quered);
        if(quered == 0) {
            return;
        }
        alSourcePlay(ptr_Source);
        if(alGetError() != AL_NO_ERROR) {
            logError("Error: Failed restarting music playback");
        }
    }
 }

 ALint MusicBuffer::getSource() {
    return ptr_Source;
 }

 MusicBuffer::MusicBuffer(const char* file) {
        alGenSources(1, &ptr_Source);
        alGenBuffers(numBuffers, ptr_Buffers);
        std::size_t frame_size;
        ptr_sndFile = sf_open(file, SFM_READ, &ptr_sfInfo);
        if(!ptr_sndFile) {
            logError("Error: Failed to load music file at path: ", file);
        }

        if(ptr_sfInfo.channels == 1) {
            ptr_Format = AL_FORMAT_MONO16;
        } else if(ptr_sfInfo.channels == 2) {
            ptr_Format = AL_FORMAT_STEREO16;
        } else if(ptr_sfInfo.channels == 3) {
            if(sf_command(ptr_sndFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT) {
                ptr_Format = AL_FORMAT_BFORMAT2D_16;
            }
        } else if(ptr_sfInfo.channels == 4) {
            if(sf_command(ptr_sndFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT) {
                ptr_Format = AL_FORMAT_BFORMAT3D_16;
            }
        }
        if(!ptr_Format) {
            sf_close(ptr_sndFile);
            ptr_sndFile = NULL;
            logError("Error: Unsupported channel count from file", file);
        }

        frame_size = ((size_t)bufferSamples * (size_t)ptr_sfInfo.channels) * sizeof(short);
        ptr_MemBuf = static_cast<short*>(malloc(frame_size));
 }

 MusicBuffer::~MusicBuffer() {
        alDeleteSources(1, &ptr_Source);
        if(ptr_sndFile) sf_close(ptr_sndFile);
        ptr_sndFile = nullptr;
        free(ptr_MemBuf);
        alDeleteBuffers(numBuffers, ptr_Buffers);
 }