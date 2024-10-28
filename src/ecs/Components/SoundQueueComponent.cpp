#include "SoundQueueComponent.hh"
#include <iostream>

void RType::SoundQueueComponent::pushSound(const sf::SoundBuffer &soundBuffer, float volume)
{
    auto sound = std::make_shared<sf::Sound>(soundBuffer);
    sound->setVolume(volume);
    _sounds.push_back({sound, false});
}

void RType::SoundQueueComponent::deleteFinishedSound()
{
    for (auto it = _sounds.begin(); it != _sounds.end(); ) {
        auto& [sound, hasPlayed] = *it;

        if (sound->getStatus() == sf::Sound::Stopped && hasPlayed)
        {
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

std::string RType::SoundQueueComponent::getOutput() const
{
    return "Sound Queue Component";
}

const std::vector<std::tuple<std::shared_ptr<sf::Sound>, bool>>& RType::SoundQueueComponent::getSounds() const
{
    return _sounds;
}
