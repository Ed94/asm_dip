$ps1_devshell = join-path $PSScriptRoot 'helpers/devshell.ps1'
. $ps1_devshell -arch amd64
$path_root      = split-path -Path $PSScriptRoot -Parent
$path_build     = join-path $path_root      'build'
$path_code      = join-path $path_root      'code'
$path_asm       = join-path $path_code      'asm'
$path_toolchain = join-path $path_root      'toolchain'
$path_radlink   = join-path $path_toolchain 'radlink'

if ((test-path $path_build) -eq $false) {
	new-item -itemtype directory -path $path_build
}

$hello_nasm = join-path $path_asm   'hello_nasm.asm'
$listing    = join-path $path_build 'hello_nasm.list'
$link_obj   = join-path $path_build 'hello_nasm.o'
$exe        = join-path $path_build 'hello_nasm.exe'

$nasm    = 'nasm'
$radlink = join-path $path_radlink 'radlink.exe'

push-location $path_root
$f_assemble_only       = '-a'
$f_bin_fmt_coff        = '-f coff'
$f_bin_fmt_win64       = '-f win64'
$f_debug               = '-g'
$f_debug_fmt_win64     = '-g cv8'
$f_dmacro              = '-Dmacro='
$f_Ipath               = '-Ipath '
$f_listing             = '-l'
$f_preprocess_only     = '-E'
$f_optimize_none       = '-O0'
$f_optimize_min        = '-O1'
$f_optimize_multi      = '-Ox'
$f_optimize_multi_disp = '-Ov'
$f_outfile             = '-o '
$f_warnings_as_errors  = '-Werror'
$args = @(
	$hello_nasm,
	$f_optimize_none,
	$f_bin_fmt_win64,
	$f_debug_fmt_win64,
	($f_listing + $listing),
	($f_outfile + $link_obj)
)
& $nasm $args

$lib_kernel32 = 'kernel32.lib'
$lib_msvcrt   = 'msvcrt.lib'

$link = 'link.exe'

$link_debug                  = '/DEBUG:'
$link_entrypoint             = '/ENTRY:'
$link_library                = '/'
$link_outfile                = '/OUT:'
$link_win_machine_64         = '/MACHINE:X64'
$link_win_subsystem_console  = '/SUBSYSTEM:CONSOLE'
$link_win_subsystem_windows  = '/SUBSYSTEM:WINDOWS'
$rad_debug                   = '/RAD_DEBUG'
$rad_debug_name              = '/RAD_DEBUG_NAME:'
$rad_large_pages             = '/RAD_LARGE_PAGES:'
$args = @(
	$rad_debug,
	# ($link_debug + 'FULL'),
	$link_win_machine_64,
	$link_win_subsystem_console,
	$lib_kernel32,
	# $lib_msvcrt,
	($link_entrypoint + 'main'),
	($link_outfile + $exe),
	$link_obj
)
& $radlink $args
pop-location
