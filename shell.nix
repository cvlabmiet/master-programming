with import <nixpkgs> {};
mkShell rec {
  name = "master-programming";
  buildInputs = [ boost ];
  nativeBuildInputs = [
    cmake
    ninja
    pandoc docproc
    graphviz
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
