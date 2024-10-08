/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** InfoEntityCommand
*/

#include "InfoEntityCommand.hh"

RType::InfoEntityCommand::InfoEntityCommand(const std::vector<long> &arguments):
    ACommand(arguments, INFO_ENTITY)
{
    std::cout << "InfoEntity command created" << std::endl;
}

// TODO: ask Sacha how i get the id from the command
void RType::InfoEntityCommand::execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll, Coordinator &coord)
{
    (void)client;
    (void)sendToClient;
    (void)sendToAll;
    (void)coord;
    // TODO: ask if every entity have an x, y and rotation?
    std::shared_ptr<RType::Entity> entity = coord.getEntityById(_data[0]);
    size_t x = entity->getComponent<PositionComponent>()->getPositions().x;
    size_t y = entity->getComponent<PositionComponent>()->getPositions().y;
    int rotation = 0; //TODO: get the rotation from the entity
    int health = entity->getComponent<HealthComponent>()->getHealth();
    EntityType type = entity->getComponent<EntityTypeComponent>()->getEntityType();

    sendToClient(Encoder::infoEntity(entity->getId(), type, x, y, rotation, health));
    // std::cout << "execution of info entity command" << std::endl;
}
