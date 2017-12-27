
#pragma once
// ����������� ������������� ����� ���������� ��������� � ��������� ��������
#include "array.h"
//---------------------------------------------------------------------------

// ����������� ����������
class TModel;

class TIntegrator
{
    protected:
        // ������������ ����������� �� ����
        long double Eps;

    public:
		// ������� �����������
        TIntegrator() : Eps( 1e-16 ) {}
        inline void setPrecision( long double Eps ) { this->Eps = Eps; }
        inline long double getPrecision() const { return Eps; }
		// ����������� �����, ����������� ��������� ���������� �������������� � ������������ ���������� ����������� ����������
        virtual long double Run(TModel* Model) = 0;
};

//---------------------------------------------------------------------------

class TDormandPrinceIntegrator : public TIntegrator
{
    private:
        // ������������ a,b,c
        static const long double c[7], a[7][6], b1[7], b2[7];
        // ������������ K[i]
        TVector K[7];
		// �������� ����
		long double u;
    public:
        TDormandPrinceIntegrator();
        long double Run(TModel* Model);
};

//---------------------------------------------------------------------------


