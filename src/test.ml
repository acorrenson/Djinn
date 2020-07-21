open Djinn

let () = Array.init 10 float_of_int
         |> xtprint

let nn = xtbuild 256 300 2

let () = xtfree nn