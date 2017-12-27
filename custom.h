#pragma once//---------------------------------------------------------------------------



#include "model.h"

//---------------------------------------------------------------------------
// ������ ���������� (��������� ������� 1)

class TArenstorfModel  : public TModel
{
    protected:
        static const long double m;
		long double D1, D2;
    public:
        TArenstorfModel(  );
		void getRight( const TVector& X, long double t, TVector& Y );
};


//---------------------------------------------------------------------------
// ������ ���������� (��������� ������� 2)

class TArenstorfModel2 : public TArenstorfModel
{
    public:
        TArenstorfModel2(  );
};
//---------------------------------------------------------------------------
