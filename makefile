includes:= -I./Libs/glfw-3.4.bin.WIN64/include -I./Libs/glad/include
#whe are keeping it static linking. 
#1 people do not have GLFW installed at system level
#2 most people do not need to modify the version
#maybe later whe make it a dll but not now
librariFiles:= ./Libs/glfw-3.4.bin.WIN64/lib-mingw-w64/libglfw3.a
libraryNames:= -lgdi32 #-lopengl32
gladBasePath:= ./Libs/glad
gladCFile:= ${gladBasePath}/src/gl.c
flags:= -Wall
targetFinal:= ./Bin/compilatio.exe
obj_folder:= ./Objects
objects:= ${obj_folder}/main.o ${obj_folder}/gl.o
#necesario por si agregamos version de linux
targetPlatform:=windows
ifeq ($(targetPlatform),windows)
flags += -mwindows 
endif

#this builds in order, it will be improved later. Here is where the actual linking gets done
build: ${objects}
	gcc -o ${targetFinal} $^ ${includes} ${librariFiles} ${libraryNames} ${flags}
#Whe must compile glad first
${obj_folder}/gl.o: ${gladCFile}
	gcc $< -o $@ -c -I ${gladBasePath}/include ${flags}
#Whe must compile this too. No necesary to link .o files so just the flags go there
${obj_folder}/main.o: main.c
	gcc -o $@ $< -c ${includes} ${flags}
