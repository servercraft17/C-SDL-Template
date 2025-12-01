mkdir build

@REM Download SDL and prepare it.
mkdir libs\SDL
curl -Lo libs/SDL.zip https://github.com/libsdl-org/SDL/releases/download/release-3.2.26/SDL3-devel-3.2.26-mingw.zip
cd libs && tar -xzf SDL.zip -C SDL --strip-components=1
del SDL.zip

cd ..

@REM Download STB header files.
mkdir libs\stb
curl -Lo libs/stb/stb_image.h https://raw.githubusercontent.com/nothings/stb/refs/heads/master/stb_image.h
curl -Lo libs/stb/stb_image_resize2.h https://raw.githubusercontent.com/nothings/stb/refs/heads/master/stb_image_resize2.h

@REM Download GLM and prepare it.
mkdir libs\cglm
curl -Lo libs/cglm.zip https://github.com/recp/cglm/archive/refs/tags/v0.9.6.zip
cd libs && tar -xzf cglm.zip -C cglm --strip-components=1
del cglm.zip

cmake -Scglm -Bcglm/build -G"MinGW Makefiles" -DCMAKE_MAKE_PROGRAM=make
cd cglm/build && make

cd ../../..

copy libs\cglm\build\libcglm.dll.a build
copy libs\cglm\build\libcglm-0.dll build

copy libs\SDL\x86_64-w64-mingw32\bin\SDL3.dll build
