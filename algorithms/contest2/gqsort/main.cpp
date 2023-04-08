#include <iostream>

void Partition(long long* arr, int& begin, int& end) {
  int pivot = arr[(end + begin) / 2];
  int i = begin;
  while (i < end) {
    while (arr[i] < pivot) {
      ++i;
    }
    while (arr[i] > pivot && i < end) {
      --end;
    }
    if (i <= end) {
      if (arr[i] > arr[end]) {
        std::swap(arr[i], arr[end]);
      }
      ++i;
      --end;
    }
  }
  begin = i;
}

void QuickSort(long long* arr, int begin, int end) {
  int i = begin, j = end;
  Partition(arr, begin, end);
  if (j > begin) {
    QuickSort(arr, begin, j);
  }
  if (i < end) {
    QuickSort(arr, i, end);
  }
}


int main() {
  int n;
  std::cin >> n;
  long long arr[100001];
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
    //arr[i] = std::rand()%100;
  }
  QuickSort(arr, 0, n - 1);
  for (int i = 0; i < n; i++) {
    std::ios_base::sync_with_stdio(false);
    std::cout << arr[i] << " ";
  }
  return 0;
}


/*#include <iostream>
#include <vector>
//#include <algorithm>

long long BubbleSort(std::vector<long long>& arr, int begin, int end) {
  int i, j;
  for (i = 0; i < end - begin; i++) {
    for (j = 0; j < end - begin - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        std::swap(arr[j], arr[j + 1]);
      }
    }
  }
  return arr[begin + (end - begin) / 2];
}

long long BFRT(std::vector<long long>& arr, int begin, int end) {
  if (end - begin <= 5) {
    return BubbleSort(arr, begin, end);
  }
  std::vector<long long> medianarr;
  std::vector<long long> five;
  for (int i = begin; i < end; i += 5) {
    int sizeoflastfifth = 0;
    for (int j = 0; j < 5; ++j) {
      five.push_back(arr[j]);
      ++sizeoflastfifth;
    }
    long long med = BubbleSort(five, 0, sizeoflastfifth);
    medianarr.push_back(med);
    five.clear();
  }
  return BFRT(medianarr, 0, medianarr.size());
}

int Partition(std::vector<long long>& arr, int begin, int end) {
  //long long pivot = BFRT(arr, begin, end);
  long long pivot = arr[(end + begin) / 2];
/*  int pivot = arr[begin];
  int count = 0;
  for (int i = begin; i <= end; i++) {
    if (arr[i] <= pivot)
      count++;
  }
  int pivotIndex = begin + count;
  std::swap(arr[pivotIndex], arr[begin]);
  int i = begin, j = end;
  while (i < pivot && j > pivot) {
    while (arr[i] <= pivot) {
      i++;
    }
    while (arr[j] > pivot) {
      j--;
    }
    if (i < pivot && j > pivot) {
      std::swap(arr[i++], arr[j--]);
    }
  }
  return pivot;*/
/*  while (begin <= end) {
    while (arr[end] > pivot) {
      --end;
    }
    while (arr[begin] < pivot) {
      ++begin;
    }
    if (begin <= end) {
      if (arr[begin] > arr[end]) {
        std::swap(arr[begin], arr[end]);
      }
      --end;
      ++begin;
    }
  }
}


/*for (int i = begin; i < end; ++i) {
  if (pivotvalue == arr[i]) {
    pivot = i;
  }
}*/
  /*int pivotvalue = arr[r];
  int i = p - 1;
  for (int j = p; j <= r - 1; j++) {
    if (arr[j] < pivotvalue) {
      i++;
      std::swap(arr[i], arr[j]);
    }
  }
  std::swap(arr[i + 1], arr[r]);
  return (i + 1);*/
//}

//void Quicksort(std::vector<long long>& arr, int begin, int end) {
 /* if (p < r) {
    int pi = Partition(arr, p, r);
    Quicksort(arr, p, pi - 1);
    Quicksort(arr, pi + 1, r);
  }*/
/*  int i = begin;
  int j = end;
  Partition(arr, begin, end);
  if (j > end) {
    Quicksort(arr, begin, j);
  }
  if (i < end) {
    Quicksort(arr, i, end);
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<long long> arr(n);
  for (int i = 0; i < n; i++) {
    //std::cin >> arr[i];
    arr[i] = std::rand()%100;
  }
  Quicksort(arr, 0, arr.size() - 1);
  for (int i = 0; i < (int)arr.size(); i++) {
    std::ios_base::sync_with_stdio(false);
    std::cout << arr[i] << " ";
  }
  return 0;
}

//arr[i] = rand()%100;

/* if (std::is_sorted(std::begin(arr), std::end(arr))) {
       std::cout << "OK";
     } else {
       std::cout << "WA";
     }*/

/*int i=p;
 int j;

 for(j=p+1; j<r; j++)
 {
   if(arr[j]<=pivotvalue)
   {
     i=i+1;
     std::swap(arr[i],arr[j]);
   }

 }

 std::swap(arr[i],arr[p]);
 return i;*/
/*int m = 0;
while (p < r && r >= 0 && p >= 0) {
  while (arr[p] < pivotvalue) {
    if(pivotvalue == arr[p]){
      ++m;
    }
    ++p;
  }
  while (arr[r] > pivotvalue) {
    --r;
  }
  if ((arr[p] == arr[r]) && (p != r)){
    ++p;
  } else if (p < r) {
    std::swap(arr[p], arr[r]);
  }
}
return r + m/2;*/