QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Предотвращение автоматического создания подкаталогов (debug и release)
CONFIG -= debug_and_release debug_and_release_target

# Текущая версия проекта (debug или release)
CONFIG(debug, debug|release) {
    BUILD_FLAG = debug
} else {
    BUILD_FLAG = release
}

# Название скомпилированного файла
TARGET = s57parser

# Путь к скомилированному файлу (для разработки)
DESTDIR = $${PWD}/build/$${BUILD_FLAG}

# Путь к скомпилированному файлу (для итоговой версии)
PROD_BUILD_PATH = $${PWD}/$${TARGET}

# Каталог заголовков (.h)
DEV_INCLUDE_PATH = $${PWD}/include

# Каталог исходников (.cpp)
DEV_SOURCE_PATH = $${PWD}/src

# Каталог сторонних файлов
DEV_VENDOR_PATH = $${PWD}/vendor

# Библиотека GDAL
GDAL_ROOT_PATH = $${DEV_VENDOR_PATH}/gdal-3.5.2

# Заголовки GDAL
GDAL_INCLUDE_PATH = $${GDAL_ROOT_PATH}/include

# Статические библиотеки GDAL
GDAL_LIB_PATH = $${GDAL_ROOT_PATH}/lib

# Динамические библиотеки GDAL
GDAL_BIN_PATH = $${GDAL_ROOT_PATH}/bin

# Динамические библиотеки GDAL
GDAL_DATA_PATH = $${GDAL_BIN_PATH}/gdal-data

# Динамические библиотеки GDAL
GDAL_PLUGIN_PATH = $${GDAL_BIN_PATH}/gdal/plugins

# Каталог UI форм
DEV_UI_PATH = $${PWD}/ui

# Каталоги промежуточных файлов
DEV_INTERMEDIATE_PATH = $${DESTDIR}/intermediate
RCC_DIR = $${DEV_INTERMEDIATE_PATH}/rcc/
MOC_DIR = $${DEV_INTERMEDIATE_PATH}/moc/
OBJECTS_DIR = $${DEV_INTERMEDIATE_PATH}/obj/

# Каталог промежуточных файлов интерфейса
UI_DIR = $${DEV_INCLUDE_PATH}/view/

# Подключение сторонних библиотек в Qt
LIBS += -L$${GDAL_LIB_PATH}/
LIBS += -lgdal_i

# Каталоги заголовков в которых следует выполнять поиск при компиляции проекта
INCLUDEPATH += $${DEV_INCLUDE_PATH}
INCLUDEPATH += $${DEV_INCLUDE_PATH}/model/
INCLUDEPATH += $${DEV_INCLUDE_PATH}/view/
INCLUDEPATH += $${DEV_INCLUDE_PATH}/service/
INCLUDEPATH += $${GDAL_INCLUDE_PATH}

# Имена заголовочных файлов в проекте
HEADERS += \
    $${DEV_INCLUDE_PATH}/view/mainwindow.h \
    $${DEV_INCLUDE_PATH}/view/logger.h \
    $${DEV_INCLUDE_PATH}/model/model.h \
    $${DEV_INCLUDE_PATH}/service/gdal_manager.h \
    $${DEV_INCLUDE_PATH}/service/s57_parser.h

# Имена исходных файлов в проекте
SOURCES += \
    $${DEV_SOURCE_PATH}/main.cpp \
    $${DEV_SOURCE_PATH}/view/mainwindow.cpp \
    $${DEV_SOURCE_PATH}/view/logger.cpp \
    $${DEV_SOURCE_PATH}/model/model.cpp \
    $${DEV_SOURCE_PATH}/service/gdal_manager.cpp \
    $${DEV_SOURCE_PATH}/service/s57_parser.cpp

# Имена UI форм в проекте
FORMS += \
    $${DEV_UI_PATH}/mainwindow.ui

# Дополнительные файлы
DISTFILES += \
    .gitignore \
    README.md

# Собрка проекта в итогововый вариант
target.path = $${PROD_BUILD_PATH}

qt_dll.path = $${PROD_BUILD_PATH}
qt_dll.files += $$[QT_INSTALL_BINS]/Qt6Core.dll
qt_dll.files += $$[QT_INSTALL_BINS]/Qt6Gui.dll
qt_dll.files += $$[QT_INSTALL_BINS]/Qt6Widgets.dll

qt_platform.path = $${PROD_BUILD_PATH}/platforms
qt_platform.files += $$[QT_INSTALL_PLUGINS]/platforms/qwindows.dll

qt_style.path = $${PROD_BUILD_PATH}/styles
qt_style.files += $$[QT_INSTALL_PLUGINS]/styles/qwindowsvistastyle.dll

gdal_dll.path = $${PROD_BUILD_PATH}
gdal_dll.files += $${GDAL_BIN_PATH}/freexl.dll
gdal_dll.files += $${GDAL_BIN_PATH}/gdal305.dll
gdal_dll.files += $${GDAL_BIN_PATH}/geos.dll
gdal_dll.files += $${GDAL_BIN_PATH}/geos_c.dll
gdal_dll.files += $${GDAL_BIN_PATH}/iconv-2.dll
gdal_dll.files += $${GDAL_BIN_PATH}/libcrypto-1_1-x64.dll
gdal_dll.files += $${GDAL_BIN_PATH}/libcurl.dll
gdal_dll.files += $${GDAL_BIN_PATH}/libexpat.dll
gdal_dll.files += $${GDAL_BIN_PATH}/libmysql.dll
gdal_dll.files += $${GDAL_BIN_PATH}/libpq.dll
gdal_dll.files += $${GDAL_BIN_PATH}/libssl-1_1-x64.dll
gdal_dll.files += $${GDAL_BIN_PATH}/libxml2.dll
gdal_dll.files += $${GDAL_BIN_PATH}/ogdi.dll
gdal_dll.files += $${GDAL_BIN_PATH}/openjp2.dll
gdal_dll.files += $${GDAL_BIN_PATH}/proj_7_2.dll
gdal_dll.files += $${GDAL_BIN_PATH}/spatialite.dll
gdal_dll.files += $${GDAL_BIN_PATH}/sqlite3.dll
gdal_dll.files += $${GDAL_BIN_PATH}/tiff.dll
gdal_dll.files += $${GDAL_BIN_PATH}/xerces-c_3_2.dll
gdal_dll.files += $${GDAL_BIN_PATH}/zlib.dll

gdal_data.path = $${PROD_BUILD_PATH}/gdal-data
gdal_data.files += $${GDAL_DATA_PATH}/*

gdal_plugin.path = $${PROD_BUILD_PATH}/gdal-plugins
gdal_plugin.files += $${GDAL_PLUGIN_PATH}/*

INSTALLS += target \
    qt_dll \
    qt_platform \
    qt_style \
    gdal_dll \
    gdal_data \
    gdal_plugin
