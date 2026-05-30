CXX     = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET  = skylink
SRCDIR  = src

SOURCES = $(SRCDIR)/main.cpp \
          $(SRCDIR)/Flight.cpp \
          $(SRCDIR)/DomesticFlight.cpp \
          $(SRCDIR)/InternationalFlight.cpp \
          $(SRCDIR)/CharterFlight.cpp \
          $(SRCDIR)/Passenger.cpp \
          $(SRCDIR)/EconomyPassenger.cpp \
          $(SRCDIR)/BusinessPassenger.cpp \
          $(SRCDIR)/FirstClassPassenger.cpp \
          $(SRCDIR)/Ticket.cpp \
          $(SRCDIR)/Airline.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
