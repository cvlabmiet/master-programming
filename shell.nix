with import <nixpkgs> {};

let
  pandocenv = myGhc.ghcWithPackages (p: with p; [
    #pandoc-crossref
    #pandoc-citeproc
    pandoc-placetable
  ]);

in mkShell rec {
  name = "pandocenv";
  buildInputs = [ cmake pandocenv docproc graphviz plantuml panflute PandocElements pandoc-pipe ];
  propagatedNativeBuildInputs = [ myGhc.pandoc ];

  shellHook = ''
    echo Welcome to ${name} environment!
  '';
}
