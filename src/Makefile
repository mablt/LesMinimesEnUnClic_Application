CC = g++ 
CPP_FLAGS = -std=c++17 -w 
EXEC_NAME = LesMinimesEnUnClic
OBJ_FILES = main.o Date.o Boat.o Deckboat.o Sailboat1.o Sailboat2.o User.o Subscriber.o Visitor.o Place.o FasteningRing.o Mooring.o Agreement.o Receipt.o Port.o PortManagement.o

$(EXEC_NAME): $(OBJ_FILES)
	$(CC) $(CPP_FLAGS) -o $(EXEC_NAME) $(OBJ_FILES)
Date.o: Date.cpp ../headers/Date.hpp
	$(CC) $(CPP_FLAGS) -c Date.cpp
Boat.o: Boat.cpp ../headers/Boat.hpp 
	$(CC) $(CPP_FLAGS) -c Boat.cpp
DeckBoat.o: Deckboat.cpp ../headers/Deckboat.hpp
	$(CC) $(CPP_FLAGS) -c Deckboat.cpp
Sailboat1.o: Sailboat1.cpp ../headers/Sailboat1.hpp
	$(CC) $(CPP_FLAGS) -c Sailboat1.cpp
Sailboat2.o: Sailboat2.cpp ../headers/Sailboat2.hpp
	$(CC) $(CPP_FLAGS) -c Sailboat2.cpp
User.o: User.cpp ../headers/User.hpp
	$(CC) $(CPP_FLAGS) -c User.cpp
Subscriber.o: Subscriber.cpp ../headers/Subscriber.hpp
	$(CC) $(CPP_FLAGS) -c Subscriber.cpp
Visitor.o: Visitor.cpp ../headers/Visitor.hpp
	$(CC) $(CPP_FLAGS) -c Visitor.cpp
Place.o: Place.cpp ../headers/Place.hpp
	$(CC) $(CPP_FLAGS) -c Place.cpp
FasteningRing.o: FasteningRing.cpp ../headers/FasteningRing.hpp
	$(CC) $(CPP_FLAGS) -c FasteningRing.cpp
Mooring.o: Mooring.cpp ../headers/Mooring.hpp
	$(CC) $(CPP_FLAGS) -c Mooring.cpp
Agreement.o: Agreement.cpp ../headers/Agreement.hpp
	$(CC) $(CPP_FLAGS) -c Agreement.cpp
Receipt.o: Receipt.cpp ../headers/Receipt.hpp
	$(CC) $(CPP_FLAGS) -c Receipt.cpp
Port.o: Port.cpp ../headers/Port.hpp
	$(CC) $(CPP_FLAGS) -c Port.cpp
PortManagement.o: PortManagement.cpp ../headers/PortManagement.hpp
	$(CC) $(CPP_FLAGS) -c PortManagement.cpp
main.o: main.cpp 
	$(CC) $(CPP_FLAGS) -c main.cpp
clean:
	rm  $(OBJ_FILES) $(EXEC_NAME)