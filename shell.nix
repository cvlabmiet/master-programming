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
  ];
  LANG = "C.UTF-8";
  shellHook = ''
    alias make="cmake --build . --"
    echo Welcome to ${name} environment!
  '';
}
