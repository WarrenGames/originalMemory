cmake_minimum_required(VERSION 3.0.0)

project( game LANGUAGES C )

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmakeModules)

if(WIN32)
	set(SDL2_DIR "")
endif(WIN32)
    
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

set(HEADERS
	sources/mainMenu/levelButtons.h
	sources/mainMenu/instructionsMenuPrincipal.h
	sources/mainMenu/mainMenuStructs.h
	sources/common/initTempStruct.h
	sources/common/loadComboTexture.h
	sources/common/initialize.h
	sources/common/defines.h
	sources/common/comboTextureStruct.h
	sources/common/loadSDL2.h
	sources/common/user.h
	sources/common/positionStruct.h
	sources/common/timeDelayStruct.h
	sources/game/displayText.h
	sources/game/initGlobalGameData.h
	sources/game/displayCards.h
	sources/game/globalGameData.h
	sources/game/loadGameGraphics.h
	sources/game/cardsGraphics.h
	sources/game/numericData.h
	sources/game/allocMeltCardsData.h
	sources/game/gameContext.h
)

set(SOURCES
	sources/mainMenu/levelButtons.c
	sources/mainMenu/instructionsMenuPrincipal.c
	sources/common/loadComboTexture.c
	sources/common/main.c
	sources/common/loadSDL2.c
	sources/common/initialize.c
	sources/common/user.c
	sources/common/initTempStruct.c
	sources/game/displayCards.c
	sources/game/displayText.c
	sources/game/initGlobalGameData.c
	sources/game/loadGameGraphics.c
	sources/game/gameContext.c
	sources/game/allocMeltCardsData.c
)

add_executable(${PROJECT_NAME} 
	WIN32
	${SOURCES} 
	${HEADERS} 
	${INC_DIRS}
)

target_include_directories(${PROJECT_NAME}
	PUBLIC ${SDL2_INCLUDE_DIRS}		
	PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
	PUBLIC ${SDL2_TTF_INCLUDE_DIRS}
	PUBLIC sources
)

target_link_libraries(
		${PROJECT_NAME} 
		${SDL2_LIBRARIES} 
		${SDL2_IMAGE_LIBRARIES} 
		${SDL2_TTF_LIBRARIES}
)

set_target_properties(
		${PROJECT_NAME} 
		PROPERTIES C_STANDARD 17 LINKER_LANGUAGE C
)

#Installation
install( DIRECTORY fonts icons licenses textures DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME} )
install( TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} )	

#Installation for unix Only for unix OS
if(UNIX)
	include(GNUInstallDirs)
	set( DESKTOP_DEST_PATH "/usr/share/applications/" )
	set( DESKTOP_FILE "original-memory.desktop" )
	
	file(WRITE ${DESKTOP_FILE} "[Desktop Entry]\n")
	file(APPEND ${DESKTOP_FILE} "Version=1.0\n")
	file(APPEND ${DESKTOP_FILE} "Type=Application\n")
	file(APPEND ${DESKTOP_FILE} "Name=Original Memory\n")
	file(APPEND ${DESKTOP_FILE} "Comment=find all the pair cards\n")
	file(APPEND ${DESKTOP_FILE} "Icon=${CMAKE_INSTALL_FULL_DATADIR}/${PROJECT_NAME}/icons/memory.ico\n")
	file(APPEND ${DESKTOP_FILE} "Exec=${CMAKE_INSTALL_FULL_BINDIR}/${PROJECT_NAME}\n")
	file(APPEND ${DESKTOP_FILE} "Path=${CMAKE_INSTALL_FULL_DATADIR}/${PROJECT_NAME}\n")
	file(APPEND ${DESKTOP_FILE} "Actions=\n")
	file(APPEND ${DESKTOP_FILE} "Categories=Game;The games of the warren;")
	
	install( FILES ${DESKTOP_FILE} DESTINATION "${DESKTOP_DEST_PATH}" )
endif(UNIX) 