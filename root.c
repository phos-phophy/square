extern int iter;

double
val (double (*f) (double), double (*g) (double), double x) 
{
    return f(x) - g(x);
}

double
root (double (*f) (double), double (*g) (double), double (*f_der) (double), double (*g_der) (double), double a, double b, double eps1)
{
    double F_der = val(f_der, g_der, b);
    double F = val(f, g, b) + val(f, g, a);
    
    double dif = val(f, g, (a + b) / 2) - F / 2; 

    double st = a;

    iter = 0;

    if ((F_der > 0 && dif < 0) || (F_der < 0 && dif > 0))
        st = b;

    F = val(f, g, st);

    do {
        F_der = val(f_der, g_der, st);

        st = st - F / F_der;

        F = val(f, g, st);
	
	iter++;

    } while ((F > 0 && F > eps1) || (F < 0 && F < -eps1));

    return st;
}
