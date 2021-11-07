with import <nixpkgs> {};
mkShell rec {
  name = "master-programming";
  buildInputs = [ (boost17x.override { useMpi = true; }) mpi icu ];
  nativeBuildInputs = [
    bash
    cmake
    ninja
    pandoc docproc
    graphviz
    xdot
    plantuml PandocElements
    asciidoc-full-with-plugins
    gcc
    gdb
  ];
  LANG = "C.UTF-8";
  hardeningDisable = [ "all" ];
  shellHook = ''
    alias make="cmake --build . --"
    echo Welcome to ${name} environment!
  '';
}
