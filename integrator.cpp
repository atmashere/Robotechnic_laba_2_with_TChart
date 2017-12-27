
#include <stdio.h>
#include <math.h>
#include "integrator.h"
#include "model.h"

// ����������� ��������� ����
template <class T>
struct STypeZero
{
    STypeZero()
    {
        T l_tTmp = 1;
        while ( ( l_tTmp /= 2 ) + 1 > 1 )
            value = l_tTmp;
    }
    T value;
};

STypeZero< long double > g_ldZero;



#define max(a, b) ( ( (a) > (b) ) ? (a) : (b) )
#define min(a, b) ( ( (a) < (b) ) ? (a) : (b) )


//===========================================================================
// class TDormandPrinceIntegrator

const long double TDormandPrinceIntegrator::c[7] = { 0, 1./5, 3./10, 4./5, 8./9, 1., 1. };
const long double TDormandPrinceIntegrator::a[7][6] = {
    { 0. },
    { 1./5 },
    { 3./40, 9./40 },
    { 44./45, -56./15, 32./9 },
    { 19372./6561, -25360./2187, 64448./6561, -212./729 },
    { 9017./3168, -355./33, 46732./5247, 49./176, -5103./18656 },
    { 35./384, 0., 500./1113, 125./192, -2187./6784, 11./84 }
};
const long double TDormandPrinceIntegrator::b1[7] = { 35./384, 0., 500./1113, 125./192, -2187./6784, 11./84, 0 };
const long double TDormandPrinceIntegrator::b2[7] = { 5179./57600, 0., 7571./16695, 393./640, -92097./339200, 187./2100, 1./40 };

//---------------------------------------------------------------------------

TDormandPrinceIntegrator::TDormandPrinceIntegrator()
    : TIntegrator() 
{
	// ����������� ��������� ����
    double v = 1.;
    while (1.+v > 1.) {
        u = v;
        v = v/2.;
    }
}

//---------------------------------------------------------------------------

long double TDormandPrinceIntegrator::Run(TModel* Model)
{

//printf ("\n1.1");
    
    long double // ��� ����� ��� �������������� (������������� �� �������� ���� ��������������)
				t = Model->getT0(),
				// ��� ����� ��� ������ (������������� ��������� �� �������� ���������)
				t_out = t,
				// ��� �������� �����
				t1 = Model->getT1(),
				// ��� ��� ��������������
				h,
				// ��� ��� ����� ��������� (���������������� ���������� ������ ����������)
				h_new = Model->getSamplingIncrement(),
				// ��� ������ �� ���� ��������������
			    e = 0;

    TVector // ��� ������ ��������� �� ������ ����
            X = Model->getInitialConditions(),
            // ��� ������ ��������� �� ����� ���� (������� 4-�� �������)
            X1( X.size() ),
            // ��� ������ ��������� �� ����� ���� ��� ��������� �������� ���� (������� 5-�� �������)
            X2( X.size() ),
            // ��� ������ ��� ������ ����������
            Xout ( X.size() ),
            // ��� ����� ��� ���������� ������������� �
            Y( X.size() );	
	
	// ���������� ��������� ����������� � ������ ��� ��������� ������������� ��������� ������
	Model->prepareResult();
	
    // �������������� ����������� ������������� K[j]
    for ( int j = 7; j > 0; --j, K[j].resize( X.size() ) );
		
    //printf ("\n1.2");
	// ������� ���������� ��������� �����
	int N = 0;
	
    //printf ("\n&&&&&&K\n");
	
    // ������� ����
	while ( t < t1 )
    {
        // ������������� ��� �� ��������
        h = h_new;
		  // ��������� ������������ �
        for ( int j = 0; j < 7; j++ )
        {
            for ( int k = X.high(); k >= 0; k-- )
            {
                Y[k] = X[k];
                for ( int s = 0; s < j; s++ )
                {
                    Y[k] += K[s][k] * a[j][s] * h;
                }
            }
           Model->getRight( Y, t + c[j] * h, K[j] );
        }
 // ��������� ����� �������� ����������� � ��������� ������ (4 � 5 �������)
        e = 0;
        for ( int k = X.high(); k >= 0; k-- )
        {
            X1[k] = X2[k] = X[k];
            for ( int j = 0; j < 7; j++ )
            {
                X1[k] += K[j][k] * b1[j] * h;
                X2[k] += K[j][k] * b2[j] * h;
            }
            e += powl( h * (X1[k] - X2[k]) / max( max( fabsl(X[k]), fabsl(X1[k]) ), max((long double)1e-5, 2*g_ldZero.value/Eps) ) , 2 );
        }
        e = sqrtl( e / X.size() );

        // ��������� ����
        h_new = h / max( 0.1, min( 5., powl(e / Eps, 0.2)/0.9 ) );

	   // ���� ��������� ������ ��������� ������������� ��������, �������� ������� ��� ������
        if ( e > Eps )
            continue;
		
        // ������������ ����������� ��� ������ ��������� ������� ������
		while ( (t_out < t + h) && (t_out <= t1) )
        {
            long double l_ldTheta = (t_out - t)/h,
                        b[6];

			 // ������������ ������������ ������� ������
            b[0] = l_ldTheta * ( 1 + l_ldTheta*(-1337./480. + l_ldTheta*(1039./360. + l_ldTheta*(-1163./1152.))));
            b[1] = 0;
            b[2] = 100. * powl(l_ldTheta, 2) * (1054./9275. + l_ldTheta*(-4682./27825. + l_ldTheta*(379./5565.)))/3.;
            b[3] = -5. * powl(l_ldTheta, 2) * (27./40. + l_ldTheta*(-9./5. + l_ldTheta*(83./96.)))/2.;
            b[4] = 18225. * powl(l_ldTheta, 2) * (-3./250. + l_ldTheta*(22./375. + l_ldTheta*(-37./600.)))/848.;
            b[5] = -22. * powl(l_ldTheta, 2) * (-3./10. + l_ldTheta*(29./30. + l_ldTheta*(-17./24.)))/7.;

			// �������� ��������� ��� ������
            for ( int k = X.high(); k >= 0; k-- )
            {
                long double l_ldSum  = 0;
                for ( int j = 5; j >= 0; j-- )
                    l_ldSum += b[j] * K[j][k];
                Xout[k] = X[k] + h * l_ldSum;
            }

            // �������� ���������� � ������
            Model->addResult( Xout, t_out );
            // ���������� ����� ������
            t_out += Model->getSamplingIncrement();
        }

        // ��������� X � ���������� ����� �� �������� ���������� ����
        X = X1;
        t += h;

        // ������� ���������� �������� ��� ���������� ���������� �����������
        N++;
    }
	
    //printf ("\n1.4");
   // printf ("\n%i", N);

	// ���������� �������� ���������� �����������
    return Eps / pow( N, 1.5 );
}


