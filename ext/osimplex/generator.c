#include "generator.h"
#include "open-simplex-noise.h"

#define GENERATOR() \
        OSimplexGenerator* generator; \
        Data_Get_Struct(self, OSimplexGenerator, generator)

#define FEATURE_SIZE 16

void Init_osimplex () {
  VALUE clsModule     = rb_define_module("OSimplex");
  VALUE clsGenerator  = rb_define_class_under(clsModule, "Generator", rb_cObject);

  rb_define_alloc_func( clsGenerator, OSimplex_Generator_allocate);
  rb_define_method(clsGenerator, "initialize", OSimplex_Generator_init, -1);
  rb_define_method(clsGenerator, "get_2d", OSimplex_Generator_get_2d, 2);
  rb_define_method(clsGenerator, "get_3d", OSimplex_Generator_get_3d, 3);
  rb_define_method(clsGenerator, "get_4d", OSimplex_Generator_get_3d, 4);
}

// Allocate a new Generator object instance.
VALUE OSimplex_Generator_allocate (VALUE klass) {
  OSimplexGenerator   *gen  = ALLOC(OSimplexGenerator);
  memset(gen, 0, sizeof(OSimplexGenerator));
  return Data_Wrap_Struct(klass, 0, OSimplex_Generator_free, gen);
}
// Initializes a newly created Generator object instance.
VALUE OSimplex_Generator_init (const int argc, const VALUE *argv, const VALUE self) {
  GENERATOR();
  VALUE   seed    = UINT2NUM(0);
  rb_scan_args(argc, argv, "01", &seed);
  open_simplex_noise(NUM2UINT(seed), &generator->context);
  return self;
}
// Frees-up a Generator object instance.
void OSimplex_Generator_free (OSimplexGenerator *generator) {
  open_simplex_noise_free(generator->context);
  xfree(generator);
}
VALUE OSimplex_Generator_get_2d (VALUE self, VALUE x, VALUE y) {
  GENERATOR();
  double  ret   = open_simplex_noise2( generator->context, NUM2DBL(x) / FEATURE_SIZE, NUM2DBL(y) / FEATURE_SIZE );
  return  rb_float_new(ret);
}
VALUE OSimplex_Generator_get_3d (VALUE self, VALUE x, VALUE y, VALUE z) {
  GENERATOR();
  double  ret   = open_simplex_noise3( generator->context, NUM2DBL(x) / FEATURE_SIZE, NUM2DBL(y) / FEATURE_SIZE, NUM2DBL(z) / FEATURE_SIZE );
  return  rb_float_new(ret);
}
VALUE OSimplex_Generator_get_4d (VALUE self, VALUE x, VALUE y, VALUE z, VALUE w) {
  GENERATOR();
  double  ret   = open_simplex_noise4( generator->context, NUM2DBL(x) / FEATURE_SIZE, NUM2DBL(y) / FEATURE_SIZE, NUM2DBL(z) / FEATURE_SIZE, NUM2DBL(w) / FEATURE_SIZE );
  return  rb_float_new(ret);
}
