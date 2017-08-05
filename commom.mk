CC	:= gcc
CXX	:= g++
LD	:= g++

CFLAGS		+= 
CXXFLAGS	+= -std=c++1z
LDFLAGS		+= 

%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@

%.o:%.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@

default:
	make $(BIN)

run:$(BIN)
	./$(BIN)

$(BIN):$(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@
