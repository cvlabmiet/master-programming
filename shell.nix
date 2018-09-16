with import <nixpkgs> {};

let
  ghcWithPackages = haskell.packages.ghc843.ghcWithPackages;
  pandocenv = ghcWithPackages (p: with p; [
    pandoc
    (pandoc-crossref.overrideAttrs (oldAttrs: { doCheck = false; }))
    pandoc-citeproc
    pandoc-placetable
  ]);

in mkShell rec {
  name = "pandocenv";
  buildInputs = [ cmake pandocenv docproc graphviz plantuml panflute PandocElements ];

  shellHook = ''
    echo Welcome to ${name} environment!
  '';
}
