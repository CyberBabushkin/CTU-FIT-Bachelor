
atomic<size_t>                   solved_red;
atomic<size_t>                   solved_cen;

//=================================================================================================
class CCustomerReal : public CCustomer
{
  public:
    //---------------------------------------------------------------------------------------------
                             CCustomerReal                 ( void )
                             : m_IdxCenter ( 0 ),
                               m_IdxRedundancy ( 0 )
    {
    }
    //---------------------------------------------------------------------------------------------
    virtual ACenter          GenCenter                     ( void ) override
    {
      this_thread::sleep_for(chrono::milliseconds(100));

      if ( m_IdxCenter < g_TestsCenter . size () )
        return g_TestsCenter[m_IdxCenter++] . first ();
      else
        return ACenter ();
    }
    //---------------------------------------------------------------------------------------------
    virtual ARedundancy      GenRedundancy                 ( void ) override
    {
      this_thread::sleep_for(chrono::milliseconds(100));

      if ( m_IdxRedundancy < g_TestsRedundancy . size () )
        return g_TestsRedundancy[m_IdxRedundancy++] . first ();
      else
        return ARedundancy ();
    }
    //---------------------------------------------------------------------------------------------
    virtual void             Solved                        ( ARedundancy       x ) override
    {

      for (auto & i : g_TestsRedundancy) {
        if (i.first()->m_Center == x->m_Center)
          i.second(x);
      }

      solved_red++;
    }
    //---------------------------------------------------------------------------------------------
    virtual void             Solved                        ( ACenter           x ) override
    {
      for (auto & i : g_TestsCenter) {
        if (i.first()->m_Center == x->m_Center)
          i.second(x);
      }
      solved_cen++;
    }
    //---------------------------------------------------------------------------------------------
  private:
    size_t                   m_IdxCenter;
    size_t                   m_IdxRedundancy;
};
//=================================================================================================



void               TestParallel                            ( void )
{
    CSolver   s;

    int numCust = 1200, numWork = 10;

    s . Start ( numWork );

    for (int i = 0; i < numCust; i++) {
        auto c = make_shared<CCustomerReal> ();
        s.AddCustomer(c);
    }

    s . Stop ();

    cout << "red solved: " << solved_red << endl;
    cout << "cen solved: " << solved_cen << endl;
}
//=================================================================================================
void               TestSequential                          ( void )
{
  for ( auto & t : g_TestsCenter )
  {
    ACenter x = t . first ();
    CSolver::Solve ( x );
    t . second ( x );
  }

  for ( auto & t : g_TestsRedundancy )
  {
    ARedundancy x = t . first ();
    CSolver::Solve ( x );
    t . second ( x );
  }
}
//=================================================================================================
int                main                                    ( void )
{
  solved_red = 0;
  solved_cen = 0;
  TestSequential ();
  TestParallel ();
  return 0;
}
