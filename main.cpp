#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct ListNode {
  ListNode* prev = nullptr;
  ListNode* next = nullptr;
  ListNode* rand = nullptr;
  std::string data;
};

int main() {
  std::ifstream in("inlet.in");
  if (!in) {
    std::cerr << "Cannot open inlet.in\n";
    return 1;
  }
  ListNode* head = nullptr;
  ListNode* iter = nullptr;
  std::string line;
  std::vector<ListNode*> pointers;  // вектор указателей на ноды
  std::vector<int> rand_indexs;     // вектор ссылок
  while (std::getline(in, line)) {
    size_t pos = line.rfind(';');
    if (pos == std::string::npos) {
      std::cerr << "Invalid line (no ';'): " << line << "\n";
      return 1;
    }
    std::string data = line.substr(0, pos);
    std::string index_str = line.substr(pos + 1);
    std::stringstream ss(index_str);
    int rand_index;
    ss >> rand_index;
    if (head != nullptr) {
      iter->next = new ListNode();
      iter->next->prev = iter;
      iter = iter->next;
      iter->data = std::move(data);
    } else {
      head = new ListNode();
      head->data = std::move(data);
      iter = head;
    }
    pointers.push_back(iter);
    rand_indexs.push_back(rand_index);
  }
  for (size_t jter = 0; jter < pointers.size(); ++jter) {
    if (rand_indexs[jter] != -1) {
      pointers[jter]->rand = pointers[rand_indexs[jter]];
    }
  }
  // запись в бинарный файл
  std::ofstream out("outlet.out", std::ios::binary);
  for (size_t jter = 0; jter < pointers.size(); ++jter) {
    size_t size = pointers[jter]->data.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(pointers[jter]->data.data(), size);
    out.write(reinterpret_cast<const char*>(&rand_indexs[jter]), sizeof(rand_indexs[jter]));
  }
  for (auto jter : pointers) {
    delete jter;
  }
}