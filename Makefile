CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC = src/main.cpp \
      src/parser.cpp \
      src/executor.cpp \
      src/pipeline.cpp \
      src/redirect.cpp \
      src/history.cpp \
      src/builtin.cpp \
      src/signals.cpp \
      src/custom.cpp

TARGET = NeoShell

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)