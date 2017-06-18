struct aag_Node
{
    int a, b, c, d;
    bool end;
    
    void set(bool e, int aa, int bb, int cc, int dd ) {
        a = aa;
        b = bb;
        c = cc;
        d = dd;
        end = e;
    }
};

aag_Node nodes[22];

void aag_create()
{
    for ( int i = 0; i < 22; i ++ )
        nodes[i] = aag_Node();
    
    int k = 0;
    
    nodes[k].set(false, 0, 0, 0, 0);
    k++;
    nodes[k].set(false, 2, 3, 4, 0);
    k++;
    nodes[k].set(false, 0, 5, 0, 0);
    k++;
    nodes[k].set(false, 6, 0, 0, 7);
    k++;
    nodes[k].set(false, 0,8,0,9   );
    k++;
    nodes[k].set(false, 11,0,0,10 );
    k++;
    nodes[k].set(false, 0,0,12,11 );
    k++;
    nodes[k].set(true, 20,13,0,0  );
    k++;
    nodes[k].set(true, 0,0,14,0   );
    k++;
    nodes[k].set(false, 0,15,0,0  );
    k++;
    nodes[k].set(false, 0,0,14,0  );
    k++;
    nodes[k].set(false, 0,16,0,0  );
    k++;
    nodes[k].set(false, 0,13,17,0 );
    k++;
    nodes[k].set(false, 0,0,0,21  );
    k++;
    nodes[k].set(false, 0,8,0,0   );
    k++;
    nodes[k].set(false, 0,0,0,18  );
    k++;
    nodes[k].set(false, 0,0,0,19  );
    k++;
    nodes[k].set(false, 0,19,0,0  );
    k++;
    nodes[k].set(false, 20,0,0,0   );
    k++;
    nodes[k].set(true, 0,0,0,0    );
    k++;
    nodes[k].set(true, 20,0,0,0  );
    k++;
    nodes[k].set(true, 0,13,0,0   );
}

int aag_goToState( int curState, char c )
{
    switch (c)
    {
        case 'a':
            return nodes[curState].a;
        case 'b':
            return nodes[curState].b;
        case 'c':
            return nodes[curState].c;
        case 'd':
            return nodes[curState].d;
        default:
            return 0;
    }
}

/**
 * students' interface
 * @param inputString null terminated string with automaton input
 * @return true if string has been accepted
 */
bool checkString(const char * inputString)
{
    aag_create();
    int state = 1;
    const char * c = inputString;
    
    while ( *c )
        state = aag_goToState( state, *(c++) );
    
    return nodes[state].end;
}

//#ifndef __PROGTEST__
//
//#include <iostream>
//
//int main() {
//
//    std::cout << checkString( "badbd" );
//    return 0;
//}
//
//#endif