#include "pch.h"
#include "MenuScene.h"

MenuScene::MenuScene(std::string id, Camera* c, World* w) : Scene(id, c, w)
{

}

void MenuScene::onEnter()
{
    addEventListener(KeyboardEvent::KEYDOWN, this, &MenuScene::onKeyDown);
    addEventListener(Button::PRESSED, this, &MenuScene::onButtonPressed);
}

void MenuScene::onExit()
{
    removeAllGameObjects();
    removeEventListener(KeyboardEvent::KEYDOWN, this, &MenuScene::onKeyDown);
    removeEventListener(Button::PRESSED, this, &MenuScene::onButtonPressed);
}

void MenuScene::update(float delta)
{
    Scene::update(delta);
}

void MenuScene::render()
{
    Scene::render();
}

void MenuScene::onKeyDown(const KeyboardEvent& e)
{
    if (e.key.code == Key::Code::Q)
    {
        Game::stop();
    }
}

void MenuScene::onButtonPressed(const UserEvent& e)
{
    std::string* buttonType = static_cast<std::string*>(e.getData1());

    
}