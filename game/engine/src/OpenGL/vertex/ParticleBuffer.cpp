//
// Created by dzmitry on 22.12.2021.
//


#include "ParticleBuffer.hpp"
#include "../GLHeaders.hpp"
#include "VertexBuffer.hpp"
#include <utils/GLUtils.cpp>

struct ParticleBuffer::Pimpl
{
    //todo remove it
    std::vector<ParticleData> data;
};

ParticleBuffer::ParticleBuffer(std::vector<ParticleData> data)
{
    _pimpl = std::make_shared<Pimpl>();
    _pimpl->data = std::move(data);

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
            4, // сколько в поле компонентов
            GL_FLOAT, //тип
            GL_FALSE, // нормализация обрезка от [-1,1]
            sizeof(ParticleData),//страйт? расстояние между двумя соседними элементами в массиве
            reinterpret_cast<void *> (offsetof(ParticleData, color))
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
            sizeof(ParticleData),//страйт? расстояние между двумя соседними элементами в массиве
            reinterpret_cast<void *> (offsetof(ParticleData, velocity))
    );
    checkErrors(__FILE__, __LINE__);

    glEnableVertexAttribArray(2);
    checkErrors(__FILE__, __LINE__);
    glVertexAttribPointer(
            1, //номер поля
            2, // сколько в поле компонентов
            GL_FLOAT, //тип
            GL_FALSE, // нормализация обрезка от [-1,1]
            sizeof(ParticleData),//страйт? расстояние между двумя соседними элементами в массиве
            reinterpret_cast<void *> (offsetof(ParticleData, pos))
    );

    checkErrors(__FILE__, __LINE__);

    glBufferData(
            GL_ARRAY_BUFFER,
            _pimpl->data.size() * sizeof(ParticleData),
            &_pimpl->data,
            GL_STATIC_DRAW);
    if (logDebug)printf("particle buffer count %d\n", _pimpl->data.size());
    checkErrors(__FILE__, __LINE__);
    //указываем выравнивае видеокарте


    glBindBuffer(GL_ARRAY_BUFFER, 0);

    count = data.size();

    if (logDebug)printf("particle count %d\n", count);
}

void ParticleBuffer::draw()
{
    if (logDebug)printf("glBindVertexArray _VAO %d\n", _VAO);
#ifdef GLES20
    glBindVertexArrayOES(_VAO);
#elif GL33
    glBindVertexArray(_VAO);
#endif

    if (logDebug)printf("glDrawElements _VAO %d\n", count);
    glDrawArrays(GL_POINTS, 0, count);

    checkErrors(__FILE__, __LINE__);

}

ParticleBuffer::ParticleBuffer(size_t capacity)
{
    this->capacity = capacity;
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
            4, // сколько в поле компонентов
            GL_FLOAT, //тип
            GL_FALSE, // нормализация обрезка от [-1,1]
            sizeof(ParticleData),//страйт? расстояние между двумя соседними элементами в массиве
            reinterpret_cast<void *> (offsetof(ParticleData, color))
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
            sizeof(ParticleData),//страйт? расстояние между двумя соседними элементами в массиве
            reinterpret_cast<void *> (offsetof(ParticleData, velocity))
    );
    checkErrors(__FILE__, __LINE__);

    glEnableVertexAttribArray(2);
    checkErrors(__FILE__, __LINE__);
    glVertexAttribPointer(
            1, //номер поля
            2, // сколько в поле компонентов
            GL_FLOAT, //тип
            GL_FALSE, // нормализация обрезка от [-1,1]
            sizeof(ParticleData),//страйт? расстояние между двумя соседними элементами в массиве
            reinterpret_cast<void *> (offsetof(ParticleData, pos))
    );

    checkErrors(__FILE__, __LINE__);

    glBufferData(
            GL_ARRAY_BUFFER,
            this->count * sizeof(ParticleData),
            nullptr,
            GL_STATIC_DRAW);
    if (logDebug)printf("particle buffer count %d\n", this->count);
    checkErrors(__FILE__, __LINE__);
    //указываем выравнивае видеокарте


    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (logDebug)printf("particle count %d\n", count);
}

void ParticleBuffer::addData(IParticleBuffer::ParticleData data)
{

    //glBindBuffer
    glBufferSubData(GL_ARRAY_BUFFER, this->curpos * sizeof (ParticleData), sizeof(ParticleData), &data );
    ++curpos;
    if(count<capacity){
        ++count;
    }
    if(curpos>=capacity){
        curpos = 0;
    }
}
