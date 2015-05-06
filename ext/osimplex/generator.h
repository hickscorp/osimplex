// class OSimplex::Generator

#ifndef OSimplexGenerator_h
#define OSimplexGenerator_h

#include <ruby.h>

typedef struct _OSimpleGenerator {
  double      scale, alpha, beta;
  struct osn_context *context;
} OSimplexGenerator;

void    Init_osimplex               ();
VALUE   OSimplex_Generator_allocate (VALUE klass);
VALUE   OSimplex_Generator_init     (const int argc, const VALUE *argv, const VALUE self);
void    OSimplex_Generator_free     (OSimplexGenerator *gen);

VALUE   OSimplex_Generator_get_2d   (VALUE self, VALUE x, VALUE y);
VALUE   OSimplex_Generator_get_3d   (VALUE self, VALUE x, VALUE y, VALUE z);
VALUE   OSimplex_Generator_get_4d   (VALUE self, VALUE x, VALUE y, VALUE z, VALUE w);

#endif
