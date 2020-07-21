

type t

external xtpredict : t -> float array -> t -> float array = "caml_xtpredict"
(* float* xtpredict(Tinn, const float* in); *)

external xttrain : t -> float array -> float array -> float -> float = "caml_xttrain"
(* float xttrain(Tinn, const float* in, const float* tg, float rate); *)


external xtbuild : int -> int -> int -> t = "caml_xtbuild"
(* Tinn xtbuild(int nips, int nhid, int nops); *)

(* external xtsave : t -> string = "caml_xtsave" *)
(* void xtsave(Tinn, const char* path); *)

(* external xtload : string -> t = "caml_xtload" *)
(* Tinn xtload(const char* path); *)

external xtfree : t -> unit = "caml_xtfree"
(* void xtfree(Tinn); *)

external _xtprint : float array -> int -> unit = "caml_xtprint"
(* void xtprint(const float* arr, const int size); *)

let xtprint m = _xtprint m (Array.length m)
