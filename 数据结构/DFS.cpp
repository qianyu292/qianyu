//Í¼µÄDFSÄ£°å
/*class solution
* {  vector<vector<int>>res;
*    vector<int>path;
*   public:
* vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph)
* {
*   traverse(graph,0);
*   return res;
* }
* void traverse(vector<vector<int>>& graph,int s)
* {
*    path.push_back(s);
*    int n=graph.size();
*    if(s==n-1)
*    {res.push(vector<int>path);
*     path.pop_back();
*     return;
*     }
*     for(int v:graph[s])
*     {traverse(graph,v);}
*     path.pop_back()
* }
};
*/