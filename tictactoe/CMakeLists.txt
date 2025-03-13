
cmake_minimum_required(VERSION 3.5)

project(tictactoe VERSION 0.1 LANGUAGES CXX)

# set(QT_DIR "C:\\Qt\\6.8.2\\android_arm64_v8a\\lib\\cmake\\Qt6")
if (UNIX)
    set(QT_DIR /home/ian/Qt/6.8.2/gcc_64/lib/cmake/Qt6)
    set(Qt6_DIR /home/ian/Qt/6.8.2/gcc_64/lib/cmake/Qt6)
    set(CMAKE_PREFIX_PATH /home/ian/Qt/6.8.2/gcc_64/lib/cmake)
endif (UNIX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# enable_testing(true)

include_directories(/home/ian/Qt/6.8.2/gcc_64/lib/cmake)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Test)

qt_standard_project_setup()

set(PROJECT_SOURCES
                  GameManager.cpp
		  GameManager.h
                  Board.cpp
                  Board.h
                  common.h
)

set(MAIN_SOURCES
    main.cpp
		  ${PROJECT_SOURCES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(tictactoe
        MANUAL_FINALIZATION
        ${MAIN_SOURCES})
    # qt_add_executable(tictactoe-tests
        # MANUAL_FINALIZATION
        # ${TEST_SOURCES} ${PROJECT_SOURCES})
endif()


target_link_libraries(tictactoe PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)# Shared Domain Presentation)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.tictactoe)
endif()
set_target_properties(tictactoe PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS tictactoe
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET tictactoe
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

# Unit tests
# set_target_properties(tictactoe-tests PROPERTIES
#     WIN32_EXECUTABLE TRUE
#     MACOSX_BUNDLE TRUE
# )
# target_link_libraries(tictactoe-tests PRIVATE
#     Qt${QT_VERSION_MAJOR}::Test
#     Qt${QT_VERSION_MAJOR}::Core
#     Qt${QT_VERSION_MAJOR}::Gui
#     Qt${QT_VERSION_MAJOR}::Widgets
# )
# target_link_libraries(tictactoe-tests PRIVATE Qt${QT_VERSION_MAJOR}::Widgets) #Shared Domain Presentation)
# install(TARGETS tictactoe-tests
#     BUNDLE  DESTINATION .
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
# )
# qt_generate_deploy_app_script(
#     TARGET tictactoe-tests
#     OUTPUT_SCRIPT deploy_script
#     NO_UNSUPPORTED_PLATFORM_ERROR
# )
# add_test(NAME tictactoe-tests COMMAND MainLoopManagerTest)

install(SCRIPT ${deploy_script})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(tictactoe)
endif()
