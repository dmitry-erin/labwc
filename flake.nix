{
  description = "Labwc";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = inputs:
    with inputs;
      flake-utils.lib.eachDefaultSystem (
        system: let
          pkgs = import nixpkgs {
            inherit system;
          };
        in rec {
          packages = {
            labwc = nixpkgs.legacyPackages.${system}.callPackage ./default.nix {
              inherit pkgs;
            };
            default = packages.labwc;
          };

          formatter = nixpkgs.legacyPackages.${system}.alejandra;
          devShells.default = pkgs.mkShell {};
        }
      );
}
