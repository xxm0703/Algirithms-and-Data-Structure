all: echo

echo.o: echo.c
	gcc -c -Wall echo.c

main.o: main.c
	gcc -c -Wall main.c

print: main.o echo.o
	gcc main.o echo.o -o print

clean:
	rm *.o echo

