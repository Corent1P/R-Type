##
## EPITECH PROJECT, 2024
## rType
## File description:
## Makefile
##

SRC_CLIENT	=	src/client/Game.cpp\

SRC_ECS	=		src/ecs/Components/PositionComponent.cpp\
			src/ecs/Components/HealthComponent.cpp\
			src/ecs/Components/EntityTypeComponent.cpp\
			src/ecs/Components/EventComponent.cpp\
			src/ecs/Components/SFWindowComponent.cpp\
			src/ecs/Components/TextureComponent.cpp\
			src/ecs/Components/SpriteComponent.cpp\
			src/ecs/Components/DirectionComponent.cpp\
			src/ecs/Components/ClockComponent.cpp\
			src/ecs/Components/VelocityComponent.cpp\
			src/ecs/Components/ActionComponent.cpp\
			rc/ecs/Components/LevelComponent.cpp\
			src/ecs/Systems/HandleEventSystem.cpp\
			src/ecs/Systems/HandleDrawSystem.cpp\
			src/ecs/Systems/HandleAnimationSystem.cpp\
			src/ecs/Systems/HandleMoveSystem.cpp\
			src/ecs/Coordinator.cpp\
			src/ecs/Entity.cpp\
			src/ecs/ISystem.cpp\
			src/ecs/ASystem.cpp\
			src/ecs/Error.cpp

SRC_PROTOCOLHANDLER	=	./src/protocolHandler/Encoder.cpp\
						./src/protocolHandler/Decoder.cpp

UNIT_TEST_CLIENT_FILE	=	tests/client/Client_tests.cpp

UNIT_TEST_ESC_FILE	=	tests/ecs/Components_tests.cpp\
						tests/ecs/Entities_tests.cpp\
						tests/ecs/Coordinator_tests.cpp

UNIT_TEST_PROTOCOLHANDLER_FILE	=	./tests/protocolHandler/encoder_test.cpp\
									./tests/protocolHandler/decoder_test.cpp

UNIT_TEST_SERVER_FILE	=	tests/server/Server_tests.cpp

UNIT_TEST_FLAGS	=	-std=c++20  --coverage -lcriterion -lsfml-graphics -lsfml-window -lsfml-system

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

unit_tests: fclean
	g++ -o unit_tests_client $(SRC_CLIENT) $(SRC_ECS) $(UNIT_TEST_FLAGS) $(UNIT_TEST_CLIENT_FILE)
	g++ -o unit_tests_ecs $(SRC_ECS) $(UNIT_TEST_FLAGS) $(UNIT_TEST_ESC_FILE)
	g++ -o unit_tests_protocolHandler $(SRC_PROTOCOLHANDLER) $(UNIT_TEST_FLAGS) $(UNIT_TEST_PROTOCOLHANDLER_FILE)
	g++ -o unit_tests_server $(UNIT_TEST_FLAGS) $(UNIT_TEST_SERVER_FILE)

tests_run: unit_tests
	./unit_tests_client --verbose
	./unit_tests_ecs --verbose
	./unit_tests_protocolHandler --verbose
	./unit_tests_server --verbose
	make clean
