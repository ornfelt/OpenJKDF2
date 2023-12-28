# notes

To build on windows:

1. follow instructions from building.md

2. use cmake gui to generate build files.

3. build in release should succeed. if you want to build with debug configuration, try these steps: first try to build in debug (some stuff will fail).

4. build in release to generate required dll's (or build them manually / change target dll's).

5. <s>open build\gamenetworkingsockets\gamenetworkingsockets.sln -> right click gamenetworkingsockets -> properties -> all configurations -> c/c++ -> code generation -> set runtime library to multi-threaded debug (/mtd). save and close.</s>

6. build in debug again!

To build on Linux:

Use original fork, or do this:

git clone --recurse-submodules -j8 https://github.com/ornfelt/OpenJKDF2

cd OpenJKDF2 && git checkout a3ecb2bc5991021e47e070129b4eda1363946140

git clone --recurse-submodules https://github.com/ValveSoftware/GameNetworkingSockets lib/GameNetworkingSockets

cd lib/GameNetworkingSockets && git checkout 505c697d0abef5da2ff3be35aa4ea3687597c3e9 && cd -

git clone --recurse-submodules https://github.com/glennrp/libpng lib/libpng

cd lib/libpng && git checkout 07b8803110da160b158ebfef872627da6c85cbdf && cd -

git clone --recurse-submodules https://github.com/madler/zlib lib/zlib

cd lib/zlib && git checkout 04f42ceca40f73e2978b50e93806c2a18c1281fc && cd -

./build_linux64.sh

# openjkdf2

![macos screenshot](docs/images/screenshot.png)

## [latest releases](https://github.com/shinyquagsire23/openjkdf2/releases) | [report a crash or bug](https://github.com/shinyquagsire23/openjkdf2/issues)

openjkdf2 is a function-by-function reimplementation of df2 in c, with 64-bit ports to windows 7+, macos 10.15+, and linux. files are organized as closely to the original game as possible, based on symbols from the grim fandango remaster android/linux/macos port, as well as scattered assertions from various other games. it also contains the original versions of `byacc` and `flex` used for cog script parsing.

openjkdf2 does *not* include any original game assets; a valid copy of jkdf2 is *required* and can be purchased from [gog](https://www.gog.com/game/star_wars_jedi_knight_dark_forces_ii) or [steam](https://store.steampowered.com/app/32380/star_wars_jedi_knight_dark_forces_ii/). the gog version is recommended, since it is drm-free and also includes the soundtrack in ogg vorbis format. if you'd like to try before you buy, a webassembly demo of openjkdf2 can be found at https://maxthomas.dev/openjkdf2/.

support for playing the original soundtrack from ogg vorbis files is primarily supported for the gog and steam versions of the game assets. original disk soundtracks can also be loaded from `music/1/track<1..11>.ogg` and `music/2/track<1..11>.ogg` for each disk's soundtrack. if files are missing, it will instead attempt to use a gog track number from `music/track<12..32>.ogg`. dumping the soundtrack from disks at install time is planned for a future release of openjkdf2, but is not currently implemented.

## platforms
openjkdf2 supports the following configurations:

| configuration | renderer | description |
| --- | --- | --- |
| 64-bit windows/sdl2 | opengl 3.3 | 64-bit windows compilation with sdl2 and openal. directx dependencies are replaced with sdl2 and openal. |
| macos x86_64/aarch64 | opengl 3.3 | 64-bit macos compilation with sdl2 and openal. all release packages include both intel and arm64. |
| 64-bit linux/sdl2 | opengl 3.3 | 64-bit linux compilation with sdl2 and openal. |
| emscripten/webassembly | webgl 2/opengl es 3 | webassembly with sdl2 and openal. runs in a web browser. since wasm only supports 32-bit pointers, this will likely be less buggy than 64-bit, but less performant. |
| x86 linux/sdl2, mmap blobs | opengl 3.3 | 32-bit linux compilation with sdl2 and openal. jk.exe is memory mapped into the process and used as a "binary blob"; unimplemented functions will fall back to jk.exe implementations. |
| 32-bit linux/sdl2, blobless | opengl 3.3 | 32-bit linux compilation with sdl2 and openal. the output executable is a swap-in replacement for jk.exe, but will be missing functions and will crash on reaching unimplemented code. |
| x86 win32/mingw dll | software/directx | win32 hooked build, jk.exe is patched to load `df2_reimpl.dll` execute `hook_init_win` before jk.exe's `main` function. unimplemented functions will fall back to jk.exe implementations. `df2_reimpl_kvm.dll` is used for the kvm target |

the following implementations are in-progress or planned:

| configuration | renderer | description | status |
| --- | --- | --- | --- |
| android | opengl es 3 | not a huge priority, but would be nice to have. | it compiles and renders! input/menuing is lacking. |
| ios | metal? | not a huge priority, but would be nice to have. | not started |
| switch libnx | opengl es 3 | not a huge priority, but would be nice to have. | not started |
| 32-bit windows/sdl2 | opengl 3.3 | windows compilation with sdl2 and openal. directx dependencies are replaced with sdl2 and openal. targeting windows xp ~ windows 7 | not started |
| 32-bit windows/directx | direct3d 3 | faithful decompilation with original directx bindings/renderer. | not started |

linux building works on aarch64/rpi4 with llvmpipe, but v3d gles has trouble with palettes.

openjkdf2 requires game data from a licensed copy of jedi knight: dark forces ii in order to run; no game assets are provided by openjkdf2. on linux, paths and filenames may be case-sensitive. your directory structure should look something like this:
```
.
├── jk.exe
├── music
│   ├── track12.ogg
│   ├── track13.ogg
│   ├── track14.ogg
│   ├── track15.ogg
│   ├── track16.ogg
│   ├── track17.ogg
│   ├── track18.ogg
│   ├── track22.ogg
│   ├── track23.ogg
│   ├── track24.ogg
│   ├── track25.ogg
│   ├── track26.ogg
│   ├── track27.ogg
│   ├── track28.ogg
│   ├── track29.ogg
│   ├── track30.ogg
│   ├── track31.ogg
│   └── track32.ogg
├── episode
│   ├── jk1.gob
│   ├── jk1ctf.gob
│   └── jk1mp.gob
├── openjkdf2-64
├── player
└── resource
    ├── res1hi.gob
    ├── res2.gob
    ├── jk_.cd
    └── video
        ├── 01-02a.smk
        ├── 03-04a.smk
        ├── 06a.smk
        ├── 08-10a.smk
        ├── 12a.smk
        ├── 16a.smk
        ├── 18-19a.smk
        ├── 21a.smk
        ├── 23a.smk
        ├── 25a.smk
        ├── 27a.smk
        ├── 33-34a.smk
        ├── 36a.smk
        ├── 38a.smk
        ├── 39a.smk
        ├── 41-42a.smk
        ├── 41da.smk
        ├── 41dsa.smk
        ├── 44a.smk
        ├── 46a.smk
        ├── 48a.smk
        ├── 50a.smk
        ├── 52-53a.smk
        ├── 54a.smk
        └── 57a.smk
```

## building

see [here](building.md) for instructions.

## contributing

contributions in the form of code cleanup and documentation are highly welcomed. see [contributing.md](contributing.md) for details on what kinds of cleanup tasks still need to be done. openjkdf2 is not currently accepting monetary donations, however [detailed bug and crash reports](https://github.com/shinyquagsire23/openjkdf2/issues) are always appreciated, including bugs/crashes involving mods.

## tl;dr: what isn't implemented, yet
 - load configuration and save configuration in setup > controls > options
 - using plus or minus to resize the screen (with sdl2, resolution auto-resizes to window size)

## usage with original jk.exe and directx using hooks
see [here](hooks.md) for instructions.

## methodology
the bulk of research and documentation occurs in ida. every function has been identified to a file prefix (ie `stdhashtable_`) with a corresponding .c/.h file. renderdroid (`rd*`) and lec stdlib (`std*`) functions are 90% canonically named, based on symbols from grim fandango remastered.

reverse engineering is a parallel effort between structure documentation and function identification. once structures are sufficiently documented, hex-rays can be used for decompilation. while most hex-rays output works outright, many loops and structures require manual intervention. output is generally cleaned and tidied to remove redunant stack variables or too-deep nesting. `sizeof` and obvious inlining and macros should also be adjusted as appropriate.

engine variables and yet-to-be-decompiled functions are referenced using `define` macros and static function pointers, respectively. once a file is decompiled enough that an engine variable is no longer referenced by non-decompiled code, the variables can be declared in their respective c files. for decompiled functions which are only referenced by non-decompiled functions, a `hook_function` call is added in `main.c` to redirect code execution to `df2_reimpl.dll` from `jk.exe`.

progress is tracked using `analyze.py`, `output.map` and `ida_copypaste_funclist_nostdlib.txt`: after compiling `df2_reimpl.dll`, symbols can be compared against the `.idb` to determine how much of the original `.text` is actually in use, and how much has been hooked and replaced.

if you'd like a copy of my idb to examine functions which haven't been decompiled yet (or for any other use), let me know.

## current progress

generated using `analyze.py`. some filenames may be inaccurate or incomplete (see `ida_copypaste_funclist_nostdlib.txt` for a full function name listing).

```

[file]                         [size]     [% of text]   [% complete]  [decomp / total] 
directx                        0x1e       0.003%        100.000%        5 / 5          
jkgob                          0x29       0.004%        100.000%        2 / 2          
jkguidecision                  0x45       0.006%        100.000%        3 / 3          
sithstrtable                   0x5b       0.008%        100.000%        4 / 4          
sithcopyright                  0x67       0.010%        100.000%        1 / 1          
jkstrings                      0x89       0.013%        100.000%        5 / 5          
jkguigeneral                   0xc5       0.018%        100.000%        3 / 3          
jksmack                        0xee       0.022%        100.000%        4 / 4          
rdface                         0xf6       0.023%        100.000%        4 / 4          
jkguicontroloptions            0x105      0.024%        100.000%        3 / 3          
stdhashkey                     0x107      0.024%        100.000%       10 / 10         
rdcanvas                       0x113      0.025%        100.000%        4 / 4          
jkguiesc                       0x18f      0.037%        100.000%        3 / 3          
rdroid                         0x1f6      0.047%        100.000%       27 / 27         
sithheader                     0x1f9      0.047%        100.000%        1 / 1          
sithtime                       0x213      0.049%        100.000%        6 / 6          
jkguisingletally               0x21b      0.050%        100.000%        4 / 4          
jkguisetup                     0x240      0.053%        100.000%        4 / 4          
jkguisound                     0x274      0.058%        100.000%        3 / 3          
sithitem                       0x275      0.058%        100.000%        5 / 5          
jkguigameplay                  0x2b2      0.064%        100.000%        3 / 3          
stdmemory                      0x2ba      0.065%        100.000%        7 / 7          
sithevent                      0x2e3      0.069%        100.000%        9 / 9          
stdmci                         0x2ef      0.070%        100.000%        7 / 7          
jkguiobjectives                0x308      0.072%        100.000%        4 / 4          
jkcontrol                      0x331      0.076%        100.000%        4 / 4          
windows                        0x39a      0.085%        100.000%       11 / 11         
stdstring                      0x3b3      0.088%        100.000%       11 / 11         
sithrendersky                  0x3c2      0.089%        100.000%        5 / 5          
jkguidialog                    0x3e0      0.092%        100.000%        6 / 6          
sithmodel                      0x3f1      0.094%        100.000%        8 / 8          
rdthing                        0x42f      0.099%        100.000%       12 / 12         
stdgdi                         0x430      0.099%        100.000%       10 / 10         
jkcutscene                     0x443      0.101%        100.000%        7 / 7          
sithkeyframe                   0x44e      0.102%        100.000%        5 / 5          
stdpcx                         0x45e      0.104%        100.000%        2 / 2          
sithdsscog                     0x460      0.104%        100.000%        4 / 4          
smack                          0x466      0.104%        100.000%        6 / 6          
sithplayeractions              0x46f      0.105%        100.000%        3 / 3          
rdmath                         0x47d      0.107%        100.000%        6 / 6          
rdlight                        0x49f      0.110%        100.000%        8 / 8          
jkguimain                      0x4b1      0.111%        100.000%        6 / 6          
stdfnames                      0x4ee      0.117%        100.000%       14 / 14         
sithsprite                     0x4f1      0.117%        100.000%        6 / 6          
jkgui                          0x4fb      0.118%        100.000%       10 / 10         
jkguititle                     0x4fb      0.118%        100.000%       10 / 10         
sithmaterial                   0x4fd      0.118%        100.000%        9 / 9          
wuregistry                     0x5b2      0.135%        100.000%       12 / 12         
stdhashtable                   0x5d6      0.138%        100.000%       10 / 10         
video                          0x5dc      0.139%        100.000%        5 / 5          
sithconsole                    0x5de      0.139%        100.000%       13 / 13         
sithexplosion                  0x61d      0.145%        100.000%        4 / 4          
sithaiclass                    0x689      0.155%        100.000%        7 / 7          
rdprimit2                      0x69a      0.157%        100.000%        5 / 5          
sithcogscript                  0x6ca      0.161%        100.000%        9 / 9          
window                         0x6db      0.163%        100.000%       13 / 13         
stdgob                         0x6dd      0.163%        100.000%       14 / 14         
jkai                           0x6e7      0.164%        100.000%        5 / 5          
sithmain                       0x72b      0.170%        100.000%       16 / 16         
jkguicontrolsaveload           0x732      0.171%        100.000%        6 / 6          
jkguiplayer                    0x73a      0.171%        100.000%        5 / 5          
rdsprite                       0x76d      0.176%        100.000%        5 / 5          
stdconffile                    0x78d      0.179%        100.000%       13 / 13         
jkguimap                       0x793      0.180%        100.000%        8 / 8          
sithtemplate                   0x79d      0.181%        100.000%       10 / 10         
sithparticle                   0x7f5      0.189%        100.000%       10 / 10         
sithsector                     0x806      0.190%        100.000%       13 / 13         
sithcomm                       0x80b      0.191%        100.000%       11 / 11         
sithmap                        0x814      0.192%        100.000%        6 / 6          
main                           0x87b      0.201%        100.000%        4 / 4          
jkguimultitally                0x8aa      0.206%        100.000%        7 / 7          
jkguisingleplayer              0x8d8      0.210%        100.000%        7 / 7          
jkcredits                      0x8e4      0.211%        100.000%        6 / 6          
sithcogfunctionsector          0x93a      0.219%        100.000%       22 / 22         
sithcogfunctionai              0x943      0.220%        100.000%       20 / 20         
stdsound                       0x9bf      0.231%        100.000%       27 / 27         
sithgamesave                   0x9bf      0.231%        100.000%        7 / 7          
jkguiforce                     0x9dd      0.234%        100.000%       11 / 11         
sithsound                      0xa00      0.237%        100.000%       13 / 13         
rdparticle                     0xa0d      0.239%        100.000%       10 / 10         
rdmaterial                     0xa2d      0.241%        100.000%        9 / 9          
sithsoundclass                 0xa46      0.244%        100.000%       16 / 16         
sithcogfunctionsound           0xa97      0.251%        100.000%       14 / 14         
rdkeyframe                     0xa99      0.251%        100.000%        8 / 8          
rdcamera                       0xaa8      0.253%        100.000%       26 / 26         
jkguisaveload                  0xb21      0.264%        100.000%        9 / 9          
rdpolyline                     0xb42      0.267%        100.000%        6 / 6          
jksaber                        0xb54      0.269%        100.000%        8 / 8          
jkguikeyboard                  0xb57      0.269%        100.000%       14 / 14         
jkguinethost                   0xbc6      0.279%        100.000%        6 / 6          
sithoverlaymap                 0xbf8      0.284%        100.000%        9 / 9          
rdvector                       0xd29      0.312%        100.000%       55 / 55         
jkguimouse                     0xdb5      0.325%        100.000%       14 / 14         
directdraw                     0xdd4      0.328%        100.000%       16 / 16         
jkepisode                      0xdd9      0.329%        100.000%       10 / 10         
sithcogfunctionplayer          0xdf0      0.331%        100.000%       42 / 42         
jkhudinv                       0xe43      0.338%        100.000%        9 / 9          
sithcogfunctionsurface         0xe92      0.346%        100.000%       38 / 38         
sithactor                      0xf9c      0.370%        100.000%       13 / 13         
stdconsole                     0xfff      0.380%        100.000%       20 / 20         
jkguimultiplayer               0x1097     0.394%        100.000%       13 / 13         
directplay                     0x10cc     0.399%        100.000%       31 / 31         
vbuffer                        0x10dc     0.400%        100.000%        4 / 4          
jkcog                          0x11b8     0.420%        100.000%       40 / 40         
stdcontrol                     0x11ec     0.425%        100.000%       22 / 22         
sithpuppet                     0x1222     0.430%        100.000%       17 / 17         
sithcamera                     0x124b     0.434%        100.000%       23 / 23         
jkguidisplay                   0x12ff     0.451%        100.000%       11 / 11         
jkguijoystick                  0x13f0     0.473%        100.000%       19 / 19         
jkdss                          0x13f6     0.474%        100.000%       32 / 32         
sithcogyacc                    0x152b     0.502%        100.000%       10 / 10         
jkres                          0x15b6     0.515%        100.000%       23 / 23         
jkmain                         0x16cd     0.541%        100.000%       53 / 53         
sithworld                      0x1718     0.548%        100.000%       22 / 22         
sithdss                        0x175d     0.554%        100.000%       22 / 22         
stdmath                        0x182a     0.573%        100.000%       23 / 23         
rdactive                       0x1a55     0.625%        100.000%        8 / 8          
sithcogexec                    0x1aec     0.639%        100.000%       31 / 31         
sithcogparse                   0x1b2a     0.645%        100.000%       26 / 26         
jkhud                          0x1c9b     0.679%        100.000%       17 / 17         
jkdev                          0x1fd6     0.755%        100.000%       41 / 41         
sithinventory                  0x2150     0.791%        100.000%       62 / 62         
sithdssthing                   0x22aa     0.823%        100.000%       37 / 37         
sithrender                     0x23de     0.851%        100.000%       22 / 22         
jkguibuildmulti                0x258b     0.891%        100.000%       24 / 24         
sithsoundmixer                 0x2626     0.905%        100.000%       37 / 37         
stddisplay                     0x267b     0.913%        100.000%       37 / 37         
sithcogfunction                0x26c2     0.920%        100.000%      119 / 119        
sithai                         0x2771     0.936%        100.000%       35 / 35         
rdmodel3                       0x2a7e     1.008%        100.000%       23 / 23         
std3d                          0x2c4a     1.051%        100.000%       39 / 39         
rdmatrix                       0x2c85     1.056%        100.000%       56 / 56         
sithaicmd                      0x2cc0     1.062%        100.000%       22 / 22         
jkguirend                      0x2cd7     1.064%        100.000%       68 / 68         
jkplayer                       0x2da2     1.083%        100.000%       45 / 45         
sithphysics                    0x310b     1.164%        100.000%       13 / 13         
sithweapon                     0x32a8     1.202%        100.000%       33 / 33         
rdcache                        0x331c     1.213%        100.000%       16 / 16         
sithcogfunctionthing           0x3a4c     1.383%        100.000%      142 / 142        
rdclip                         0x81f2     3.084%        100.000%       17 / 17         
sithaiawareness                0x31f      0.074%        90.488%         5 / 6          
stdcomm                        0x53c      0.124%        98.955%        16 / 17         
stdfileutil                    0x687      0.155%        54.159%         6 / 11         
stdbmp                         0x6b8      0.159%        0.000%          0 / 3          
sithanimclass                  0x6cc      0.161%        94.080%         4 / 5          
stdstrtable                    0x7b6      0.183%        82.877%         4 / 6          
stdcolor                       0x97e      0.225%        24.198%         3 / 11         
jkgame                         0x98f      0.227%        80.384%        12 / 13         
stdpaleffects                  0xa66      0.247%        85.875%        16 / 21         
stdlbm                         0xc24      0.288%        0.000%          0 / 3          
rdcolormap                     0xcf4      0.307%        47.738%         7 / 12         
stdplatform                    0xdde      0.329%        49.042%        37 / 43         
sithplayer                     0xe72      0.343%        95.944%        23 / 27         
stdbitmap                      0xeb6      0.349%        47.398%         6 / 14         
sithtrackthing                 0xf9f      0.371%        90.098%        12 / 15         
rdpuppet                       0x101f     0.383%        97.407%        15 / 19         
stdgif                         0x1162     0.412%        0.000%          0 / 4          
sithcommand                    0x11b2     0.420%        91.545%        18 / 20         
sithintersect                  0x12a8     0.443%        92.588%         9 / 12         
rdprimit3                      0x16e0     0.543%        91.684%         7 / 9          
stdfont                        0x181a     0.572%        75.284%        12 / 20         
sithsurface                    0x1c6a     0.674%        96.838%        33 / 35         
sithcog                        0x1ed3     0.731%        90.686%        21 / 28         
sithmulti                      0x252a     0.882%        91.423%        29 / 35         
sithcollision                  0x2827     0.953%        91.954%        19 / 22         
sithcontrol                    0x285a     0.958%        99.613%        31 / 33         
siththing                      0x338c     1.223%        86.829%        43 / 49         
rdraster                       0xf04d     5.702%        0.195%          1 / 89         
rdzraster                      0x15fb4    8.346%        0.000%          0 / 73         
rdafraster                     0x1620d    8.402%        0.000%          0 / 122        
rdnraster                      0x304d4    18.339%       0.000%          0 / 87         
---------------------------------------------------------------------------------

total completion:
-----------------
56.758% by weight
95.857% by weight excluding rasterizer
2694 / 3169 functions
2694 / 2798 functions excluding rasterizer

subsystem breakdown (not decomp'd)
----------------------------------
[subsys]       [% of text]  [todo / total]
sith           0.542%           40 / 1319
stdplatform    0.168%            6 / 43
std            1.494%           47 / 376
jkgui          0.000%            0 / 284
rd             0.216%           11 / 345
jk             0.044%            1 / 324
raster         40.778%         370 / 371
other          0.000%            0 / 107
-----------------------------------------
total          43.242%         475 / 3169

subsystem breakdown (not decomp'd, excl raster)
-----------------------------------------------
[subsys]       [% of text]  [todo / total]
sith           0.916%           40 / 1319
stdplatform    0.283%            6 / 43
std            2.524%           47 / 376
jkgui          0.000%            0 / 284
rd             0.364%           11 / 345
jk             0.075%            1 / 324
other          0.000%            0 / 107
-----------------------------------------
total          4.162%          105 / 2798

```
