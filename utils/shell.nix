{ pkgs ? import <nixpkgs> { } }:
pkgs.mkShell
{
	nativeBuildInputs = with pkgs; [
# Dev-related pkgs:
		cmakeWithGui
		gcc
		gdb
		meson
		ninja
		rsync
		zip
# CKA_NOTE: Taken from the-nix-way/dev-templates: https://github.com/the-nix-way/dev-templates/blob/main/c-cpp/flake.nix
		clang-tools
		cmake
		codespell
		conan
		cppcheck
		doxygen
		gtest
		lcov
		vcpkg
		vcpkg-tool
	];
	buildInputs = with pkgs; [
# Libraries
		alsa-lib
		libclang
		libgcc
		libGL
		mesa
		xorg.libX11
		xorg.libXi
		xorg.libXcursor
		xorg.libXinerama
		xorg.libXrandr
		xorg.libXxf86vm
		xorg.xorgproto
	];
}
