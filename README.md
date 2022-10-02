# S57Parser
S57Parser is a Qt application that is used to convert IHO S-57 to a specific JSON format.

## Requirements

Development requires [compiled GDAL](https://www.gisinternals.com/release.php) and setting the following environment variables:

* `PATH: <Path to GDAL DLLs>`
* `GDAL_DATA: <Path to gdal data folder>`
* `GDAL_DRIVER_PATH: <Path to gdal plugins folder>`

All paths must contain only Latin characters, otherwise GDAL won't work correctly.

You also need to include GDAL headers and gdal_i.lib library.
