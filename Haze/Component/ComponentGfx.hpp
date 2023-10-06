/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** Component
*/

#pragma once
#include "Component.hpp"
#include "inputs.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>

namespace Haze
{
    struct Sprite : public Component
    {
        Sprite(std::string path) : path(path)
        {
            std::cout << "path " << path << std::endl;
            texture.loadFromFile(path);
            sprite.setTexture(texture);
        }
        std::string path;
        sf::Sprite sprite;
        sf::Texture texture;
        std::string getType() const override
        {
            return "Sprite";
        }
        void show() const override { std::cout << "flm" << path << std::endl; }
    };

    struct Animation : public Component
    {
        enum AnimationType
        {
            LOOP,
            BOOMERANG,
            ONCE
        };
        struct intRect
        {
            int x;
            int y;
            int width;
            int height;
        };
        Animation(std::vector<intRect> frames, AnimationType type, bool direction, double tics) : frames(frames), type(type), tics(tics), direction(direction)
        {
        }
        std::vector<intRect> frames;
        AnimationType type = AnimationType::LOOP;
        double tics;
        size_t currentFrame = 0;
        bool direction = true;
        std::chrono::time_point<std::chrono::high_resolution_clock> lastAnimation = std::chrono::high_resolution_clock::now();
        std::string getType() const override { return "Animation"; }
        void show() const override { std::cout << "Animation: " << std::endl; }
    };

    struct Window : public Component
    {
        Window(int width, int height) : width(width), height(height)
        {
            window.create(sf::VideoMode(width, height), "R-Type");
            window.setFramerateLimit(60);
            window.setKeyRepeatEnabled(true);
        }
        int width;
        int height;
        sf::RenderWindow window;
        sf::Event event;
        std::string getType() const override
        {
            return "Window";
        }
        void show() const override { std::cout << "Window: " << width << ", " << height << std::endl; }
    };

    struct OnKeyPressed : public Component
    {
        OnKeyPressed(std::function<void(int, std::vector<InputType>)> callback) : callback(callback) {}
        std::function<void(int, std::vector<InputType>)> callback;
        std::string getType() const override
        {
            return "OnKeyPressed";
        }
        void show() const override { std::cout << "OnKeyPressed" << std::endl; }
    };

    struct OnKeyReleased : public Component
    {
        OnKeyReleased(std::function<void(int, std::vector<InputType>)> callback) : callback(callback) {}
        std::function<void(int, std::vector<InputType>)> callback;
        std::string getType() const override
        {
            return "OnKeyReleased";
        }
        void show() const override { std::cout << "OnKeyReleased" << std::endl; }
    };

    struct OnMousePressed : public Component
    {
        OnMousePressed(std::function<void(int)> callback) : callback(callback) {}
        std::function<void(int)> callback;
        std::string getType() const override
        {
            return "OnMousePressed";
        }
        void show() const override { std::cout << "OnMousePressed" << std::endl; }
    };

    struct OnMouseReleased : public Component
    {
        OnMouseReleased(std::function<void(int)> callback) : callback(callback) {}
        std::function<void(int)> callback;
        std::string getType() const override
        {
            return "OnMouseReleased";
        }
        void show() const override { std::cout << "OnMouseReleased" << std::endl; }
    };

    struct HitboxDisplay : public Component
    {
        HitboxDisplay()
        {
            rect.setFillColor(sf::Color::Transparent);
            rect.setOutlineColor(sf::Color::Red);
            rect.setOutlineThickness(5);
        }
        sf::Color color = sf::Color::Red;
        sf::RectangleShape rect;

        std::string getType() const override
        {
            return "HitboxDisplay";
        }
        void show() const override { std::cout << "HitboxDisplay: " << std::endl; }
    };

    struct Text : public Component
    {
        Text(std::string text, sf::Color color) : text(text), color(color)
        {
            font.loadFromFile("assets/fonts/arial.ttf");
            textObj.setFont(font);
            textObj.setString(text);
            textObj.setFillColor(color);
        }
        std::string text;
        sf::Color color;
        sf::Font font;
        sf::Text textObj;
        std::string getType() const override
        {
            return "Text";
        }
        void show() const override { std::cout << "Text: " << text << std::endl; }
    };
}
