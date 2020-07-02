#include "genTree.hpp"
#include "Evenement.hpp"
#include <fstream>
#include <iostream>
#include <unistd.h>

void genTree::generatePoint(csv::CSVRow row, std::vector<std::string> &data)
{
    Evenement new_point{};

    if (row[data[6]] == "" || row[data[5]] == "" || row[data[7]] == "")
        return;

    // * Set The Position with the given longitude and latitude
    // * longitude + Latitude
    // std::cout << radius << std::endl;
    float radius = row[data[7]].get<float>() * 100.0f / 289935.0f;
    new_point.m_shape_Evenement.setRadius(radius);
    new_point.m_shape_Evenement.setOrigin(new_point.m_shape_Evenement.getRadius() / 2, new_point.m_shape_Evenement.getRadius() / 2);
    new_point.m_shape_Evenement.setPosition({1000 * row[data[6]].get<float>() / 180, 530 * row[data[5]].get<float>() / -90});
    new_point.m_shape_Evenement.setOutlineColor(sf::Color(0,0,0,130));
    new_point.m_shape_Evenement.setFillColor(sf::Color(230, 0, 0, 80));
    new_point.m_shape_Evenement.setOutlineThickness(0.3 );
    m_point.push_back(new_point);
}

/*
    * Scale the size of the point according to the current zoom
    * of the view
*/

void genTree::scalePoint(sf::Vector2f actualSize)
{
    // auto radius = m_point[0].m_shape_Evenement.getRadius();

    // static float oldRatio = 2000;

    // // * Iteration on all the points
    // for (auto &i : m_point)
    // {
    //     if (actualSize.x/oldRatio > 1)
    //         i.m_shape_Evenement.setRadius(radius * 1.02);
    //     else if (actualSize.x / oldRatio < 1)
    //         i.m_shape_Evenement.setRadius(radius * 0.98);
    // }
    // oldRatio = actualSize.x;
}

/* 
    * Event Handling
    * W/S Zoom in/out
    * Key arrow to move the View
*/

void genTree::event()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Resized)
        {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            m_window.setView(sf::View(visibleArea));
        }
        else if (event.type == sf::Event::Closed)
            m_window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            sf::View view = m_window.getView();
            view.zoom(0.99);
            m_window.setView(view);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            sf::View view = m_window.getView();
            view.zoom(1.01);
            m_window.setView(view);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            sf::View view = m_window.getView();
            view.move(-20, 0);
            m_window.setView(view);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            sf::View view = m_window.getView();
            view.move(20, 0);
            m_window.setView(view);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            sf::View view = m_window.getView();
            view.move(0, -20);
            m_window.setView(view);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            sf::View view = m_window.getView();
            view.move(0, 20);
            m_window.setView(view);
        }
    }
}

void genTree::changeLifeSpawn()
{
    // for (auto &i : m_point)
    // {
    //     if (m_year == i.m_data.intDate[0] && m_month == i.m_data.intDate[1])
    //         i.initLifeSpawn();
    //     else if (m_year > i.m_data.intDate[0] || m_year == i.m_data.intDate[0] && m_month < i.m_data.intDate[1])
    //     {
    //         i.decreaseLifeSpawn();
    //     }
    // }
}

void genTree::run()
{
    sf::Clock clock;

    while (m_window.isOpen()) {
        // * Init the View
        
        if (m_year == 1000) {
            sf::View view = m_window.getView();
            view.setCenter(0, 0);
            m_window.setView(view);
        }

        event();
        
        sf::Time elapsed1 = clock.getElapsedTime();
        if (elapsed1.asMilliseconds() >= 50) {
            // std::cout << "Year " << m_year << " Month " << m_month << std::endl;
            m_year = (m_month == 12) ? m_year + 1 : m_year;
            m_month = (m_month != 12) ? m_month + 1 : 1;
            clock.restart();
        }


        m_window.draw(m_background);
        // changeLifeSpawn();
        for (auto &i : m_point)
        {
            // if (i.isAlive() == true)
            m_window.draw(i.getShape());
        }
        m_window.display();
        m_window.clear();
        scalePoint(m_window.getView().getSize());
    }
}

void genTree::init(csv::CSVReader &rows, std::vector<std::string> data)
{
    for (auto &i : rows)
        generatePoint(i, data);
}