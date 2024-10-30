##
## EPITECH PROJECT, 2024
## rType
## File description:
## Makefile
##

SRC_CLIENT	=	src/client/Game.cpp\
				src/client/communication/Client.cpp\
				src/client/ClientError.cpp

SRC_ECS	=		src/ecs/Components/PositionComponent.cpp\
			src/ecs/Components/HealthComponent.cpp\
			src/ecs/Components/EntityTypeComponent.cpp\
			src/ecs/Components/SFWindowComponent.cpp\
			src/ecs/Components/EventComponent.cpp\
			src/ecs/Components/TextureComponent.cpp\
			src/ecs/Components/SpriteComponent.cpp\
			src/ecs/Components/DirectionComponent.cpp\
			src/ecs/Components/ClockComponent.cpp\
			src/ecs/Components/ActionComponent.cpp\
			src/ecs/Components/DirectionPatternComponent.cpp\
			src/ecs/Components/VelocityComponent.cpp\
			src/ecs/Components/LevelComponent.cpp\
			src/ecs/Components/ScaleComponent.cpp\
			src/ecs/Components/IntRectComponent.cpp\
			src/ecs/Components/MappingInputComponent.cpp\
			src/ecs/Components/TextComponent.cpp\
			src/ecs/Components/ClickEffectComponent.cpp\
			src/ecs/Components/MenuComponent.cpp\
			src/ecs/Components/ParseLevelInfoComponent.cpp\
			src/ecs/Systems/HandleEventSystem.cpp\
			src/ecs/Systems/HandleColisionSystem.cpp\
			src/ecs/Systems/HandleDrawSystem.cpp\
			src/ecs/Systems/HandleAnimationSystem.cpp\
			src/ecs/Systems/HandleMoveSystem.cpp\
			src/ecs/Systems/HandleMoveSpriteSystem.cpp\
			src/ecs/Systems/HandleShootSystem.cpp\
			src/ecs/Systems/HandlePatternSystem.cpp\
			src/ecs/Systems/HandleEntitySpawnSystem.cpp\
			src/ecs/Coordinator.cpp\
			src/ecs/Entity.cpp\
			src/ecs/ISystem.cpp\
			src/ecs/ASystem.cpp\
			src/ecs/EcsError.cpp

SRC_PROTOCOLHANDLER	=	./src/protocolHandler/Encoder.cpp\
						./src/protocolHandler/Decoder.cpp

SRC_COMMAND	=	./src/server/command/ACommand.cpp	\
				./src/server/server/Server.cpp	\
				./src/server/clientServer/ClientServer.cpp	\
				./src/server/Error.cpp	\
				./src/server/command/factory/CommandFactory.cpp	\
				./src/server/command/commands/ActionPlayerCommand.cpp	\
				./src/server/command/commands/ConnexionCommand.cpp	\
				./src/server/command/commands/DisconnexionCommand.cpp	\
				./src/server/command/commands/DeleteEntityCommand.cpp	\
				./src/server/command/commands/GameStartCommand.cpp	\
				./src/server/command/commands/GameEndCommand.cpp	\
				./src/server/command/commands/InfoEntityCommand.cpp	\
				./src/server/command/commands/InfoLevelCommand.cpp	\
				./src/server/command/commands/MoveEntityCommand.cpp	\
				./src/server/command/commands/MovePlayerCommand.cpp	\
				./src/server/command/commands/NewEntityCommand.cpp	\

UNIT_TEST_CLIENT_FILE	=	tests/client/Client_tests.cpp

UNIT_TEST_ESC_FILE	=	tests/ecs/Components_tests.cpp\
						tests/ecs/Entities_tests.cpp\
						tests/ecs/Coordinator_tests.cpp

UNIT_TEST_PROTOCOLHANDLER_FILE	=	./tests/protocolHandler/encoder_test.cpp\
									./tests/protocolHandler/decoder_test.cpp

UNIT_TEST_SERVER_FILE	=	tests/server/Server_tests.cpp

UNIT_TEST_COMMAND_FILE	=	tests/server/Command_tests.cpp

UNIT_TEST_FLAGS	=	-std=c++20  --coverage -lcriterion -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -ljsoncpp -llua

clean:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.gcov
	cd tests/ && rm -rf *.gcov

fclean:     clean
	rm -rf unit_tests_client
	rm -rf unit_tests_ecs
	rm -rf unit_tests_server
	rm -rf unit_tests_protocolHandler
	rm -rf unit_tests_command

unit_tests: fclean
	g++ -o unit_tests_client $(SRC_PROTOCOLHANDLER) $(SRC_CLIENT) $(SRC_ECS) $(UNIT_TEST_FLAGS) $(UNIT_TEST_CLIENT_FILE)
	g++ -o unit_tests_ecs $(SRC_PROTOCOLHANDLER) $(SRC_ECS) $(UNIT_TEST_FLAGS) $(UNIT_TEST_ESC_FILE)
	g++ -o unit_tests_protocolHandler $(SRC_PROTOCOLHANDLER) $(UNIT_TEST_FLAGS) $(UNIT_TEST_PROTOCOLHANDLER_FILE)
	g++ -o unit_tests_server $(UNIT_TEST_FLAGS) $(UNIT_TEST_SERVER_FILE)
	g++ -o unit_tests_command $(SRC_COMMAND) $(SRC_ECS) $(SRC_PROTOCOLHANDLER) $(UNIT_TEST_FLAGS) $(UNIT_TEST_COMMAND_FILE)

tests_run: unit_tests
	./unit_tests_client --verbose
	./unit_tests_ecs --verbose
	./unit_tests_protocolHandler --verbose
	./unit_tests_server --verbose
	./unit_tests_command --verbose
	make clean
