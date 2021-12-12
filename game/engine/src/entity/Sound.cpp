//
// Created by dzmitry on 08.12.2021.
//

#include <SDL_rwops.h>
#include <stdexcept>
#include <SDL_audio.h>
#include <memory>

#include "Sound.hpp"

/* SDL_AudioFormat of files, such as s16 little endian */
#define AUDIO_FORMAT AUDIO_S16LSB
/* Frequency of the file */
#define AUDIO_FREQUENCY 48000
/* 1 mono, 2 stereo, 4 quad, 6 (5.1) */
#define AUDIO_CHANNELS 2
/* Specifies a unit of audio data to be used at a time. Must be a power of 2 */
#define AUDIO_SAMPLES 4096

struct Sound::Pimpl
{
    Uint8 *audio_chunk;
    Uint32 audio_len;
    Uint8 *audio_pos;
    SDL_AudioSpec want;
    SDL_AudioDeviceID audio_device_id;
};

Sound::Sound(std::string_view filepath)
{
    _pimpl = std::make_shared<Pimpl>();

    SDL_RWops *file = SDL_RWFromFile(filepath.data(), "rb");
    if (file == nullptr)
    {
        throw std::runtime_error("Filed to open file: " + std::string(filepath));
    }

    const int32_t allow_changes = 0;
    const int32_t is_capture_device = 0;


    const int32_t auto_delete_file = 1;
    uint8_t *sample_buffer_from_file = nullptr;
    uint32_t sample_buffer_len_from_file = 0;

    SDL_AudioSpec want;
    SDL_AudioSpec audioSpec{};
    SDL_AudioSpec *returned;

    SDL_memset(&want, 0, sizeof(want)); /* or SDL_zero(want) */
    want.freq = AUDIO_FREQUENCY;
    want.format = AUDIO_F32;
    want.channels = AUDIO_CHANNELS;
    want.samples = AUDIO_SAMPLES;
    want.callback = [](void *userdata, Uint8 *stream,
                       int len)
    {
        printf("lol");
    };  // you wrote this function elsewhere.
    const SDL_AudioSpec *loaded = SDL_LoadWAV_RW(file,
                                                 auto_delete_file,
                                                 &audioSpec,
                                                 &sample_buffer_from_file,
                                                 &sample_buffer_len_from_file);


    const char *name = nullptr;
    /* int devices_cound = SDL_GetNumAudioDevices(0);
     for (int i = 0; i < devices_cound; i++)
     {
         printf("SDL_GetAudioDeviceName: %s", SDL_GetAudioDeviceName(i, 0));
     }*/
    _pimpl->audio_device_id = SDL_OpenAudioDevice(
            name,
            is_capture_device,
            loaded,
            returned,
            allow_changes
    );

    printf("error: %s", SDL_GetError());

    if (returned == nullptr)
    {
        throw std::runtime_error("returned null");
    }
    if ( loaded->format != returned->format){
        printf("loaded: %d returned: %d\n", loaded->format, returned->format);
        throw std::runtime_error("incorrect formats");
    }
    if (
            loaded->format != returned->format ||
            loaded->channels != returned->channels ||
            loaded->freq != returned->freq)
    {
        throw std::runtime_error("FAIL");
    }

    printf("size %d\n", sizeof(loaded));
}

void Sound::play()
{

}

void Sound::pause()
{

}

void Sound::stop()
{

}

bool Sound::is_playing()
{
    return false;
}

