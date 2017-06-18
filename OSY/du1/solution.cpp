//
//  solution.cpp
//  du1
//
//  Created by Andrey Babushkin on 14/03/2017.
//  Copyright © 2017 Mannannlegur. All rights reserved.
//

#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <thread>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <atomic>
using namespace std;

#define __DEBUG__

//=================================================================================================


class CLink
{
public:
    //---------------------------------------------------------------------------------------------
    CLink                         ( const string    & from,
                                   const string    & to,
                                   double            delay )
    : m_From ( from ),
    m_To ( to ),
    m_Delay ( delay )
    {
    }
    //---------------------------------------------------------------------------------------------
    string                   m_From;
    string                   m_To;
    double                   m_Delay;
};


//=================================================================================================


class CCenter
{
public:
    //---------------------------------------------------------------------------------------------
    CCenter                       ( void )
    {
    }
    //---------------------------------------------------------------------------------------------
    virtual                  ~CCenter                      ( void )
    {
    }
    //---------------------------------------------------------------------------------------------
    void                     AddLink                       ( const CLink     & l )
    {
        m_Links . push_back ( l );
    }
    //---------------------------------------------------------------------------------------------
    friend ostream         & operator <<                   ( ostream         & os,
                                                            const CCenter   & x )
    {
        os << "Center: " << x . m_Center << ", Max delay: " << x . m_MaxDelay << '\n';
        for ( const auto & p : x . m_Delays )
            cout << '\t' << " -> " << p . first << ": " << p . second << '\n';
        return os;
    }
    //---------------------------------------------------------------------------------------------
    vector<CLink>            m_Links;
    string                   m_Center;
    double                   m_MaxDelay;
    map<string,double>       m_Delays;
};
typedef shared_ptr<CCenter> ACenter;


//=================================================================================================


class CRedundancy
{
public:
    //---------------------------------------------------------------------------------------------
    CRedundancy                   ( const string    & center )
    : m_Center ( center )
    {
    }
    //---------------------------------------------------------------------------------------------
    virtual                  ~CRedundancy                  ( void )
    {
    }
    //---------------------------------------------------------------------------------------------
    void                     AddLink                       ( const CLink     & l )
    {
        m_Links . push_back ( l );
    }
    //---------------------------------------------------------------------------------------------
    friend ostream         & operator <<                   ( ostream         & os,
                                                            const CRedundancy & x )
    {
        for ( const auto & p : x . m_Redundancy )
            cout << x . m_Center << " - " << p . first << ": " << p . second << '\n';
        return os;
    }
    //---------------------------------------------------------------------------------------------
    
    vector<CLink>            m_Links;
    string                   m_Center;
    map<string,int>          m_Redundancy;
};
typedef shared_ptr<CRedundancy> ARedundancy;


//=================================================================================================


class CCustomer
{
public:
    //---------------------------------------------------------------------------------------------
    virtual                  ~CCustomer                    ( void )
    {
    }
    //---------------------------------------------------------------------------------------------
    virtual ACenter          GenCenter                     ( void ) = 0;
    //---------------------------------------------------------------------------------------------
    virtual ARedundancy      GenRedundancy                 ( void ) = 0;
    //---------------------------------------------------------------------------------------------
    virtual void             Solved                        ( ARedundancy       x ) = 0;
    //---------------------------------------------------------------------------------------------
    virtual void             Solved                        ( ACenter           x ) = 0;
    //---------------------------------------------------------------------------------------------
};

typedef shared_ptr<CCustomer> ACustomer;
//=================================================================================================
#endif /* __PROGTEST__ */


//=================================================================================================

#define QUEUE_MAX 100

class CSolver
{
public:
    //---------------------------------------------------------------------------------------------
    static void              Solve                         ( ACenter           x );
    //---------------------------------------------------------------------------------------------
    static void              Solve                         ( ARedundancy       x );
    //---------------------------------------------------------------------------------------------
    CSolver                       ( void ) : numberOfCustomers(0), 
                                             stopped(false), 
                                             lastCustomerDied(false) {};
    //---------------------------------------------------------------------------------------------
    ~CSolver                      ( void ) { if (!stopped) Stop(); };
    //---------------------------------------------------------------------------------------------
    void                     Start                         ( int               thrCnt );
    //---------------------------------------------------------------------------------------------
    void                     Stop                          ( void );
    //---------------------------------------------------------------------------------------------
    void                     AddCustomer                   ( ACustomer         c );
    //---------------------------------------------------------------------------------------------
private:
    class Problem
    {
    public:
        Problem(ARedundancy & red, ACustomer & cust) : _customer(cust),
                                                       _center(nullptr),
                                                       _redundancy(red) {}
        
        Problem(ACenter & cen, ACustomer & cust)     : _customer(cust),
                                                       _center(cen),
                                                       _redundancy(nullptr) {}
        
        ACenter             getCenter           () { return _center; }
        ARedundancy         getRedundancy       () { return _redundancy; }
        ACustomer           getCustomer         () { return _customer; }
        
    private:
        ACustomer           _customer;
        ACenter             _center;
        ARedundancy         _redundancy;
    };

// 47BEGIN
    class Subproblem
    {
    public:
        Subproblem(ARedundancy redundancy,
                   shared_ptr<mutex> problemMutex,
                   shared_ptr<vector<vector<long>>> graph,
                   long fromIndex,
                   long toIndex,
                   string toName,
                   atomic<size_t> * cnt) : parent(redundancy),
                                           parentMutex(problemMutex),
                                           graph(graph),
                                           fromIndex(fromIndex),
                                           toIndex(toIndex),
                                           toName(toName),
                                           counter(cnt) {}
        ~Subproblem() {};

        ARedundancy                             parent;
        shared_ptr<mutex>                       parentMutex;
        shared_ptr<vector<vector<long>>>        graph;
        long                                    fromIndex;
        long                                    toIndex;
        string                                  toName;
        atomic<size_t> *                        counter;
    };

    static queue<Subproblem>                subproblemsQueue;
    static mutex                            subproblemsMutex;
// 47END

    vector<thread>                          workingThreads;
    queue<Problem>                          problemQueue;
    mutex                                   problemMutex;
    condition_variable                      consumerCV;
    condition_variable                      producerCV;

    atomic<size_t>                          numberOfCustomers;
    atomic<bool>                            stopped;
    atomic<bool>                            lastCustomerDied;

// 47BEGIN
    static void solveSubRedProblem                  ();
// 47END

    static bool bfsSearch                           (const vector<vector<long>> & graph,
                                                     long from,
                                                     long to,
                                                     vector<long> & parent);
    static int  findDisjointPaths                   (const vector<vector<long>> & graph,
                                                     long from,
                                                     long to);
    void        clientRedundancyThreadFunction      (ACustomer customer);
    void        clientCenterThreadFunction          (ACustomer customer);
    void        workerFunction                      ();
};

void CSolver::Start(int thrCnt) {
    if (thrCnt <= 0)
        return;

    for (int i = 0; i < thrCnt; i++) {
        workingThreads.push_back(thread(&CSolver::workerFunction, this));
    }
}

void CSolver::Stop() {
    unique_lock<mutex> locker(problemMutex);
    stopped = true;
    consumerCV.notify_one();
    producerCV.notify_one();
    locker.unlock();

    for (auto & t : workingThreads)
        if (t.joinable())
            t.join();
}

void CSolver::AddCustomer(ACustomer cust) {
    unique_lock<mutex> locker(problemMutex);

    numberOfCustomers += 2;
    consumerCV.notify_one();
    producerCV.notify_one();
    locker.unlock();

    thread(&CSolver::clientCenterThreadFunction, this, cust).detach();
    thread(&CSolver::clientRedundancyThreadFunction, this, cust).detach();
}

void CSolver::clientCenterThreadFunction(ACustomer customer) {
    if (customer.get() == nullptr)
        return;
    
    while (true) {
        ACenter cenProblem = customer->GenCenter();
        unique_lock<mutex> lock(problemMutex);
        producerCV.wait(lock, [=] {return problemQueue.size() <= QUEUE_MAX; });

        if (cenProblem.get() == nullptr) {
            numberOfCustomers --;

            if (numberOfCustomers == 0 && stopped)
                lastCustomerDied = true;

            consumerCV.notify_one();
            lock.unlock();
            return;
        }

        Problem prob(cenProblem, customer);
        problemQueue.push(prob);
        consumerCV.notify_one();

    }
}

void CSolver::clientRedundancyThreadFunction(ACustomer customer) {
    if (customer.get() == nullptr)
        return;
    
    while (true) {
        ARedundancy redProblem = customer->GenRedundancy();
        unique_lock<mutex> lock(problemMutex);
        producerCV.wait(lock, [=] {return problemQueue.size() <= QUEUE_MAX; });

        if (redProblem.get() == nullptr) {
            numberOfCustomers --;

            if (numberOfCustomers == 0 && stopped)
                lastCustomerDied = true;

            consumerCV.notify_one();
            lock.unlock();
            return;
        }

        Problem prob(redProblem, customer);
        problemQueue.push(prob);
        consumerCV.notify_one();
    }
}

void CSolver::workerFunction() {
    while (true) {

// 47BEGIN
        subproblemsMutex.lock();
        size_t maxP = subproblemsQueue.size() / 20;
        subproblemsMutex.unlock();

        for (size_t i = 0; i < maxP; i++)
            solveSubRedProblem();
// 47END
        unique_lock<mutex> lock(problemMutex);
        consumerCV.wait(lock, [=] {return lastCustomerDied || problemQueue.size() > 0;});

        if (lastCustomerDied) {
            if (problemQueue.size() == 0) {
                consumerCV.notify_all();
                lock.unlock();
                return;
            }
            consumerCV.notify_one();
        }

        Problem task(problemQueue.front());
        problemQueue.pop();

        producerCV.notify_one();
        lock.unlock();

        ACenter cent = task.getCenter();
        ARedundancy red = task.getRedundancy();
        ACustomer cust = task.getCustomer();

        if (cent.get() != nullptr) {
            Solve(cent);
            cust->Solved(cent);
        }

        if (red.get() != nullptr) {
            Solve(red);
            cust->Solved(red);
        }

    }
}

void CSolver::Solve(ACenter x) {

    map<string, long> keys;
    map<long, string> keysIntToStr;
    long lastUnused = 0;

    for (const auto &l : x->m_Links) {
        if (keys.find(l.m_From) == keys.end()) {
            keys.insert(make_pair(l.m_From, lastUnused));
            keysIntToStr.insert(make_pair(lastUnused++, l.m_From));
        }
        if (keys.find(l.m_To) == keys.end()) {
            keys.insert(make_pair(l.m_To, lastUnused));
            keysIntToStr.insert(make_pair(lastUnused++, l.m_To));
        }
    }

    vector<vector<double>> FWMatrix(keys.size(),
                                    vector<double>(keys.size(),
                                                   numeric_limits<double>::max()));
    vector<double> maxValues(keys.size(), numeric_limits<double>::min());

    for (size_t i = 0; i < FWMatrix.size(); i++) {
        FWMatrix[i][i] = 0.;
    }

    for (const auto &l : (*x).m_Links) {
        long indFrom = keys.find(l.m_From)->second;
        long indTo = keys.find(l.m_To)->second;

        if (l.m_Delay < FWMatrix[indFrom][indTo]) {
            FWMatrix[indFrom][indTo] = l.m_Delay;
            FWMatrix[indTo][indFrom] = l.m_Delay;
        }
    }

    //FW BEGIN
    for (size_t k = 0; k < keys.size(); k++)
        for (size_t i = 0; i < keys.size(); i++)
            for (size_t j = 0; j < keys.size(); j++)
                FWMatrix[i][j] = min(FWMatrix[i][j], FWMatrix[i][k] + FWMatrix[k][j]);
    //FW END

    for (size_t i = 0; i < keys.size(); i++)
        maxValues[i] = *max_element(FWMatrix[i].cbegin(), FWMatrix[i].cend());

    auto centerIterator = min_element(maxValues.cbegin(), maxValues.cend());
    size_t centerIndex = (size_t) (centerIterator - maxValues.cbegin());
    x->m_Center = keysIntToStr.find(centerIndex)->second;
    x->m_MaxDelay = *centerIterator;

    for (size_t i = 0; i < keys.size(); i++) {
        string name = keysIntToStr.find(i)->second;

        if (name != x->m_Center) {
            x->m_Delays.insert(make_pair(name, FWMatrix[centerIndex][i]));
        }
    }
}

void CSolver::Solve(ARedundancy x) {
    if (x->m_Links.size() == 0)
        return;

    map<string, long> keys;
    map<long, string> keysIntToStr;

    long lastUnused = 0;

    for (const auto &l : (*x).m_Links) {
        if (keys.find(l.m_From) == keys.end()) {
            keys.insert(make_pair(l.m_From, lastUnused));
            keysIntToStr.insert(make_pair(lastUnused++, l.m_From));
        }
        if (keys.find(l.m_To) == keys.end()) {
            keys.insert(make_pair(l.m_To, lastUnused));
            keysIntToStr.insert(make_pair(lastUnused++, l.m_To));
        }
    }

    auto graphSP = shared_ptr<vector<vector<long>>>(new vector<vector<long>>(keys.size(), vector<long>(keys.size(), 0)));
    vector<vector<long>> & graph = *graphSP;

    for (const auto &l : (*x).m_Links) {
        long indFrom = keys.find(l.m_From)->second;
        long indTo = keys.find(l.m_To)->second;

        graph[indFrom][indTo] += 1;
        graph[indTo][indFrom] += 1;
    }

    long keyFrom = keys.find(x->m_Center)->second;

// 47BEGIN

    auto mut = shared_ptr<mutex>(new mutex()); // one mutex for all subproblems of the problem
    atomic<size_t> cnt(0); // counter of solved subproblems
    size_t shouldBe = keys.size() - 1; // how many problems we must solve before return (1 stands for a center node)
    bool needsParal = shouldBe > 1000;
// 47END

    for (auto it = keys.begin(); it != keys.end(); it ++) {
        string to = it->first;
        long keyTo = keys.find(to)->second;

        if (keyTo == keyFrom)
            continue;

// 47BEGIN
        if (needsParal) {
            unique_lock<mutex> lock(subproblemsMutex);
            Subproblem sp(x, mut, graphSP, keyFrom, keyTo, to, &cnt);
            subproblemsQueue.push(sp);
        } else {
            x->m_Redundancy.insert(make_pair(to, findDisjointPaths(graph, keyFrom, keyTo)));
        }
// 47END
    }

// 47BEGIN
    // the method won't return until the cnt is not equal to the total number of problems
    // waits until ALL subproblems are solved by other threads
    while (needsParal && cnt < shouldBe) {
        solveSubRedProblem();
    }
// 47END
}

// 47BEGIN
queue<CSolver::Subproblem>       CSolver::subproblemsQueue;
mutex                            CSolver::subproblemsMutex;

void CSolver::solveSubRedProblem() {
    unique_lock<mutex> lock(CSolver::subproblemsMutex);

    if (CSolver::subproblemsQueue.empty())
        return;

    Subproblem sp = CSolver::subproblemsQueue.front();
    CSolver::subproblemsQueue.pop();
    lock.unlock();

    string toName = sp.toName;
    auto & graph = *sp.graph;
    long keyFrom = sp.fromIndex;
    long keyTo = sp.toIndex;
    int paths = findDisjointPaths(graph, keyFrom, keyTo);

    sp.parentMutex->lock();
    sp.parent->m_Redundancy.insert(make_pair(sp.toName, paths));
    *(sp.counter) += 1;
    sp.parentMutex->unlock();
}
// 47END

bool CSolver::bfsSearch(const vector<vector<long>> & graph, long from, long to, vector<long> & parent) {
    if (from >= (long)graph.size() || to >= (long)graph.size())
        return false;
    
    queue<long> q;
    vector<bool> visited(graph.size(), 0);
    q.push(from);
    visited[from] = true;
    parent[from] = -1;
    
    while (! q.empty()) {
        long u = q.front();
        q.pop();
        
        for (long v = 0; v < (long)graph.size(); v++)
        {
            if (visited[v] == false && graph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
                if (v == to)
                    return true;
            }
        }
    }
    
    return false;
}

int CSolver::findDisjointPaths(const vector<vector<long>> & graph, long from, long to) {
    long u, v;
    size_t V = graph.size();
    vector<vector<long>> rGraph(graph);
    
    vector<long> parent(V);
    
    int max_flow = 0;
    
    while (bfsSearch(rGraph, from, to, parent))
    {
        long path_flow = LONG_MAX;
        
        for (v = to; v != from; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        
        for (v = to; v != from; v = parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        
        max_flow += path_flow;
    }
    
    return max_flow;
}

//=================================================================================================

#ifndef __PROGTEST__
#include "data.inc"
#include "test.inc"
#endif /* __PROGTEST__ */
