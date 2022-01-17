//
// Created by dzmitry on 20.11.2021.
//

#include <entity/event/IWindowEvent.hpp>
#include "WindowEventManagerImpl.hpp"
#include <SDL.h>
#include <scenes/IScene.hpp>
#include <cstdio>
#include <utility>

void WindowEventManagerImpl::handleEvents()
{
    SDL_Event e;
    SDL_PollEvent(&e);

    std::shared_ptr<IWindowEvent> windowEvent = nullptr;
    if (e.type == SDL_QUIT)
    {
        printf("QUIT in WEM\n");
        windowEvent = std::make_shared<SimpleWindowEvent>(QUIT);
    } else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
    {
        KeyboardKey key;
        KeyboardAction action;
        if (e.type == SDL_KEYDOWN)
        {
            action = KEY_DOWN;
        } else
        {
            action = KEY_UP;
        }
        switch (e.key.keysym.sym)
        {
            case SDLK_a:
                key = A;
                break;
            case SDLK_b:
                key = B;
                break;
            case SDLK_c:
                key = C;
                break;
            case SDLK_d:
                key = D;
                break;
            case SDLK_e:
                key = E;
                break;
            case SDLK_f:
                key = F;
                break;
            case SDLK_g:
                key = G;
                break;
            case SDLK_h:
                key = H;
                break;
            case SDLK_j:
                key = J;
                break;
            case SDLK_i:
                key = I;
                break;
            case SDLK_k:
                key = K;
                break;
            case SDLK_l:
                key = L;
                break;
            case SDLK_m:
                key = M;
                break;
            case SDLK_n:
                key = N;
                break;
            case SDLK_o:
                key = O;
                break;
            case SDLK_r:
                key = R;
                break;
            case SDLK_s:
                key = S;
                break;
            case SDLK_t:
                key = T;
                break;

            case SDLK_q:
                key = Q;
                break;
            case SDLK_v:
                key = V;
                break;
            case SDLK_w:
                key = W;
                break;
            case SDLK_x:
                key = X;
                break;
            case SDLK_y:
                key = Y;
                break;
            case SDLK_z:
                key = Z;
                break;
        }
        windowEvent = std::make_shared<KeyboardEvent>(key, action);
    } else
    {
        windowEvent = std::make_shared<SimpleWindowEvent>(UNKNOWN);
        // printf("something WEM");
        // we = new WindowEvent();
    }

    auto keyboardEvent = std::dynamic_pointer_cast<KeyboardEvent>(windowEvent);
    std::optional<KeyboardKey> pressedKey = {};
    bool pressedState = false;
    if (keyboardEvent && keyboardEvent->action == KEY_DOWN)
    {
        if (!pressed.count(keyboardEvent->key))
        {
            pressed.insert(keyboardEvent->key);
            pressedKey = keyboardEvent->key;
            pressedState = true;
        }
    } else if (keyboardEvent && keyboardEvent->action == KEY_UP)
    {
        if (pressed.count(keyboardEvent->key))
        {
            pressed.erase(pressed.find(keyboardEvent->key));
            pressedKey = keyboardEvent->key;
            pressedState = false;
        }
    }

    if (pressedKey)
    {
        for (auto &listener: pressChangedListeners)
        {
            if (listener.onKeyboardKeyPressChanged(pressedKey.value(), pressedState))
            {
                break;
            }
        }
    }
    for (const auto &listener: listeners)
    {
        if (listener(windowEvent))
        {
            break;
        }
    }
}

void WindowEventManagerImpl::add(IWindowEventManager::IEventListener const &listener)
{
    listeners.push_back(listener);
}

void WindowEventManagerImpl::remove(IWindowEventManager::IEventListener const &listener)
{
    //todo
    //std::remove(listeners.begin(), listeners.end(), listener);
    //
    //listeners.erase(std::find(listeners.begin(), listeners.end(), listener));
}

void WindowEventManagerImpl::add(const IKeyboardKeyListener listener)
{
    pressChangedListeners.push_back(listener);
}

void WindowEventManagerImpl::remove(const IKeyboardKeyListener  listener)
{
    //todo
    //std::remove(pressChangedListeners.begin(), pressChangedListeners.end(), listener);
    //pressChangedListeners.erase(std::find(pressChangedListeners.begin(), pressChangedListeners.end(), listener));
}

