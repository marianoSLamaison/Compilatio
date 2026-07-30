includes:= -I./Libs/glfw-3.4.bin.WIN64/include -I./Libs/glad/include
#whe are keeping it static linking. 
#1 people do not have GLFW installed at system level
#2 most people do not need to modify the version
#maybe later whe make it a dll but not now
librariFiles:= ./Libs/glfw-3.4.bin.WIN64/lib-mingw-w64/libglfw3.a
libraryNames:= -lgdi32 #-lopengl32
gladBasePath:= ./Libs/glad
gladCFile:= ${gladBasePath}/src/gl.c
flags= -Wall 
targetPlatform:=windows
ifeq ($(targetPlatform),windows)
flags += -mwindows 
endif

#this builds in order, it will be improved later. Here is where the actual linking gets done
build: gl.o main.o 
	gcc -o compilatio.exe $^ ${includes} ${librariFiles} ${libraryNames} ${flags}
#Whe must compile glad first
gl.o: ${gladCFile}
	gcc $< -o gl.o -c -I ${gladBasePath}/include ${flags}
#Whe must compile this too. No necesary to link .o files so just the flags go there
main.o: main.c
	gcc -o main.o $< -c ${flags}
