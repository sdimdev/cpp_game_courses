//
// Created by dzmitry on 22.12.2021.
//

#ifndef GAME_GLPARTICALPROGRAM_HPP
#define GAME_GLPARTICALPROGRAM_HPP


#include <cstdint>
#include "GLProgram.hpp"

class GLParticalProgram: public GLProgram
{
public:
    explicit GLParticalProgram(const char* vs);
    ~GLParticalProgram();

protected:
    uint32_t vertexShader;
    //uint32_t fragmentShader;
};


#endif //GAME_GLPARTICALPROGRAM_HPP
