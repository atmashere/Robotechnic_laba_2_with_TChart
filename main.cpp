#include "mainwindow.h"
#include <QApplication>
#include "qcustomplot.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

/*
 * Standard library


#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "array.h"

#define max(a, b) ( ( (a) > (b) ) ? (a) : (b) )
#define min(a, b) ( ( (a) < (b) ) ? (a) : (b) )


#include "integrator.h"
#include "custom.h"


void showResult(TModel* model);

int main()
{


    TModel* Model1 = new TArenstorfModel();
    showResult(Model1);
    delete Model1;

    printf("\n===========================================================================\n");

    TModel* Model2 = new TArenstorfModel2();
    showResult(Model2);
    delete Model2;

    return 0;
}


void showResult(TModel* model){

    TIntegrator* Integrator = new TDormandPrinceIntegrator();
        Integrator->setPrecision(1e-16);
        //printf ("1");
        Integrator->Run( model );
        //printf ("2");
        TMatrix Result = model->getResult();

        TVector Res = model->getInitialConditions();


        printf ("\nVector Res: \n");
        for (int z=0; z<4; z++)
        {
            printf("%f   ", Res[z]);
        }
        printf("\n---------------------------------------------------------------------------");


        printf("\nCount string Matrix_x = %i", Result.rowCount());
        printf("\nCount column Matrix_x = %i", Result.colCount());

        printf("\n---------------------------------------------------------------------------");

        printf("\nResult: \n");
        for (int i=0; i<Result.rowCount(); i++)
        {
            for (int j=0; j<Result.colCount(); j++)
            {
                printf("%10.7f ; ", Result(i,j));
            }
            printf("\n");
        }


        delete Integrator;
}
*/
