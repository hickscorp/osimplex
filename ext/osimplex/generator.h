// class OSimplex::Generator

#ifndef OSimplexGenerator_h
#define OSimplexGenerator_h

#include <ruby.h>

typedef struct _OSimpleGenerator {
  double      scale, alpha, beta;
  struct osn_context *context;
} OSimplexGenerator;

void    Init_osimplex                   ();
VALUE   OSimplex_Generator_allocate     (VALUE klass);
VALUE   OSimplex_Generator_init         (const int argc, const VALUE *argv, const VALUE self);
void    OSimplex_Generator_free         (OSimplexGenerator *gen);

VALUE   OSimplex_Generator_get_2d       (const VALUE self, const VALUE x, const VALUE y);
VALUE   OSimplex_Generator_get_3d       (const VALUE self, const VALUE x, const VALUE y, const VALUE z);
VALUE   OSimplex_Generator_get_4d       (const VALUE self, const VALUE x, const VALUE y, const VALUE z, const VALUE w);

VALUE   OSimplex_Generator_get_2d_chunk (const VALUE self, const VALUE x, const VALUE y, const VALUE width, const VALUE height);
VALUE   OSimplex_Generator_get_3d_chunk (const VALUE self, const VALUE x, const VALUE y, const VALUE z, const VALUE width, const VALUE height);
VALUE   OSimplex_Generator_get_4d_chunk (const VALUE self, const VALUE x, const VALUE y, const VALUE z, const VALUE w, const VALUE width, const VALUE height);

#endif
