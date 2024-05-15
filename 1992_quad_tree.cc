#include <iostream>
#include <string>

using namespace std;

static constexpr int kMaxImgRow = 70;

int img_size;

int img[kMaxImgRow][kMaxImgRow];

string quad_tree(int tl_r, int tl_c, int br_r, int br_c) {
  if (tl_r == br_r) {
    return to_string(img[tl_r][tl_c]);
  }

  int half_r = (tl_r + br_r) >> 1;
  int half_c = (tl_c + br_c) >> 1;

  string tl = quad_tree(tl_r, tl_c, half_r, half_c);
  string tr = quad_tree(tl_r, half_c + 1, half_r, br_c);
  string bl = quad_tree(half_r + 1, tl_c, br_r, half_c);
  string br = quad_tree(half_r + 1, half_c + 1, br_r, br_c);

  if (tl == tr && tr == bl && bl == br) {
    if (tl == "0" || tl == "1") { return tl; }
  }

  return "(" + tl + tr + bl + br + ")";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> img_size;

  for (int i = 0; i < img_size; ++i) {
    string line;
    cin >> line;
    for (int j = 0; j < img_size; ++j) {
      img[i][j] = line[j] - '0';
    }
  }

  cout << quad_tree(0, 0, img_size - 1, img_size - 1);

  return 0;
}