all: compile link

compile:
	g++ -c main.cpp -I"C:\Users\krist\Desktop\libraries\SFML-2.5.1\include" -DSFML_STATIC

link:
	g++ main.o -o main -L"C:\Users\krist\Desktop\libraries\SFML-2.5.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows

clean:
	rm -f main *.o