//
// Created by dzmitry on 05.01.2022.
//

#ifndef GAME_IRESOURCESMANAGER_HPP
#define GAME_IRESOURCESMANAGER_HPP

#include "ITexture.hpp"
#include <memory>
#include <map>
#include <iostream>

template<typename T>
class IResourcesManager
{
public:
    ~IResourcesManager() = default;

    std::shared_ptr<T> resourceForName(std::string name, const std::function<std::shared_ptr<T>(void)> &resourceCreator) const;

    template <typename FUN> void forEach(FUN fun);
    void clear() const;

private:
    mutable std::unordered_map<std::string, std::shared_ptr<T>> _resources;
};

template<typename T>
std::shared_ptr<T> IResourcesManager<T>::resourceForName(std::string name, const std::function<std::shared_ptr<T>(
        void)> &resourceCreator) const
{
    std::shared_ptr<T> el;

    auto it = _resources.find(name);

    if (it == std::end(_resources))
    {
        //std::cout << "Create [" << name << std::endl;
        el = resourceCreator();
        _resources[name] = el;
        //std::cout << "]" << name << " end" <<  std::endl;
    }
    else
    {
        el = it->second;
    }

    return el;
}

template<typename T>
template<typename FUN>
void IResourcesManager<T>::forEach(FUN fun)
{
    for (const auto& res : _resources)
    {
        fun(res.second);
    }
}

template<typename T>
void IResourcesManager<T>::clear() const
{
    auto it = _resources.begin();
    while (it != _resources.end())
    {
        if (it->second->refCount() == 1)
        {
            //std::cout << "Remove " << it->first << std::endl;
            it = _resources.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

#endif //GAME_IRESOURCESMANAGER_HPP
