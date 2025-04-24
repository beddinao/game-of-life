# Install script for directory: /goinfre/beddinao/game-of-life/assets/SDL3

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/goinfre/beddinao/game-of-life/assets/SDL3/build/sdl3.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/goinfre/beddinao/game-of-life/assets/SDL3/build/libSDL3.0.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL3.0.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL3.0.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL3.0.dylib")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/goinfre/beddinao/game-of-life/assets/SDL3/build/libSDL3.dylib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/goinfre/beddinao/game-of-life/assets/SDL3/build/libSDL3_test.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL3_test.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL3_test.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL3_test.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3headersTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3headersTargets.cmake"
         "/goinfre/beddinao/game-of-life/assets/SDL3/build/CMakeFiles/Export/35815d1d52a6ea1175d74784b559bdb6/SDL3headersTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3headersTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3headersTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3" TYPE FILE FILES "/goinfre/beddinao/game-of-life/assets/SDL3/build/CMakeFiles/Export/35815d1d52a6ea1175d74784b559bdb6/SDL3headersTargets.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3sharedTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3sharedTargets.cmake"
         "/goinfre/beddinao/game-of-life/assets/SDL3/build/CMakeFiles/Export/35815d1d52a6ea1175d74784b559bdb6/SDL3sharedTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3sharedTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3sharedTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3" TYPE FILE FILES "/goinfre/beddinao/game-of-life/assets/SDL3/build/CMakeFiles/Export/35815d1d52a6ea1175d74784b559bdb6/SDL3sharedTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3" TYPE FILE FILES "/goinfre/beddinao/game-of-life/assets/SDL3/build/CMakeFiles/Export/35815d1d52a6ea1175d74784b559bdb6/SDL3sharedTargets-relwithdebinfo.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3testTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3testTargets.cmake"
         "/goinfre/beddinao/game-of-life/assets/SDL3/build/CMakeFiles/Export/35815d1d52a6ea1175d74784b559bdb6/SDL3testTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3testTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3/SDL3testTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3" TYPE FILE FILES "/goinfre/beddinao/game-of-life/assets/SDL3/build/CMakeFiles/Export/35815d1d52a6ea1175d74784b559bdb6/SDL3testTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3" TYPE FILE FILES "/goinfre/beddinao/game-of-life/assets/SDL3/build/CMakeFiles/Export/35815d1d52a6ea1175d74784b559bdb6/SDL3testTargets-relwithdebinfo.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL3" TYPE FILE FILES
    "/goinfre/beddinao/game-of-life/assets/SDL3/build/SDL3Config.cmake"
    "/goinfre/beddinao/game-of-life/assets/SDL3/build/SDL3ConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL3" TYPE FILE FILES
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_assert.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_asyncio.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_atomic.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_audio.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_begin_code.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_bits.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_blendmode.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_camera.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_clipboard.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_close_code.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_copying.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_cpuinfo.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_dialog.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_egl.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_endian.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_error.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_events.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_filesystem.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_gamepad.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_gpu.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_guid.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_haptic.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_hidapi.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_hints.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_init.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_intrin.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_iostream.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_joystick.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_keyboard.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_keycode.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_loadso.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_locale.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_log.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_main.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_main_impl.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_messagebox.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_metal.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_misc.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_mouse.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_mutex.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_oldnames.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_opengl.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_opengl_glext.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_opengles.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_opengles2.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_opengles2_gl2.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_opengles2_gl2ext.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_opengles2_gl2platform.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_opengles2_khrplatform.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_pen.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_pixels.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_platform.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_platform_defines.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_power.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_process.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_properties.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_rect.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_render.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_scancode.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_sensor.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_stdinc.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_storage.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_surface.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_system.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_thread.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_time.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_timer.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_touch.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_tray.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_version.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_video.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_vulkan.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/build/include-revision/SDL3/SDL_revision.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL3" TYPE FILE FILES
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_test.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_test_assert.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_test_common.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_test_compare.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_test_crc32.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_test_font.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_test_fuzzer.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_test_harness.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_test_log.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_test_md5.h"
    "/goinfre/beddinao/game-of-life/assets/SDL3/include/SDL3/SDL_test_memory.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/licenses/SDL3" TYPE FILE FILES "/goinfre/beddinao/game-of-life/assets/SDL3/LICENSE.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/goinfre/beddinao/game-of-life/assets/SDL3/build/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/goinfre/beddinao/game-of-life/assets/SDL3/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
