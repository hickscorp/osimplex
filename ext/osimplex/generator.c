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
  OSimplexGenerator* gen;
  Data_Get_Struct(self, OSimplexGenerator, gen);

  VALUE   seed    = UINT2NUM(0);
  VALUE   scale   = rb_float_new(1.0);
  VALUE   alpha   = rb_float_new(1.0);
  VALUE   beta    = rb_float_new(0.0);

  rb_scan_args(argc, argv, "04", &seed, &scale, &alpha, &beta);

  open_simplex_noise(NUM2UINT(seed), &gen->context);
  gen->scale      = NUM2DBL( scale );
  gen->alpha      = NUM2DBL( alpha );
  gen->beta       = NUM2DBL( beta );

  return self;
}
// Frees-up a Generator object instance.
void OSimplex_Generator_free (OSimplexGenerator *gen) {
  open_simplex_noise_free(gen->context);
  xfree(gen);
}

inline double normalize (const double n, const OSimplexGenerator *gen) {
  // Normalize between 0 and 1, apply contrast and brightness, then stay within 0..1 range.
  return max( min( gen->alpha * ( ( ( 1.0 + n ) / 2.0 ) + gen->beta ), 1.0 ), 0.0 );
}
VALUE OSimplex_Generator_get_2d (VALUE self, VALUE x, VALUE y) {
  OSimplexGenerator* gen;
  Data_Get_Struct(self, OSimplexGenerator, gen);

  double  ret   = open_simplex_noise2( gen->context, NUM2DBL(x) / gen->scale, NUM2DBL(y) / gen->scale );
  return  rb_float_new( normalize(ret, gen ) );
}
VALUE OSimplex_Generator_get_3d (VALUE self, VALUE x, VALUE y, VALUE z) {
  OSimplexGenerator* gen;
  Data_Get_Struct(self, OSimplexGenerator, gen);

  double  ret   = open_simplex_noise3( gen->context, NUM2DBL(x) / gen->scale, NUM2DBL(y) / gen->scale, NUM2DBL(z) / gen->scale );
  return  rb_float_new( normalize(ret, gen ) );
}
VALUE OSimplex_Generator_get_4d (VALUE self, VALUE x, VALUE y, VALUE z, VALUE w) {
  OSimplexGenerator* gen;
  Data_Get_Struct(self, OSimplexGenerator, gen);

  double  ret   = open_simplex_noise4( gen->context, NUM2DBL(x) / gen->scale, NUM2DBL(y) / gen->scale, NUM2DBL(z) / gen->scale, NUM2DBL(w) / gen->scale );
  return  rb_float_new( normalize(ret, gen ) );
}
