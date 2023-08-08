/*
using map of pair
$ time ./grid_map_pair
??????R??????U??????????????????????????LD????D?
201
./grid_map_pair  16.78s user 0.05s system 97% cpu 17.182 total

using opPath[9][9]
$ time ./grid
??????R??????U??????????????????????????LD????D?
201
./grid  0.03s user 0.00s system 4% cpu 0.730 total

$ time ./grid_map_pair
????????????????????????????????????????????????
88418
./grid_map_pair  300.33s user 0.65s system 98% cpu 5:06.70 total

===============================
$ time ./grid
????????????????????????????????????????????????
88418
./grid  0.26s user 0.01s system 24% cpu 1.103 total

$ time ./grid
????U???????????D???????????????????????????????
6665
./grid  0.03s user 0.00s system 4% cpu 0.737 total
*/
#include <iostream>
#include <map>
using namespace std;

const int DIR_LEN = 4;
int dr[DIR_LEN] = {-1, 0, 1, 0};
int dc[DIR_LEN] = {0, 1, 0, -1};
const int PATH_LEN = 48; // length of all possible paths
int p[PATH_LEN];
const int GRID_SIZE = 7;
// added border to all four sides so a 7x7 becomes a 9x9
map<pair<int, int>, bool> onPath;

int tryPath(int pathIdx, int curR, int curC)
{
    if (!(0 <= curR && curR < GRID_SIZE && 0 <= curC && curC < GRID_SIZE))
        return 0;
    // Optimization 3
    if ((onPath[{curR, curC - 1}] && onPath[{curR, curC + 1}]) &&
        (!onPath[{curR - 1, curC}] && !onPath[{curR + 1, curC}]))
        return 0;
    if ((onPath[{curR - 1, curC}] && onPath[{curR + 1, curC}]) &&
        (!onPath[{curR, curC - 1}] && !onPath[{curR, curC + 1}]))
        return 0;

    if (curR == 6 && curC == 0)
    { // reached endpoint before visiting all
        if (pathIdx == PATH_LEN)
            return 1;
        return 0;
    }

    if (pathIdx == PATH_LEN)
        return 0;

    int ret = 0;
    onPath[{curR, curC}] = true;

    // turn already determined:
    if (p[pathIdx] < 4)
    {
        int nxtR = curR + dr[p[pathIdx]];
        int nxtC = curC + dc[p[pathIdx]];
        if (!onPath[{nxtR, nxtC}])
            ret += tryPath(pathIdx + 1, nxtR, nxtC);
    }
    // see Java solution for optimization 4 implementation
    else
    { // iterate through all four possible turns
        for (int i = 0; i < DIR_LEN; i++)
        {
            int nxtR = curR + dr[i];
            int nxtC = curC + dc[i];
            if (onPath[{nxtR, nxtC}])
                continue;
            ret += tryPath(pathIdx + 1, nxtR, nxtC);
        }
    }
    // reset and return
    onPath[{curR, curC}] = false;
    return ret;
}

int main()
{
    string line;
    getline(cin, line);

    // convert path to ints
    for (int i = 0; i < PATH_LEN; i++)
    {
        char cur = line[i];

        if (cur == 'U')
            p[i] = 0;
        else if (cur == 'R')
            p[i] = 1;
        else if (cur == 'D')
            p[i] = 2;
        else if (cur == 'L')
            p[i] = 3;
        else
            p[i] = 4; // cur == '?'
    }

    // set borders of grid

    // initialize the inside of the grid to be completely empty

    int startIdx = 0;
    int startR = 0;
    int startC = 0; // always start path at (1, 1)
    int ans = tryPath(startIdx, startR, startC);
    cout << ans << endl;
}