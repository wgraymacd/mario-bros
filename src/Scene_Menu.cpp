#include "Scene_Menu.h"
#include "Scene_Play.h"
#include "Scene.h"
#include "Assets.hpp"
#include "GameEngine.h"
#include "Action.hpp"

#include <SFML/Graphics.hpp>

/// @brief constructs a new Scene_Menu object, calls Scene_Menu::init
/// @param gameEngine the game's main engine; required by Scene to access the GameEngine object
Scene_Menu::Scene_Menu(GameEngine &gameEngine)
    : Scene(gameEngine)
{
    init();
}

/// @brief initialized the MENU scene: registers keybinds, sets text attributes, and defines level paths
void Scene_Menu::init()
{
    registerAction(sf::Keyboard::W, "UP");
    registerAction(sf::Keyboard::S, "DOWN");
    registerAction(sf::Keyboard::D, "PLAY");
    registerAction(sf::Keyboard::Escape, "QUIT");

    m_title = "2D Platformer";
    m_menuStrings.push_back("Level 1");
    m_menuStrings.push_back("Level 2");
    m_menuStrings.push_back("Level 3");

    m_levelPaths.push_back("../bin/level1.txt");
    m_levelPaths.push_back("../bin/level2.txt");
    m_levelPaths.push_back("../bin/level3.txt");

    m_menuText.setFont(m_game.assets().getFont("PixelCowboy"));
    m_menuText.setCharacterSize(64);
}

/// @brief updates the scene's state
void Scene_Menu::update()
{
    // only one thing to update in Menu scene, rendering
    sRender();
}

/// @brief performs the given action
/// @param action an Action to perform; action has a type and a name
void Scene_Menu::sDoAction(const Action &action)
{
    if (action.type() == "START")
    {
        if (action.name() == "UP")
        {
            m_selectedMenuIndex = (m_selectedMenuIndex > 0) ? --m_selectedMenuIndex : m_menuStrings.size() - 1;
        }
        else if (action.name() == "DOWN")
        {
            m_selectedMenuIndex = (m_selectedMenuIndex + 1) % m_menuStrings.size();
        }
        else if (action.name() == "PLAY")
        {
            m_game.addScene("PLAY", std::make_shared<Scene_Play>(m_game, m_levelPaths[m_selectedMenuIndex]));
        }
        else if (action.name() == "QUIT")
        {
            onEnd();
        }
    }
}

/// @brief renders the scene background and text
void Scene_Menu::sRender()
{
    // clear the window to a blue
    m_game.window().setView(m_game.window().getDefaultView());
    m_game.window().clear(sf::Color(100, 100, 255));

    // draw the game title in the top-left of the screen
    m_menuText.setCharacterSize(48);
    m_menuText.setString(m_title);
    m_menuText.setFillColor(sf::Color::Black);
    m_menuText.setPosition(sf::Vector2f(10, 10));
    m_game.window().draw(m_menuText);

    // draw all of the menu options
    for (size_t i = 0; i < m_menuStrings.size(); i++)
    {
        m_menuText.setString(m_menuStrings[i]);
        m_menuText.setFillColor(i == m_selectedMenuIndex ? sf::Color::White : sf::Color::Black);
        m_menuText.setPosition(sf::Vector2f(10, 110 + i * 72));
        m_game.window().draw(m_menuText);
    }

    // draw the controls in the bottom left
    m_menuText.setCharacterSize(20);
    m_menuText.setString("up: w    down: s    play: d    back: esc");
    m_menuText.setFillColor(sf::Color::Black);
    m_menuText.setPosition(sf::Vector2f(10, m_game.window().getSize().y - m_menuText.getLocalBounds().height - 10));
    m_game.window().draw(m_menuText);

    m_game.window().display();
}

/// @brief quits the game
void Scene_Menu::onEnd()
{
    m_game.quit();
}