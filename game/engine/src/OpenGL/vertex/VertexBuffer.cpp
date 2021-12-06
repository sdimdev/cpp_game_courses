//
// Created by dzmitry on 05.12.2021.
//

#include <GL/glew.h>
#include "VertexBuffer.hpp"
#include <utils/GLUtils.cpp>

VertexBuffer::VertexBuffer(const Engine &engine,
                               MeshData data)
        : _engine(engine)
{
    glGenVertexArrays(1, &_VAO);

    glBindVertexArray(_VAO);

    glGenBuffers(1, &_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, data.points.size() * sizeof(Vertex), data.points.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2,
                          GL_FLOAT, GL_FALSE,  sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2,
                          GL_FLOAT, GL_FALSE,  sizeof(Vertex), (void*)offsetof(Vertex, textCoord));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 data.indexes.size() * sizeof(std::uint32_t),
                 data.indexes.data(), GL_STATIC_DRAW);

    checkErrors(__FILE__, __LINE__);
    _count = data.indexes.size();
}


void VertexBuffer::draw()
{
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, 0);

    checkErrors(__FILE__, __LINE__);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &_VBO);

    if (_IBO != 0)
    {
        glDeleteBuffers(1, &_IBO);
    }


#ifdef GLES
    glDeleteVertexArraysOES(1, &_VAO);
#else
    glDeleteVertexArrays(1, &_VAO);
#endif
    checkErrors(__FILE__, __LINE__);
}