#pragma once

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Parsing.hpp"

class Evenement
{
private:
    // m_Evenement_type Evenement_type;
    int lifeSpawn = 255;
    bool Alive = false;
public:
    sf::CircleShape m_shape_Evenement;
    // n_data m_data;
    
    // Evenement(m_Evenement_type a, sf::Color col = {255, 255, 255, 255}) {}
    Evenement()
    {
        m_shape_Evenement.setOrigin(m_shape_Evenement.getRadius(), m_shape_Evenement.getRadius());
    };
    ~Evenement() = default;
    const int getLifeSpawn() const { return lifeSpawn; };
    void setPosition(float x, float y) { m_shape_Evenement.setPosition({x, y}); };
    void setPosition(sf::Vector2f pos) { m_shape_Evenement.setPosition(pos); };
    void setColor(sf::Color color) { m_shape_Evenement.setFillColor(color); };
    sf::CircleShape &getShape() { return m_shape_Evenement; };
    void initLifeSpawn()
    {
        Alive = true;
    };
    void decreaseLifeSpawn()
    {
        // if (lifeSpawn == 0) {
        //     Alive = false;
        //     return;
        // }
        // lifeSpawn -= 1;
        // auto color = m_shape_Evenement.getFillColor();
        // color.a = lifeSpawn;
        // m_shape_Evenement.setFillColor(color);
    }
    bool isAlive() { return Alive; }
};

//-380
//