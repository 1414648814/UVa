#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
int g[205][205];
char pattern[205][205];
int cond1(int x, int y, int r, int c, int cellcnt) {
    int dx[] = {0,0,1,-1};
    int dy[] = {1,-1,0,0};
    queue<int> X, Y;
    int i, tx, ty;
    char used[205][205] = {};
    X.push(x), Y.push(y);
    used[x][y] = 1;
    cellcnt--;
    while(!X.empty()) {
        x = X.front(), X.pop();
        y = Y.front(), Y.pop();
        for(i = 0; i < 4; i++) {
            tx = x+dx[i], ty = y+dy[i];
            if(tx < 0 || ty < 0 || tx >= r || ty >= c)
                continue;
            if(used[tx][ty] == 0 && pattern[tx][ty] == '#') {
                used[tx][ty] = 1;
                cellcnt--;
                X.push(tx), Y.push(ty);
            }
        }
    }
    return cellcnt == 0;
}
int cond2(int x, int y, int r, int c) {
    int dx[] = {0,0,1,-1};
    int dy[] = {1,-1,0,0};
    queue<int> X, Y;
    int Wb = g[x][y], i, tx, ty;
    char used[205][205] = {};
    if(pattern[x][y] == '.') {
        X.push(x), Y.push(y);
        used[x][y] = 1;
    } else
        return 1;
    Wb--;
    while(!X.empty()) {
        x = X.front(), X.pop();
        y = Y.front(), Y.pop();
        for(i = 0; i < 4; i++) {
            tx = x+dx[i], ty = y+dy[i];
            if(tx < 0 || ty < 0 || tx >= r || ty >= c)
                continue;
            if(used[tx][ty] == 0 && pattern[tx][ty] == '.') {
                if(g[tx][ty])   return 0; // other Wb
                used[tx][ty] = 1;
                Wb--;
                if(Wb < 0)      return 0;
                X.push(tx), Y.push(ty);
            }
        }
    }
    return Wb == 0;
}
int cond3(int x, int y, int r, int c) {
    int dx[] = {0,0,1,1,1,-1,-1,-1};
    int dy[] = {1,-1,0,1,-1,0,1,-1};
    queue<int> X, Y;
    int i, tx, ty;
    char used[205][205] = {};
    if(pattern[x][y] != '.')
        return 1;
    X.push(x), Y.push(y);
    used[x][y] = 1;
    while(!X.empty()) {
        x = X.front(), X.pop();
        y = Y.front(), Y.pop();
        if(x == 0 || x == r-1 || y == 0 || y == c-1)
            return 1;
        for(i = 0; i < 8; i++) {
            tx = x+dx[i], ty = y+dy[i];
            if(tx < 0 || ty < 0 || tx >= r || ty >= c)
                continue;
            if(used[tx][ty] == 0 && pattern[tx][ty] == '.') {
                used[tx][ty] = 1;
                X.push(tx), Y.push(ty);
            }
        }
    }
    return 0;
}
int cond4(int r, int c) {
    int i, j;
    for(i = 0; i < r-1; i++) {
        for(j = 0; j < c-1; j++) {
            bool flag = (pattern[i][j] == '.' || pattern[i][j+1] == '.' ||
                         pattern[i+1][j] == '.' || pattern[i+1][j+1] == '.');
            if(flag == false)
                return 0;
        }
    }
    return 1;
}
int main() {
    int testcase;
    int r, c, n;
    int x, y, v, i, j, k;
    scanf("%d", &testcase);
    while(testcase--) {
        if(scanf("%d %d %d", &r, &c, &n) != 3)
            return 0;
        memset(g, 0, sizeof(g));
        int tot = 0;
        int ret = 1;
        for(i = 0; i < n; i++) {
            scanf("%d %d %d", &x, &y, &v);
            g[x][y] = v;
            tot += v;
        }
        for(i = 0; i < r; i++)
            scanf("%s", &pattern[i]);
        int cellcnt = 0;
        int unshaded = 0;
        for(i = 0; i < r; i++)
            for(j = 0; j < c; j++)
                if(pattern[i][j] == '#')
                    cellcnt++, x = i, y = j;
                else
                    unshaded++;
        if(tot != unshaded) {
            puts("not solved");
            continue;
        }
        if(!cond1(x, y, r, c, cellcnt)) {
            puts("not solved");
            continue;
        }
        for(i = 0; i < r && ret; i++) {
            for(j = 0; j < c && ret; j++) {
                if(g[i][j]) {
                    ret &= cond2(i, j, r, c);
                }
            }
        }
        if(!ret) {
            puts("not solved");
            continue;
        }
        for(i = 0; i < r && ret; i++) {
            for(j = 0; j < c && ret; j++) {
                if(g[i][j]) {
                    ret &= cond3(i, j, r, c);
                }
            }
        }
        if(!ret) {
            puts("not solved");
            continue;
        }
        ret &= cond4(r, c);
        if(!ret) {
            puts("not solved");
            continue;
        }
        puts("solved");
    }
    return 0;
}
/*
5

5 5 5
0 2 1
0 4 2
2 2 1
3 4 2
4 0 2
.#.#.
.###.
.#.##
###..
..###
*/
