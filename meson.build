project('libparser', 'cpp', version: 'master')

# Features
## add_project_arguments('-DBAN_LEFT_RECURSIVE', language : 'cpp')

# Infos
THE_ASSEMBLER = 'GAS'
THE_BUILDER = 'Ninja'

THE_COMPILER = '@0@ @1@'.format(
  meson.get_compiler('cpp').get_id(),
  meson.get_compiler('cpp').version()
)

THE_VERSION='master'
THE_BRANCH='master'
THE_OS = '@0@ @1@'.format(
  build_machine.system(),
  build_machine.cpu()
)

THE_PROJECT = 'LibParser'

add_project_arguments('-DTHE_ASSEMBLER="@0@"'.format(THE_ASSEMBLER), language : 'cpp')
add_project_arguments('-DTHE_COMPILER="@0@"'.format(THE_COMPILER), language : 'cpp')
add_project_arguments('-DTHE_BUILDER="@0@"'.format(THE_BUILDER), language : 'cpp')
add_project_arguments('-DTHE_OS="@0@"'.format(THE_OS), language : 'cpp')
add_project_arguments('-DTHE_BRANCH="@0@"'.format(THE_BRANCH), language : 'cpp')
add_project_arguments('-DTHE_VERSION="@0@"'.format(THE_VERSION), language : 'cpp')
add_project_arguments('-DTHE_PROJECT="@0@"'.format(THE_PROJECT), language : 'cpp')

# Future Dependencies
liblexer_dep = dependency(
  'liblexer',
  fallback: ['liblexer', 'liblexer_dep'],
  version: 'master',
)

include = include_directories('include')

main = executable('main.exe', [
    'src/main.cc',
    'src/tests/lexem.cc',
    'src/tests/symbol.cc',
    'src/tests/production.cc',
    'src/tests/parser_topdown.cc',
    'src/tests/parser_bottomup.cc',
    'src/tests/terminal.cc',
    'src/tests/nonterminal.cc',
    'src/tests/node.cc',
    'src/tests/calc.cc'
  ], include_directories : include,
  dependencies: [liblexer_dep])

libparser_dep = declare_dependency(
  include_directories : include)
