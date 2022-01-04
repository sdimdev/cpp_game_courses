//
// Created by dzmitry on 22.12.2021.
//

#ifndef GAME_ISHADERBUFFER_HPP
#define GAME_ISHADERBUFFER_HPP


class IShaderBuffer
{
public:
    ~IShaderBuffer() = default;
    virtual void draw();
};


#endif //GAME_ISHADERBUFFER_HPP
