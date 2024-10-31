#include "SoundQueueComponent.hh"
#include <iostream>

RType::SoundQueueComponent::SoundQueueComponent():
    _globalSoundVolume(100)
{}

void RType::SoundQueueComponent::pushSound(const sf::SoundBuffer &soundBuffer, float volume)
{
    auto sound = std::make_shared<sf::Sound>(soundBuffer);
    sound->setVolume(volume * (_globalSoundVolume / 100.0));
    _sounds.push_back({sound, false});
}

void RType::SoundQueueComponent::deleteFinishedSound()
{
    for (auto it = _sounds.begin(); it != _sounds.end(); ) {
        auto& [sound, hasPlayed] = *it;

        if (sound->getStatus() == sf::Sound::Stopped && hasPlayed) {
            it = _sounds.erase(it);
        } else {
            ++it;
        }
    }
}

void RType::SoundQueueComponent::playAllSounds()
{
    for (auto& [sound, hasPlayed] : _sounds) {
        if (sound->getStatus() != sf::Sound::Status::Playing) {
            sound->play();
            hasPlayed = true;
        }
    }
}

void RType::SoundQueueComponent::setGlobalSoundVolume(int volume)
{
    _globalSoundVolume = volume < 0 ? 0 : volume;
    _globalSoundVolume = _globalSoundVolume > 100 ? 100 : _globalSoundVolume;
    for (auto& [sound, hasPlayed] : _sounds) {
        sound->setVolume(sound->getVolume() * _globalSoundVolume / 100);
    }
}

std::size_t RType::SoundQueueComponent::getGlobalSoundVolume() const
{
    return _globalSoundVolume;
}

std::string RType::SoundQueueComponent::getOutput() const
{
    return "Sound Queue Component";
}

const std::vector<std::tuple<std::shared_ptr<sf::Sound>, bool>>& RType::SoundQueueComponent::getSounds() const
{
    return _sounds;
}
