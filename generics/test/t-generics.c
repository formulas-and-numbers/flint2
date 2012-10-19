/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2012 Fredrik Johansson

******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "generics.h"

int main()
{
    ring_t ZZ, ZZp, ZZpx, ZZpxy;
    gen_t P, R, Q;
    elem_t p;
    long size[3] = {8, 8, 8};

    flint_rand_t state;
    flint_randinit(state);

#if 1
    ring_init_fmpz(ZZ);
#else
    ring_init_limb(ZZ);
#endif

    elem_init(p, ZZ);
    elem_set_si(p, 17, ZZ);
    ring_init_mod(ZZp, ZZ, p);
    ring_init_poly(ZZpx, ZZp);
    ring_init_poly(ZZpxy, ZZpx);

    gen_init(P, ZZpxy);
    gen_init(R, ZZpxy);
    gen_init(Q, ZZpxy);

    gen_randtest(P, state, size);
    gen_randtest(R, state, size);

    gen_mul(Q, P, R);

    gen_print(P);
    gen_print(R);
    gen_print(Q);

    gen_clear(P);
    gen_clear(R);
    gen_clear(Q);

    elem_clear(p, ZZ);
    ring_clear(ZZpxy);
    ring_clear(ZZpx);
    ring_clear(ZZp);
    ring_clear(ZZ);

    flint_randclear(state);
    _fmpz_cleanup();
    return EXIT_SUCCESS;
}
