import os
import sys
import rtconfig
from SCons.Script import *

if os.getenv('RTT_ROOT'):
    RTT_ROOT = os.getenv('RTT_ROOT')
else:
    RTT_ROOT = os.path.normpath(os.getcwd() + '/../../../..')

# set RTT_ROOT
if not os.getenv("RTT_ROOT"): 
    RTT_ROOT="rt-thread"

sys.path = sys.path + [os.path.join(RTT_ROOT, 'tools')]
try:
    from building import *
except:
    print('Cannot found RT-Thread root directory, please check RTT_ROOT')
    print(RTT_ROOT)
    exit(-1)


TARGET = 'rtthread.' + rtconfig.TARGET_EXT

DefaultEnvironment(tools=[])
env = Environment(tools = ['mingw'],
    AS = rtconfig.AS, ASFLAGS = rtconfig.AFLAGS,
    CC = rtconfig.CC, CFLAGS = rtconfig.CFLAGS,
    AR = rtconfig.AR, ARFLAGS = '-rc',
    CXX = rtconfig.CXX, CXXFLAGS = rtconfig.CXXFLAGS,
    LINK = rtconfig.LINK, LINKFLAGS = rtconfig.LFLAGS)
env.PrependENVPath('PATH', rtconfig.EXEC_PATH)

if rtconfig.PLATFORM in ['iccarm']:
    env.Replace(CCCOM = ['$CC $CFLAGS $CPPFLAGS $_CPPDEFFLAGS $_CPPINCFLAGS -o $TARGET $SOURCES'])
    env.Replace(ARFLAGS = [''])
    env.Replace(LINKCOM = env["LINKCOM"] + ' --map project.map')

Export('RTT_ROOT')
Export('rtconfig')

SDK_ROOT = os.path.abspath('./')

if os.path.exists(SDK_ROOT + '/Libraries'):
    libraries_path_prefix = SDK_ROOT + '/Libraries'
else:
    libraries_path_prefix = os.path.dirname(SDK_ROOT) + '/Libraries'

SDK_LIB = libraries_path_prefix
Export('SDK_LIB')

# prepare building environment
objs = PrepareBuilding(env, RTT_ROOT, has_libcpu=False)

ch32_library = 'ch32v20x_libraries'
rtconfig.BSP_LIBRARY_TYPE = ch32_library

bsp_vdir = 'build'
library_vdir = 'build/libraries'

# include libraries
objs.extend(SConscript(os.path.join(libraries_path_prefix, ch32_library, 'SConscript'), variant_dir=library_vdir + '/ch32_library', duplicate=0))

# common include drivers
objs.extend(SConscript(os.path.join(libraries_path_prefix, 'ch32_drivers','SConscript')))

# make a building
DoBuilding(TARGET, objs)
