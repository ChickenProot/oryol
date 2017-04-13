#
#   Puppet manifest to setup Oryol dev environment
#   for compiling to native Linux and emscripten
#

# essential packages
class essentials {

    package { "lib32z1": }
    package { "zlib1g": }
    package { "build-essential": }
    package { "vim": }
    package { "git": }
    package { "unzip": }
    package { "cmake": }
    package { "cmake-curses-gui": }
    package { "ninja-build": }
    package { "default-jre": }
    package { "ant": }
    package { "lib32stdc++6": }
}

# native Linux build requirements
class oryol-build {
    package { "libcurl4-gnutls-dev": }
    package { "uuid-dev": }
    package { "libglu1-mesa-dev": }
    package { "xorg-dev": }
}

include essentials
include oryol-build

