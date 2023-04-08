#include <iostream>
#include <set>

class Track {
public:
    std::pair<int, int> pair;
    std::multiset<std::pair<int, int>> y1; // storing (y1, x) pairs sorted by y1
    std::multiset<std::pair<int, int>> y2;// storing (y2, x) pairs sorted by y2
    std::multiset<int> points; // storing refill points of a track
    std::multiset<int> distance; //storing distances
    void InsertAllValues(Track* track, int n, int x) {
        int ref_x; //
        int ref_y1; // temporary variables for filling the sets
        int ref_y2; //
        for (int i = 0; i < n; i++) {
            std::cin >> ref_x >> ref_y1 >> ref_y2;
            pair.first = ref_y1;
            pair.second = ref_x;
            track->y1.insert(pair);
            pair.first = ref_y2;
            track->y2.insert(pair);
        }
        track->points.insert(0);
        track->points.insert(x);
        track->distance.insert(x); // inserting the maximum distance
    }
};
int main() {

  int n;
  int x;
  int y;
  std::cin >> n >> y >> x;
  for (int i = 0; i < n; i++) {
    int xi, yi1, yi2;
    std::cin >> xi >> yi1 >> yi2;
    pair.first = yi1;
    pair.second = xi;
    track->y1.insert(pair);
    pair.first = ref_y2;
    track->y2.insert(pair);
  }
  /*  std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    Track* track = new Track;
    int n;
    int x;
    int y;
    std::cin >> n >> y >> x;
    track->InsertAllValues(track, n, x);
    std::multiset<std::pair<int, int>>::iterator it_y1 = track->y1.begin();
    std::multiset<std::pair<int, int>>::iterator it_y2 = track->y2.begin();
    for (int i = 0; i <= y; i++) {
        while (it_y1 != track->y1.end() && it_y1->first <= i) {
            auto temp_it = track->points.insert(it_y1->second);
            auto temp_it1 = ++temp_it;
            auto temp_it2 = --temp_it;
            temp_it2--;
            track->distance.erase(*temp_it1 - *temp_it2);
            track->distance.insert(*temp_it1 - *temp_it);
            track->distance.insert(*temp_it - *temp_it2);
            it_y1++;
        }
        while (it_y2 != track->y2.end() && it_y2->first < i) {
            auto temp_it = track->points.find(it_y2->second);
            auto temp_it1 = ++temp_it;
            auto temp_it2 = --temp_it;
            temp_it2--;
            track->distance.insert(*temp_it1 - *temp_it2);
            track->distance.erase(*temp_it1 - *temp_it);
            track->distance.erase(*temp_it - *temp_it2);
            track->points.erase(it_y2->second);
            it_y2++;
        }
        std::multiset<int>::iterator it = track->distance.end();
        it--;
        std::cout << *it << std::endl;
    }
    delete track;*/
}