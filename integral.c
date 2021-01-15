double
integral (double (*f) (double), double a, double b, double eps2)
{
    char flag = 0;

    if (a > b) {
	double temp = a;
	a = b;
	b = temp;

	flag = 1;
    }
    
    int count = 20;

    double dif = 0;
    double step = (b - a) / count;
    double ans1 = 0, ans2 = 0;

    for (int i = 0; i < count; i++)
        ans1 = f(a + (i + 0.5) * step);

    ans1 *= step;
    
    do {

	ans2 = 0;
	count <<= 1;
        step /= 2;

	for (int i = 0; i < count; i++)
            ans2 += f(a + (i + 0.5) * step);

	ans2 *= step;

        dif = (ans1 - ans2) / 3;
	if (dif < 0)
	    dif *= -1;

	ans1 = ans2;

    } while (dif > eps2);

    if (flag)
        ans2 = -ans2;

    return ans2;
}
