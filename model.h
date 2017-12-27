//---------------------------------------------------------------------------

#pragma once

// ����������� ������������� ����� ���������� ��������� � ��������� ��������
#include "array.h"

//---------------------------------------------------------------------------
// ������� ����� ������ ��� �����������

class TModel
{
    protected:
        // ��������� �������
        TVector X0;
        // ��������� �� ����������� �������� ������ �����������
        long double SamplingIncrement;
        // ������ � ��������� ������� ��������������
        long double t0, t1;
        // ��������� �����������
        TMatrix Result;
        // ������� ����� � ������� �����������
		int N;
		
    public:
        // ����� ����������� ������� - ������������� ���������� �� ���������
        TModel()
            : SamplingIncrement( 1e-1 )
            , t0( 0. )
            , t1( 90. )
            , N( 0.1 )
        {}
        // ����������� ������������� ������� ������ ������ �� (X - ������ ���������, t - ����������� ��������)
        //virtual TVector getRight( const TVector& X, long double t ) = 0;
		
		virtual void getRight( const TVector& X, long double t, TVector& Y ) = 0;
		
        // ��������� ��������� �������
        inline TVector getInitialConditions() const { return X0; }
        // ������� ������� - �� ����������� ������� ��������� �������
        inline int getOrder() const { return X0.size(); }

        // �������� ������ �����������
        inline long double getSamplingIncrement() const { return SamplingIncrement; }

        // ���������� ��������� ���������� ��������������
        inline long double getT0() const { return t0; }
        inline long double getT1() const { return t1; }
       
		// ��������� ������� �����������
		inline TMatrix getResult() const { return Result; }
        // ������ ����������� (� ���� ������ � ���������� ��������� ������������ ������ � ���� 
		// ������ ��� ������ � ����������� ������� �����������)
        virtual void addResult( const TVector& X, long double t );
		// ������� ������� ����������� (��� ����� � ������������)
		virtual void clearResult();
		// ���������� ������� ����������� ��� ����� ������������ ��������� ������
		virtual void prepareResult();
};

//---------------------------------------------------------------------------
