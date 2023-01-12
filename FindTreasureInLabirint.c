#include<stdio.h>
#include<stdlib.h>

struct Graph
{
	struct Graph **kids;
	int *damageInRoom;
	int *waysExisting;
	int value;
	int countWaysFrom;
};

int findTreasure(struct Graph g, int protect, int maxGold)
{
	int returnMax = -1;
	if (maxGold < g.value) maxGold = g.value;
	for (int i = 0; i < g.countWaysFrom; i++)
	{
		if (protect - g.damageInRoom[g.waysExisting[i]] >= 0)
		{
			int c;
			c = findTreasure(*(g.kids[g.waysExisting[i]]), protect - g.damageInRoom[g.waysExisting[i]], maxGold);
			if (c > returnMax) returnMax = c;
		}
	}
	if (returnMax > maxGold) return returnMax;
	else return maxGold;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n = 0, from = 0, to = 0, val = 0, p = 0, m = 0, dam = 0;
	struct Graph *g;
	scanf("%d%d%d", &p, &n, &m);
	g = (struct Graph*)malloc(n * sizeof(struct Graph));
	for (int i = 0; i < n; i++) {
		g[i].countWaysFrom = 0;
		g[i].value = 0;
		g[i].kids = (struct Graph**)malloc((n)*sizeof(struct Graph*));
		g[i].waysExisting = (int*)malloc((n)*sizeof(int));
		g[i].damageInRoom = (int*)malloc((n)*sizeof(int));
		for (int j = 0; j < n-1; j++)
		{
			g[i].damageInRoom[j] = -1;
			g[i].waysExisting[j] = -1;
		}
	}
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d%d", &from, &to, &dam);
		g[from].damageInRoom[to] = dam;
		g[from].waysExisting[g[from].countWaysFrom] = to;
		g[from].kids[g[from].waysExisting[g[from].countWaysFrom]] = &g[to];
		g[from].countWaysFrom++;
	}
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &g[i].value);
	}
	printf("%d", findTreasure(g[0], p, 0));//çâåíî ãðàôà, àìóëåò, òåêóùåå çîëîòî
	for(int i = 0; i < n; i++)
    {
        free(g[i].kids);
        free(g[i].waysExisting);
        free(g[i].damageInRoom);
    }
    free(g);
	return 0;
}
