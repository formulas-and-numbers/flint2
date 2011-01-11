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

    Copyright (C) 1509 William Hart
    Copyright (C) 2010 Sebastian Pancratz

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_poly.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, result;
    flint_rand_t state;

    printf("evaluate_horner_mpq....");
    fflush(stdout);

    flint_randinit(state);

    /* Check aliasing */
    for (i = 0; i < 750; i++)
    {
        fmpz_t a, b;
        mpq_t x, y;
        fmpz_poly_t f;

        fmpz_init(a);
        fmpz_init(b);
        mpq_init(x);
        mpq_init(y);
        fmpz_poly_init(f);
        fmpz_poly_randtest(f, state, n_randint(state, 100), 150);
        fmpz_randtest(a, state, 100);
        fmpz_randtest_not_zero(b, state, 100);
        fmpz_get_mpz(mpq_numref(x), a);
        fmpz_get_mpz(mpq_denref(x), b);
        mpq_canonicalize(x);

        fmpz_poly_evaluate_horner_mpq(y, f, x);
        fmpz_poly_evaluate_horner_mpq(x, f, x);

        result = (mpq_equal(x, y));
        if (!result)
        {
            printf("FAIL:\n");
            fmpz_print(a), printf("\n\n");
            fmpz_print(b), printf("\n\n");
            fmpz_poly_print(f), printf("\n\n");
            abort();
        }

        fmpz_clear(a);
        fmpz_clear(b);
        mpq_clear(x);
        mpq_clear(y);
        fmpz_poly_clear(f);
    }

    /* Check that (f+g)(a) = f(a) + g(a) */
    for (i = 0; i < 750; i++)
    {
        fmpz_t a, b;
        mpq_t x, y, z;
        fmpz_poly_t f, g;

        fmpz_init(a);
        fmpz_init(b);
        mpq_init(x);
        mpq_init(y);
        mpq_init(z);
        fmpz_poly_init(f);
        fmpz_poly_init(g);
        fmpz_poly_randtest(f, state, n_randint(state, 100), 150);
        fmpz_poly_randtest(g, state, n_randint(state, 100), 150);
        fmpz_randtest(a, state, 100);
        fmpz_randtest_not_zero(b, state, 100);
        fmpz_get_mpz(mpq_numref(x), a);
        fmpz_get_mpz(mpq_denref(x), b);
        mpq_canonicalize(x);

        fmpz_poly_evaluate_horner_mpq(y, f, x);
        fmpz_poly_evaluate_horner_mpq(z, g, x);
        mpq_add(y, y, z);
        fmpz_poly_add(f, f, g);
        fmpz_poly_evaluate_horner_mpq(z, f, x);

        result = (mpq_equal(y, z));
        if (!result)
        {
            printf("FAIL:\n");
            fmpz_print(a), printf("\n\n");
            fmpz_print(b), printf("\n\n");
            abort();
        }

        fmpz_clear(a);
        fmpz_clear(b);
        mpq_clear(x);
        mpq_clear(y);
        mpq_clear(z);
        fmpz_poly_clear(f);
        fmpz_poly_clear(g);
    }

    /* Check that (f*g)(a) = f(a) * g(a) */
    for (i = 0; i < 750; i++)
    {
        fmpz_t a, b;
        mpq_t x, y, z;
        fmpz_poly_t f, g;

        fmpz_init(a);
        fmpz_init(b);
        mpq_init(x);
        mpq_init(y);
        mpq_init(z);
        fmpz_poly_init(f);
        fmpz_poly_init(g);
        fmpz_poly_randtest(f, state, n_randint(state, 50), 100);
        fmpz_poly_randtest(g, state, n_randint(state, 50), 100);
        fmpz_randtest(a, state, 100);
        fmpz_randtest_not_zero(b, state, 100);
        fmpz_get_mpz(mpq_numref(x), a);
        fmpz_get_mpz(mpq_denref(x), b);
        mpq_canonicalize(x);

        fmpz_poly_evaluate_horner_mpq(y, f, x);
        fmpz_poly_evaluate_horner_mpq(z, g, x);
        mpq_mul(y, y, z);
        fmpz_poly_mul(f, f, g);
        fmpz_poly_evaluate_horner_mpq(z, f, x);

        result = (mpq_equal(y, z));
        if (!result)
        {
            printf("FAIL:\n");
            fmpz_print(a), printf("\n\n");
            fmpz_print(b), printf("\n\n");
            abort();
        }

        fmpz_clear(a);
        fmpz_clear(b);
        mpq_clear(x);
        mpq_clear(y);
        mpq_clear(z);
        fmpz_poly_clear(f);
        fmpz_poly_clear(g);
    }

    flint_randclear(state);
    _fmpz_cleanup();
    printf("PASS\n");
    return 0;
}
