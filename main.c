#include <stdio.h>
#include <string.h>
#include "math_module.h"
#include "funct.h"

#define COLOR_RED "\033[0;31m"

int iter = 0; // count the number of iterations

int
main (int args, char *argv[])
{
    char *keys[] = {"-help", "-iter", "-absc", "-test"};

    char flag_iter = 0, flag_absc = 0;

    double (*test_f[])(double) = {f1_test, f2_test, f3_test};

    double (*test_f_der[])(double) = {f1_test_der, f2_test_der, f3_test_der};

    char err_message[] = COLOR_RED
	    "ERROR: Undefined keys or incorrect format\n"
	    "Please use the -help key to see a list of all keys\n";

    char *f_name[] = {"y = (x - 2)(x + 2)", "y = sqrt(x) - 1", "y = e ^ (x + 1) - 1", 
	    "e ^ (-x) + 3 = 2x - 2", "e ^ (-x) + 3 = 1 / x", "2x - 2 = 1 / x"};

    if (args > 1) {

	if (!strcmp(argv[1], keys[0])) {
	    printf("List of all keys:\n"
	            "-help      prints list of all keys and their description\n"
	            "-iter      prints count of iteration\n"
	            "-absc      prints abscissa of points of intersection\n"
	            "-test      tests the \"root\" and \"integral\" functions\n\n"
	            "You can use the -absc and -iter keys with each other\n\n"
	            "You should use the -test key with following paraments:\n"
	            "integral/root number_that_specifies_the_function "
	       	    "start_point end_point accuracy\n\n"
		    "Example of usage: integral 3 4 10 0.0001\n\n"
	            "The functions for test:\n");

	    for (int i = 0; i < 3; i++)
	        printf("%d) %s\n", i + 1, f_name[i]);

	    return 0;
	}

	if (!strcmp(argv[1], keys[3])) {
	    int funct = 0;
            double st_p = 0, end_p = 0, esp = 0;

            if (args == 7 && sscanf(argv[3], "%d", &funct) && funct > 0 && funct < 4
	            && sscanf(argv[4], "%lf", &st_p) && sscanf(argv[5], "%lf", &end_p)
		    && sscanf(argv[6], "%lf", &esp)) {

		if (!strcmp(argv[2], "integral"))
	            printf("Integral of %s from %lf to %lf is %lf\n",f_name[funct - 1],
		            st_p, end_p ,integral(test_f[funct - 1], st_p, end_p, esp));

		else if (!strcmp(argv[2], "root"))
		    printf("Root of %s is %lf\n", f_name[funct - 1],root(test_f[funct - 1],
			    zero_funct, test_f_der[funct - 1], zero_funct, st_p, end_p, esp));

		else
		    printf("%s", err_message);

	    } else
	        printf("%s", err_message);

	    return 0;
	}

	for (size_t i = 1; i < args; i++) {
	    if (!strcmp(argv[i], keys[1])) {
	    	flag_iter = 1;
		break;
	    }
	}

	for (size_t i = 1; i < args; i++) {
	    if (!strcmp(argv[i], keys[2])) {
	    	flag_absc = 1;
		break;
	    }
	}

	if (!(flag_iter || flag_absc)) {
	    printf("%s", err_message);
	    return 0;
	}

    }

    double x1 = root(f1, f2, f1_der, f2_der, 0, 5, 0.00001);
    int iter_12 = iter;

    double x2 = root(f1, f3, f1_der, f3_der, 0.1, 5, 0.00001);
    int iter_13 = iter;

    double x3 = root(f2, f3, f2_der, f3_der, 0.1, 5, 0.00001);
    int iter_23 = iter;

    if (flag_absc || flag_iter) {

    	printf("%s    ", f_name[3]);
	if (flag_absc) printf("x = %lf    ", x1);
	if (flag_iter)
	    printf("%d iterations", iter_12);

	printf("\n%s     ", f_name[4]);
	if (flag_absc) printf("x = %lf    ", x2);
	if (flag_iter)
	    printf("%d iterations", iter_13);
	
	printf("\n%s           ", f_name[5]);
	if (flag_absc) printf("x = %lf    ", x3);
	if (flag_iter)
	    printf("%d iterations", iter_23);

	printf("\n\n");
    }

    double square = integral(f1, x2, x1, 0.00001);
    square -= integral(f2, x3, x1, 0.00001);
    square -= integral(f3, x2, x3, 0.00001);

    printf("Square is %lf\n", square);

    return 0;
}
