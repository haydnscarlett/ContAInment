find_program(
        ASTYLE_EXE NAMES astyle
        PATHS ${CMAKE_SOURCE_DIR}/Tools/*/${PLATFORM}/)

if( ASTYLE_EXE )
    message("Astyle:        " ${ASTYLE_EXE})

    list(APPEND ASTYLE_ARGS
            --quiet
            --formatted
            --options=${CMAKE_SOURCE_DIR}/.astylerc
            ${CMAKE_SOURCE_DIR}/Source/"*.cpp"
            ${CMAKE_SOURCE_DIR}/Source/"*.h*"
    )

    #add_custom_command(
    #        TARGET ${PROJECT_NAME}
    #        PRE_BUILD
    #        COMMAND ${CMAKE_BINARY_DIR}/bin/astyle ${ASTYLE_ARGS}
    #        COMMENT "running astyle")

    add_custom_target(
            FormatCode
            COMMAND ${CMAKE_SOURCE_DIR}/Tools/Astyle/${PLATFORM}/astyle ${ASTYLE_ARGS}
            COMMENT "running astyle"
    )

endif()
