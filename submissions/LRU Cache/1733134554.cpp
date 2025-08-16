# Title: LRU Cache
# Submission ID: 1733134554
# Status: Time Limit Exceeded
# Date: August 13, 2025 at 08:07:07 AM GMT+5:30

class LRUCache {
public:
    vector<pair<int, int>> cache;
    int n;
    
    LRUCache(int capacity) {
        n = capacity;
    }
    
    int get(int key) {
        for (int i = 0; i < cache.size(); i++) {
            if (cache[i].first == key) {
                int value = cache[i].second;
                auto temp = cache[i];
                cache.erase(cache.begin() + i);
                cache.push_back(temp); 
                return value;
            }
        }
        return -1;
    }
    
    void put(int key, int value) {

        for (int i = 0; i < cache.size(); i++) {
            if (cache[i].first == key) {
                cache.erase(cache.begin() + i);
                cache.push_back({key, value});
                return;
            }
        }

        if (cache.size() == n) {
            cache.erase(cache.begin());
        }

        cache.push_back({key, value});
    }
};
