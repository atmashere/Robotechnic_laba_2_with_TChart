#include "mainwindow.h"
//#include "mainwindow.ui"

#include "ui_mainwindow.h"

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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

        TModel* Model1 = new TArenstorfModel();
        MainWindow::showResult(Model1);
        delete Model1;

        //printf("\n===========================================================================\n");

        //TModel* Model2 = new TArenstorfModel2();
        //MainWindow::showResult(Model2);
        //delete Model2;


}


void MainWindow::showResult(TModel* model){

    TIntegrator* Integrator = new TDormandPrinceIntegrator();
        Integrator->setPrecision(1e-16);
        //printf ("1");
        Integrator->Run( model );
        //printf ("2");
        TMatrix Result = model->getResult();

        TVector Res = model->getInitialConditions();

    QVector<double> x(Result.rowCount()), y(Result.rowCount());


        //printf ("\nVector Res: \n");
        //for (int z=0; z<4; z++)
        //{
            //printf("%f   ", Res[z]);
        //}
        //printf("\n---------------------------------------------------------------------------");


        //printf("\nCount string Matrix_x = %i", Result.rowCount());
        //printf("\nCount column Matrix_x = %i", Result.colCount());

        //printf("\n---------------------------------------------------------------------------");

        //printf("\nResult: \n");
        for (int i=0; i<Result.rowCount(); i++)
        {
            for (int j=0; j<Result.colCount(); j++)
            {
                if (j == 1) { x[i] = Result(i,j); }
                if (j == 2) { y[i] = Result(i,j); }
                //printf("%10.7f ; ", Result(i,j));
            }
            //printf("\n");
        }

        ui->widget->clearGraphs();//Если нужно, но очищаем все графики
        //Добавляем один график в widget
        ui->widget->addGraph();
        //Говорим, что отрисовать нужно график по нашим двум массивам x и y
        ui->widget->graph(0)->setData(x, y);
        ui->widget->graph(0)->setPen(QColor(50, 50, 50, 255));//задаем цвет точки
        ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);//убираем линии
        //формируем вид точек
        ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

        ui->widget->xAxis->setLabel("x");
        ui->widget->yAxis->setLabel("y");

        ui->widget->xAxis->setRange(-2, 2);
        ui->widget->yAxis->setRange(-2, 2);

        ui->widget->replot();

        delete Integrator;
}
