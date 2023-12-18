{ pkgs ? import <nixpkgs> {} }:
with pkgs;
mkShell rec {
  name = "master-programming";
  buildInputs = [ (boost.override { useMpi = true; }) mpi icu ];
  nativeBuildInputs = [
    bash
    cmake
    ninja
    parallel
    graphviz plantuml xdot
    asciidoc-full-with-plugins
    gdb
  ];
  LANG = "C.UTF-8";
  hardeningDisable = [ "all" ];
  shellHook = ''
    echo Welcome to ${name} environment!
  '';
}
