//
// Created by dzmitry on 05.12.2021.
//

#include <GL/glew.h>
#include "VertexBuffer.hpp"
#include <utils/GLUtils.cpp>

VertexBuffer::VertexBuffer(MeshData data)
{
    glGenVertexArrays(1, &_VAO);

    glBindVertexArray(_VAO);

    glGenBuffers(1, &_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, data.points.size() * sizeof(Vertex), data.points.data(), GL_STATIC_DRAW);
    printf("vertex count %d\n", data.points.size());
    //указываем выравнивае видеокарте

    glVertexAttribPointer(
            0, //номер поля
            2, // сколько в поле компонентов
            GL_FLOAT, //тип
            GL_FALSE, // нормализация обрезка от [-1,1]
            sizeof(Vertex),//страйт? расстояние между двумя соседними элементами в массиве
            reinterpret_cast<void *> (offsetof(Vertex, position))
            //reinterpret_cast<void *>(0) //смещение от начала структуры offsetof(Vertex, x);
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
            1, //номер поля
            2, // сколько в поле компонентов
            GL_FLOAT, //тип
            GL_FALSE, // нормализация обрезка от [-1,1]
            sizeof(Vertex),//страйт? расстояние между двумя соседними элементами в массиве
            reinterpret_cast<void *> (offsetof(Vertex, textCoord))
    );
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 data.indexes.size() * sizeof(std::uint32_t),
                 data.indexes.data(), GL_STATIC_DRAW);

    checkErrors(__FILE__, __LINE__);
    _count = data.indexes.size();
    printf("indexes count %d\n", _count);
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