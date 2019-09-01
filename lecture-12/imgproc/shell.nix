with import <nixpkgs> {};
let
  cxxopts = stdenv.mkDerivation rec {
    name = "cxxopts";
    version = "2.1.1";
    src = fetchFromGitHub {
      owner = "jarro2783";
      repo = name;
      rev = "v${version}";
      sha256 = "1l0bm0ysqa7j7kqhfi4mk6k4rhh5xc6mx82lw468sccn8m8a4ppg";
    };
    buildInputs = [ cmake ];
  };

in mkShell rec {
  name = "imgproc";
  buildInputs = [ boost168 libpng libjpeg cxxopts catch2 ];
  nativeBuildInputs = [ cmake gnumake gcc9 clang gdb valgrind strace cpplint include-what-you-use dpkg ];
  hardeningDisable = [ "all" ];
}
