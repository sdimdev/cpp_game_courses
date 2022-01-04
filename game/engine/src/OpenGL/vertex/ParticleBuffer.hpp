//
// Created by dzmitry on 22.12.2021.
//

#ifndef GAME_PARTICLEBUFFER_HPP
#define GAME_PARTICLEBUFFER_HPP


#include <vector>
#include <memory>
#include "entity/IParticleBuffer.hpp"

class ParticleBuffer : public IParticleBuffer
{
public:
    ParticleBuffer(std::vector<ParticleData> data);
    ParticleBuffer(size_t count);
    void addData(ParticleData data);

    ~ParticleBuffer() = default;

private:
    uint32_t _VAO = 0;
    uint32_t _VBO = 0;

    uint32_t count = 0;
    uint32_t capacity = 0;
    uint32_t curpos = 0;

    bool isDynamic = false;


    struct Pimpl;
    std::shared_ptr<Pimpl> _pimpl;

    void draw();
};


#endif //GAME_PARTICLEBUFFER_HPP
