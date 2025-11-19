mkdir build

@REM Download SDL and prepare it.
mkdir libs\SDL
curl -Lo libs/SDL.zip https://github.com/libsdl-org/SDL/releases/download/release-3.2.26/SDL3-devel-3.2.26-mingw.zip
cd libs && tar -xzf SDL.zip -C SDL --strip-components=1
del SDL.zip

cd ..

mkdir libs\stb
curl -Lo libs/stb/stb_image.h https://raw.githubusercontent.com/nothings/stb/refs/heads/master/stb_image.h
curl -Lo libs/stb/stb_image_resize2.h https://raw.githubusercontent.com/nothings/stb/refs/heads/master/stb_image_resize2.h

copy libs\SDL\x86_64-w64-mingw32\bin\SDL3.dll build