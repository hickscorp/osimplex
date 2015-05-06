#include "generator.h"
#include "open-simplex-noise.h"

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define GENERATOR() \
        OSimplexGenerator* generator; \
        Data_Get_Struct(self, OSimplexGenerator, generator)

void Init_osimplex () {
  VALUE clsModule     = rb_define_module("OSimplex");
  VALUE clsGenerator  = rb_define_class_under(clsModule, "Generator", rb_cObject);

  rb_define_alloc_func( clsGenerator,               OSimplex_Generator_allocate);
  rb_define_method(     clsGenerator, "initialize", OSimplex_Generator_init, -1);
  rb_define_method(     clsGenerator, "get_2d",     OSimplex_Generator_get_2d, 2);
  rb_define_method(     clsGenerator, "get_3d",     OSimplex_Generator_get_3d, 3);
  rb_define_method(     clsGenerator, "get_4d",     OSimplex_Generator_get_3d, 4);
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
  VALUE   seed      = UINT2NUM(0);
  VALUE   scale     = rb_float_new(1.0);
  VALUE   alpha     = rb_float_new(1.0);
  VALUE   beta      = rb_float_new(0.0);
  rb_scan_args(argc, argv, "03", &seed, &alpha, &beta);
  generator->scale  = NUM2DBL( scale );
  generator->alpha  = NUM2DBL( alpha );
  generator->beta   = NUM2DBL( beta );
  open_simplex_noise(NUM2UINT(seed), &generator->context);
  return self;
}
// Frees-up a Generator object instance.
void OSimplex_Generator_free (OSimplexGenerator *generator) {
  open_simplex_noise_free(generator->context);
  xfree(generator);
}

inline double normalize (double n, double alpha, double beta) {
  // Normalize between 0 and 1, apply contrast and brightness, then stay within 0..1 range.
  return max( min( alpha * ( ( ( 1.0 + n ) / 2.0 ) + beta ), 1.0 ), 0.0 );
}
VALUE OSimplex_Generator_get_2d (VALUE self, VALUE x, VALUE y) {
  GENERATOR();
  double  ret   = open_simplex_noise2( generator->context, NUM2DBL(x) / generator->scale, NUM2DBL(y) / generator->scale );
  return  rb_float_new( normalize(ret, generator->alpha, generator->beta) );
}
VALUE OSimplex_Generator_get_3d (VALUE self, VALUE x, VALUE y, VALUE z) {
  GENERATOR();
  double  ret   = open_simplex_noise3( generator->context, NUM2DBL(x) / generator->scale, NUM2DBL(y) / generator->scale, NUM2DBL(z) / generator->scale );
  return  rb_float_new( normalize(ret, generator->alpha, generator->beta) );
}
VALUE OSimplex_Generator_get_4d (VALUE self, VALUE x, VALUE y, VALUE z, VALUE w) {
  GENERATOR();
  double  ret   = open_simplex_noise4( generator->context, NUM2DBL(x) / generator->scale, NUM2DBL(y) / generator->scale, NUM2DBL(z) / generator->scale, NUM2DBL(w) / generator->scale );
  return  rb_float_new( normalize(ret, generator->alpha, generator->beta) );
}
