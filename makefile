includes:= -I./Libs/glfw-3.4.bin.WIN64/include -I./Libs/include
librariFiles:= ./Libs/glfw-3.4.bin.WIN64/lib-mingw-w64/libglfw3.a
flags:= -Wall 
build:
	gcc ./Libs/src/gl.c main.c -o compilatio.exe ${includes} ${librariFiles} -lgdi32 -lopengl32 ${flags}

