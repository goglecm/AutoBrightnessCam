let g:ale_c_flawfinder_minlevel = 3
let g:ale_cpp_flawfinder_minlevel = 3

let g:ale_lint_delay = 2000

let g:ale_linters = {
            \ 'c'   : ['gcc', 'clang', 'cppcheck'],
            \ 'h'   : ['gcc', 'clang'],
            \ 'cpp' : ['gcc', 'clang']}

let g:ale_linters_explicit = 1

let g:ale_c_clangtidy_options = '
            \ -Isource/libs/inc
            \ -Ibuild
            \ -Isource/libs/inc_test
            \ -DABC_PICTURE_DIR=\"\"
            \ -DABC_CONFIG_FILENAME=\"aubrca.conf\"
            \ -DABC_CONFIG_DEFAULTS_FILENAME=\"defaults.conf\"
            \ -DABC_HAS_UPOWER=0
            \ -DDEBUG=1
            \ -DABC_LOGGING_ON=1
            \ -DABC_HAS_LIBCONFIG=1
            \ -DABC_LOGGING_DEFAULT_FILENAME=\"log.log\"'

let g:ale_cpp_clangtidy_options = '
            \ -Isource/libs/inc
            \ -Isource/libs/inc_test
            \ -Isource/libs/tests/test_lib/inc
            \ -Ibuild
            \ -DABC_PICTURE_DIR=\"\"
            \ -DABC_CONFIG_FILENAME=\"aubrca.conf\"
            \ -DABC_CONFIG_DEFAULTS_FILENAME=\"defaults.conf\"
            \ -DABC_HAS_UPOWER=0
            \ -DDEBUG=1
            \ -DABC_LOGGING_ON=1
            \ -DABC_HAS_LIBCONFIG=1
            \ -DABC_LOGGING_DEFAULT_FILENAME=\"log.log\"'

""""""""""""""""""""
" CPPCHECK options "
""""""""""""""""""""

let g:ale_cpp_cppcheck_options = '
            \ -DABC_PICTURE_DIR=\"\"
            \ -DABC_CONFIG_FILENAME=\"aubrca.conf\"
            \ -DABC_CONFIG_DEFAULTS_FILENAME=\"defaults.conf\"
            \ -DABC_HAS_UPOWER=0
            \ --std=c++11
            \ --enable=warning,style,performance,portability,information
            \ -Ibuild
            \ -Ibuild/source
            \ -DABC_LOGGING_ON=1
            \ -DABC_HAS_LIBCONFIG=1
            \ -DABC_LOGGING_DEFAULT_FILENAME=\"log.log\"
            \ -DDEBUG=1
            \ -Isource/libs/inc_test
            \ -Isource/libs/tests/test_lib/inc
            \ -Isource/libs/inc'

let g:ale_c_cppcheck_options = '
            \ -DABC_PICTURE_DIR=\"\"
            \ -DABC_CONFIG_FILENAME=\"aubrca.conf\"
            \ -DABC_CONFIG_DEFAULTS_FILENAME=\"defaults.conf\"
            \ -DABC_LOGGING_ON=1
            \ -DABC_HAS_LIBCONFIG=1
            \ -DABC_LOGGING_DEFAULT_FILENAME=\"log.log\"
            \ -DDEBUG=1
            \ -DABC_HAS_UPOWER=0
            \ --std=c99
            \ --enable=warning,style,performance,portability,information
            \ -DHAVE_CONFIG_H
            \ -Isource/libs/inc
            \ -Isource/libs/inc_test
            \ -Ibuild
            \ -Ibuild/source'


"""""""""""""""""
" CLANG options "
"""""""""""""""""

let g:ale_c_clang_options = '
            \ -DABC_PICTURE_DIR=\"\"
            \ -DABC_LOGGING_ON=1
            \ -DABC_HAS_LIBCONFIG=1
            \ -DABC_LOGGING_DEFAULT_FILENAME=\"log.log\"
            \ -DABC_CONFIG_FILENAME=\"aubrca.conf\"
            \ -DABC_CONFIG_DEFAULTS_FILENAME=\"defaults.conf\"
            \ -DABC_HAS_UPOWER=0
            \ -DDEBUG=1
            \ -std=gnu99
            \ -DHAVE_CONFIG_H
            \ -Isource/libs/inc_test
            \ -Wno-unknown-warning-option
            \ -Ibuild/source
            \ -Ibuild
            \ -Wall
            \ -Wpedantic
            \ -Wextra
            \ -Wno-unknown-warning
            \ -Wdouble-promotion
            \ -Wformat-y2k
            \ -Wmissing-include-dirs
            \ -Wswitch-default
            \ -Wunused-parameter
            \ -Wstrict-aliasing
            \ -Wstrict-overflow=5
            \ -Wtrampolines
            \ -Wfloat-equal
            \ -Wshadow
            \ -Wpointer-arith
            \ -Wbad-function-cast
            \ -Wc++-compat
            \ -Wcast-qual
            \ -Wcast-align
            \ -Wwrite-strings
            \ -Wconversion
            \ -Wno-sign-conversion
            \ -Wjump-misses-init
            \ -Wlogical-op
            \ -Wstrict-prototypes
            \ -Wold-style-definition
            \ -Wmissing-declarations
            \ -Wredundant-decls
            \ -Wnested-externs
            \ -Wunsuffixed-float-constants
            \ -Wunsafe-loop-optimizations
            \ -Isource/libs/inc'

let g:ale_cpp_clang_options = '
            \ -DABC_PICTURE_DIR=\"\"
            \ -DABC_CONFIG_FILENAME=\"aubrca.conf\"
            \ -DABC_CONFIG_DEFAULTS_FILENAME=\"defaults.conf\"
            \ -DABC_HAS_UPOWER=0
            \ -Ibuild
            \ -Ibuild/source
            \ -DABC_LOGGING_ON=1
            \ -DABC_HAS_LIBCONFIG=1
            \ -DABC_LOGGING_DEFAULT_FILENAME=\"log.log\"
            \ -DDEBUG=1
            \ -Isource/libs/inc
            \ -Isource/libs/inc_test
            \ -Isource/libs/tests/test_lib/inc
            \ -std=c++11
            \ -Wall
            \ -Wextra'


"""""""""""""""
" GCC options "
"""""""""""""""

let g:ale_c_gcc_options = '
            \ -DABC_PICTURE_DIR=\"\"
            \ -DABC_CONFIG_FILENAME=\"aubrca.conf\"
            \ -DABC_CONFIG_DEFAULTS_FILENAME=\"defaults.conf\"
            \ -DABC_HAS_UPOWER=0
            \ -DABC_LOGGING_ON=1
            \ -DABC_HAS_LIBCONFIG=1
            \ -DABC_LOGGING_DEFAULT_FILENAME=\"log.log\"
            \ -DDEBUG=1
            \ -std=gnu99
            \ -DHAVE_CONFIG_H
            \ -Isource/libs/inc_test
            \ -Ibuild/source
            \ -Ibuild
            \ -Wall
            \ -Wpedantic
            \ -Wextra
            \ -Wno-unknown-warning
            \ -Wdouble-promotion
            \ -Wformat-y2k
            \ -Wmissing-include-dirs
            \ -Wswitch-default
            \ -Wunused-parameter
            \ -Wstrict-aliasing
            \ -Wstrict-overflow=5
            \ -Wtrampolines
            \ -Wfloat-equal
            \ -Wshadow
            \ -Wpointer-arith
            \ -Wbad-function-cast
            \ -Wc++-compat
            \ -Wcast-qual
            \ -Wcast-align
            \ -Wwrite-strings
            \ -Wconversion
            \ -Wno-sign-conversion
            \ -Wjump-misses-init
            \ -Wlogical-op
            \ -Wstrict-prototypes
            \ -Wold-style-definition
            \ -Wmissing-declarations
            \ -Wredundant-decls
            \ -Wnested-externs
            \ -Wunsuffixed-float-constants
            \ -Wunsafe-loop-optimizations
            \ -Isource/libs/inc'

let g:ale_cpp_gcc_options = '
            \ -DABC_PICTURE_DIR=\"\"
            \ -DABC_CONFIG_FILENAME=\"aubrca.conf\"
            \ -DABC_CONFIG_DEFAULTS_FILENAME=\"defaults.conf\"
            \ -DABC_HAS_UPOWER=0
            \ -DDEBUG=1
            \ -Ibuild
            \ -Ibuild/source
            \ -DABC_LOGGING_ON=1
            \ -DABC_HAS_LIBCONFIG=1
            \ -DABC_LOGGING_DEFAULT_FILENAME=\"log.log\"
            \ -Isource/libs/inc
            \ -Isource/libs/inc_test
            \ -Isource/libs/tests/test_lib/inc
            \ -std=c++11
            \ -Wall
            \ -Wextra'
