// -*- mode: c++; compile-command: "g++ -g -std=c++23 part2.cpp" -*-

// Copyright 2024 <Ole P. Orhagen>

// Use spans to handle the disk images

#include "../utils.hpp"

using disk_map = vector<int>;

using file_id = size_t;

using disk_map_spans = vector<std::span<int>>;

disk_map convert(disk_map_spans& m) {
  disk_map dm{};
  for (auto e : m) {
    dm.insert(dm.end(), e.begin(), e.end());
  }
  return dm;
}

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
      // std::cout << "Creating span: " << s << "\n";
      // std::cout << "Span start: " << *span_start_it << "\n";
      // std::cout << "Span end: " << *it << "\n";

      files.push_back(s);
      span_start_it = it;
      last_filetype = *it;
    }
  }
  files.push_back({span_start_it, it});
  // for (const auto& f : files) {
  //   std::cout << "Files: " << f << "\n";
  // }
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

auto Compact(disk_map_spans& xpanded) -> disk_map {
  // Now we compact the file from the highest file_ID

  disk_map m{convert(xpanded)};

  int nr_of_files{std::ranges::max(m)};

  std::cout << "Nr of files: " << nr_of_files << "\n";

  // For each file, try and move it to a free space at the start
  for (int i = nr_of_files; i >= 0; i--) {
    std::cout << "M prior: " << m << "\n";

    std::cout << "File nr: " << i << "\n";
    // Now with the map as the base, we can be more dynamic
    auto spans = splitDiskMapIntoFiles(m);

    // find the file we are working on
    auto file_view =
        spans | std::views::filter([i](auto file) { return file[0] == i; });

    auto file = *file_view.begin();

    // Find the first free space which has the required amount of free space
    auto free_space =
        std::find_if(spans.begin(), spans.end(), [&](auto free_file) {
          return free_file[0] == -1 and free_file.size() >= file.size();
        });

    if (free_space == spans.end()) {
      // No free space available for this file
      continue;
    }

    // Swap the file and free-space
    // std::cout << "Free: " << free_space << "\n";

    // I have an index problem
    // TODO - Make sure the swap always is to the left
    // std::distance(file_view.begin(), spans.begin());
    size_t file_dist{100};
    auto free_dist = 0;
    for (auto it = free_space; it != spans.end(); it++) {
      free_dist += it->size();
    }

    for (auto i = 0; i < m.size(); ++i) {
      if (m[i] == file[0]) {
        file_dist = m.size() - i;
      }
    }

    std::cout << "Greater file dist: " << file_dist << "\n";
    std::cout << "Lesser free dist: " << free_dist << "\n";
    if (free_dist <= file_dist) {
      continue;
    }

    std::cout << "Swapping: " << file << " and " << *free_space << "\n";
    std::swap_ranges(file.begin(), file.end(), free_space->begin());

    std::cout << "M  post: " << m << "\n";
  }

  return m;
}

// Type conversion from disk_map_spans -> disk_map
// template <>
// disk_map_spans::operator int() const {
//   return {};
// }
long long int hashfunction(disk_map v) {
  long long int hash{0};
  for (long long int i = 0; i < v.size(); ++i) {
    if (v[i] == -1)
      continue;
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

  auto compacted_disk = Compact(c);

  for (auto file : compacted_disk) {
    std::cout << "Compacted file: " << file << "\n";
  }

  // disk_map _m = convert(compacted_disk);

  std::cout << compacted_disk << "\n";

  std::cout << "HHash: " << hashfunction(compacted_disk) << "\n";

  return 0;
}
