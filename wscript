VERSION='1.6.5'
APPNAME='soulfu'

def set_options(opt):
    opt.tool_options('compiler_cc')

def configure(conf):
    conf.check_tool('compiler_cc')
    conf.check_cfg(package='sdl', at_least_version='1.2.11',\
                   args='--libs --cflags')
"""Definitely needs:
    jpeglib.h from jpeg, libGL, libGLext, SDL, SDL_net
    """
#    conf.check_cfg(msg='Checking for ffmpeg', \
#                   package='libavcodec libavformat libavutil', \
#                   args='--libs --cflags',
#                   uselib_store='FFMPEG')
#    conf.check(lib='ltdl')

def build(bld):
    obj = bld(
            source = bld.path.ant_glob("src/*.c"),
            includes = "src",
            target = 'soulfu',
            features = 'cc cprogram',
            uselib = 'SDL'
            )

