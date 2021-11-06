glMath.dll: dynamicObject/matrix.o dynamicObject/vec3.o
	g++ -shared dynamicObject/matrix.o dynamicObject/vec3.o -O2 -o glMath.dll

dynamicObject/matrix.o: src/matrix.cpp headers/matrix.h dynamicObject
	g++ -c -fPIC src/matrix.cpp -o dynamicObject/matrix.o -O2
dynamicObject/vec3.o: src/vec3.cpp headers/vec3.h dynamicObject
	g++ -c -fPIC src/vec3.cpp -o dynamicObject/vec3.o -O2

glMath.lib: object/matrix.o object/vec3.o
	ar rcs glMath.lib object/matrix.o object/vec3.o

object/matrix.o: src/matrix.cpp headers/matrix.h object
	g++ -c src/matrix.cpp -o object/matrix.o -O2
object/vec3.o: src/vec3.cpp headers/vec3.h object
	g++ -c src/vec3.cpp -o object/vec3.o -O2

dynamicObject:
	mkdir dynamicObject
object:
	mkdir object