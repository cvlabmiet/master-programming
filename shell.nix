with import <nixpkgs> {};

let
  pandoc_m = with haskell.packages.ghc843; pandoc_2_3.override { haddock-library = haddock-library_1_6_0; };
  ghcWithPackages = haskell.packages.ghc843.ghcWithPackages;
  pandocenv = ghcWithPackages (p: with p; [
    pandoc-crossref
    (pandoc-citeproc_0_14_4.override { pandoc = pandoc_m; })
    pandoc-placetable
  ]);

in mkShell rec {
  name = "pandocenv";
  buildInputs = [ cmake pandocenv docproc graphviz plantuml panflute PandocElements pandoc-pipe ];
  propagatedNativeBuildInputs = [ pandoc_m ];

  shellHook = ''
    echo Welcome to ${name} environment!
  '';
}
