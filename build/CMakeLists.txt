cmake_minimum_required (VERSION 2.8.11)
project (qt_proj)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)
find_package( OpenCV REQUIRED )

#INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})
add_definitions(-std=c++11)

set(EXECUTABLE_OUTPUT_PATH ../bin)
set(SRC_BASE ../src)
set(QT_UI_BASE_PATH ../data/qt)

set( SOURCES
    ${SRC_BASE}/main.cpp
    ${SRC_BASE}/TimeMeasure.cpp
    ${SRC_BASE}/Windows/MainWindow.cpp
    ${SRC_BASE}/Windows/VideoWindow.cpp
    ${SRC_BASE}/Windows/ThresholdWindow.cpp
    ${SRC_BASE}/Windows/FilesWindow.cpp
    ${SRC_BASE}/Windows/RegionGrowthWindow.cpp
    ${SRC_BASE}/Windows/ViewerWindow.cpp
    ${SRC_BASE}/Windows/PlateLocationWindow.cpp
    ${SRC_BASE}/QMouseEventerImage.cpp
    ${SRC_BASE}/Rectangle.cpp
    ${SRC_BASE}/ImageProcessing/PlateLocation.cpp
    ${SRC_BASE}/ImageProcessing/RegionGrowthLumOrdered/RegionGrowthLumOrdered.cpp
    ${SRC_BASE}/ImageProcessing/RegionGrowthLumOrdered/Region.cpp
    ${SRC_BASE}/ImageProcessing/RegionGrowthLumOrdered/RegionsManager.cpp
    ${SRC_BASE}/ImageProcessing/RegionGrowthLumOrdered/RegionsAnalyzer.cpp
    ${SRC_BASE}/ImageProcessing/RegionGrowthLumOrdered/RegionsPainter.cpp
)

set( ALL_SOURCES 
    ${SOURCES}
)
            
SET( QT_UIS
     ${QT_UI_BASE_PATH}/MainWindow.ui
     ${QT_UI_BASE_PATH}/Video.ui
     ${QT_UI_BASE_PATH}/Threshold.ui
     ${QT_UI_BASE_PATH}/Files.ui
     ${QT_UI_BASE_PATH}/RegionGrowth.ui
     ${QT_UI_BASE_PATH}/Viewer.ui
     ${QT_UI_BASE_PATH}/PlateLocation.ui
)
                            
QT5_WRAP_UI(QTTEST_GEN_UIS ${QT_UIS} )             
                
include_directories(${SRC_BASE} ${CMAKE_CURRENT_BINARY_DIR} )
                     
add_executable(qt_proj_exe ${SRC_BASE}/main.cpp 
					${ALL_SOURCES}
                    ${QTTEST_GEN_UIS})
                    
                    
qt5_use_modules(qt_proj_exe Widgets OpenGL)

set(qt_proj_LIBRARIES ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ) 
                   
target_link_libraries(qt_proj_exe ${qt_proj_LIBRARIES} ${QT_LIBRARIES} ${OpenCV_LIBS} )

if (WIN32)
    set(CMAKE_CXX_FLAGS  "/MP")
    add_definitions( -D_VARIADIC_MAX=10 )
endif (WIN32)