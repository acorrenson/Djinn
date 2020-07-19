
(* typedef struct
   {
    // All the weights.
                 float* w;
    // Hidden to output layer weights.
                                float* x;
   // Biases.
       float* b;
   // Hidden layer.
              float* h;
   // Output layer.
              float* o;
   // Number of biases - always two - Tinn only supports a single hidden layer.
                                                                          int nb;
   // Number of weights.
                 int nw;
   // Number of inputs.
                 int nips;
   // Number of hidden neurons.
                        int nhid;
   // Number of outputs.
                 int nops;
   }
   Tinn; *)


module Djinn = struct 

  type t = {
    (* All the weights. *)
    w : float array;
    (* Hidden to output layer weights. *)
    x : float array;
    (* Biases. *)
    b : float array;
    (* Hidden layer. *)
    h : float array;
    (* Output layer. *)
    o : float array;
    (* Number of biases - always two - Tinn only supports a single hidden layer. *)
    nb : int;
    (* Number of weights. *)
    nw : int;
    (* Number of inputs. *)
    nips : int;
    (* Number of hidden neurons. *)
    nhid : int;
    (* Number of outputs. *)
    nops : int;
  }

  external xtpredict : t -> float array -> t -> float array = "caml_xtpredict"
  (* float* xtpredict(Tinn, const float* in); *)

  external xttrain : t -> float array -> float array -> float = "caml_xttrain"
  (* float xttrain(Tinn, const float* in, const float* tg, float rate); *)

  external xtbuild : int -> int -> int -> t = "caml_xtbuild"
  (* Tinn xtbuild(int nips, int nhid, int nops); *)

  external xtsave : t -> string = "caml_xtsave"
  (* void xtsave(Tinn, const char* path); *)

  external xtload : string -> t = "caml_xtload"
  (* Tinn xtload(const char* path); *)

  (* todo ? *)
  (* void xtfree(Tinn); *)

  external xtprint : float array -> unit
  (* void xtprint(const float* arr, const int size); *)

end