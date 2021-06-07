# Hello World Premium

The next level in Hello Worlding

## Compiling Hello World Premium

### POSIX

- Install GCC and GNU Make (build-essential).
- Install CMake 3.12 or higher (cmake).
- Install wxWidgets (libwx_gtk3u3.0-devel, probably).
- Get the source files from GitHub.
- Run `cmake .` on the root folder.
- Run `cmake --build .` on the root folder.
- The CLI executable `hwp` and the GUI executable `hwp_gui` will be in the `bin` folder.
	- You can run `hwp -h` to see how to use the program.

### Windows

- Install GCC (probably MinGW x64).
- Install CMake 3.12 or higher.
- Install wxWidgets (I'm using 3.1.5).
	- You must have a folder with two folders: `lib` and `include`. You can download those from the website (the "Development Files" and "Header Files"), but it will probably not be compatible with your version of the compiler. It might be better to compile those files yourself - see the section [Compiling wxWidgets](#compiling-wxwidgets).
	- For the FindwxWidgets module to work, the folder inside the lib folder must be called `gcc_dll`. The ones from the website might not have this structure so you must rename it.
		- FindwxWidgets is trash, by the way.
	- There're multiple ways for FindwxWidgets to find the installation, the easiest is to set the environment variable `WXWIN` to the root folder of wxWidgets.
- Get the source files from GitHub.
- Run `cmake .` on the root folder.
	- On Windows the default generator is Visual Studio, to use MinGW, set the environment variable `CMAKE_GENERATOR` to `MinGW Makefiles` beforehand.
- Run `cmake --build .` on the root folder.
- The CLI executable `hwp.exe` and the GUI executable `hwp_gui.exe` will be in the `bin` folder.
	- The system has to be able to find the dll files. Either copy them to `bin` or put the specific folders in the `PATH` environment variable. Here's the list of used files and their locations:		
		- GCC (in `bin` inside the root MinGW x64 folder):
			- libstdc++-6.dll
			- libgcc_s_seh-1.dll
			- libwinpthread-1.dll
		- wxWidgets (in `lib\gcc_dll` inside the root wxWidgets folder) (these may have different names depending on how you linked it):
			- wxbase315u_gcc_custom.dll
			- wxmsw315u_core_gcc_custom.dll
	- You can run `hwp.exe -h` to see how to use the program.

## Compiling wxWidgets

### POSIX

I dunno, never needed to do that

### Windows

- Get the [source files](https://www.wxwidgets.org/downloads/) of wxWidgets.
- Go to the folder `build\msw`.
- Run `mingw32-make -f makefile.gcc SHARED=1 UNICODE=1 SHELL=cmd BUILD=release`.
	- You can use the option `-j` to specify the number of threads to be used, you can use the same amount as the number of cores your processor has. However, if you use this, it might be hard to see any error messages. In case the program finishes running, try running it again without this option to see if everything is working (make will not recompile already done files).
- Now the compiled files are in `lib\gcc_dll`.

## TODO
- [ ] Project
	- [ ] UML Diagrams
	- [ ] Cycle of life methodology
	- [ ] Deployment plan
	- [ ] Prototyping
- [ ] Basics
	- [x] Print Hello World
	- [ ] User documentation
	- [ ] Set as default application for .hw files
	- [ ] Scheduled Hello Worlds
	- [ ] Unit tests
- [ ] Graphical User Interface
	- [ ] Background images
	- [ ] Tips at initialization
	- [ ] Confirmation at closing
	- [ ] Multiple monitors support
	- [ ] Animated Hello World
	- [ ] Read sign
- [ ] VR support
	- [ ] 3d rotation
	- [ ] Physical bouncing
	- [ ] Kinect
- [ ] Social
	- [ ] Share Hello World activity with friends
	- [ ] Invite friends
	- [ ] See who is Hello Worlding
	- [ ] Online lobbies
	- [ ] Chats (only Hello World allowed)
	- [ ] User profile, avatar and password
	- [ ] Ranks
	- [ ] Administration panel
- [ ] Launcher
	- [ ] CLI/GUI selection
	- [ ] DirectX/OpenGL selection
	- [ ] Enable hardware optimization
		- [ ] Fast inverse square root for enhanced Hello Worlding
	- [ ] 256 colors
- [ ] Installer
	- [ ] Terms and conditions
		- [ ] User must agree on not using for illegal purposes
	- [ ] Service plans
		- [ ] Free trial period
		- [ ] Standard
		- [ ] Professional
		- [ ] Gold
		- [ ] Premium
		- [ ] Global Offensive
- [ ] Auto-update
- [ ] Hello World library
	- [ ] Executable only calls .dll
- [ ] Connectivity and security
	- [ ] Data use optimization
	- [ ] Login screen
	- [ ] Cryptography
	- [ ] SSL Certificate
- [ ] Configuration screen
	- [ ] Fonts
	- [ ] Effects
	- [ ] Dark mode
	- [ ] Amoled support
	- [ ] Look and Feel
	- [ ] Open at system startup
	- [ ] Load plugins (visuals, NetPlay, ...)
	- [ ] Run on background (minimize to system tray)
- [ ] Build targets
	- [ ] Release
	- [ ] Debug
	- [ ] Bootable
- [ ] Accessibility
	- [ ] Options for blind or vision impaired persons
		- [ ] Voice synthesizer
	- [ ] Options for deaf or hard of hearing persons
		- [ ] Subtitles
	- [ ] Options for low internet connections
	- [ ] Options for non-English speakers
		- [ ] Automatic translation to any language
	- [ ] True universal access
- [ ] Github Repository
	- [ ] Instructions for compiling wxWidgets on POSIX
	- [ ] Wiki
		- [ ] Design principles
		- [ ] Project guidelines 

## Still open questions:

* GPL or MIT license? Which version? 
* Which SGBD should we use?

## FAQ (Frequently Asked Questions)

### Can I distribute Hello World Premium?

Yes.

### Can I sell Hello World Premium?

No.

### Can I modify Hello World Premium?

Maybe.

### How do I can download the binary files?

You must compile the program by yourself. See [Compiling Hello World Premium](#compiling-hello-world-premium) for more information.

### How do I can contribute to the Hello World Premium project?

We encourage developers from all the world to engage in the mission to construct the next level in Hello Worlding. Feel free to pull request, post insights or issues on the official Hello World Premium GitHub repository.

### My question is not on the list. What do I do?

Contact the official Hello World Premium GitHub repository collaborators via email.
