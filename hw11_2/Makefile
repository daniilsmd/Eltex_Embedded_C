BIN := HW11_2
OBJ := *.o
SRC := *.c

all: $(BIN)

$(BIN): $(OBJ)
		$(CC) $(OBJ) -o $(BIN) $(LDFLAGS)

%.o: %.c
		$(CC) $^ $(CFLAGS) -c