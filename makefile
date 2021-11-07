CC=gcc
# CFLAGS=-I. -g -Wall -fsanitize=address,undefined -fno-omit-frame-pointer
CFLAGS=-I. -g -Wall
CXX      = g++
CXXFLAGS = -Wall -ansi -g -std=c++17

DEPS =
ODIR = ./obj
_OBJ = ordered_lock_test.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
LIBS=-lm -pthread

# default build test app
ordered_lock_test: $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)
	chmod a+x $@

# run valgrind
valgrind: ordered_lock_test
	valgrind --leak-check=full --log-file="./valgrind_log.txt" --show-leak-kinds=all --track-origins=yes --show-reachable=yes --trace-children=yes ./$<
	cat ./valgrind_log.txt

$(ODIR)/%.o: %.c $(DEPS) | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: %.cpp $(DEPS) | $(ODIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(ODIR):
	mkdir -p $@

clean:
	rm -f ./ordered_lock_test $(OBJ) gmon.out ./valgrind_log.txt
	rm -rf $(ODIR)