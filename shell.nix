with import <nixpkgs> {};

mkShell rec {
  name = "master-programming";
  nativeBuildInputs = [ cmake pandoc pandoc-crossref docproc graphviz plantuml PandocElements ];

  shellHook = ''
    echo Welcome to ${name} environment!
  '';
}
