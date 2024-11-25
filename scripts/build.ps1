$misc = join-path $PSScriptRoot 'helpers/misc.ps1'
. $misc

$path_root      = git rev-parse --show-toplevel
$path_build     = join-path $path_root 'build'
$path_scripts   = join-path $path_root 'scripts'
$path_source    = join-path $path_root 'source'
$path_toolchain = join-path $path_root 'toolchain'

verify-path $path_build
push-location $path_build
	function build-hello {
	}
	build-hello

	function build-copy_hello {
	}
	# build-copy_hello
pop-location
