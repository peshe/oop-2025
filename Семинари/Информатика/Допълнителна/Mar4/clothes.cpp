#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

struct ClothSize {
    struct USSize
    {
        enum BASE {S,M,L} base;
        int nx;
    };
    union
    {
        USSize us_size;
        double fr_size;
    };
    enum ACTIVE {US, FR} active;
};

ClothSize next(ClothSize::USSize x)
{
    ClothSize rtn;
    rtn.active = ClothSize::US;
    switch(x.base)
    {
        case ClothSize::USSize::S: 
        if(x.nx == 0)
        {
            rtn.us_size.base = ClothSize::USSize::M;
            rtn.us_size.nx = 0;
        }  
        else
        {
            rtn.us_size.base = ClothSize::USSize::S;
            rtn.us_size.nx = x.nx - 1;
        }
        break;
        case ClothSize::USSize::M:
        { 
            rtn.us_size.base = ClothSize::USSize::L;
            rtn.us_size.nx = 0;       
        }
        break;
        case ClothSize::USSize::L: 
        {
            rtn.us_size.nx = x.nx + 1;
            rtn.us_size.base = ClothSize::USSize::L;
        }   
        break; 
    }
    return rtn;
}

ClothSize next(ClothSize x)
{
    ClothSize rtn;
    switch(x.active)
    {
        case ClothSize::US : 
            rtn = next(x.us_size);
        break;
        case ClothSize::FR : 
        {
            rtn.fr_size = x.fr_size + 0.5;
            rtn.active = ClothSize::FR;
        }
    }
    return rtn;
}

static void print_x(int n)
{
    while(n-->0) cout.put('X');
}

void print(ClothSize::USSize x)
{
    switch(x.base)
    {
        case ClothSize::USSize::S: print_x(x.nx); cout << "S" << endl; break;
        case ClothSize::USSize::M: cout << "M" << endl; break;
        case ClothSize::USSize::L: print_x(x.nx); cout << "L" << endl;break;
    }
}

void print(ClothSize x)
{
    switch(x.active)
    {
        case ClothSize::US: print(x.us_size); break;
        case ClothSize::FR: cout << x.fr_size << endl; break;
    }

}


ClothSize conv_us(ClothSize s)
{

    ClothSize rtn;
    rtn.active = ClothSize::US;
    if(s.fr_size < 37)
    {        
        rtn.us_size.nx = round((38-s.fr_size)/2);
        rtn.us_size.base = ClothSize::USSize::S;
    }
    else if(s.fr_size > 39)
    {
        rtn.us_size.nx = round((s.fr_size-40)/2);
        rtn.us_size.base = ClothSize::USSize::L;
    }
    else
    {
        rtn.us_size.nx = 0;
        rtn.us_size.base = ClothSize::USSize::M;
    }
    return rtn;

}

int main()
{
    ClothSize s;
    
    s.active = ClothSize::US;
    s.us_size.base = ClothSize::USSize::S;
    s.us_size.nx = 4;

    for(int k = 0; k < 10; ++k)
    {
        print(s);
        s = next(s);
    }

    cout << "==========" << endl;

    for(float f = 36; f < 46; f += 1)
    {
        ClothSize s;
        s.active = ClothSize::FR;
        s.fr_size = f;

        ClothSize u = conv_us(s);
        cout << f << " "; print(u);
    }

}