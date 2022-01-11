import os
from SCons.Defaults import SharedCheck, ProgScan
from SCons.Script.SConscript import SConsEnvironment
import platform

plat = platform.system()

env = Environment()
env['CC'] = 'g++'
env.SCONS_CXX_STANDARD = 'c++17'
#env['CC'] = 'g++'

env.Append(CPPFLAGS = ['-std=c++17'])

t = env.Program(target = 'FreePass', source =['FreePass.cpp'])

