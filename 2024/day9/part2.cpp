// -*- mode: c++; compile-command: "g++ -g -std=c++23 part2.cpp" -*-

// Copyright 2024 <Ole P. Orhagen>

// Use spans to handle the disk images

#include "../utils.hpp"

using disk_map = vector<int>;

disk_map Xpand(disk_map file) {
  disk_map ret{};
  int counter{0};
  for (auto i = 0; i < file.size(); ++i) {
    int j = file[i];
    for (int k = 0; k < j; ++k) {
      int x = i % 2 == 0 ? counter : -1;
      ret.push_back(x);
    }
    i % 2 == 0 && counter++;
  }

  return ret;
}

using file_id = size_t;

using disk_map_spans = vector<std::span<int>>;

// Create an array of spans over the underlying disk map, enabling us to swap them
disk_map_spans splitDiskMapIntoFiles(disk_map& m) {
  assert(m.size() > 0);
  auto it = m.begin();
  auto last_filetype{m[0]};
  disk_map_spans files{};
  auto span_start_it = it;
  for (; it != m.end(); it++) {
    auto cur_filetype{*it};
    if (cur_filetype != last_filetype) {
      // Create a span from the previous file
      std::span<int> s(span_start_it, it);
      std::cout << "Creating span: " << s << "\n";
      std::cout << "Span start: " << *span_start_it << "\n";
      std::cout << "Span end: " << *it << "\n";

      files.push_back(s);
      span_start_it = it;
      last_filetype = *it;
    }
  }
  files.push_back({span_start_it, it});
  for (const auto& f : files) {
    std::cout << "Files: " << f << "\n";
  }
  return files;
}

optional<std::span<int>> findFirstFreeSpace(disk_map_spans v,
                                            size_t required_free_space) {
  auto free_block =
      std::find_if(v.begin(), v.end(), [required_free_space](auto block) {
        return block[0] == -1 and block.size() >= required_free_space;
      });

  if (free_block == v.end()) {
    return nullopt;
  }

  return *free_block;
}

disk_map Compact(disk_map_spans& xpanded) {
  // Now we compact the file from the highest file_ID
  for (auto rev_it = xpanded.rbegin(); rev_it != xpanded.rend(); rev_it++) {
    auto file = *rev_it;
    std::cout << "Rev file: " << file << "\n";

    auto free_space = findFirstFreeSpace(xpanded, file.size());
  }

  return {};
}

long long int hashfunction(disk_map v) {
  long long int hash{0};
  for (long long int i = 0; i < v.size(); ++i) {
    if (v[i] == -1)
      return hash;
    hash += i * v[i];
  }
  return hash;
}

int main(int argc, char* argv[]) {

  const string compacted_file = split_lines(argv[1])[0];

  const disk_map m = digits(compacted_file);

  auto x = Xpand(m);

  std::cout << "The Xpanded file: " << x << "\n";

  auto c = splitDiskMapIntoFiles(x);

  for (const auto& f : c) {
    std::cout << "File: " << f << "\n";
  }

  // std::cout << "Disk map: " << "\n";

  Compact(c);

  // std::cout << "HHash: " << c << "\n";

  return 0;
}
