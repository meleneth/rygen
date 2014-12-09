AC_PREREQ([2.59])
AC_INIT([rygen], [1.0], [your_email@example.org])
AM_INIT_AUTOMAKE([foreign -Wall -Werror subdir-objects])
AC_PROG_CXX
AC_PROG_INSTALL
AX_CXX_COMPILE_STDCXX_14
AM_PATH_SDL2
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
AC_CONFIG_MACRO_DIR([m4])
AX_CHECK_GL
AC_CHECK_LIB([png], [png_get_copyright])
CXXFLAGS="$CXXFLAGS $GL_CFLAGS"
CPPFLAGS="$CPPFLAGS $GL_CFLAGS"
LIBS="$LIBS $GL_LIBS"
AC_CHECK_LIB(GLEW, glewInit, LIBS="$LIBS -lGLEW", AC_MSG_ERROR([GLEW required. Please see INSTALL]))

# Check for SDL_image library
 AC_CHECK_LIB(SDL2_image, IMG_LoadPNG_RW, , AC_MSG_ERROR([
 *** Unable to find SDL_image libary with PNG support
 (http://www.libsdl.org/projects/SDL_image/)
 ]))
AM_SILENT_RULES([yes])
AM_PROG_AR
AC_OUTPUT

