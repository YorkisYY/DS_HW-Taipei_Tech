
#define MIN(x, y) (x < y ? x : y)

// 鏈表結構定義
typedef struct _linklist_ {
    int val;                // 資料值
    struct _linklist_ *next; // 指向下一個節點的指針
} linklist_t;

// 圖的節點結構定義
typedef struct _graph_node_ {
    int count;              // 節點的鄰居數量
    linklist_t *head;       // 指向鄰居節點列表的頭指針
    linklist_t *tail;       // 指向鄰居節點列表的尾指針
} graph_node_t;

// 生成新的鏈表節點
linklist_t *generate_node(int val) {
    linklist_t *list = malloc(sizeof(linklist_t));
    list->val = val;
    list->next = NULL;

    return list;
}

// 將節點加入圖的鄰居列表的尾部
void graph_node_push_back(graph_node_t *node, int val) {
    if(node->tail == NULL) {
        node->head = generate_node(val);
        node->tail = node->head;
        node->count++;
    }
    else {
        node->tail->next = generate_node(val);
        node->count++;
        node->tail = node->tail->next;
    }
}

// 取得節點的鄰居數量
int get_graph_neighbor_count(graph_node_t *node) {
    return node->count;
}

// 輸出節點的鄰居節點列表
void print_neighbor_nodes(graph_node_t *node) {
    linklist_t *temp = node->head;
    printf("{");
    while(temp != NULL) {
        printf("%d,", temp->val);
        temp = temp->next;
    }
    printf("}\n");
}

void dfs(int u, int p, graph_node_t **graph, int n, int *disc, int *low, bool *visited, int *time, int **bridges, int *i_bridge) {
    disc[u] = ++(*time);  // 標記節點 u 的發現時間，並遞增時間計數器
    low[u] = *time;       // 初始化節點 u 的 low 值為其發現時間
    visited[u] = true;    // 標記節點 u 為已訪問

    // 獲取節點 u 的鄰居節點列表的頭指針
    linklist_t *node = graph[u]->head;

    // 遍歷節點 u 的每個鄰居節點
    while(node != NULL) {
        int v = node->val;  // 獲取鄰居節點的值
        node = node->next;  // 移動到下一個鄰居節點

        // 如果鄰居節點是父節點，則跳過
        if(v == p) continue;

        // 如果鄰居節點尚未訪問，則進行深度優先搜索
        if(!visited[v]) dfs(v, u, graph, n, disc, low, visited, time, bridges, i_bridge);

        // 更新節點 u 的 low 值
        low[u] = MIN(low[u], low[v]);

        // 如果節點 v 的 low 值大於節點 u 的發現時間，則找到了一條關鍵連接
        if(low[v] > disc[u]) {
            // 將關鍵連接存儲在 bridges 數組中
            bridges[*i_bridge][0] = u;
            bridges[*i_bridge][1] = v;
            (*i_bridge)++;
        }
    }
}


/**
 * 查找關鍵連接
 * 返回一個大小為 *returnSize 的二維數組，*returnColumnSizes 中的大小作為列的大小。
 * 注意：返回的數組和 *columnSizes 數組必須進行內存分配，假設調用者會調用 free()。
 */
int **criticalConnections(int n, int **connections, int connectionsSize, int *connectionsColSize, int *returnSize, int **returnColumnSizes) {
    // 創建圖的節點數組
    graph_node_t **graph = (graph_node_t **)malloc(n*sizeof(graph_node_t *));
    for(int i=0;i<n;i++) {
        graph[i] = (graph_node_t *)malloc(sizeof(graph_node_t));
        memset(graph[i], 0, sizeof(graph_node_t));
    }

    // 初始化用於 DFS 的數組
    int *disc = (int *)malloc(n*sizeof(int));
    int *low = (int *)malloc(n*sizeof(int));
    bool *visited = (int *)malloc(n*sizeof(int));
    memset(disc, 0, n*sizeof(int));
    memset(low, 0, n*sizeof(int));
    memset(visited, 0, n*sizeof(int));

    // 初始化用於存儲關鍵連接的數組
    int **bridges = (int **)malloc(n*sizeof(int *));
    *returnSize = 0;
    for(int i=0;i<n;i++) {
        bridges[i] = (int *)malloc(2*sizeof(int));
    }

    // 構建圖
    for(int i=0;i<connectionsSize;i++) {
        assert(connectionsColSize[i]==2);
        int a = connections[i][0];
        int b = connections[i][1];
        graph_node_push_back(graph[a], b);
        graph_node_push_back(graph[b], a);
    }

    // 開始 DFS
    int time = 0;
    dfs(0, 0, graph, n, disc, low, visited, &time, bridges, returnSize);

    // 設置列大小
    int *col_sz = malloc((*returnSize)*sizeof(int));
    for(int i=0;i<*returnSize;i++) {
        col_sz[i] = 2;
    }
    *returnColumnSizes = col_sz;

    return bridges;
}