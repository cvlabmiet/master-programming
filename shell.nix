with import <nixpkgs> {};
mkShell rec {
  name = "master-programming";
  buildInputs = [ (boost17x.override { useMpi = true; }) mpi icu ];
  nativeBuildInputs = [
    bash
    cmake
    ninja
    graphviz plantuml xdot
    asciidoc-full-with-plugins
    gdb
  ];
  LANG = "C.UTF-8";
  hardeningDisable = [ "all" ];
  shellHook = ''
    alias make="cmake --build . --"
    echo Welcome to ${name} environment!
  '';
}
