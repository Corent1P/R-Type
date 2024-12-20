/*
** EPITECH PROJECT, 2024
** rType
** File description:
** AttackComponent
*/

#include "AttackComponent.hh"

RType::AttackComponent::AttackComponent():
    _currentPatternIndex(0)
{
}

void RType::AttackComponent::pushBackAttacksPatterns(Pattern pattern)
{
    switch (pattern) {
        case SPAWN_BABY_FLY:
            _patterns.push_back(AttackPatterns::spawnBabyFly);
            break;
        case SPAWN_STING:
            _patterns.push_back(AttackPatterns::spawnSting);
            break;
        case SPACE_SHIP_SHOOT:
            _patterns.push_back(AttackPatterns::spaceShipShoot);
            break;
        case WAVE_SHOOT:
            _patterns.push_back(AttackPatterns::waveShoot);
            break;
        case SPAWN_BABY_OCTOPUS:
            _patterns.push_back(AttackPatterns::spawnBabyOctopus);
            break;
        case SPAWN_KAMIKAZE_OCTOPUS:
            _patterns.push_back(AttackPatterns::spawnKamikazeOctopus);
            break;
        case SPAWN_WALL_STATIC_BOMB:
            _patterns.push_back(AttackPatterns::spawnWallStaticBomb);
            break;
        case SPAWN_WALL_ZIGZAG_BOMB:
            _patterns.push_back(AttackPatterns::spawnWallZigZagBomb);
            break;
        default:
            break;
    }
}

void RType::AttackComponent::pushBackAttacksPatterns(std::string pattern)
{
    if (pattern == "spawnBabyFly")
        _patterns.push_back(AttackPatterns::spawnBabyFly);
    else if (pattern == "spawnSting")
        _patterns.push_back(AttackPatterns::spawnSting);
    else if (pattern == "spaceShipShoot")
        _patterns.push_back(AttackPatterns::spaceShipShoot);
    else if (pattern == "waveShoot")
        _patterns.push_back(AttackPatterns::waveShoot);
    else if (pattern == "spawnBabyOctopus")
        _patterns.push_back(AttackPatterns::spawnBabyOctopus);
    else if (pattern == "spawnKamikazeOctopus")
        _patterns.push_back(AttackPatterns::spawnKamikazeOctopus);
    else if (pattern == "spawnWallStaticBomb")
        _patterns.push_back(AttackPatterns::spawnWallStaticBomb);
    else if (pattern == "spawnWallZigZagBomb")
        _patterns.push_back(AttackPatterns::spawnWallZigZagBomb);
    else
        throw EcsError("Attack pattern: " + pattern + "was not found");
}

void RType::AttackComponent::executeCurrentAttackPattern(std::shared_ptr<RType::Entity> boss, std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient)
{
    if (_currentPatternIndex < _patterns.size()) {
        _patterns[_currentPatternIndex](boss, addEntity, sendMessageToAllClient);
    }
}

void RType::AttackComponent::nextAttackPattern(void)
{
    _currentPatternIndex = (_currentPatternIndex + 1) % _patterns.size();
}

std::size_t RType::AttackComponent::getNumberOfPattern(void) const
{
	return _patterns.size();
}

std::size_t RType::AttackComponent::getCurrentPatternIndex(void) const
{
	return _currentPatternIndex;
}

std::string RType::AttackComponent::getOutput() const
{
    std::string output("Attack Component");
	return output;
}