//
// Created by dzmitry on 05.12.2021.
//

#include "../GLHeaders.hpp"
#include "VertexBuffer.hpp"
#include <utils/GLUtils.cpp>

struct VertexBuffer::Pimpl {
    //todo remove it
    // MeshData* data;
};

VertexBuffer::VertexBuffer(MeshData data) {
    _pimpl = std::make_shared<Pimpl>();
#ifdef GLES20
    glGenVertexArraysOES(1, &_VAO);
#elif GL33
    glGenVertexArrays(1, &_VAO);
#endif
    checkErrors(__FILE__, __LINE__);

#ifdef GLES20
    glBindVertexArrayOES(_VAO);
#elif GL33
    glBindVertexArray(_VAO);
#endif

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
    if (logDebug)printf("vertex count %d\n", data.points.size());
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
    if (logDebug)printf("indexes count %d\n", _count);
}


void VertexBuffer::draw() {
    if (logDebug)printf("glBindVertexArray _VAO %d\n", _VAO);
#ifdef GLES20
    glBindVertexArrayOES(_VAO);
#elif GL33
    glBindVertexArray(_VAO);
#endif
    if (logDebug)printf("glDrawElements _VAO %d\n", _count);
    glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, 0);

    checkErrors(__FILE__, __LINE__);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &_VBO);

    if (_IBO != 0) {
        glDeleteBuffers(1, &_IBO);
    }

#ifdef GLES20
    glDeleteVertexArraysOES(1, &_VAO);
#elif GL33
    glDeleteVertexArrays(1, &_VAO);
#endif
    checkErrors(__FILE__, __LINE__);
}

/*MeshData *VertexBuffer::getMesh()
{
    return nullptr;
}*/
