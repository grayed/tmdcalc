// frames.h
// Last modified 04.09.2017 by Artem Lipatov

#ifndef FRAMES_H
#define FRAMES_H

#include "utils.h"
#include "HEPVector4.h"

void cm2z(THEPVector4 pcm, THEPVector4& pz);   // c.m. frame -> c.m. frame with OZ going along to the H 3-momentum
void z2cm(THEPVector4 pz, THEPVector4& pcm);   // c.m. frame with OZ going along to the H 3-momentum -> c.m. frame
void cm2rf(THEPVector4 pcm, THEPVector4& prf); // c.m. frame -> H rest frame
void rf2cm(THEPVector4 prf, THEPVector4& pcm); // H rest frame - > c.m. frame

void cm2hl(THEPVector4 pcm, THEPVector4& phl); // c.m. frame -> helicity frame
void cm2tg(THEPVector4 pcm, THEPVector4& ptg); // c.m. frame -> target frame
void cm2cs(THEPVector4 pcm, THEPVector4& pcs); // c.m. frame -> Collins-Soper frame
void cm2pl(THEPVector4 pcm, THEPVector4& ppl); // c.m. frame -> perpendicular helicity frame

#endif

