#include<stdio.h>
#include<string.h>
#include<limits.h>
typedef struct pt
{
	int x;
	int y;
}pt;
int adj[4][2]={ { 0, 1},
				{ 1, 0},
				{ 0,-1},
				{-1, 0}};

int arr[10][10] = { {1,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{2,2,0,2,2,0,0,0,0,0},
					{0,2,0,0,2,2,2,0,0,0},
					{0,2,0,2,0,0,2,0,0,0},
					{0,0,2,0,0,0,2,0,0,0},
					{0,0,0,0,0,0,2,2,2,0},
					{0,0,0,0,0,0,0,0,2,3}};
					// This matrix is our map.
					// 1 = start
					// 2 = wall
					// 3 = end
					// 8 = processed/processing. Means it tried going there but failed
					// 9 = final path. Means it succeeded with this path


/*
** Not Always best path. See the example below.
** Run it and see for yourself how horrific the result is
*/

/*
int arr[10][10] = { {1,0,0,0,0,0,0,0,0,0},
					{0,0,2,2,2,2,2,2,2,0},
					{0,0,0,0,0,0,0,0,2,0},
					{0,0,0,0,0,0,0,0,2,0},
					{0,0,0,0,0,0,0,0,2,0},
					{0,0,0,0,0,0,0,0,2,0},
					{0,0,0,0,0,0,0,0,2,0},
					{0,0,0,0,0,0,0,0,2,0},
					{2,2,2,2,2,2,2,2,2,0},
					{0,0,0,0,0,0,0,0,0,3}};
*/
int abs(int x);
int max(int i, int j);
int search(pt *, int val);
/* Search Value In Array.
** Returns 1 for success and 0 for not found
** i and j get appropriate values on call
*/
int inside(pt p);
int manhattanDistance(pt p, pt q);
int euclideanDistance(pt p, pt q);
pt newPoint(pt p, int dx, int dy);
int pathFound(pt p, pt q);
/* BackTracking Function. Finds Shortest
** Path using one of the distance Functions.
** Returns 1 on finding a valid path.
** For no path found, returns 0.
*/
int abs(int x){return x>=0?x:-x;}
int max(int i, int j){return  i<j?j:i;}
int search(pt *p, int val)
{
	for((p->x)=0;(p->x)<10;(p->x)++)
		for((p->y)=0;(p->y)<10;(p->y)++)
			if(arr[(p->x)][(p->y)]==val)
				return 1;
	return 0;
}
void printArr()
{
	for(int i=0;i<10;i++)
		{
			for(int j=0;j<10;j++)
				printf("%d ",arr[i][j]);
			printf("\n");
		}
}
int inside(pt p)
{
	return (p.x>=0&&p.y>=0&&p.x<10&&p.y<10&&arr[p.x][p.y]!=2&&arr[p.x][p.y]!=8);
}
int manhattanDistance(pt p, pt q)
{
	if(!(inside(p) && (inside(q))))
		return INT_MAX;
	return (abs((p.x) - (q.x)) + abs((p.y) - (q.y)));
}
int euclideanDistance(pt p, pt q)
{
	if(!(inside(p) && (inside(q))))
		return INT_MAX;
	return max(abs((p.x) - (q.x)), abs((p.y) - (q.y)));
}
pt newPoint(pt p, int dx, int dy)
{
	pt q=p;
	q.x += dx;
	q.y += dy;
	return q;
}
int pathFound(pt p, pt q)
{	
	if(arr[p.x][p.y]==2)// || arr[p.x][p.y]==8)
		return 0;
	int dist = manhattanDistance(p, q);
	if(dist == 1)
		return 1;
	arr[p.x][p.y]=8;
	pt t;	
	int min;
	int pos;
	int tmp[4];
	for(int i=0;i<4;i++)
	tmp[i] = manhattanDistance(newPoint(p, adj[i][0], adj[i][1]), q);
	for(int j=0;j<4;j++)
	{
		min=INT_MAX;
		pos=0;
		for(int i=0;i<4;i++)
		{
			if(tmp[i]!=-1 && tmp[i]<=min)
				{
					min=tmp[i];
					pos=i;
				}
		}
		tmp[pos]=-1;
		t = newPoint(p, adj[pos][0], adj[pos][1]);
		if( !inside(t) || arr[t.x][t.y] == 8)
			break;
		if(pathFound(t, q))
		{
			arr[t.x][t.y]=9;
			return 1;
		}
	}


	return 0;
}
int main()
{
	pt start;
	pt end;
	if((!search(&start, 1))||(!search(&end, 3)))
		return 0;
	if(pathFound(start, end))
	{
		arr[start.x][start.y]=1;
		printArr();
	}
	else printf("Can not find a continous path.\n");
	return 0;
}
