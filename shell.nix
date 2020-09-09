with import <nixpkgs> {};

mkShell rec {
  name = "master-programming";
  nativeBuildInputs = [ cmake pandoc docproc graphviz plantuml PandocElements ];

  LANG = "C.UTF-8";

  shellHook = ''
    echo Welcome to ${name} environment!
  '';
}
