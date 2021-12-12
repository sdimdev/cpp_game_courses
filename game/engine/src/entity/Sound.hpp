//
// Created by dzmitry on 08.12.2021.
//

#ifndef GAME_SOUND_HPP
#define GAME_SOUND_HPP


#include <string_view>

class Sound
{
public:
    void play();
    void pause();
    void stop();
    bool is_playing();
    explicit Sound(std::string_view filename);
private:
    struct Pimpl;
    std::shared_ptr<Pimpl> _pimpl;
};


#endif //GAME_SOUND_HPP
