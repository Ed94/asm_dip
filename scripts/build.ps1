$misc = join-path $PSScriptRoot 'helpers/misc.ps1'
. $misc

$path_root      = git rev-parse --show-toplevel
$path_build     = join-path $path_root 'build'
$path_scripts   = join-path $path_root 'scripts'
$path_source    = join-path $path_root 'source'
$path_toolchain = join-path $path_root 'toolchain'

$path_fasm  = join-path $path_toolchain 'fasmw17332'
$path_fasmg = join-path $path_toolchain 'fasmg.kl0e'
$path_fasm2 = join-path $path_toolchain 'fasm2'

$fasm  = join-path $path_fasm  'FASM.EXE'
$fasmg = join-path $path_fasmg 'fasmg.exe'
# $fasm2 = join-path $path_fasm2 "fasmg.exe -iInclude('fasm2.inc')"

verify-path $path_build
push-location $path_build
function build-hello
{
	$env:include = join-path $path_fasm2 'include'

	$asm_hello = join-path $path_source 'hello.asm'
	$exe_hello = 'hello.exe'

	& $fasmg $asm_hello $exe_hello
}
build-hello
pop-location
