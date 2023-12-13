release:
	bintostruct dxcube_resize128_02.bmp dxfacelight.h dxtexture 
	windres resource.rc -o resource.o
	gcc -s -c loadbmp.c -o bmp.o
	gcc -s -c main.c -o main.o
	gcc -s resource.o bmp.o main.o -o main -o main -Wl,-subsystem,windows -lenigl -lopengl32 -lglu32 -lgdi32

debug:
	bintostruct dxcube_resize128_02.bmp dxfacelight.h dxtexture
	gcc -g -c loadbmp.c -o bmp.o
	gcc -g -c main.c -o main.o
	gcc bmp.o main.o -o main -o main -lenigl -lopengl32 -lglu32 -lgdi32

clean:
	rm -r *.o
	rm -r *.exe