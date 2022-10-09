class Solution {
    public:
        vector<int> findArray(vector<int>& pref) {

            // a ^ a = 0
            // a ^ 0 = a
            // a ^ b = c
            // a ^ c = a ^ a ^ b = b

            // pref[i] = a[i] ^ a[i - 1] ^ ... ^ a[0]
            // pref[0] = a[0]
            // pref[1] = a[1] ^ a[0]
            // a[1] = pref[1] ^ (a[0] = pref[0])

            // pref[2] = pref[1] ^ a[2]
            // a[2] = pref[2] ^ pref[1]

            // pref[i] = pref[i - 1] ^ a[i]
            // a[i] = pref[i] ^ pref[i - 1]

            // i = 0, a[0] = pref[0]

            vector<int> a(pref.size());
            a[0] = pref[0];
            for (int i = 1; i < pref.size(); ++i) {
                a[i] = pref[i] ^ pref[i - 1];
            }

            return a;
        }
};
