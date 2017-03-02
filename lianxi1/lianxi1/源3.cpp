#include<stdio.h>
#include<vector>
using std::vector;
#include<queue>
using std::priority_queue;

struct node {
	int index;
	int value;
	node(int index0 = 0, int value0 = 0) :index(index0), value(value0) {}
	bool operator<(const struct node &x)const {
		return value>x.value;
	}
};
int dijkstra(const int &start, const int &end, const vector<vector<int> > &edges, const int &N) {
	vector<int> discs(N, -1);
	vector<bool> marks(N, false);
	int newp(start);
	marks[newp] = true;
	discs[newp] = 0;
	priority_queue<node> priQue;
	for (int loop = 1; loop <= N - 1; loop++) {
		for (int j = 0; j<(int)edges[newp].size(); j++) {
			int next = edges[newp][j];
			if (marks[next] == true)continue;
			int cost(1);
			if (discs[next] == -1 || cost + discs[newp]<discs[next]) {
				discs[next] = cost + discs[newp];
				priQue.push(node(next, discs[next]));
			}
		}
		/*
		int minm(-1);
		for(int i = 0;i<N;i++){
		if(marks[i]==true)continue;
		if(discs[i]==-1)continue;
		if(minm==-1||discs[i]<minm){
		minm=discs[i];
		newp=i;
		}
		}
		*/
		node cur = priQue.top();
		priQue.pop();
		newp = cur.index;
		marks[newp] = true;
		if (newp == end)break;
	}
	for (int i = 0; i<N; i++) {
		printf("%d ", discs[i]);
	}
	putchar('\n');
	return discs[end];
}

int main() {
	int N(-1);
	scanf("%d", &N);
	vector<vector<int> > edges(N);
	for (int i = 0; i<N; i++) {
		int K(-1);
		scanf("%d:", &K);
		for (int j = 0; j<K; j++) {
			int temp(-1);
			scanf("%d", &temp);
			edges[i].push_back(temp);
		}
	}
	int start(-1), end(-1);
	scanf("%d%d", &start, &end);
	int res = dijkstra(start, end, edges, N);
	res == -1 ? puts("No") : printf("YES %d\n", res);
	return 0;
}