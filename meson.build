project('demo_sticky', 'cpp',default_options : ['cpp_std=c++17'], license: 'GPL3', version: '0.0.1')

qt5 = import('qt5')
qt5core = dependency('qt5', modules : 'Core')
qt5widgets = dependency('qt5', modules : 'Widgets')
qt5gui = dependency('qt5', modules : 'Gui')
qt5svg = dependency('qt5', modules : 'Svg')
qt5test = dependency('qt5', modules : 'Test')

SciQLopPlots_dep = dependency('SciQLopPlots', fallback : ['SciQLopPlots', 'SciQLopPlots_dep'])
cpp_utils_dep = dependency('cpp_utils')
range_dep = dependency('range-v3',  fallback : ['range-v3', 'range_dep'])
channels_dep = dependency('channels')
fft_dep = dependency('fft')
thread_dep = dependency('threads')

subdir('src')
