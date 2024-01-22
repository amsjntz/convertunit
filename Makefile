SOURCES= $(wildcard src/*.c)
OBJECTFILES= $(subst .c,.o,$(SOURCES))

CFLAGS= -Wall -Wextra -std=c99

ifdef DEBUG
	CFLAGS+= -g
endif

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

compile: objs
	gcc $(CFLAGS) $(OBJECTFILES) -o build/convertunit -L../bignum/ -lbignum -I../bignum/include/

objs: $(OBJECTFILES)

%.o: %.c
	gcc -c $(CFLAGS) $< -o $@ -L../bignum/ -lbignum -I../bignum/include/

run: compile
	./build/convertunit

clean:
	find . -type f -name '*.o' -delete
	rm -f vgcore.*

