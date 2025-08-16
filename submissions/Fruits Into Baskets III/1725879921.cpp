# Title: Fruits Into Baskets III
# Submission ID: 1725879921
# Status: Time Limit Exceeded
# Date: August 6, 2025 at 09:49:15 PM GMT+5:30

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
                    break;  // Place in first available (leftmost) valid basket
                }
            }
            if (!placed) unplaced++;
        }

        return unplaced;
    }
};
