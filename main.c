#include <stdio.h>
#include <math.h>
#include <string.h>

#define EPS1 0.00001
#define EPS2 0.0001

#define A12 1.0
#define B12 1.5

#define A23 0.5
#define B23 1.0

#define A13 -3.0
#define B13 -2.0

static unsigned num_iter = 0;

extern double f1(double x); // Функция 1
extern double f2(double x); // Функция 2
extern double f3(double x); // Функция 3

extern double df1(double x); // первая производная функции 1
extern double df2(double x); // первая производная функции 2
extern double df3(double x); // первая производная функции 3

extern double ddf1(double x); // вторая производная функции 1
extern double ddf2(double x); // вторая производная функции 2
extern double ddf3(double x); // вторая производная функции 3


double test_f1(double x) {
    return pow(x, 2)+3*x+2;
}
double test_df1(double x) {
    return 2*x+3;
}
double test_ddf1(double x) {
    return 2.0;
}

double test_f2(double x) {
    return (5-2*x)/7;
}
double test_df2(double x) {
    return -2.0/7;
}
double test_ddf2(double x) {
    return 0.0;
}

double test_f3(double x) {
    return 3/(x+4);
}
double test_df3(double x) {
    return -3/((x+4)*(x+4));
}
double test_ddf3(double x) {
    return 6/((x+4)*(x+4)*(x+4));
}

double root(double (*f1)(double), double (*f2)(double), double a, double b, double eps, double (*df1)(double), double (*df2)(double), double (*ddf1)(double), double (*ddf2)(double)) {// функция вычисляет по методу хорд и касательных
    do {
        if ((f1(a) - f2(a)) * (ddf1(a) - ddf2(a)) < 0)
            a -= (a - b) / ((f1(a) - f2(a)) - (f1(b) - f2(b))) * (f1(a) - f2(a));
        else if ((f1(a) - f2(a)) * (ddf1(a) - ddf2(a)) > 0)
            a -= (f1(a) - f2(a)) / (df1(a) - df2(a));
        if ((f1(b) - f2(b)) * (ddf1(b) - ddf2(b)) < 0)
            b -= (b - a) / ((f1(b) - f2(b)) - (f1(a) - f2(a))) * (f1(b) - f2(b));
        else if ((f1(b) - f2(b)) * (ddf1(b) - ddf2(b)) > 0)
            b -= (f1(b) - f2(b)) / (df1(b) - df2(b));
        num_iter++;
    } while (fabs(a - b) > 2 * eps);//Построение хорд и касательных продолжается до достижения необходимой точности решения е
    return (a + b) / 2.0;
}

double root2(double (*f1)(double), double (*f2)(double), double a, double b, double eps, double (*df1)(double), double (*df2)(double)) {// функция вычисляет по методу хорд и касательных
    do {
        double temp = a - (((f1(a) - f2(a)) * (b-a)) / (f1(b) - f2(b) - f1(a) + f2(a)));
        b = b - ((f1(b) - f2(b)) / (df1(b) - df2(b)));
        a = temp;
        num_iter++;
    } while (fabs(a - b) > 2 * eps);//Построение хорд и касательных продолжается до достижения необходимой точности решения е
    return a;
}

double integral(double (*f)(double), double a, double b, double eps2) { //функция нахождения определенного интеграла методом прямоугольников
    double step = 0.1, x; //начальное разбиение на 10 частей
    double I_n = f(a)*(b - a);
    double I_2n = 0.0;
    while (1) {
        I_2n = 0.0;
        for (x = a; x < b; x += step * (b - a))
            I_2n += f(x) * fabs(b - a) * step;
        if (fabs(I_2n - I_n) < eps2)
            return I_2n;
        I_n = I_2n;
        step *= 0.5; //увеличение разбиения в 2 раза
    }
}

void help() {
    printf("-help : write all keys\n");
    printf("-abscissas : to write abscissas\n");
    printf("-iter : to write amount of iterations to solve \n");
    printf("-test_root : for test root function\n");
    printf("-test_integral : for test integral function\n");
}

void test_root() {
    printf("Choose functions:\n1) x^2+3x+2\n2) (5-2*x)/7\n3) 3/(x+4)\n");
    int nf, ng;
    printf("f = ");
    scanf("%d", &nf);
    printf("g = ");
    scanf("%d", &ng);

    double (*f)(double);
    double (*df)(double);
    double (*ddf)(double);
    if (nf == 1) {
        f = test_f1;
        df = test_df1;
        ddf = test_ddf1;
    } else if (nf == 2) {
        f = test_f2;
        df = test_df2;
        ddf = test_ddf2;
    } else {
        f = test_f3;
        df = test_df3;
        ddf = test_ddf3;
    }

    double (*g)(double);
    double (*dg)(double);
    double (*ddg)(double);
    if (ng == 1) {
        g = test_f1;
        dg = test_df1;
        ddg = test_ddf1;
    } else if (ng == 2) {
        g = test_f2;
        dg = test_df2;
        ddg = test_ddf2;
    } else {
        g = test_f3;
        dg = test_df3;
        ddg = test_ddf3;
    }

    double a, b, eps1;
    printf("Enter [a,b] and precision eps\n");
    printf("a = ");
    scanf("%lf", &a);
    printf("b = ");
    scanf("%lf", &b);
    printf("eps = ");
    scanf("%lf", &eps1);

    //double r = root(f, g, a, b, eps1, df, dg, ddf, ddg);
    double r = root2(f, g, a, b, eps1, df, dg);
    if (r > b || r < a) {
    	printf("No root on [%.3lf, %.3lf]\n", a, b);
    }
    else {  	
    	printf("Root is %lf\n", r);
    }
}

void test_integral() {
    printf("Choose function:\n1) x^2+3x+2\n2) (5-2*x)/7\n3) 3/(x+4)\n");
    int n;
    printf("f = ");
    scanf("%d", &n);

    double a, b;
    double eps2;
    printf("Enter [a,b] and precision eps\n");
    printf("a = ");
    scanf("%lf", &a);
    printf("b = ");
    scanf("%lf", &b);
    printf("eps = ");
    scanf("%lf", &eps2);

    double I;
    if (n == 1) {
        I = integral(test_f1, a, b, eps2);
    } else if (n == 2) {
        I = integral(test_f2, a, b, eps2);
    } else {
        I = integral(test_f3, a, b, eps2);
    }

    printf("I = %lf\n", I);
}

int main(int argc, char** argv) {
//точки пересечения функций
    //double x_12 = root(f1, f2, A12, B12, EPS1, df1, df2, ddf1, ddf2);
    //double x_23 = root(f2, f3, A23, B23, EPS1, df2, df3, ddf2, ddf3);
    //double x_13 = root(f1, f3, A13, B13, EPS1, df1, df3, ddf1, ddf3);
    unsigned iter1, iter2, iter3;
    double x_12 = root2(f1, f2, A12, B12, EPS1, df1, df2);
    iter1 = num_iter;
    num_iter = 0;
    double x_23 = root2(f2, f3, A23, B23, EPS1, df2, df3);
    iter2 = num_iter;
    num_iter = 0;
    double x_13 = root2(f1, f3, A13, B13, EPS1, df1, df3);
    iter3 = num_iter;
    


    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-help") == 0) {
            help();
        }

        if (strcmp(argv[i], "-abscissas") == 0) {
            printf("f1 intersects f2 in %lf\n", x_12);
            printf("f2 intersects f3 in %lf\n", x_23);
            printf("f3 intersects f1 in %lf\n", x_13);
        }

        if (strcmp(argv[i], "-iter") == 0) {
            printf("Amount of iterations 1:  %u\n", iter1);
            printf("Amount of iterations 2:  %u\n", iter2);
            printf("Amount of iterations 3:  %u\n", iter3);
        }

        if (strcmp(argv[i], "-test_root") == 0) {
            test_root();
        }

        if (strcmp(argv[i], "-test_integral") == 0) {
            test_integral();
        }
    }
    if (argc == 1) {
    	//интегралы функций на найденных отрезках
    	double I1 = integral(f1, x_13, x_12, EPS2);
    	double I2 = integral(f2, x_23, x_12, EPS2);
    	double I3 = integral(f3, x_13, x_23, EPS2);

    	double S = I1 - I2 - I3;
    	printf("AREA :  %lf\n", S);
    }	
    return 0;
}