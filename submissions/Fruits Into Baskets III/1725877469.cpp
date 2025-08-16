# Title: Fruits Into Baskets III
# Submission ID: 1725877469
# Status: Time Limit Exceeded
# Date: August 6, 2025 at 09:47:18 PM GMT+5:30

class Solution {
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int n = fruits.size();
        vector<bool> used(n, false); 
        int unplaced = 0;

        for (int i = 0; i < n; ++i) {
            bool placed = false;
            for (int j = 0; j < n; ++j) {
                if (!used[j] && baskets[j] >= fruits[i]) {
                    used[j] = true;
                    placed = true;
                    break;
                }
            }
            if (!placed) unplaced++;
        }

        return unplaced;
    }
};
