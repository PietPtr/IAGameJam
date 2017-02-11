CC = g++
VPATH = src
CXXFLAG = --std=c++11 -I include -Ofast
HEADERS = $(wildcard include/*.h)
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
OBJ = main.o Game.o Switch.o Line.o Connection.o Machines/SolarPanel.o Machines/Battery.o Machines/Heater.o Machines/CO2Remover.o Machines/Computer.o Machines/Dish.o Machines/Light.o Machines/WaterPurifier.o
EXEC = game
all : ll
%.o : %.cpp
	$(CC) -c $< -o $@ $(CXXFLAG)
ll : $(OBJ) $(HEADERS)
	$(CC) -o $(EXEC) $(OBJ) $(LIBS)
.PHONY : clean
clean :
	rm $(EXEC) $(OBJ)

run : ll
	./game
