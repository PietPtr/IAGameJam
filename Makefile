CC = g++
VPATH = src
CXXFLAG = --std=c++11 -I include -Ofast
HEADERS = $(wildcard include/*.h)
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
OBJ = main.o Game.o Switch.o Line.o SolarPanel.o Battery.o Heater.o CO2Remover.o Computer.o Dish.o Light.o WaterPurifier.o
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
