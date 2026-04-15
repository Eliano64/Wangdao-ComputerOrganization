#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define k 16
#define M 16 * 16

int ran(int *cache, int *query) {
  int shoot = 0;
  int cur = 0;
  for (int i = 0; i < 10 * M; ++i) {
    int isShoot = 0;
    for (int j = 0; j < 4 * k; ++j) {
      if (cache[j] == query[i]) {
        shoot++;
        isShoot = 1;
        break;
      }
      if (cache[j] == 0) {
        break;
      }
    }
    if (!isShoot) {
      if (cur < 4 * k && cache[cur] == 0) {
        cache[cur] = query[i];
        ++cur;
      } else {
        cur = rand() % (4 * k);
        cache[cur] = query[i];
      }
    }
  }
  return shoot;
}

int fifo(int *cache, int *query) {
  int shoot = 0;
  int cur = 0;
  for (int i = 0; i < 10 * M; ++i) {
    int isShoot = 0;
    for (int j = 0; j < 4 * k; ++j) {
      if (cache[j] == query[i]) {
        shoot++;
        isShoot = 1;
        break;
      }
      if (cache[j] == 0) {
        break;
      }
    }
    if (!isShoot) {
      cache[cur] = query[i];
      cur = (cur + 1) % (4 * k);
    }
  }
  return shoot;
}

void _update(int * cache, int *cnt, int i, int isShoot) {
  for (int j = 0; j < 4 * k; ++j) {
    if (!isShoot && cache[j]) {
      cnt[j]++;
    }
    if(isShoot && cnt[j]<cnt[i]){
        cnt[j]++;
    }
  }
  cnt[i] = 0;
}

int _select(int *cnt) {
  int max = cnt[0];
  int ret = 0;
  for (int i = 1; i < 4 * k; ++i) {
    ret = max > cnt[i] ? ret : i;
    max = max > cnt[i] ? max : cnt[i];
  }
  return ret;
}

int lru(int *cache, int *query) {
  int shoot = 0;
  int cur = 0;
  int cnt[4 * k] = {};

  for (int i = 0; i < 10 * M; ++i) {
    int isShoot = 0;
    for (int j = 0; j < 4 * k; ++j) {
      if (cache[j] == query[i]) {
        shoot++;
        isShoot = 1;
        _update(cache, cnt, j, isShoot);
        break;
      }
      if (cache[j] == 0) {
        break;
      }
    }
    if (!isShoot) {
      if (cur < 4 * k && cache[cur] == 0) {
        cache[cur] = query[i];
        _update(cache,cnt, cur,isShoot);
        ++cur;
      } else {
        cur = _select(cnt);
        _update(cache, cnt, cur,isShoot);
        cache[cur] = query[i];
      }
    }
  }
  return shoot;
}

int _lSelect(int *fre) {
  int min = fre[0];
  int ret = 0;
  for (int i = 1; i < 4 * k; ++i) {
    ret = min < fre[i] ? ret : i;
    min = min < fre[i] ? min : fre[i];
  }
  fre[ret] = 0;
  return ret;
}

int lfu(int *cache, int *query) {
  int shoot = 0;
  int cur = 0;
  int fre[4 * k] = {};
  for (int i = 0; i < 10 * M; ++i) {
    int isShoot = 0;
    for (int j = 0; j < 4 * k; ++j) {
      if (cache[j] == query[i]) {
        shoot++;
        isShoot = 1;
        fre[j]++;
        break;
      }
      if (cache[j] == 0) {
        break;
      }
    }
    if (!isShoot) {
      if (cur < 4 * k && cache[cur] == 0) {
        cache[cur] = query[i];
        fre[cur]++;
        ++cur;
      } else {
        cur = _lSelect(fre);
        cache[cur] = query[i];
      }
    }
  }
  return shoot;
}

static int (*func[4])(int *, int *) = {ran, fifo, lru, lfu

};

const char *names[4] = {"ran", "fifo", "lru", "lfu"};

int main() {
  srand((unsigned)time(NULL));
  int query[10 * M] = {};
  for (int i = 0; i < 5 * M; ++i) {
    while (!query[i]) {
      query[i] = rand() % (5*k);
    }
  }
  for (int i = 5*M; i < 10 * M; ++i) {
    while (!query[i]) {
      query[i] = rand() % (k) + 5*k;
    }
  }
  printf("case 1: 前5M次集中在1-5k，后5M次集中在5k-6K\n");
  for (int i = 0; i < 4; ++i) {
    int cache[4 * k] = {};
    int cnt = func[i](cache, query);
    printf("%s命中率: %.2f\n", names[i], cnt * 100.f / (10 * M));
  }
  for (int i = 0; i < 10 * M; ++i) {
    while (!query[i]) {
      query[i] = rand() % (5*k);
    }
  }
  printf("case 2: 10M次集中在1-5k\n");
  for (int i = 0; i < 4; ++i) {
    int cache[4 * k] = {};
    int cnt = func[i](cache, query);
    printf("%s命中率: %.2f\n", names[i], cnt * 100.f / (10 * M));
  }
}