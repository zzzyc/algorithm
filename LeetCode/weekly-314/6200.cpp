class Solution {
    public:
        int hardestWorker(int n, vector<vector<int>>& logs) {
            int id = n, time = 0;

            int start = 0;
            for (int i = 0; i < logs.size(); ++i) {
                if (logs[i][1] - start > time || (logs[i][1] - start == time && logs[i][0] < id)) {
                    time = logs[i][1] - start;
                    id = logs[i][0];
                }
                start = logs[i][1];
            }

            return id;
        }
};
