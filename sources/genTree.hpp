#pragma once

#include <vector>
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Evenement.hpp"
#include "Parsing.hpp"

class genTree
{
private:
    sf::RenderWindow m_window;
    std::vector<Evenement> m_point;
    // std::vector<n_data> m_data;
    sf::Texture texture;
    sf::Sprite m_background;

    int m_year = 1000;
    int m_month = 1;
private:
    void scalePoint(sf::Vector2f actualSize);
    void generatePoint(csv::CSVRow, std::vector<std::string> &);
    void event();
    void changeLifeSpawn();

public:
    genTree() : m_window(sf::VideoMode(2000, 1000) ,"Test Covid", sf::Style::Resize)
    {
        if (!texture.loadFromFile("pictures/mapLowRes.png"))
            throw std::logic_error("File not Found");
        m_background.setTexture(texture);

        sf::FloatRect a = m_background.getGlobalBounds();
        m_background.setScale(2000/a.width, 1000/a.height);
        m_background.setPosition({-1000, -500});
        
    };
    virtual ~genTree() = default;
    void run();
    void init(csv::CSVReader &, std::vector<std::string>);
};
