# S57Parser
S57Parser is a Qt application that is used to convert IHO S-57 to a specific JSON format.

## Requirements
1. [Qt4+ (with QtCreator and MSVC compiler)](https://www.qt.io/download)
2. [GDAL compiled binaries](https://www.gisinternals.com/release.php)

## Development
1. GDAL setup:
	+ Download GDAL compiled binaries, libraries and headers from the link above
	+ Unzip the downloaded archives to any folder
2. Qt project setup:
	+ Open S57Parser.pro as QtCreator project:
	+ Select a compiler similar to the one that compiled GDAL binaries
	+ Set the following environment variables (in QtCreator project) that GDAL requires:
		- `PATH: <Path to the bin directory in GDAL>`
		- `GDAL_DATA: <Path to the gdal-data directory in GDAL>`
		- `GDAL_DRIVER_PATH: <Path to the plugins directory in GDAL>`
	+ Configure .pro file:
		- `GDAL_ROOT_PATH: <Path to the GDAL>`
		- `GDAL_INCLUDE_PATH: <Path to the include directory in GDAL>`
		- `GDAL_LIB_PATH: <Path to the lib directory in GDAL>`
		- `GDAL_BIN_PATH: <Same as PATH above>`
		- `GDAL_DATA_PATH: <Same as GDAL_DATA above>`
		- `GDAL_PLUGIN_PATH: <Same as GDAL_DRIVER_PATH above>`

__All paths must contain only Latin characters, otherwise GDAL won't work correctly.__

## Building standalone executable
1. Switch to "Release" configuration
2. Add a new "Make" step with the "install" argument to the project "Build steps"
3. Now building the project in the "Release" configuration will generate a folder with a name equals to the "TARGET" variable in the .pro file (by default, s57parser). The executable file will be copied to this folder along with all the necessary data.
