AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I .

bin_PROGRAMS = pong
pong_SOURCES = \
Ball.cxx \
GameState.cxx \
Paddle.cxx \
PongController.cxx \
PongRenderer.cxx \
PongScene.cxx \
pong.cxx

AM_CPPFLAGS = $(DEPS_CFLAGS) $(BOOST_CPPFLAGS) $(GCOV_CFLAGS) $(V3D_CPPFLAGS) $(luxa_CFLAGS)
AM_LDFLAGS = $(GCOV_LDFLAGS) \
$(V3D_GL_LDFLAGS) $(V3D_GUI_LDFLAGS) $(V3D_HOOKAH_LDFLAGS) \
$(BOOST_SIGNALS_LDFLAGS) $(BOOST_SYSTEM_LDFLAGS) $(BOOST_FILESYSTEM_LDFLAGS) $(BOOST_PROGRAM_OPTIONS_LDFLAGS)

pong_LDADD = $(DEPS_LIBS) \
$(BOOST_SIGNALS_LIBS) $(BOOST_SYSTEM_LIBS) $(BOOST_FILESYSTEM_LIBS) $(BOOST_PROGRAM_OPTIONS_LIBS) $(gl_LIBS) \
$(libpng_LIBS) $(JPEG_LIBS) $(liblog4cxx_LIBS) $(freetype2_LIBS) $(luxa_LIBS) $(sdl_LIBS) $(openal_LIBS) $(freealut_LIBS) \
$(V3D_INPUT_LIBS) $(V3D_COMMAND_LIBS) $(V3D_IMAGE_LIBS) $(V3D_FONT_LIBS) $(V3D_TYPES_LIBS) $(V3D_GL_LIBS) $(V3D_GUI_LIBS) \
$(V3D_AUDIO_LIBS) $(V3D_HOOKAH_LIBS) $(V3D_HOOKAH_SDL_LIBS)

