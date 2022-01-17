//
// Created by dzmitry on 29.11.2021.
//

#ifndef GAME_SPRITE_HPP
#define GAME_SPRITE_HPP


#include <vec2.hpp>
#include <engine/Engine.hpp>
#include "SpriteData.hpp"
#include <ext/matrix_float3x3.hpp>
#include "Node.hpp"
#include "ITextureMapSettable.hpp"

class Sprite : public Node, public ITextureMapSettable
{
public:
    explicit Sprite(std::shared_ptr<Engine> engine, std::string_view filepath);

    ~Sprite() override;

    std::shared_ptr<SpriteData> spriteData = nullptr;

    glm::mat3 getTransform() override;

    void setTexturePoint1(glm::vec2 point) override;

    void setTexturePoint2(glm::vec2 point) override;

    void drawNode() override;

    void visitNode() override;


protected:
    std::shared_ptr<Engine> engine;
};


#endif //GAME_SPRITE_HPP
