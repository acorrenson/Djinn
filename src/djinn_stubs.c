#define CAML_NAME_SPACE
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>
#include <stdio.h>
#include <tinn/Tinn.h>

/**
 * @brief Custom operations to handle opaque type Djinn.t
 *
 */
static struct custom_operations tinn_ops = {"djinn",
                                            custom_finalize_default,
                                            custom_compare_default,
                                            custom_hash_default,
                                            custom_serialize_default,
                                            custom_deserialize_default,
                                            custom_compare_ext_default,
                                            custom_fixed_length_default};

/**
 * @brief Value to Tinn structure
 *
 */
#define Tinn_val(t) (*((Tinn *)Data_custom_val(t)))

/**
 * @brief Convert an OCaml float array into a C float array.
 * Allocation is performed by the function.
 *
 * @param arr
 * @param size
 * @return float*
 */
static float *caml_array_to_array(value arr, int size) {
  float *c_arr = malloc(sizeof(float) * size);
  for (int i = 0; i < size; i++) {
    c_arr[i] = Double_array_field(arr, i);
  }
  return c_arr;
}

/**
 * @brief Binding to xtpredict
 *
 * @param nn A Djinn.t object
 * @param in An input float array
 * @return value
 */
value caml_xtpredict(value nn, value in) {
  CAMLparam2(nn, in);
  Tinn c_nn = Tinn_val(nn);
  float *c_in = caml_array_to_array(in, c_nn.nips);
  float *c_ret = xtpredict(c_nn, c_in);
  value ret = caml_alloc_float_array(c_nn.nops);
  for (int i = 0; i < c_nn.nips; i++) {
    Store_double_field(ret, i, c_ret[i]);
  }
  free(c_in);
  free(c_ret);
  CAMLreturn(ret);
}

/**
 * @brief Binding to xtprint
 *
 * @param m A float array
 * @param n The size of the array
 * @return value
 */
value caml_xtprint(value m, value n) {
  CAMLparam2(m, n);
  int c_n = Int_val(n);
  float *c_m = caml_array_to_array(m, c_n);
  xtprint(c_m, c_n);
  free(c_m);
  CAMLreturn(Val_unit);
}

/**
 * @brief Binding to xttrain.
 *
 * @param nn    The neural network
 * @param in    The inputs
 * @param tg    The labels
 * @param rate  The learning rate
 * @return value  The overall error
 */
value caml_xttrain(value nn, value in, value tg, value rate) {
  CAMLparam4(nn, in, tg, rate);
  Tinn c_nn = Tinn_val(nn);
  float *c_in = caml_array_to_array(in, c_nn.nips);
  float *c_tg = caml_array_to_array(tg, c_nn.nips);
  float c_rate = Double_val(rate);
  xttrain(c_nn, c_in, c_tg, c_rate);
  free(c_in);
  free(c_tg);
  CAMLreturn(Val_unit);
}

/**
 * @brief Binding to xtbuild
 *
 * @param nips Number of inputs
 * @param nhid Number of hidden neurons
 * @param nops Number of outputs
 * @return value  A Djinn.t object
 */
value caml_xtbuild(value nips, value nhid, value nops) {
  CAMLparam3(nips, nhid, nops);
  int c_nips = Int_val(nips);
  int c_nops = Int_val(nops);
  int c_nhid = Int_val(nhid);
  value t = caml_alloc_custom(&tinn_ops, sizeof(Tinn), 0, 1);
  Tinn_val(t) = xtbuild(c_nips, c_nhid, c_nops);
  CAMLreturn(t);
}

value caml_xtsave(value t, value f) {
  CAMLparam2(t, f);
  xtsave(Tinn_val(t), String_val(f));
  CAMLreturn(Val_unit);
}

value caml_xtload(value f) {
  CAMLparam1(f);
  value t = caml_alloc_custom(&tinn_ops, sizeof(Tinn), 0, 1);
  Tinn_val(t) = xtload(String_val(f));
  CAMLreturn(t);
}

/**
 * @brief Binding to xtfree
 *
 * @param t A Djinn.t object
 */
value caml_xtfree(value t) {
  CAMLparam1(t);
  xtfree(Tinn_val(t));
  CAMLreturn(Val_unit);
}

/**
 * @brief Display constant fields of a Tinn object for debug
 * purposes.
 *
 * @param t
 * @return value
 */
value caml_nn_display(value t) {
  CAMLparam1(t);
  Tinn c_nn = Tinn_val(t);
  printf("Nips: %d\nNops: %d\nNhid: %d\nNw: %d\n", c_nn.nips, c_nn.nops,
         c_nn.nhid, c_nn.nw);
  CAMLreturn(Val_unit);
}