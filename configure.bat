mkdir build

@REM Download SDL and prepare it.
mkdir libs\SDL
curl -Lo libs/SDL.zip https://github.com/libsdl-org/SDL/releases/download/release-3.2.26/SDL3-devel-3.2.26-mingw.zip
cd libs && tar -xzf SDL.zip -C SDL --strip-components=1
del SDL.zip

cd ..

copy libs\SDL\x86_64-w64-mingw32\bin\SDL3.dll build