$misc = join-path $PSScriptRoot 'helpers/misc.ps1'
. $misc

$path_root      = git rev-parse --show-toplevel
$path_build     = join-path $path_root 'build'
$path_scripts   = join-path $path_root 'scripts'
$path_source    = join-path $path_root 'source'
$path_toolchain = join-path $path_root 'toolchain'

# Note: No longer using nasm
if ($false) {
	$url_yasm = 'https://github.com/yasm/yasm.git'

	$path_yasm    = join-path $path_toolchain 'yasm'
	$path_libyasm = join-path $path_yasm 'libyasm'

	clone-gitrepo $path_yasm $url_yasm
}
