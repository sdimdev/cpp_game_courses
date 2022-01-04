//
// Created by dzmitry on 22.12.2021.
//

#include <random>
#include "ParticleEmmiter.hpp"

ParticleEmmiter::ParticleEmmiter(size_t count)
{
    //vector.reserve(count)
    //start pos by transform
    //

    std::uniform_real_distribution<> angleGen(0, 360);
    std::uniform_real_distribution<> velGen(1, 5);
    for(size_t i = 0; i< count; i++){
        //Particle
    }

}
