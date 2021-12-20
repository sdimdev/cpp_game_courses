//
// Created by dzmitry on 05.12.2021.
//

#include <GL/glew.h>
#include "VertexBuffer.hpp"
#include <utils/GLUtils.cpp>

struct VertexBuffer::Pimpl
{
    //todo remove it
    MeshData* data;
};
VertexBuffer::VertexBuffer(MeshData data)
{
    _pimpl = std::make_shared<Pimpl>();
    _pimpl->data = &data;
    glGenVertexArrays(1, &_VAO);
    checkErrors(__FILE__, __LINE__);

    glBindVertexArray(_VAO);

    glGenBuffers(1, &_VBO);
    checkErrors(__FILE__, __LINE__);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    checkErrors(__FILE__, __LINE__);
    glEnableVertexAttribArray(0);
    checkErrors(__FILE__, __LINE__);
    glVertexAttribPointer(
            0, //номер поля
            2, // сколько в поле компонентов
            GL_FLOAT, //тип
            GL_FALSE, // нормализация обрезка от [-1,1]
            sizeof(Vertex),//страйт? расстояние между двумя соседними элементами в массиве
            reinterpret_cast<void *> (offsetof(Vertex, position))
            //reinterpret_cast<void *>(0) //смещение от начала структуры offsetof(Vertex, x);
    );
    checkErrors(__FILE__, __LINE__);
    glEnableVertexAttribArray(1);
    checkErrors(__FILE__, __LINE__);
    glVertexAttribPointer(
            1, //номер поля
            2, // сколько в поле компонентов
            GL_FLOAT, //тип
            GL_FALSE, // нормализация обрезка от [-1,1]
            sizeof(Vertex),//страйт? расстояние между двумя соседними элементами в массиве
            reinterpret_cast<void *> (offsetof(Vertex, textCoord))
    );

    checkErrors(__FILE__, __LINE__);

    glBufferData(
            GL_ARRAY_BUFFER,
            data.points.size() * sizeof(Vertex),
            data.points.data(),
            GL_STATIC_DRAW);
    if(logDebug)printf("vertex count %d\n", data.points.size());
    checkErrors(__FILE__, __LINE__);
    //указываем выравнивае видеокарте


    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 data.indexes.size() * sizeof(std::uint32_t),
                 data.indexes.data(),
                 GL_STATIC_DRAW);

    checkErrors(__FILE__, __LINE__);
    _count = data.indexes.size();
    if(logDebug)printf("indexes count %d\n", _count);
}


void VertexBuffer::draw()
{
    if(logDebug)printf("glBindVertexArray _VAO %d\n", _VAO);
    glBindVertexArray(_VAO);
    if(logDebug)printf("glDrawElements _VAO %d\n", _count);
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

/*MeshData *VertexBuffer::getMesh()
{
    return nullptr;
}*/
