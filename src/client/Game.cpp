/*
** EPITECH PROJECT, 2024
** rType
** File description:
** Game
*/

#include "Game.hh"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <boost/asio/detail/std_fenced_block.hpp>

RType::Game::Game(boost::asio::io_context &ioContext, const std::string &host, const std::string &port):
    _client(ioContext, host, port)
{
    _stopLoop = false;

    _font = std::make_shared<sf::Font>();
    if (!_font->loadFromFile("ressources/font/VCR_OSD_MONO_1.001.ttf")) {
        throw ClientError("Font not load");
    }

    createWindow();
    createMenu();
    createDeathMenu();
    createWinMenu();
    createPlayer();
    createSound();
    createGameSystem();
    createEntityMap();
    try {
        _receipter = std::thread(&Game::loopReceive, this);
    } catch(const std::exception& e) {
        throw std::exception(e);
    }
    _initConnection = false;
}

RType::Game::~Game()
{
    _client.send(Encoder::disconnexion());
    if (_receipter.joinable()) {
        _receipter.join();
    }
}

const RType::Coordinator &RType::Game::getCoordinator() const
{
	return _coord;
}

void RType::Game::gameLoop()
{
    std::shared_ptr<RType::ISystem> drawSystem = nullptr;
    std::shared_ptr<RType::ISystem> drawTextSystem = nullptr;
    std::shared_ptr<RType::ISystem> clearSystem = nullptr;
    std::shared_ptr<RType::ISystem> displaySystem = nullptr;

    std::shared_ptr<RType::ClockComponent> clockComponent = nullptr;
    std::shared_ptr<RType::SFWindowComponent> windowComponent = nullptr;
    std::shared_ptr<RType::MenuComponent> menuComponent = nullptr;

    float logicTime = 0.0;
    float renderTime = 0.0;
    float deltaTime = 0.0;

    int frameCount = 0;
    float fpsTime = 0.0;
    float fps = 0.0;

    for (auto sys : _coord.getSystems()) {
        if (sys->getType() == SystemType::S_DRAW)
            drawSystem = sys;
        if (sys->getType() == SystemType::S_DRAWTEXT)
            drawTextSystem = sys;
        if (sys->getType() == SystemType::S_DISPLAY)
            displaySystem = sys;
        if (sys->getType() == SystemType::S_CLEAR)
            clearSystem = sys;
    }

    for (auto entity: _coord.getEntities()) {
        if (entity->getComponent<RType::SFWindowComponent>() != nullptr
        && entity->getComponent<RType::ClockComponent>() != nullptr
        && entity->getComponent<RType::MenuComponent>() != nullptr) {
            clockComponent = entity->getComponent<RType::ClockComponent>();
            windowComponent = entity->getComponent<RType::SFWindowComponent>();
            menuComponent = entity->getComponent<RType::MenuComponent>();
            break;
        }
    }

    while (!_stopLoop && clockComponent) {
        deltaTime = clockComponent->getClock(LOGIC_CLOCK).restart().asSeconds();
        logicTime += deltaTime;
        while (logicTime >= FRAME_TIME_LOGIC) {
            std::unique_lock<std::mutex> lock(_mtx);
            for (auto sys : _coord.getSystems())
                if (sys->getType() != SystemType::S_DRAW && sys->getType() != SystemType::S_DRAWTEXT && sys->getType() != SystemType::S_CLEAR && sys->getType() != SystemType::S_DISPLAY)
                    sys->effects(_coord.getEntities());
            if (menuComponent && menuComponent->getMenu() == LOADING && !getGameHasStarted()) {
                connectToServer();
            } else if (menuComponent && menuComponent->getMenu() == LOADING && getGameHasStarted()) {
                menuComponent->setMenu(GAME);
            }
            logicTime -= FRAME_TIME_LOGIC;
            if (menuComponent && menuComponent->getMenu() == OPTIONS) {
                for (auto entity: _coord.getEntities()) {
                    if (entity->getComponent<RType::EntityTypeComponent>() != nullptr
                    && entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == E_WINDOW)
                        _soundsEntity->getComponent<SoundQueueComponent>()->setGlobalSoundVolume(entity->getComponent<SoundVolumeComponent>()->getVolume());
                }
            }
        }

        renderTime += deltaTime;
        fpsTime += deltaTime;
        if (renderTime >= RENDER_FRAME_TIME) {
            frameCount++;
            if (clearSystem != nullptr) {
                std::unique_lock<std::mutex> lock(_mtx);
                clearSystem->effects(_coord.getEntities());
            }
            if (drawSystem != nullptr) {
                std::unique_lock<std::mutex> lock(_mtx);
                drawSystem->effects(_coord.getEntities());
            }
            if (drawTextSystem != nullptr) {
                std::unique_lock<std::mutex> lock(_mtx);
                drawTextSystem->effects(_coord.getEntities());
            }
            if (displaySystem != nullptr) {
                std::unique_lock<std::mutex> lock(_mtx);
                displaySystem->effects(_coord.getEntities());
            }
            renderTime = 0.0;
            std::unique_lock<std::mutex> lock(_mtx);
            if (windowComponent != nullptr && !windowComponent->getIsOpen()) {
                _client.cancel();
                _stopLoop = true;
                break;
            }
        }

        if (fpsTime >= 1.0) {
            fps = frameCount / fpsTime;
            std::cout << "FPS: " << fps << std::endl;
            frameCount = 0;
            fpsTime = 0.0;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void RType::Game::loopReceive()
{
    std::basic_string<unsigned char> command;
    COMMAND_INFO receiveInfo;

    while (!_stopLoop) {
        command = _client.receive();
        receiveInfo = Decoder::getCommandInfo(command);

        std::unique_lock<std::mutex> lock(_mtx);
        auto entities = _coord.getEntities();
        std::shared_ptr<MenuComponent> menuComponent = nullptr;

        switch (receiveInfo.first) {
            case NEW_ENTITY:
                if (_initConnection) {
                    createEntity(receiveInfo.second[1],
                                static_cast<RType::EntityType>(receiveInfo.second[0]),
                                static_cast<short> (receiveInfo.second[2]),
                                static_cast<short> (receiveInfo.second[3]),
                                receiveInfo.second[4]);
                    if (EntityTypeComponent::isWeapon((EntityType)receiveInfo.second[0])) {
                        sf::Vector2f position = getBulletPosition((int)receiveInfo.second[0], (int)receiveInfo.second[2], (int)receiveInfo.second[3]);
                        createEntity(E_BULLET_EFFECT, position.x, position.y - 20);
                    }
                } else {
                    if (receiveInfo.second[0] != E_PLAYER)
                        continue;
                    _initConnection = true;
                    auto entities = _coord.getEntities();
                    for (const auto &entity : entities) {
                        if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == E_PLAYER)
                            entity->setServerId(receiveInfo.second[1]);
                    }
                }
                break;

            case DELETE_ENTITY:
                for (const auto &entity : entities) {
                    if (entity->getComponent<RType::SFWindowComponent>() != nullptr
                    && entity->getComponent<RType::MenuComponent>() != nullptr)
                        menuComponent = entity->getComponent<RType::MenuComponent>();
                    if (entity->getServerId() == receiveInfo.second[0]) {
                        if (entity->getComponent<RType::EntityTypeComponent>() == nullptr)
                            continue;
                        if (entity->GET_POSITION_X > 0) {
                            if (EntityTypeComponent::isWeapon(GET_ENTITY_TYPE(entity)) || EntityTypeComponent::isEnnemyShoot(GET_ENTITY_TYPE(entity)))
                                switch(GET_ENTITY_TYPE(entity)) {
                                    case RType::E_BULLET_2:
                                        createEntity(E_HIT_EFFECT_2, (entity->GET_POSITION_X + 32), entity->GET_POSITION_Y);
                                        break;
                                    case RType::E_BULLET_3:
                                        createEntity(E_HIT_EFFECT_3, (entity->GET_POSITION_X + 32), entity->GET_POSITION_Y);
                                        break;
                                    case RType::E_BULLET_4:
                                        createEntity(E_HIT_EFFECT_3, (entity->GET_POSITION_X + 32), entity->GET_POSITION_Y);
                                        break;
                                    default:
                                        createEntity(E_HIT_EFFECT, entity->GET_POSITION_X, entity->GET_POSITION_Y);
                                        break;
                                }
                            if (EntityTypeComponent::isMob(GET_ENTITY_TYPE(entity)) && !EntityTypeComponent::isBoss(GET_ENTITY_TYPE(entity)))
                                    createEntity(E_EXPLOSION_EFFECT, entity->GET_POSITION_X, entity->GET_POSITION_Y);
                        }
                        if (EntityTypeComponent::isBoss(GET_ENTITY_TYPE(entity)))
                            for (int i = 0; i < 50; i++)
                                createEntity(E_EXPLOSION_EFFECT, entity->GET_POSITION_X + (std::rand() % 400), entity->GET_POSITION_Y + (std::rand() % 400));
                        if (GET_ENTITY_TYPE(entity) == E_PLAYER)
                            if (entity->getComponent<ActionComponent>() && menuComponent) {
                                if (entity->getComponent<HealthComponent>())
                                    entity->getComponent<HealthComponent>()->setIsDead(true);
                                menuComponent->setMenu(DEAD);
                            }
                        _coord.deleteEntity(entity);
                    }
                }
                break;

            case MOVE_ENTITY:
                for (const auto &entity : entities) {
                    if (entity->getServerId() == receiveInfo.second[0] &&
                        entity->getComponent<RType::PositionComponent>() &&
                        entity->getComponent<RType::SpriteComponent>()) {
                        entity->getComponent<RType::PositionComponent>()->setPositions(
                            static_cast<short>(receiveInfo.second[1]), static_cast<short>(receiveInfo.second[2]));
                        entity->getComponent<RType::SpriteComponent>()->getSprite()->setPosition(
                            static_cast<short>(receiveInfo.second[1]), static_cast<short>(receiveInfo.second[2]));
                        break;
                    }
                }
                break;
            case DISCONNEXION:
                _stopLoop = true;
                break;
            case INFO_ENTITY:
                for (const auto &entity : entities) {
                    if (entity->getServerId() == receiveInfo.second[0]) {
                        if (entity->getComponent<RType::PositionComponent>())
                            entity->getComponent<RType::PositionComponent>()->setPositions(
                                static_cast<short>(receiveInfo.second[2]), static_cast<short>(receiveInfo.second[3]));
                        if (entity->getComponent<RType::HealthComponent>()) {
                            entity->getComponent<RType::HealthComponent>()->setHealth(receiveInfo.second[5]);
                        }
                        break;
                    }
                }
                break;
            case INFO_LEVEL:
                for (const auto &entity : entities) {
                    if (entity->getComponent<RType::EntityTypeComponent>()
                    && entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == E_WINDOW
                    && entity->getComponent<LevelComponent>()) {
                        entity->getComponent<LevelComponent>()->setLevel(static_cast<short>(receiveInfo.second[0]));
                        break;
                    }
                }
                break;
            case GAME_END:
                for (const auto &entity : entities) {
                    if (entity->getComponent<RType::EntityTypeComponent>()
                    && entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == E_WINDOW
                    && entity->getComponent<MenuComponent>()) {
                        entity->getComponent<MenuComponent>()->setMenu(WIN);
                        break;
                    }
                }
                break;
            case INFO_SCORE:
                for (const auto &entity : entities) {
                    if (entity->getComponent<RType::SFWindowComponent>() != nullptr
                    && entity->getComponent<RType::ScoreComponent>() != nullptr ) {
                        entity->getComponent<RType::ScoreComponent>()->setScore(static_cast<std::uint16_t>(receiveInfo.second[0]));
                        break;
                    }
                }
                break;
            default:
                break;
        }
    }
}


void RType::Game::createMenu()
{
    std::shared_ptr<RType::Entity> title = createText(150, "R-TYPE", 100);
    title->PUSH_MENU_COMPONENT_E(HOME);

    std::shared_ptr<RType::Entity> loading = createText(660, 400, "LOADING ...");
    loading->PUSH_MENU_COMPONENT_E(LOADING);

    std::shared_ptr<RType::Entity> buttonPlayButton = createButton(400, "PLAY");

    buttonPlayButton->PUSH_MENU_COMPONENT_E(HOME);
    buttonPlayButton->pushComponent(std::make_shared<RType::ClickEffectComponent> (
        [] (std::shared_ptr<Entity> window) {
            window->getComponent<MenuComponent>()->setMenu(LOADING);
        }
    ));

    std::shared_ptr<RType::Entity> buttonOption = createButton(600, "OPTION");
    buttonOption->PUSH_MENU_COMPONENT_E(HOME);
    buttonOption->pushComponent(std::make_shared<RType::ClickEffectComponent> (
        [] (std::shared_ptr<Entity> window) {
            window->getComponent<MenuComponent>()->setMenu(OPTIONS);
        }
    ));

    std::shared_ptr<RType::Entity> buttonExit = createButton(800, "EXIT");
    buttonExit->PUSH_MENU_COMPONENT_E(HOME);
    buttonExit->pushComponent(std::make_shared<RType::ClickEffectComponent> (
        [] (std::shared_ptr<Entity> window) {
            window->getComponent<SFWindowComponent>()->getWindow()->close();
        }
    ));
}

void RType::Game::createOptionMenu()
{
    createText(150, "OPTIONS", 80)->PUSH_MENU_COMPONENT_E(OPTIONS);

    std::shared_ptr<RType::Entity> buttonMappingInput = createButton(700, "Mapping Inputs");
    buttonMappingInput->PUSH_MENU_COMPONENT_E(OPTIONS);
    buttonMappingInput->pushComponent(std::make_shared<RType::ClickEffectComponent> (
        [] (std::shared_ptr<Entity> window) {
            window->getComponent<MenuComponent>()->setMenu(MAPPING_INPUT);
        }
    ));

    std::shared_ptr<RType::Entity> buttonReturnOpt = createButton(900, "GO BACK");
    buttonReturnOpt->PUSH_MENU_COMPONENT_E(OPTIONS);
    buttonReturnOpt->pushComponent(std::make_shared<RType::ClickEffectComponent>(
        [](std::shared_ptr<Entity> window) {
            window->getComponent<MenuComponent>()->setMenu(HOME);
        }
    ));
    sf::Font font;
    font.loadFromFile("./ressources/font/VCR_OSD_MONO_1.001.ttf");
    sf::Text fullField("Music Volume: - 100 +", font, 60);
    for (auto &entity: _coord.getEntities()) {
        if (entity->getComponent<EntityTypeComponent>() != nullptr && entity->getComponent<EntityTypeComponent>()->getEntityType() != E_WINDOW)
            continue;
        int x = entity->getComponent<RType::SFWindowComponent>()->getWindow()->getSize().x;
        std::shared_ptr<RType::Entity> music = createText((x - fullField.getGlobalBounds().width) / 2, 300, "Music Volume: ");
        music->PUSH_MENU_COMPONENT_E(OPTIONS);
        sf::FloatRect titleBound = music->getComponent<TextComponent>()->getText()->getGlobalBounds();
        std::shared_ptr<Entity> plusButton = createButton(music->getComponent<PositionComponent>()->getPositionX() + titleBound.width, 300, "- ");
        plusButton->PUSH_MENU_COMPONENT_E(OPTIONS);
        plusButton->pushComponent(std::make_shared<ClickEffectComponent>(
            [](std::shared_ptr<Entity> window) {
                (void) window;
                window->getComponent<MusicComponent>()->setVolume(window->getComponent<MusicComponent>()->getVolume() - 10);
            }
        ));
        titleBound = plusButton->getComponent<TextComponent>()->getText()->getGlobalBounds();
        std::shared_ptr<Entity> volumeLevel = createText(plusButton->getComponent<PositionComponent>()->getPositionX() + titleBound.width, 300,"50");
        volumeLevel->PUSH_MENU_COMPONENT_E(OPTIONS);
        volumeLevel->pushComponent(std::make_shared<AutoUpdateTextComponent>(MUSIC_VOLUME));
        titleBound = volumeLevel->getComponent<TextComponent>()->getText()->getGlobalBounds();
        std::shared_ptr<Entity> minusButton = createButton(volumeLevel->getComponent<PositionComponent>()->getPositionX() + titleBound.width, 300, "  +");
        minusButton->PUSH_MENU_COMPONENT_E(OPTIONS);
        minusButton->pushComponent(std::make_shared<ClickEffectComponent>(
            [](std::shared_ptr<Entity> window) {
                (void) window;
                window->getComponent<MusicComponent>()->setVolume(window->getComponent<MusicComponent>()->getVolume() + 10);
            }
        ));

        fullField.setString("Sound Volume: - 100 +");
        std::shared_ptr<RType::Entity> sound = createText((x - fullField.getGlobalBounds().width) / 2, 500, "Sound Volume: ");
        sound->PUSH_MENU_COMPONENT_E(OPTIONS);
        titleBound = sound->getComponent<TextComponent>()->getText()->getGlobalBounds();
        std::shared_ptr<Entity> plusButton2 = createButton(sound->getComponent<PositionComponent>()->getPositionX() + titleBound.width, 500, "- ");
        plusButton2->PUSH_MENU_COMPONENT_E(OPTIONS);
        plusButton2->pushComponent(std::make_shared<ClickEffectComponent>(
            [](std::shared_ptr<Entity> window) {
                (void) window;
                window->getComponent<SoundVolumeComponent>()->setVolume(window->getComponent<SoundVolumeComponent>()->getVolume() - 10);
            }
        ));
        titleBound = plusButton2->getComponent<TextComponent>()->getText()->getGlobalBounds();
        std::shared_ptr<Entity> volumeLevel2 = createText(plusButton2->getComponent<PositionComponent>()->getPositionX() + titleBound.width, 500,
               std::to_string(50));
        volumeLevel2->PUSH_MENU_COMPONENT_E(OPTIONS);
        volumeLevel2->pushComponent(std::make_shared<AutoUpdateTextComponent>(SOUND_VOLUME));
        titleBound = volumeLevel2->getComponent<TextComponent>()->getText()->getGlobalBounds();
        std::shared_ptr<Entity> minusButton2 = createButton(volumeLevel2->getComponent<PositionComponent>()->getPositionX() + titleBound.width, 500, "  +");
        minusButton2->PUSH_MENU_COMPONENT_E(OPTIONS);
        minusButton2->pushComponent(std::make_shared<ClickEffectComponent>(
            [](std::shared_ptr<Entity> window) {
                (void) window;
                window->getComponent<SoundVolumeComponent>()->setVolume(window->getComponent<SoundVolumeComponent>()->getVolume() + 10);
            }
        ));
        break;
    }
}

void RType::Game::createMappingInputButton(std::shared_ptr<RType::MappingInputComponent> mappingInput)
{
    createText(150, "MAPPING INPUTS", 80)->PUSH_MENU_COMPONENT_E(MAPPING_INPUT);
    std::shared_ptr<RType::Entity> buttonLeft = createButton(600, 350, "Left: " + MappingInputComponent::getKeyName(mappingInput->getMappingInput(INPUT_LEFT)));
    buttonLeft->SET_BUTTON_TYPE(INPUT_LEFT);
    std::shared_ptr<RType::TextComponent> textLeft = buttonLeft->getComponent<TextComponent>();
    textLeft->setTextWithoutVariable("Left: ");

    buttonLeft->PUSH_MENU_COMPONENT_E(MAPPING_INPUT);
    buttonLeft->pushComponent(std::make_shared<RType::ClickEffectComponent>(
        [mappingInput](std::shared_ptr<Entity> window) {
            (void) window;
            mappingInput->setInputToDefined(INPUT_LEFT);
        }
    ));

    std::shared_ptr<RType::Entity> buttonRight = createButton(600, 420, "Right: " + MappingInputComponent::getKeyName(mappingInput->getMappingInput(INPUT_RIGHT)));
    buttonRight->SET_BUTTON_TYPE(INPUT_RIGHT);
    std::shared_ptr<RType::TextComponent> textRight = buttonRight->getComponent<TextComponent>();
    textRight->setTextWithoutVariable("Right: ");
    buttonRight->PUSH_MENU_COMPONENT_E(MAPPING_INPUT);
    buttonRight->pushComponent(std::make_shared<RType::ClickEffectComponent>(
        [mappingInput](std::shared_ptr<Entity> window) {
            (void) window;
            mappingInput->setInputToDefined(INPUT_RIGHT);
        }
    ));

    std::shared_ptr<RType::Entity> buttonUp = createButton(600, 490, "Up: " + MappingInputComponent::getKeyName(mappingInput->getMappingInput(INPUT_UP)));
    buttonUp->SET_BUTTON_TYPE(INPUT_UP);
    std::shared_ptr<RType::TextComponent> textUp = buttonUp->getComponent<TextComponent>();
    textUp->setTextWithoutVariable("Up: ");
    buttonUp->PUSH_MENU_COMPONENT_E(MAPPING_INPUT);
    buttonUp->pushComponent(std::make_shared<RType::ClickEffectComponent>(
        [mappingInput](std::shared_ptr<Entity> window) {
            (void) window;
            mappingInput->setInputToDefined(INPUT_UP);
        }
    ));

    std::shared_ptr<RType::Entity> buttonDown = createButton(600, 560, "Down: " + MappingInputComponent::getKeyName(mappingInput->getMappingInput(INPUT_DOWN)));
    buttonDown->SET_BUTTON_TYPE(INPUT_DOWN);
    std::shared_ptr<RType::TextComponent> textDown = buttonDown->getComponent<TextComponent>();
    textDown->setTextWithoutVariable("Down: ");
    buttonDown->PUSH_MENU_COMPONENT_E(MAPPING_INPUT);
    buttonDown->pushComponent(std::make_shared<RType::ClickEffectComponent>(
        [mappingInput](std::shared_ptr<Entity> window) {
            (void) window;
            mappingInput->setInputToDefined(INPUT_DOWN);
        }
    ));

    std::shared_ptr<RType::Entity> buttonShoot = createButton(600, 630, "Shoot: " + MappingInputComponent::getKeyName(mappingInput->getMappingInput(INPUT_SHOOT)));
    buttonShoot->SET_BUTTON_TYPE(INPUT_SHOOT);
    std::shared_ptr<RType::TextComponent> textShoot = buttonShoot->getComponent<TextComponent>();
    textShoot->setTextWithoutVariable("Shoot: ");

    buttonShoot->PUSH_MENU_COMPONENT_E(MAPPING_INPUT);
    buttonShoot->pushComponent(std::make_shared<RType::ClickEffectComponent>(
        [mappingInput](std::shared_ptr<Entity> window) {
            (void) window;
            mappingInput->setInputToDefined(INPUT_SHOOT);
        }
    ));

    std::shared_ptr<RType::Entity> buttonReturn = createButton(900, "GO BACK");
    buttonReturn->PUSH_MENU_COMPONENT_E(MAPPING_INPUT);
    buttonReturn->pushComponent(std::make_shared<RType::ClickEffectComponent>(
        [](std::shared_ptr<Entity> window) {
            window->getComponent<MenuComponent>()->setMenu(OPTIONS);
        }
    ));
}

void RType::Game::createDeathMenu()
{
    std::shared_ptr<RType::Entity> title = createText(200, "You're dead!");
    title->PUSH_MENU_COMPONENT_E(DEAD);

    std::shared_ptr<RType::Entity> subTitle = createText(300, "There's a Fabien mode if you prefer :)");
    subTitle->PUSH_MENU_COMPONENT_E(DEAD);

    std::shared_ptr<RType::Entity> buttonSpectate = createButton(600, "SPECTATE");
    buttonSpectate->PUSH_MENU_COMPONENT_E(DEAD);
    buttonSpectate->pushComponent(std::make_shared<RType::ClickEffectComponent> (
        [] (std::shared_ptr<Entity> window) {
            window->getComponent<MenuComponent>()->setMenu(GAME);
        }
    ));

    std::shared_ptr<RType::Entity> buttonExit = createButton(800, "EXIT");
    buttonExit->PUSH_MENU_COMPONENT_E(DEAD);
    buttonExit->pushComponent(std::make_shared<RType::ClickEffectComponent> (
        [] (std::shared_ptr<Entity> window) {
            window->getComponent<SFWindowComponent>()->getWindow()->close();
        }
    ));
}

void RType::Game::createWinMenu()
{
    std::shared_ptr<RType::Entity> title = createText(200, "You've won! Well done ;)");
    title->PUSH_MENU_COMPONENT_E(WIN);

    std::shared_ptr<RType::Entity> buttonExit = createButton(800, "EXIT");
    buttonExit->PUSH_MENU_COMPONENT_E(WIN);
    buttonExit->pushComponent(std::make_shared<RType::ClickEffectComponent> (
        [] (std::shared_ptr<Entity> window) {
            window->getComponent<SFWindowComponent>()->getWindow()->close();
        }
    ));
}

std::shared_ptr<RType::Entity> RType::Game::createButton(int x, int y, std::string text)
{
    std::shared_ptr<RType::Entity> button = _coord.generateNewEntity();

    button->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_BUTTON));
    std::shared_ptr<TextComponent> textComponent = button->pushComponent(std::make_shared<RType::TextComponent>(text, 60, _font));
    sf::FloatRect size = textComponent->getText()->getGlobalBounds();
    button->pushComponent(std::make_shared<RType::PositionComponent>(x, y));
    button->pushComponent(std::make_shared<RType::IntRectComponent>(x, y, size.width, size.height + 25));
    button->pushComponent(std::make_shared<RType::HoverEffectComponent>());
    return button;
}

std::shared_ptr<RType::Entity> RType::Game::createButton(int y, std::string text)
{
    std::shared_ptr<RType::Entity> button = _coord.generateNewEntity();

    for (auto &entity: _coord.getEntities()) {
        if (entity->getComponent<RType::SFWindowComponent>() == nullptr)
            continue;
        button->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_BUTTON));
        std::shared_ptr<TextComponent> textComponent = button->pushComponent(std::make_shared<RType::TextComponent>(text, 60, _font));
        sf::FloatRect size = textComponent->getText()->getGlobalBounds();
        sf::Vector2<unsigned int> windowSize = entity->getComponent<RType::SFWindowComponent>()->getWindow()->getSize();
        button->pushComponent(std::make_shared<RType::PositionComponent>((windowSize.x - size.width) / 2, y));
        button->pushComponent(std::make_shared<RType::IntRectComponent>((windowSize.x - size.width) / 2, y, size.width, size.height + 25));
        button->pushComponent(std::make_shared<RType::HoverEffectComponent>());
    }
    return button;
}

std::shared_ptr<RType::Entity> RType::Game::createText(int x, int y, std::string text)
{
    std::shared_ptr<RType::Entity> textEntity = _coord.generateNewEntity();

    textEntity->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_TEXT));
    std::shared_ptr<TextComponent> textComponent = textEntity->pushComponent(std::make_shared<RType::TextComponent>(text, 60, _font));
    textEntity->pushComponent(std::make_shared<RType::PositionComponent>(x, y));
    return textEntity;
}

std::shared_ptr<RType::Entity> RType::Game::createText(int y, std::string text)
{
    std::shared_ptr<RType::Entity> textEntity = _coord.generateNewEntity();

    for (auto &entity: _coord.getEntities()) {
        if (entity->getComponent<RType::SFWindowComponent>() == nullptr)
            continue;
        textEntity->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_TEXT));
        std::shared_ptr<TextComponent> textComponent = textEntity->pushComponent(std::make_shared<RType::TextComponent>(text, 60, _font));
        sf::FloatRect size = textComponent->getText()->getGlobalBounds();
        sf::Vector2<unsigned int> windowSize = entity->getComponent<RType::SFWindowComponent>()->getWindow()->getSize();
        textEntity->pushComponent(std::make_shared<RType::PositionComponent>((windowSize.x - size.width) / 2, y));
    }
    return textEntity;
}

std::shared_ptr<RType::Entity> RType::Game::createText(int y, std::string text, std::size_t fontSize)
{
    std::shared_ptr<RType::Entity> textEntity = _coord.generateNewEntity();

    for (auto &entity: _coord.getEntities()) {
        if (entity->getComponent<RType::SFWindowComponent>() == nullptr)
            continue;
        textEntity->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_TEXT));
        std::shared_ptr<TextComponent> textComponent = textEntity->pushComponent(std::make_shared<RType::TextComponent>(text, fontSize, _font));
        sf::FloatRect size = textComponent->getText()->getGlobalBounds();
        sf::Vector2<unsigned int> windowSize = entity->getComponent<RType::SFWindowComponent>()->getWindow()->getSize();
        textEntity->pushComponent(std::make_shared<RType::PositionComponent>((windowSize.x - size.width) / 2, y));
    }
    return textEntity;
}

void RType::Game::createEntity(const RType::EntityType &type, const int &posX,
                               const int &posY, const int &idToFollow)
{
    Json::Reader reader;
    Json::Value entityInfo;
    std::ifstream file;
    std::shared_ptr<RType::Entity> entity = _coord.generateNewEntity();
    std::shared_ptr<RType::Entity> entityToFollow = nullptr;

    std::string filepath("./config/entities/" + _entityTypeMap[type] + ".json");

    file.open(filepath);
    if (!file.is_open() || !reader.parse(file, entityInfo)) {
        std::cerr << "Error while reading or parsing the json: " << filepath << std::endl;
        return;
    }
    if (type == E_PLAYER)
        entity->PUSH_TYPE_E(E_ALLIES);
    else
        entity->PUSH_TYPE_E(type);
    POS_COMPONENT position = entity->PUSH_POS_E(posX, posY);
    SCALE_COMPONENT scale = entity->PUSH_SCALE_E(entityInfo["scale"]["x"].asFloat(),
                                                 entityInfo["scale"]["y"].asFloat());
    RECT_COMPONENT intRect = entity->PUSH_RECT_E(entityInfo["rect"]["x"].asInt(),
                                                 entityInfo["rect"]["y"].asInt(),
                                                 entityInfo["rect"]["width"].asInt(),
                                                 entityInfo["rect"]["height"].asInt());
    TEXTURE_COMPONENT texture = getTextureComponent(entityInfo["sprite"].asString());
    entity->pushComponent(CREATE_SPRITE_COMPONENT(texture->getTexture(),
                          position->getPositions(), sf::Vector2f(scale->getScaleX(),
                          scale->getScaleY()), sf::IntRect(intRect->getIntRectLeft(),
                          intRect->getIntRectTop(), intRect->getIntRectWidth(),
                          intRect->getIntRectHeight())));
    entity->PUSH_CLOCK_E();
    if (entityInfo["health"].asBool() == true)
        entity->PUSH_HEALTH_E(entityInfo["health"].asInt());
    if (entityInfo["damage"].asBool() == true)
        entity->PUSH_DAMAGE_E(entityInfo["damage"].asInt());
    if (entityInfo["speed"].asBool() == true)
        entity->PUSH_VELOCITY_E(entityInfo["speed"].asInt());
    if (entityInfo["pattern"].asBool() == true)
        entity->PUSH_PATTERN_E(static_cast<RType::PatternType>(entityInfo["pattern"].asInt()));
    if (!entityInfo["sound"].asString().empty() && _soundsEntity && _soundsEntity->getComponent<SoundQueueComponent>() && entityInfo["soundVolume"].asBool() == true) {
        SOUND_BUFFER_COMPONENT soundBuffer = getSoundBufferComponent(entityInfo["sound"].asString());
        _soundsEntity->getComponent<SoundQueueComponent>()->pushSound(soundBuffer->getSoundBuffer(), entityInfo["soundVolume"].asFloat());
    } else if (!entityInfo["sound"].asString().empty() && _soundsEntity && _soundsEntity->getComponent<SoundQueueComponent>()) {
        SOUND_BUFFER_COMPONENT soundBuffer = getSoundBufferComponent(entityInfo["sound"].asString());
        _soundsEntity->getComponent<SoundQueueComponent>()->pushSound(soundBuffer->getSoundBuffer());
    }
    if (entityInfo["isShooting"].asBool() == true) {
        auto action = entity->PUSH_ACTION_E();
        action->setActions(SHOOTING, true);
    }
    if (entityInfo["intervalShoot"].asBool() == true) {
        entity->PUSH_INTERVALSHOOT_E(entityInfo["intervalShoot"].asFloat());
    }

    if (entityInfo["attack"].isArray()) {
        auto attackComponent = entity->PUSH_ATTACK_E();
        for (const auto &attack : entityInfo["attack"]) {
            if (attack.isString()) {
                attackComponent->pushBackAttacksPatterns(attack.asString());
            }
        }
    }

    if (entityInfo["score"].asBool() == true) {
        entity->pushComponent(std::make_shared<ScoreComponent>(entityInfo["score"].asInt()));
    }

    entity->PUSH_MENU_COMPONENT_E(GAME);
    file.close();
    if (entity->getComponent<RType::DirectionPatternComponent>() &&
        entity->getComponent<RType::DirectionPatternComponent>()->getPatternType() == RType::FOLLOW_PLAYER) {
        entityToFollow = getEntityByServerId(_coord.getEntities(), idToFollow);
        if (!entityToFollow)
            return;
        entity->getComponent<RType::DirectionPatternComponent>()->setEntityToFollow(entityToFollow->getId());
    }
}


void RType::Game::createEntity(const long &serverId, const RType::EntityType &type,
                               const int &posX, const int &posY, const int &idToFollow)
{
    Json::Reader reader;
    Json::Value entityInfo;
    std::ifstream file;
    std::shared_ptr<RType::Entity> entity = _coord.generateNewEntity(serverId);
    std::shared_ptr<RType::Entity> entityToFollow = nullptr;
    std::string filepath("./config/entities/" + _entityTypeMap[type] + ".json");

    file.open(filepath);
    if (!file.is_open() || !reader.parse(file, entityInfo)) {
        std::cerr << "Error while reading or parsing the json: " << filepath << std::endl;
        return;
    }
    if (type == E_PLAYER)
        entity->PUSH_TYPE_E(E_ALLIES);
    else
        entity->PUSH_TYPE_E(type);
    POS_COMPONENT position = entity->PUSH_POS_E(posX, posY);
    SCALE_COMPONENT scale = entity->PUSH_SCALE_E(entityInfo["scale"]["x"].asFloat(),
                                                 entityInfo["scale"]["y"].asFloat());
    RECT_COMPONENT intRect = entity->PUSH_RECT_E(entityInfo["rect"]["x"].asInt(),
                                                 entityInfo["rect"]["y"].asInt(),
                                                 entityInfo["rect"]["width"].asInt(),
                                                 entityInfo["rect"]["height"].asInt());
    TEXTURE_COMPONENT texture = getTextureComponent(entityInfo["sprite"].asString());
    entity->pushComponent(CREATE_SPRITE_COMPONENT(texture->getTexture(),
                          position->getPositions(), sf::Vector2f(scale->getScaleX(),
                          scale->getScaleY()), sf::IntRect(intRect->getIntRectLeft(),
                          intRect->getIntRectTop(), intRect->getIntRectWidth(),
                          intRect->getIntRectHeight())));
    entity->PUSH_CLOCK_E();
    if (entityInfo["health"].asBool() == true)
        entity->PUSH_HEALTH_E(entityInfo["health"].asInt());
    if (entityInfo["damage"].asBool() == true)
        entity->PUSH_DAMAGE_E(entityInfo["damage"].asInt());
    if (entityInfo["speed"].asBool() == true)
        entity->PUSH_VELOCITY_E(entityInfo["speed"].asInt());
    if (entityInfo["pattern"].asBool() == true)
        entity->PUSH_PATTERN_E(static_cast<RType::PatternType>(entityInfo["pattern"].asInt()));
    if (entityInfo["isShooting"].asBool() == true) {
        auto action = entity->PUSH_ACTION_E();
        action->setActions(SHOOTING, true);
    }
    if (entityInfo["intervalShoot"].asBool() == true) {
        entity->PUSH_INTERVALSHOOT_E(entityInfo["intervalShoot"].asFloat());
    }
    if (entityInfo["attack"].isArray()) {
        auto attackComponent = entity->PUSH_ATTACK_E();
        for (const auto &attack : entityInfo["attack"]) {
            if (attack.isString()) {
                attackComponent->pushBackAttacksPatterns(attack.asString());
            }
        }
    }
    if (!entityInfo["sound"].asString().empty() && _soundsEntity && _soundsEntity->getComponent<SoundQueueComponent>() && entityInfo["soundVolume"].asBool() == true) {
        SOUND_BUFFER_COMPONENT soundBuffer = getSoundBufferComponent(entityInfo["sound"].asString());
        _soundsEntity->getComponent<SoundQueueComponent>()->pushSound(soundBuffer->getSoundBuffer(), entityInfo["soundVolume"].asFloat());
    } else if (!entityInfo["sound"].asString().empty() && _soundsEntity && _soundsEntity->getComponent<SoundQueueComponent>()) {
        SOUND_BUFFER_COMPONENT soundBuffer = getSoundBufferComponent(entityInfo["sound"].asString());
        _soundsEntity->getComponent<SoundQueueComponent>()->pushSound(soundBuffer->getSoundBuffer());
    }

    if (entityInfo["score"].asBool() == true) {
        entity->pushComponent(std::make_shared<ScoreComponent>(entityInfo["score"].asInt()));
    }

    entity->PUSH_MENU_COMPONENT_E(GAME);
    file.close();
    if (entity->getComponent<RType::DirectionPatternComponent>() &&
        entity->getComponent<RType::DirectionPatternComponent>()->getPatternType() == RType::FOLLOW_PLAYER) {
        entityToFollow = getEntityByServerId(_coord.getEntities(), idToFollow);
        if (!entityToFollow)
            return;
        entity->getComponent<RType::DirectionPatternComponent>()->setEntityToFollow(entityToFollow->getId());
    }
}

void RType::Game::createPlayer()
{
    std::shared_ptr<RType::Entity> player = _coord.generateNewEntity();

    player->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_PLAYER));
    std::shared_ptr<RType::PositionComponent> position = player->pushComponent(std::make_shared<RType::PositionComponent>(10, 10));
    std::shared_ptr<RType::ScaleComponent> scale = player->pushComponent(std::make_shared<RType::ScaleComponent>(2.0, 2.0));
    std::shared_ptr<RType::IntRectComponent> intRect = player->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 26, 21));
    auto health = player->pushComponent(std::make_shared<RType::HealthComponent>(50));
    std::shared_ptr<RType::TextureComponent> texture = getTextureComponent("./ressources/players/player-sheet.png");

    player->pushComponent(std::make_shared<RType::SpriteComponent>(texture->getTexture(), position->getPositions(),
    sf::Vector2f(scale->getScaleX(), scale->getScaleY()),
    sf::IntRect(intRect->getIntRectLeft(),intRect->getIntRectTop(), intRect->getIntRectWidth(), intRect->getIntRectHeight())));
    player->pushComponent(std::make_shared<RType::DirectionComponent>());
    player->pushComponent(std::make_shared<RType::ClockComponent>());
    player->pushComponent(std::make_shared<RType::ActionComponent>());
    player->pushComponent(std::make_shared<VelocityComponent>(10));
    player->pushComponent(std::make_shared<RType::DamageComponent>(1));
    player->pushComponent(std::make_shared<RType::PowerUpComponent>());
    player->PUSH_MENU_COMPONENT_E(GAME);

    std::shared_ptr<RType::Entity> lifeValue = _coord.generateNewEntity();
    lifeValue->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_HEALTHTEXT));
    lifeValue->pushComponent(health);
    std::shared_ptr<TextComponent> textComponent = lifeValue->pushComponent(std::make_shared<RType::TextComponent>("Life: 100%", 60, _font));
    lifeValue->pushComponent(std::make_shared<RType::PositionComponent>(0, 950));
    textComponent->setTextWithoutVariable("Life: ");
    lifeValue->PUSH_MENU_COMPONENT_E(GAME);
}


void RType::Game::createSound()
{
    _soundsEntity = _coord.generateNewEntity();

    _soundsEntity->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_SOUNDS));
    _soundsEntity->pushComponent(std::make_shared<RType::SoundQueueComponent>());
}

void RType::Game::createWindow()
{
    std::shared_ptr<RType::Entity> window = _coord.generateNewEntity();

    window->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_WINDOW));
    window->pushComponent(std::make_shared<RType::SFWindowComponent>(1920, 1080));
    window->pushComponent(std::make_shared<RType::EventComponent>());
    window->pushComponent(std::make_shared<RType::ClockComponent>());
    window->pushComponent(std::make_shared<RType::LevelComponent>(1));
    window->pushComponent(std::make_shared<RType::MusicComponent>("ressources/musics/music.mp3"));
    window->pushComponent(std::make_shared<RType::SoundVolumeComponent>());
    auto score = window->pushComponent(std::make_shared<RType::ScoreComponent>(0));

    createParallaxBackground(window);

    window->PUSH_MENU_COMPONENT_E(HOME);

    auto mappingInput = window->pushComponent(std::make_shared<MappingInputComponent>());
    createMappingInputButton(mappingInput);
    createOptionMenu();


    std::shared_ptr<RType::Entity> scoreValue = _coord.generateNewEntity();
    scoreValue->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_SCORETEXT));
    scoreValue->pushComponent(score);
    std::shared_ptr<TextComponent> textScoreComponent = scoreValue->pushComponent(std::make_shared<RType::TextComponent>("Score: 0", 60, _font));
    scoreValue->pushComponent(std::make_shared<RType::PositionComponent>(900, 950));
    textScoreComponent->setTextWithoutVariable("Score: ");
    scoreValue->PUSH_MENU_COMPONENT_E(GAME);
}

void RType::Game::createGameSystem()
{
    std::unique_lock<std::mutex> lock(_mtx);
    _coord.generateNewSystem(std::make_shared<HandleEventSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1, true),
        std::bind(&RType::Game::disconnexion, this)
    ));

    _coord.generateNewSystem(std::make_shared<HandlePatternSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1, true)
    ));

    _coord.generateNewSystem(std::make_shared<HandleSoundSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1, true)
    ));

    _coord.generateNewSystem(std::make_shared<HandleMusicSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1, true)
    ));

    _coord.generateNewSystem(std::make_shared<HandleMoveSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1, true),
        std::bind(&RType::Game::trySendMessageToServer, this, std::placeholders::_1)
    ));

    _coord.generateNewSystem(std::make_shared<HandleMoveSpriteSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1, true)
    ));

    _coord.generateNewSystem(std::make_shared<HandleShootSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1, true),
        std::bind(&RType::Game::trySendMessageToServer, this, std::placeholders::_1)
    ));

    _coord.generateNewSystem(std::make_shared<HandleAnimationSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1, true)
    ));

    _coord.generateNewSystem(std::make_shared<HandleClearSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1, true)
    ));

    _coord.generateNewSystem(std::make_shared<HandleDrawSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1, true)
    ));

    _coord.generateNewSystem(std::make_shared<HandleDrawTextSystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1, true)
    ));

    _coord.generateNewSystem(std::make_shared<HandleDisplaySystem>(
        std::bind(&RType::Coordinator::addEntity, &_coord),
        std::bind(&RType::Coordinator::deleteEntity, &_coord, std::placeholders::_1, true)
    ));
}

void RType::Game::createParallaxBackground(std::shared_ptr<RType::Entity> window)
{
    float winMaxX = window->getComponent<RType::SFWindowComponent>()->getWindow()->getSize().x;
    float winMaxY = window->getComponent<RType::SFWindowComponent>()->getWindow()->getSize().y;
    std::unordered_map<Backgrounds, std::vector<std::string>> bgMap =
    {
        {Backgrounds::PURPLEBG, {"./ressources/parallax/purple/back.png", "./ressources/parallax/purple/front.png"}},
        {Backgrounds::BLUEBG, {"./ressources/parallax/blue/back.png", "./ressources/parallax/blue/mid.png", "./ressources/parallax/blue/front.png"}},
        {Backgrounds::REDBG, {"./ressources/parallax/red/back.png", "./ressources/parallax/red/stars.png", "./ressources/parallax/red/mid.png", "./ressources/parallax/red/front.png"}},
        {Backgrounds::SATURNBG, {"./ressources/parallax/saturn/back.png", "./ressources/parallax/blue/mid.png", "./ressources/parallax/saturn/front.png"}},
        // {Backgrounds::BROWNBG, 6},
        {Backgrounds::GREENBG, {"./ressources/parallax/green/back.png", "./ressources/parallax/green/mid.png", "./ressources/parallax/green/front.png"}}
    };
    for (std::size_t i = 0; i < bgMap.size(); i++) {
        for (std::size_t j = 0; j < bgMap[static_cast<Backgrounds>(i)].size(); j++) {
            createParallaxEntity(bgMap[static_cast<Backgrounds>(i)][j], 0, 0, winMaxX, winMaxY, j, i + 1);
            createParallaxEntity(bgMap[static_cast<Backgrounds>(i)][j], winMaxX, 0, winMaxX, winMaxY, j, i + 1);
        }
    }
}

void RType::Game::createParallaxEntity(const std::string &path, const int &posX, const int &posY,
    const int &winMaxX,const int &winMaxY, const int &index, const int &level)
{
    std::shared_ptr<RType::Entity> backgrounds = _coord.generateNewEntity();
    std::shared_ptr<RType::TextureComponent> texture = getTextureComponent(path);
    std::shared_ptr<RType::PositionComponent> position = backgrounds->pushComponent(CREATE_POS_COMPONENT(posX, posY));
    float spriteHeight = 0.;
    float spriteWidth = 0.;

    backgrounds->pushComponent(CREATE_ENTITY_TYPE(RType::E_LAYER));
    backgrounds->pushComponent(std::make_shared<SpriteComponent>(texture->getTexture(),
        position->getPositions()));
    spriteWidth = texture->getTexture()->getSize().x;
    spriteHeight = texture->getTexture()->getSize().y;
    backgrounds->getComponent<SpriteComponent>()->getSprite()->setScale(sf::Vector2f(float(winMaxX / spriteWidth), float(winMaxY / spriteHeight)));
    backgrounds->pushComponent(std::make_shared<RType::DirectionPatternComponent>(STRAIGHT_LEFT));
    backgrounds->pushComponent(std::make_shared<VelocityComponent>((index + 1)));
    backgrounds->pushComponent(std::make_shared<LevelComponent>(level));
    backgrounds->PUSH_MENU_COMPONENT_E(EVERYWHERE);
}

std::shared_ptr<RType::TextureComponent> RType::Game::getTextureComponent(const std::string &path)
{
    if (_texturesMap.find(path) != _texturesMap.end()) {
        return _texturesMap[path];
    }

    auto texture = std::make_shared<RType::TextureComponent>(path);
    _texturesMap[path] = texture;

    return texture;
}

std::shared_ptr<RType::SoundBufferComponent> RType::Game::getSoundBufferComponent(const std::string &path)
{
    if (_soundBufferMap.find(path) != _soundBufferMap.end()) {
        return _soundBufferMap[path];
    }

    auto soundBuffer = std::make_shared<RType::SoundBufferComponent>(path);
    _soundBufferMap[path] = soundBuffer;

    return soundBuffer;
}

bool RType::Game::getGameHasStarted(void) const
{
    return _initConnection;
}

void RType::Game::connectToServer(void)
{
    _client.send(Encoder::connexion());
}

void RType::Game::trySendMessageToServer(const std::basic_string<unsigned char> &message)
{
    if (_initConnection)
        _client.send(message);
}


std::ostream &operator<<(std::ostream &s, const RType::Game &game)
{
    s << game.getCoordinator();
    return s;
}

void RType::Game::disconnexion(void)
{
    // trySendMessageToServer(Encoder::disconnexion());
    // _initConnection = false;
}

std::shared_ptr<RType::Entity> RType::Game::getPlayerEntity(void)
{
    auto entities = _coord.getEntities();
    for (const auto &entity : entities) {
        if (!entity->getComponent<RType::EntityTypeComponent>())
            continue;
        if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == E_PLAYER)
            return entity;
    }
    return nullptr;
}

sf::Vector2f RType::Game::getBulletPosition(int type, int posX, int posY)
{
    // !Data to get dynamically
    switch (type) {
        case RType::E_BULLET:
            return sf::Vector2f(posX, posY + (6 * 2) / 2);
        case RType::E_BULLET_2:
            return sf::Vector2f(posX, posY + (32 * 2) / 2);
        case RType::E_BULLET_3:
            return sf::Vector2f(posX, posY + (32 * 3.) / 2);
        case RType::E_BULLET_4:
            return sf::Vector2f(posX, posY + (192 * 0.5) / 2);
        case RType::E_FORCEPOD_BULLET:
            return sf::Vector2f(posX, posY + (6 * 2) / 2);
        case RType::E_FORCEPOD_BULLET_2:
            return sf::Vector2f(posX, posY + (6 * 2) / 2);
        case RType::E_FORCEPOD_BULLET_3:
            return sf::Vector2f(posX, posY + (6 * 2) / 2);
        case RType::E_BULLET_LASER:
            return sf::Vector2f(posX, posY + (32 * 2.) / 2);
        case RType::E_BULLET_LASER_2:
            return sf::Vector2f(posX, posY + (32 * 3.) / 2);
        case RType::E_BULLET_LASER_3:
            return sf::Vector2f(posX, posY + (32 * 3.) / 2);
        case RType::E_BULLET_LASER_4:
            return sf::Vector2f(posX, posY + (48 * 4.) / 2);
        default:
            return sf::Vector2f(0, 0);
    }
}

std::shared_ptr<RType::Entity> RType::Game::getEntityByServerId(std::vector<std::shared_ptr<RType::Entity>> entities, int serverId)
{
    for (const auto &entity : entities) {
        if (entity->getServerId() == serverId)
            return entity;
    }
    return nullptr;
}

void RType::Game::createEntityMap(void)
{
    _entityTypeMap[E_OTHER] = "other";
    _entityTypeMap[E_WINDOW] = "window";
    _entityTypeMap[E_PLAYER] = "allies";
    _entityTypeMap[E_ALLIES] = "allies";
    _entityTypeMap[E_SPACE_SHIP_1] = "space_ship_1";
    _entityTypeMap[E_SPACE_SHIP_2] = "space_ship_2";
    _entityTypeMap[E_SPACE_SHIP_3] = "space_ship_3";
    _entityTypeMap[E_OCTOPUS] = "octopus";
    _entityTypeMap[E_FLY] = "fly";
    _entityTypeMap[E_BABY_FLY] = "baby_fly";
    _entityTypeMap[E_FLY_BOSS] = "fly_boss";
    _entityTypeMap[E_SPACE_SHIP_BOSS] = "space_ship_boss";
    _entityTypeMap[E_OCTOPUS_BOSS] = "octopus_boss";
    _entityTypeMap[E_BOMBER_BOSS] = "bomber_boss";
    _entityTypeMap[E_BABY_OCTOPUS] = "baby_octopus";
    _entityTypeMap[E_SPACE_SHIP_4] = "space_ship_4";
    _entityTypeMap[E_BUTTON] = "button";
    _entityTypeMap[E_LAYER] = "layer";
    _entityTypeMap[E_SHIELD] = "shield";
    _entityTypeMap[E_ITEM_WEAPON] = "item_weapon";
    _entityTypeMap[E_ITEM_SHIELD] = "item_shield";
    _entityTypeMap[E_ITEM_HEAL] = "item_heal";
    _entityTypeMap[E_BULLET] = "bullet_1";
    _entityTypeMap[E_BULLET_2] = "bullet_2";
    _entityTypeMap[E_BULLET_3] = "bullet_3";
    _entityTypeMap[E_BULLET_4] = "bullet_4";
    _entityTypeMap[E_SPACE_SHIP_BULLET] = "space_ship_bullet";
    _entityTypeMap[E_SPACE_SHIP_SEMI_DIAGONAL_UP] = "space_ship_semi_diagonal_up_bullet";
    _entityTypeMap[E_SPACE_SHIP_SEMI_DIAGONAL_DOWN] = "space_ship_semi_diagonal_down_bullet";
    _entityTypeMap[E_SPACE_SHIP_DIAGONAL_UP] = "space_ship_diagonal_up_bullet";
    _entityTypeMap[E_SPACE_SHIP_DIAGONAL_DOWN] = "space_ship_diagonal_down_bullet";
    _entityTypeMap[E_ENNEMY_BULLET] = "ennemy_bullet";
    _entityTypeMap[E_BULLET_EFFECT] = "bullet_effect";
    _entityTypeMap[E_HIT_EFFECT] = "hit_effect";
    _entityTypeMap[E_EXPLOSION_EFFECT] = "explosion_effect";
    _entityTypeMap[E_TEXT] = "text";
    _entityTypeMap[E_ITEM_FORCEPOD] = "item_forcepod";
    _entityTypeMap[E_FORCEPOD] = "forcepod";
    _entityTypeMap[E_FORCEPOD_BULLET] = "forcepod_bullet";
    _entityTypeMap[E_FORCEPOD_2] = "forcepod2";
    _entityTypeMap[E_FORCEPOD_3] = "forcepod3";
    _entityTypeMap[E_BULLET_LASER] = "laser";
    _entityTypeMap[E_BULLET_LASER_2] = "laser2";
    _entityTypeMap[E_BULLET_LASER_3] = "laser3";
    _entityTypeMap[E_BULLET_LASER_4] = "laser4";
    _entityTypeMap[E_CHARGING_EFFECT] = "charging_effect";
    _entityTypeMap[E_FORCEPOD_BULLET_2] = "forcepod_bullet2";
    _entityTypeMap[E_FORCEPOD_BULLET_3] = "forcepod_bullet3";
    _entityTypeMap[E_STING] = "sting";
    _entityTypeMap[E_STATIC_BOMB] = "static_bomb";
    _entityTypeMap[E_ZIGZAG_BOMB] = "zigzag_bomb";
    _entityTypeMap[E_ZIGZAG_BOMB_REVERSE] = "zigzag_bomb_reverse";
    _entityTypeMap[E_HIT_EFFECT_2] = "hit_effect2";
    _entityTypeMap[E_HIT_EFFECT_3] = "hit_effect3";
    _entityTypeMap[E_HIT_EFFECT_4] = "hit_effect4";
}
