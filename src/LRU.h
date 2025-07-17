#pragma once

#include <iostream>
#include <list>
#include <stdexcept>
#include <unordered_map>

namespace NGame {

template<typename Key, typename Value>
class TLRU {
public:
    using TPair = std::pair<Key, Value>;
    using TKey = Key;
    using TValue = Value;

    TLRU(std::size_t capacity) 
        : Capacity_(capacity) {
    }

    const Value& Get(const Key& key) const {
        auto it = Map_.find(key);
        if (it == Map_.end()) {
            throw std::runtime_error("lru cache miss");
        }

        Cache_.splice(Cache_.begin(), Cache_, it->second);
        return it->second->second;
    }

    void Set(const Key& key, const Value& value) {
        Set(key, value, [](auto& value){});
    }

    template<typename UnaryPredicate>
    void Set(const Key& key, const Value& value, UnaryPredicate p) {
        auto it = Map_.find(key);
        if (it != Map_.end()) {
            p(*it->second);
            Cache_.erase(it->second);
            Map_.erase(it);
        }

        Cache_.push_front(std::make_pair(key, value));
        Map_[key] = Cache_.begin();

        while (Map_.size() > Capacity_) {
            auto lastElement = --(Cache_.end());
            p(*lastElement);
            Map_.erase(lastElement->first);
            Cache_.erase(lastElement);
        }
    }

    bool Contains(const Key& key) const {
        return Map_.find(key) != Map_.end();
    }

    std::size_t Size() const {
        return Map_.size();
    }

    std::size_t Capacity() const {
        return Capacity_;
    }

    void Clear() {
        Cache_.clear();
        Map_.clear();
    }

private:
    using TIterator = typename std::list<TPair>::iterator;

    mutable std::list<TPair> Cache_;
    mutable std::unordered_map<Key, TIterator> Map_;
    std::size_t Capacity_;
};

} // namespace NGame
