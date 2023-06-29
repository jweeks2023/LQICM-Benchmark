CC = clang-16
EFLAGS = -Wall -Werror
FLAGS = -lm -Werror
SRCDIR = ./CodeToTest
SOURCES := ${wildcard $(SRCDIR)/*.c}
OBJECTS := ${SOURCES:.c=.o}

.PHONY: errorChecking

errorChecking: ${OBJECTS}
	@${CC} ${FLAGS} $^ -o $@

${SRCDIR}/%.o: ${SRCDIR}/%.c
	@${CC} ${EFLAGS} -c $< -o $@ || { echo "Skipping $< due to errors/warnings"; rm -f $@; }

clean:
	rm -f $(OBJECTS)
