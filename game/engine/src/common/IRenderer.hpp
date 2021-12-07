//
// Created by dzmitry on 19.11.2021.
//

#ifndef GAME_IRENDERER_HPP
#define GAME_IRENDERER_HPP

#include <vector>
#include <bitmap/Bitmap.hpp>
#include <entity/MeshData.hpp>

class IVertexBuffer;

class IShaderProgram;

class ITexture;

class IRenderer
{

public:
    struct Command
    {
        std::shared_ptr<IVertexBuffer> vertexBuffer;
        std::shared_ptr<IShaderProgram> program;
    };

    void addCommand(Command command) const
    {
        commands.push_back(std::move(command));
    }

    virtual void draw() = 0;

    virtual void startDrawing() = 0;

    virtual void endDrawing() = 0;

    virtual std::shared_ptr<IVertexBuffer> createVertexBuffer(MeshData data) = 0;

    virtual std::shared_ptr<IShaderProgram> createProgram(std::string_view name) = 0;

    virtual std::shared_ptr<ITexture> createTexture(Bitmap bitmap) = 0;

protected:
    mutable std::vector<Command> commands;
};


#endif //GAME_IRENDERER_HPP
