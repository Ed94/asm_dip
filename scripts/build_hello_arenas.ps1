$ps1_devshell = join-path $PSScriptRoot 'helpers/devshell.ps1'
. $ps1_devshell -arch amd64
$path_root      = split-path -Path $PSScriptRoot -Parent
$path_build     = join-path $path_root      'build'
$path_code      = join-path $path_root      'code'
$path_asm       = join-path $path_code      'asm'
$path_toolchain = join-path $path_root      'toolchain'
$path_rad       = join-path $path_toolchain 'rad'

if ((test-path $path_build) -eq $false) {
	new-item -itemtype directory -path $path_build
}

$unit_name = 'hello_arenas'

$src         = join-path $path_asm   "$unit_name.asm"
$unit        = join-path $path_build "$unit_name.unit.asm"
$listing     = join-path $path_build "$unit_name.asm.list"
$link_obj    = join-path $path_build "$unit_name.o"
$map         = join-path $path_build "$unit_name.map"
$pdb         = join-path $path_build "$unit_name.pdb"
$rdi         = join-path $path_build "$unit_name.rdi"
$rdi_listing = join-path $path_build "$unit_name.rdi.list"
$exe         = join-path $path_build "$unit_name.exe"

$nasm    = 'nasm'
$link    = 'link.exe'
$radbin  = join-path $path_rad 'radbin.exe'
$radlink = join-path $path_rad 'radlink.exe'

push-location $path_root
$f_assemble_only       = '-a'
$f_bin_fmt_coff        = '-f coff'
$f_bin_fmt_win64       = '-f win64'
$f_debug               = '-g'
$f_debug_fmt_win64     = '-g cv8'
$f_dmacro              = '-Dmacro='
$f_Ipath               = '-Ipath '
$f_listing             = '-l'
$f_listing_plus        = '-L+'
$f_preprocess_only     = '-E'
$f_optimize_none       = '-O0'
$f_optimize_min        = '-O1'
$f_optimize_multi      = '-Ox'
$f_optimize_multi_disp = '-Ov'
$f_outfile             = '-o '
$f_warnings_as_errors  = '-Werror'

# $nargs = @(
# 	$src,
# 	$f_preprocess_only,
# 	$f_optimize_none,
# 	($f_outfile + $unit)
# )
# write-host 'Preprocessing'
# $nargs | ForEach-Object { Write-Host $_ }
# & $nasm $nargs

$nargs = @(
	$src,
	$f_optimize_none,
	$f_bin_fmt_win64,
	$f_debug_fmt_win64,
	$f_listing_plus,
	($f_listing + $listing),
	($f_outfile + $link_obj)
)
write-host 'Assembling'
$nargs | ForEach-Object { Write-Host "`t$_" }
& $nasm $nargs

$lib_kernel32 = 'kernel32.lib'
$lib_msvcrt   = 'msvcrt.lib'

$link_nologo                 = '/NOLOGO'
$link_debug                  = '/DEBUG:'
$link_entrypoint             = '/ENTRY:'
$link_mapfile                = '/MAP:'
$link_no_incremental 	     = '/INCREMENTAL:NO'
$link_large_address_aware    = '/LARGEADDRESSAWARE:NO'
$link_listing                = '/LIST'
$link_outfile                = '/OUT:'
$link_win_machine_64         = '/MACHINE:X64'
$link_win_pdb 		         = '/PDB:'
$link_win_subsystem_console  = '/SUBSYSTEM:CONSOLE'
$link_win_subsystem_windows  = '/SUBSYSTEM:WINDOWS'
$rad_debug                   = '/RAD_DEBUG'
$rad_debug_name              = '/RAD_DEBUG_NAME:'
$rad_large_pages             = '/RAD_LARGE_PAGES:'
$nargs = @(
	# $rad_debug,
	$link_nologo,
	($link_debug + 'FULL'),
	($link_mapfile + $map),
	($link_win_pdb + $pdb),
	# $link_listing,
	$link_no_incremental,
	$link_large_address_aware,
	$link_win_machine_64,
	$link_win_subsystem_console,
	$lib_kernel32,
	# $lib_msvcrt,
	($link_entrypoint + 'main'),
	($link_outfile + $exe),
	$link_obj
)
write-host 'Linking'
$nargs | ForEach-Object { Write-Host "`t$_" }
& $link $nargs
pop-location

$rbin_out  = '--out:'
$rbin_dump = '--dump'

write-host 'Dumping RDI'
$nargs  = @($pdb, ($rbin_out + $rdi))
& $radbin $nargs
$nargs = @($rbin_dump, $rdi)
$dump = & $radbin $nargs
$dump > $rdi_listing
