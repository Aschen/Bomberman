##
## Makefile for  in /home/brunne_r/Public/cpp_bomberman
##
## Made by Romain Brunner
## Login   <brunne_r@epitech.net>
##
## Started on  Thu 22/05/2014 00:00
##

CXX	=		clang++

RM	=		rm -f

DIR_INCS =		-I./src/network/includes/ -I./src/game/includes/ -I./src/graph/includes/

DIR_LIBS =		./libs/


FILE_SERVER_NO_PATH	=	Server.cpp \
				Client.cpp \
				Network.cpp \
				Socket.cpp \
				Time.cpp \

FILE_GAME_NO_PATH	=	AElem.cpp \
				Player.cpp \
				Maps.cpp \
				Gameplay.cpp \
				Bomb.cpp \
				GBox.cpp \
				Wall.cpp \
				GFlames.cpp \

FILE_GRAPH_NO_PATH	=	BasicShader.cpp \
				GameEngine.cpp \
				Wall.cpp \
				AObject.cpp \
				Player.cpp \
				Box.cpp \
				Bomb.cpp \
				Flames.cpp \
				Menu.cpp \
				Cursor.cpp \

FILE_SERVER	=	$(addprefix ./src/network/, $(FILE_SERVER_NO_PATH))
FILE_GAME	=	$(addprefix ./src/game/, $(FILE_GAME_NO_PATH))
FILE_GRAPH	=	$(addprefix ./src/graph/, $(FILE_GRAPH_NO_PATH))


SRCS_SERVER	=	$(FILE_SERVER) $(FILE_GAME) $(FILE_GRAPH) src/network/maintest.cpp

SRCS_CLIENT	=	$(FILE_SERVER) $(FILE_GAME) $(FILE_GRAPH) src/network/maintestclient.cpp

SRCS_GAME	=	$(FILE_SERVER) $(FILE_GAME) $(FILE_GRAPH) src/game/gameplay_main.cpp

SRCS_GRAPH	=	$(FILE_SERVER) $(FILE_GAME) $(FILE_GRAPH) src/graph/main_graph.cpp


#CXXFLAGS=	-g3 ##-Wall -W -Wextra
#CXXFLAGS=	-W -Wall
CXXFLAGS +=	$(DIR_INCS) -g3

LXXFLAGS = -lgdl_gl -lGL -lGLEW -ldl -lrt -lfbxsdk -lSDL2 -lpthread -g3


OBJS_SERVER	=	$(SRCS_SERVER:.cpp=.o)

OBJS_CLIENT	=	$(SRCS_CLIENT:.cpp=.o)

OBJS_GAME	=	$(SRCS_GAME:.cpp=.o)

OBJS_GRAPH	=	$(SRCS_GRAPH:.cpp=.o)


NAME_SERVER	=	server

NAME_CLIENT	=	client

NAME_GAME	=	game

NAME_GRAPH	=	bomberman

all:		 $(NAME_GRAPH)

$(NAME_SERVER):	$(OBJS_SERVER)
		$(CXX) -o $(NAME_SERVER) $(OBJS_SERVER) -L$(DIR_LIBS) $(LXXFLAGS)

$(NAME_CLIENT):	$(OBJS_CLIENT)
		$(CXX) -o $(NAME_CLIENT) $(OBJS_CLIENT) -L$(DIR_LIBS) $(LXXFLAGS)

$(NAME_GAME):	$(OBJS_GAME)
		$(CXX) -o $(NAME_GAME) $(OBJS_GAME) -L$(DIR_LIBS) $(LXXFLAGS)

$(NAME_GRAPH):	$(OBJS_GRAPH)
		$(CXX) -o $(NAME_GRAPH) $(OBJS_GRAPH) -L$(DIR_LIBS) $(LXXFLAGS)

clean:
		$(RM) $(OBJS_SERVER)
		$(RM) $(OBJS_CLIENT)
		$(RM) $(OBJS_GAME)
		$(RM) $(OBJS_GRAPH)

fclean:		clean
		$(RM) $(NAME_GRAPH)

debug:		$(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_GAME)
		$(CXX) -o -g3 $(NAME_SERVER) $(OBJS_SERVER)
		$(CXX) -o -g3 $(NAME_CLIENT) $(OBJS_CLIENT)
		$(CXX) -o -g3 $(NAME_GRAPH) $(OBJS_GRAPH)
		$(CXX) -o -g3 $(NAME_GAME) $(OBJS_GAME)

re: fclean all
