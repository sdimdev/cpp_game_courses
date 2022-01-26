//
// Created by dzmitry on 24.01.2022.
//

#ifndef GAME_JAVAMANAGER_HPP
#define GAME_JAVAMANAGER_HPP


#include <string>

class JavaManager
{
public:
    static const JavaManager& instance();
    bool openBrowser(std::string url) const;
};


#endif //GAME_JAVAMANAGER_HPP
