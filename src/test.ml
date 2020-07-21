open Djinn

let nn = xtbuild 100 100 2

let () =
  xtsave nn "test.djinn";
  xtfree nn;
  xtload "test.djinn" |> nn_display
