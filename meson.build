project('libparser', 'cpp', version: 'master')

# Features
## add_global_arguments('-DSMART_PRODUCTION_VALIDATION', language : 'cpp')

include = include_directories('include')

main = executable('main.exe', [
    'src/main.cc',
    'src/tests/symbol.cc',
    'src/tests/production.cc',
    'src/tests/parser.cc',
  ], include_directories : include)

libparser_dep = declare_dependency(
  include_directories : include)
