# Title: Fruits Into Baskets III
# Submission ID: 1725878586
# Status: Wrong Answer
# Date: August 6, 2025 at 09:48:11 PM GMT+5:30

class Solution {
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        multiset<int> availableBaskets(baskets.begin(), baskets.end());
        int unplaced = 0;

        for (int fruit : fruits) {
            auto it = availableBaskets.lower_bound(fruit);
            if (it != availableBaskets.end()) {
                availableBaskets.erase(it);  // Assign basket and remove it
            } else {
                unplaced++;  // No basket found
            }
        }

        return unplaced;
    }
};