//
// Created by dzmitry on 22.12.2021.
//

#ifndef GAME_IPARTICLEBUFFER_HPP
#define GAME_IPARTICLEBUFFER_HPP

#include <vec2.hpp>
#include <vec4.hpp>

class IParticleBuffer
{
public:
    struct ParticleData
    {
        glm::vec4 color;
        glm::vec2 velocity;
        glm::vec2 pos;
    };

    ~IParticleBuffer() = default;
};


#endif //GAME_IPARTICLEBUFFER_HPP
