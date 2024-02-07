TARGET = bin/dbview
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

run: clean default
		./$(TARGET) -f ./mynewdb.db -n
		./$(TARGET) -f ./mynewdb.db 
		./$(TARGET) -f ./mynewdb.db -a "Demo Dean,123 Fake St.,69420"

default: $(TARGET)

clean:
		rm -rf ./obj
		rm -rf ./bin
		rm -f ./*.db
		mkdir ./obj ./bin

$(TARGET): $(OBJ)
		gcc -o $@ $?

obj/%.o : src/%.c
		gcc -c $< -o $@ -Iinclude
