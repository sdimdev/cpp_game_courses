//
// Created by dzmitry on 08.12.2021.
//

#include <SDL_rwops.h>
#include <stdexcept>
#include <SDL_audio.h>
#include <memory>
#include <string>
#include <vector>

#include "Sound.hpp"

/* SDL_AudioFormat of files, such as s16 little endian */
#define AUDIO_FORMAT AUDIO_S16LSB
/* Frequency of the file */
#define AUDIO_FREQUENCY 48000
/* 1 mono, 2 stereo, 4 quad, 6 (5.1) */
#define AUDIO_CHANNELS 2
/* Specifies a unit of audio data to be used at a time. Must be a power of 2 */
#define AUDIO_SAMPLES 4096


namespace
{
    struct AudioBuf
    {
        uint8_t* start       = nullptr;
        size_t   size        = 0;
        size_t   current_pos = 0;
    };

    struct AudioManager
    {
        std::vector<AudioBuf> buffers;
    };

    static void audio_callback(void* userdata, uint8_t* stream, int len)
    {
        auto audioManager = static_cast<AudioManager*>(userdata);
        SDL_memset(stream, 0, len);
        for (auto& buffer : audioManager->buffers)
        {
            //TODO: check is playing or pause
            //TODO: looping

            auto amount = buffer.size - buffer.current_pos;
            if ( amount > len )
            {
                amount = len;
            }

            SDL_MixAudioFormat(stream,
                               buffer.start + buffer.current_pos,
                               AUDIO_S16LSB,
                               amount,
                               SDL_MIX_MAXVOLUME);

            buffer.current_pos += amount;

            if (buffer.current_pos >= buffer.size)
            {
                buffer.current_pos = 0;
            }
        }
    }
}


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

    SDL_AudioSpec audioSpecFromFile{};
    const int32_t auto_delete_file            = 1;
    uint8_t*      sample_buffer_from_file     = nullptr;
    uint32_t      sample_buffer_len_from_file = 0;

    SDL_AudioSpec* audio_spec = SDL_LoadWAV_RW(file,
                                               auto_delete_file,
                                               &audioSpecFromFile,
                                               &sample_buffer_from_file,
                                               &sample_buffer_len_from_file);

    if (audio_spec == nullptr)
    {
        throw std::runtime_error(std::string(filepath) + " can't parse and load audio samples from file");
    }

    const int32_t allow_changes = 0;
    const char*   device_name       = nullptr;
    const int32_t is_capture_device = 0;

    static AudioManager audioManager;
    AudioBuf buf;
    buf.start = sample_buffer_from_file;
    buf.size = sample_buffer_len_from_file;
    buf.current_pos = 0;
    audioManager.buffers.push_back(buf);

    audioSpecFromFile.callback = audio_callback;
    audioSpecFromFile.userdata = &audioManager;

    SDL_AudioSpec returned{};
    SDL_AudioDeviceID audio_device_id = SDL_OpenAudioDevice(
            device_name, is_capture_device, &audioSpecFromFile, &returned, allow_changes);
    if (audio_device_id == 0)
    {
        throw std::runtime_error("Can't open Audio Device");
    }

    if (audioSpecFromFile.format != returned.format ||
        audioSpecFromFile.channels != returned.channels || audioSpecFromFile.freq != returned.freq)
    {
        throw std::runtime_error("Audio Device doesn't support our format");
    }

    SDL_PauseAudioDevice(audio_device_id, SDL_FALSE);
   /* _pimpl->audio_device_id = SDL_OpenAudioDevice(
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

    printf("size %d\n", sizeof(loaded));*/
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

