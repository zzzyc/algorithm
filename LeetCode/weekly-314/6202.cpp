class Solution {
    public:
        string robotWithString(string s) {
            /*
               s = "abcddcaz"

               1. s = "bcddcaz", t = "a", paper = ""
               2. s = "bcddcaz", t = "", paper = "a"
               3. s = "cddcaz", t = "b", paper = "a"
               4. s = "ddcaz", t = "bc", paper = "a"
               5. s = "dcaz", t = "bcd", paper = "a"
               6. s = "caz", t = "bcdd", paper = "a"
               7. s = "az", t = "bcddc", paper = "a"
               8. s = "z", t = "bcddca", paper = "a"
               9. s = "z", t = "bcddc", paper = "aa"
               10. s = "z", t = "bcdd", paper = "aac"
               11. s = "z", t = "bcd", paper = "aacd"
               12. s = "z", t = "bc", paper = "aacdd"
               13. s = "z", t = "b", paper = "aacddc"
               14. s = "z", t = "", paper = "aacddcb"
               15. s = "", t = "z", paper = "aacddcb"
               16. s = "", t = "", paper = "aacddcbz"

*/

            /*
               s = "zza"
               1. s = "za", t = "z", paper = ""
               2. s = "a", t = "zz", paper = ""
               3. s = "", t = "zza", paper = ""
               4. s = "", t = "zz", paper = "a"
               5. s = "", t = "z", paper = "az"
               6. s = "", t = "", paper = "azz"
               */

            /*
               s = "bac"
               1. s = "ac", t = "b", paper = ""
               2. s = "c", t = "ba", paper = ""
               3. s = "c", t = "b", paper = "a"
               4. s = "c", t = "", paper = "ab"
               5. s = "", t = "c", paper = "ab"
               6. s = "", t = "", paper = "abc"
               */

            reverse(s.begin(), s.end());
            string t = "";
            string paper = "";

            vector<int> cnt(26, 0);
            for (auto c: s) cnt[c - 'a'] += 1;
            int cur = 0;

            while (!s.empty() || !t.empty()) {
                if (s.empty()) {
                    while (!t.empty()) paper += t.back(), t.pop_back();
                } else if (t.empty()) {
                    t += s.back();
                    cnt[s.back() - 'a'] -= 1;
                    s.pop_back();
                } else {
                    // 1. s中存在的最小字符 小于 t.back()
                    while (cur < 26 && cnt[cur] <= 0) cur += 1;
                    if (t.back() > (cur + 'a')) {
                        t += s.back();
                        cnt[s.back() - 'a'] -= 1;
                        s.pop_back();
                    } else {
                        paper += t.back();
                        t.pop_back();
                    }
                }
            }

            return paper;
        }
};
