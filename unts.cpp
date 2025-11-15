#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <algorithm>
#include <map>
#include <array>
#include <valarray>

/* UNTS structures realization */

// STD::ARRAY<BOOL,SIZE> FLAGS --> is the main structure in the uts structures for checking existense of elements
// if element exists -> 1 else 0

namespace unts {
template<typename Type, std::size_t Size>
class unique_array { // structure for keeping unique elements in array
    std::array<Type,Size> uniq_arr; // elements in array
    std::array<bool,Size> flags;
    std::set<Type> set_uniq; // std::set structure for deleting dublications in array
public:
    unique_array() {
        std::fill(flags.begin(),flags.end(),0); // flags are 0 in default in constructor
        if constexpr (!std::is_arithmetic<Type>::value) {
            if constexpr (std::is_same_v<Type,std::string>) { // <----------------------| //
                for(auto& put_elem : uniq_arr) {put_elem = std::string("");}                                                                         // | //
            } else if(std::is_same_v<Type,char>) {                                      // | //
                for(std::size_t full_uniq_arr = 0; full_uniq_arr < Size; ++full_uniq_arr) {// | //
                    uniq_arr[full_uniq_arr] = ' ';                                          // | //
                }                                                                          // | //
            } // <----------------------------------------------------------------------------| //
        } else {
            std::fill(uniq_arr.begin(),uniq_arr.end(),(Type)0); // automatic filling unique elements if they are integers by zero //
        }
    }
    Type operator[](std::size_t&& index) {
        if(index >= Size) {throw std::out_of_range("Out of range exception");}
        return uniq_arr.at(index);
    }
    void add(std::size_t index, Type element) {
        auto find_element = std::find(uniq_arr.begin(),uniq_arr.end(),element);
        if(find_element == uniq_arr.end()) {
            if(index < 0 || index >= Size) {throw std::out_of_range("Out of range exception");}
            uniq_arr[index] = element;
        }
        for(auto& emplace : uniq_arr) {
            set_uniq.emplace(emplace);
        }
    }
    void for_each() {
        std::for_each(set_uniq.begin(),set_uniq.end(),[](Type element){std::cout << element << " ";});
        std::cout << std::endl;
    }
    unique_array(const unique_array& other_) {
        this->uniqArr = other_.uniq_arr;
        this->flags = other_.flags;         // copying constructor
        this->set_uniq= other_.set_uniq;
    }
    void reverse() {
        set_uniq.clear();
        for(std::reverse_iterator rev_it = uniq_arr.begin(); rev_it != uniq_arr.end(); ++rev_it) {
            set_uniq.emplace((*rev_it));
        }
    }
    void swap(const unique_array& other) {
        if(uniq_arr.size() == other.uniq_arr.size()) {
            for(std::size_t swap_values = 0; swap_values < uniq_arr.size(); ++swap_values) {
                auto save_elem = uniq_arr[swap_values];
                uniq_arr[swap_values] = other.uniq_arr[swap_values];
                other.uniq_arr[swap_values] = save_elem;
            }
        } else {
            for(std::size_t swap_values = 0; swap_values < other.uniq_arr.size(); ++swap_values) {
                auto save_elem = uniq_arr[swap_values];
                uniq_arr[swap_values] = other.uniq_arr[swap_values];
                other.uniq_arr[swap_values] = save_elem;
            }
        }
    }
    auto begin() {return uniq_arr.begin();}
    auto end() {return uniq_arr.end();}
    auto cbegin() {return uniq_arr.cbegin();}
    auto cend() {return uniq_arr.cend();}
    auto crbegin() {return uniq_arr.crbegin();}
    auto crend() {return uniq_arr.crend();}
    std::size_t real_size() {
        std::size_t fact_size = std::count(flags.begin(),flags.end(),1);
        return fact_size;
    }
    std::size_t size() {return Size;}
    Type front() {return uniq_arr[0];}
    Type back() {return uniq_arr[Size - 1];}
    void clear() {
        set_uniq.clear();
        std::fill(uniq_arr.begin(),uniq_arr.end(),set_uniq.begin());
    }
    void erase(Type& element) {
        set_uniq.erase(element);
        std::size_t index = 0;
        for(auto& set : set_uniq) {
            uniq_arr[index] = set;
            index++;
        }
    }
    bool is_empty() { // if structure empty or not
        std::size_t count_null_elements = std::count(flags.begin(),flags.end(),0); // count null elements in structure //
        return count_null_elements >= Size;
    }
}; // UNIQUE_ARRAY <std::set + std::array> //
template<typename Type>
class unique_priority_queue { // priority_queue with unique priorities
    std::deque<Type> uniq_prio_queue;
    std::set<Type> un_pr_queue;
public:
    unique_priority_queue(const unique_priority_queue& other) {
        this->uniq_prio_queue = other.uniq_prio_queue;
        this->un_pr_queue = other.un_pr_queue;
    }
    unique_priority_queue(std::initializer_list<Type> list) {
        auto begin = list.begin();
        auto end = list.end();
        for(std::size_t put = 0; put < list.size() && begin != end; ++put) {
            uniq_prio_queue.push((*begin));
            un_pr_queue.emplace((*begin));
            ++begin;
        }
    }
    void push(const Type&& element) {
        uniq_prio_queue.push(element);
        un_pr_queue.emplace(element);
    }
    void for_each() {
        std::for_each(un_pr_queue.begin(),un_pr_queue.end(),[](Type element){std::cout << element << " ";});
        std::cout << std::endl;
    }

    auto begin() {return un_pr_queue.begin();}
    auto end() {return un_pr_queue.end();}
    auto cbegin() {return un_pr_queue.cbegin();}
    auto cend() {return un_pr_queue.cend();}
    auto crbegin() {return un_pr_queue.crbegin();}
    auto crend() {return un_pr_queue.crend();}
    void pop() {
        uniq_prio_queue.pop();
    }
    std::size_t real_size() {
        std::size_t fact_size = std::count(un_pr_queue.begin(),un_pr_queue.end(),1);
        return fact_size;
    }
    void clear() {
        for(std::size_t clean_the_queue = 0; clean_the_queue < uniq_prio_queue.size(); ++clean_the_queue) {
            uniq_prio_queue.pop();
        }
        un_pr_queue.clear();
    }
}; // UNIQUE_PRIORITY_QUEUE <std::set + std::priority_queue> //

template<typename Type, std::size_t Size>
class static_list { // specific list with fixed size like in std::array
    std::list<Type> stat_list; // the main list
    std::array<Type,Size> s_list; // for keeping elements and analyze fixed size
    std::array<bool,Size> flags;
    std::size_t index; // for filling and iterations elements by index
    std::size_t _size;
public:
    static_list(std::initializer_list<Type> generate_stat_list) : index(0) {
        if(generate_stat_list.size() > Size) {
            throw std::runtime_error("Out of bounds exception");
        } else {
            auto first = generate_stat_list.begin();
            auto last = generate_stat_list.end();
            for(std::size_t i = 0; i < Size && first != last; ++i) {
                s_list[i] = (*first);
                flags[i] = 1;
                ++first;
            }
            stat_list.assign(s_list.begin(),s_list.end());
            index = stat_list.size();
            _size = Size;
        }
    }
    static_list(const static_list& other) {
        this->stat_list = other.stat_list;
        this->s_list = other.s_list;
        this->flags = other.flags;
    }
    static_list() : index(0) {
        stat_list.resize(Size);
        std::fill(flags.begin(),flags.end(),0);
        _size = Size;
    }
    auto begin(){return s_list.begin();}
    auto end(){return s_list.end();}
    auto rbegin(){return s_list.rbegin();}
    auto rend(){return s_list.rend();}
    auto cbegin(){return s_list.cbegin();}
    auto cend(){return s_list.cend();}
    auto crbegin(){return s_list.crbegin();}
    auto crend(){return s_list.crend();}
    auto const_iterator(){return s_list.const_iterator;}
    auto reverse_iterator(){return s_list.reverse_iterator;}
    auto const_reverse_iterator(){return s_list.const_reverse_iterator;}
    std::size_t size() {return Size;}
    std::size_t real_size() {
        std::size_t fact_size = std::count(flags.begin(),flags.end(),1);
        return fact_size;
    }
    template<typename Iter1, typename Iter2>
    void assign(Iter1 __first, Iter2 __last) { // automatic filling elements in structure by constant operators //
        Iter1 current_iterator = __first;
        for(std::size_t i = 0; i < Size && current_iterator != __last; ++i) {
            s_list[i] = (*current_iterator);
            flags[i] = 1;
            ++current_iterator;
        }
        stat_list.assign(s_list.begin(),s_list.end());
        index = stat_list.size();
    }
    void erase(Type position) {
        std::size_t iterate_again = 0;
        auto find_pos = std::find(stat_list.begin(),stat_list.end(),position);
        if(find_pos == stat_list.end()) {
            throw std::runtime_error("Unknown position");
        }
        stat_list.erase(find_pos);
        std::fill(flags.begin(),flags.end(),0);
        for(auto& return_values_to_s_list : stat_list) {
            s_list.at(iterate_again) = return_values_to_s_list;
            flags.at(iterate_again) = 1;
            iterate_again++;
        }
    }
    void push_back(Type&& element) {
        if(index >= Size) {throw std::runtime_error("Out of range exception");}
        stat_list.push_back(element);
        s_list[index] = element;
        flags[index] = 1;
        index++;
    }
    void pop_back() {
        _size--;
        if(_size == 0) {throw std::runtime_error("Out of range exception");}
        flags[_size] = 0;
    }
    void emplace_back(Type&& element) {
        if(index >= Size) {throw std::runtime_error("Out of range exception");}
        stat_list.emplace_back(element);
        s_list.at(index) = element;
        flags.at(index) = 1;
    }
    void emplace_front(Type&& element, std::size_t next_index = 1) {
        if(index >= Size && next_index >= Size) {throw std::runtime_error("Out of range exception");}
        if(index >= Size) {throw std::runtime_error("Out of range exception");}
        stat_list.emplace_front(element);
        s_list.at(next_index) = s_list.at(index);
        flags[next_index] = 1;
        s_list.at(index) = element;
        flags[index] = 1;
        index++;
        next_index++;
    }
    void pop_front(std::size_t rev_index = Size) {
        if(rev_index < 0) {throw std::runtime_error("Out of range exception");}
        stat_list.pop_front();
        s_list.at(rev_index) = s_list.end();
        rev_index--;
    }
    Type front() {return s_list.at(0);}
    Type back() {return s_list.at(Size - 1);}
    void for_each() {
        for(std::size_t iterate_elements = 0; iterate_elements < Size; ++iterate_elements) {
            if(flags[iterate_elements] == 1) {
                std::cout << s_list[iterate_elements] << " ";
            }
        }
    }
    void clear() {
        stat_list.clear();
        std::fill(s_list.begin(),s_list.end(),stat_list.begin());
        std::fill(flags.begin(),flags.end(),0); // automatic cleaning the flags by filling zero
    }
}; // STATIC_LIST <std::array + std::list> //
template<typename Key, typename Value, std::size_t Size>
class static_map { // map with fixed size like static list
    std::map<Key,Value> stat_map; // the main map
    std::array<bool,Size> flags;
    std::size_t index; // for filling and iteration elements by index
public:
    static_map() : index(0) {
        std::fill(flags.begin(),flags.end(),0); // default constructor which fills the flags by zero
    }
    void insert(Key set_key, Value set_value) {
        if(index >= Size) {throw std::runtime_error("Out of range exception");}
        stat_map[set_key] = set_value;
        flags[index] = 1;
        index++;
    }
    auto begin(){return stat_map.begin();}
    auto end() {return stat_map.end();}
    auto rbegin() {return stat_map.rbegin();}
    auto rend() {return stat_map.rend();}
    void for_each() {
        for(auto& iterate : stat_map) {
            std::cout << iterate.first << " " << iterate.second << std::endl;
        }
    }
    Value& operator[](Key key) {
        if(index >= Size) {throw std::runtime_error("Out of range exception");}
        stat_map.emplace(key,Value());
        index++;
        return stat_map.at(key);
    }
    Value at(Key&& key) {
        Value val_result;
        try {
            val_result = stat_map.at(key);
        } catch (const std::out_of_range exc) {
            throw std::runtime_error(exc.what());
        }
        return val_result;
    }
    std::size_t size() {return Size;}
    std::size_t real_size() { // real_size is the size which counts existense elements in structure
        std::size_t fact_size = std::count(flags.begin(),flags.end(),1);
        return fact_size;
    }
    void erase(Key&& key) {
        std::size_t count_existed_elements = 0;
        this->stat_map.erase(key);
        std::fill(flags.begin(),flags.end(),0);
        for(auto& _ : this->stat_map) {
            count_existed_elements++;
        }
        for(std::size_t return_existed_flags = 0; return_existed_flags < count_existed_elements; ++return_existed_flags) {
            flags.at(count_existed_elements) = 1;
        }
        Size = count_existed_elements;
    }
    void clear() {
        stat_map.clear();
        std::fill(flags.begin(),flags.end(),0);
    }
    bool is_empty() {
        std::size_t count_null_keys_and_values = std::count(flags.begin(),flags.end(),0);
        if(count_null_keys_and_values >= Size) {
            return true;
        }
        return false;
    }
}; // STATIC_MAP <std::array + std::map> //
template<typename Type, std::size_t Size>
class static_deque { // the deque with fixed size
    std::array<bool,Size> flags;
    std::deque<Type> stat_deque; // the main deque
    std::size_t index;
    std::size_t __size = Size;  // for pop and push methods
    std::size_t pre_index;
public:
    static_deque() : index(0), pre_index(Size) {
        if(__size <= 0) {throw std::runtime_error("Invalid size error");}
        std::fill(flags.begin(),flags.end(),0);
    }
    static_deque(std::initializer_list<Type> list) {
        if(__size <= 0) {throw std::runtime_error("Invalid size error");}
        if(list.size() > __size) {throw std::runtime_error("Out of bounds exception");}
        stat_deque.assign(list.begin(),list.end());
        std::fill(flags.begin(),flags.end(),1);
        index = __size;
    }
    static_deque(const static_deque& other) {
        this->stat_deque = other.stat_deque;
        this->flags = other.flags;
    }
    void push(const Type&& element) {
        if(index >= __size) {throw std::runtime_error("Out of range exception");}
        stat_deque.push_front(element);
        flags[index] = 1;
        index++;
    }
    template<typename Iter1, typename Iter2>
    void assign(Iter1 __first, Iter2 __last) { // assign algorithm with const iterator type
        // for automatic setting values to structure
        Iter1 begin = __first;
        for(std::size_t to_s_queue = 0; to_s_queue < Size && begin != __last; ++to_s_queue) {
            stat_deque.push_front((*begin));
            flags[to_s_queue] = 1;
            ++begin;
        }
    }
    void pop() {
        if(index < 0) {throw std::runtime_error("Out of range exception");}
        stat_deque.pop_front();
        index--;
        flags[index] = 0;
    }
    void for_each() {
        for(std::size_t iterate = 0; iterate < flags.size(); ++iterate) {
            if(flags[iterate] == 1) {
                std::cout << stat_deque[iterate] << " ";
            }
        }
        std::cout << std::endl;
    }
    Type front() {return stat_deque.front();}
    Type back() {return stat_deque.back();}
    bool is_empty() {
        std::size_t is_null = std::count(flags.begin(),flags.end(),0);
        return is_null >= Size;
    }
    Type operator[](std::size_t _index) {
        if(_index < 0 || _index >= Size) {throw std::runtime_error("Out of range exception");}
        return stat_deque.at(_index);
    }
    std::size_t size() const {return Size;}
    std::size_t real_size() {
        std::size_t fact_size = std::count(flags.begin(),flags.end(),1);
        return fact_size;
    }
    void erase(Type&& element) {
        auto find_element = std::find(stat_deque.begin(),stat_deque.end(),element);
        auto find_from_first_element = std::find(stat_deque.begin(),stat_deque.end(),stat_deque.at(0));
        if(find_element == stat_deque.end()) {throw std::out_of_range("Out of range exception");}
        flags[std::distance(find_from_first_element,find_element)] = 0;
        stat_deque.erase(find_element);
    }
    void push_back(Type element) {
        stat_deque.push_back(element);
        flags[index] = 1;
    }
    void push_front(Type element) {
        if(pre_index >= Size) {throw std::out_of_range("Out of range exception");}
        std::size_t pre_index = 0;
        stat_deque.push_front(element);
        flags[pre_index] = 1;
        pre_index++;
    }
    void pop_front() {
        std::size_t pre_index = 0;
        stat_deque.pop_front();
        flags[pre_index] = 0;
        pre_index++;
    }
    void resize(std::size_t new_size) {
        stat_deque.resize(new_size);
        __size = new_size;
    }
    auto begin() {return stat_deque.begin();}
    auto end() {return stat_deque.end();}
    auto rbegin() {return stat_deque.rbegin();}
    auto rend() {return stat_deque.rend();}
    auto cbegin() {return stat_deque.cbegin();}
    auto cend() {return stat_deque.cend();}
    auto crbegin() {return stat_deque.crbegin();}
    auto crend() {return stat_deque.crend();}
    void clear() {
        stat_deque.clear();
        std::fill(flags.begin(),flags.end(),0);
    }
}; // STATIC_DEQUE <std::array + std::deque> //
template<typename Type, std::size_t Size>
class static_valarray {
private:
    std::valarray<Type> stat_val;
    std::array<Type,Size> s_val;
    std::array<bool,Size> flags;
public:
    static_valarray() : stat_val(Size) {
        if(!std::is_arithmetic<Type>::value) {
            throw std::runtime_error("Type must be arithmetic for static_valarray");
        } else {
            std::fill(std::begin(stat_val), std::end(stat_val),(Type)0);
            std::fill(s_val.begin(), s_val.end(),(Type)0);
            std::fill(flags.begin(), flags.end(),0);
        }
    }
    void add(std::size_t index, Type&& element) {
        if(index < 0 || index >= Size) {
            throw std::runtime_error("Out of range exception");
        }
        stat_val[index] = element;
        s_val[index] = element;
        flags[index] = 1;
    }
    void for_each() {
        for(std::size_t iterate = 0; iterate < flags.size(); ++iterate) {
            if(this->flags[iterate] == 1) {
                std::cout << this->stat_val[iterate] << " ";
            }
        }
    }
    auto begin() {return s_val.begin();}
    auto end() {return s_val.end();}
    auto rbegin() {return s_val.rbegin();}
    auto rend() {return s_val.rend();}
    Type front() {return stat_val[0];}
    Type back() {return stat_val[Size - 1];}
    static_valarray(const static_valarray& other) {
        this->stat_val = other.stat_val;
        this->s_val = other.s_val;
        this->flags = other.flags;
    }
    static_valarray operator+(Type&& operand) {
        for(auto& every_element_for_addition : this->stat_val) {
            every_element_for_addition += operand;
        }
        return *this;
    }
    static_valarray operator-(Type&& operand) {
        for(auto& every_element_for_division : this->stat_val) {
            every_element_for_division -= operand;
        }
        return *this;
    }
    static_valarray operator*(Type&& operand) {
        for(auto& every_element_for_multiplication : this->stat_val) {
            every_element_for_multiplication *= operand;
        }
        return *this;
    }
    static_valarray operator/(Type&& operand) {
        if(operand == (Type)0) {throw std::runtime_error("Division by zero");}
        for(auto& every_element_for_division : this->stat_val) {
            every_element_for_division /= operand;
        }
        return *this;
    }
    static_valarray operator%(Type&& operand) {
        if(operand == (Type)0) {throw std::runtime_error("Division by zero");}
        for(auto& every_element_for_module_division : this->stat_val) {
            every_element_for_module_division %= operand;
        }
        return *this;
    }
    void erase(Type element) {
        auto find_element = std::find(s_val.begin(),s_val.end(),element);
        auto first_element = std::find(s_val.begin(),s_val.end(),s_val.at(0));
        int index = std::distance(first_element,find_element);
        flags[index] = 0;
    }
    static_valarray operator+(const static_valarray& other) {
        if(this->stat_val.size() != other.stat_val.size()) {
            for(std::size_t plus_vals = 0; plus_vals < this->stat_val.size(); ++plus_vals) {
                if(plus_vals >= other.stat_val.size()) {break;}
                this->stat_val[plus_vals] += other.stat_val[plus_vals];
            }
        } else {
            for(std::size_t plus_vals = 0; plus_vals < Size; ++plus_vals) {
                this->stat_val[plus_vals] += other.stat_val[plus_vals];
            }
        }
        return *this;
    }
    void swap(const static_valarray& other) {
        if(stat_val.size() == other.stat_val.size()) {
            for(std::size_t swap_values = 0; swap_values < stat_val.size(); ++swap_values) {
                auto save_elem = stat_val[swap_values];
                stat_val[swap_values] = other.stat_val[swap_values];
                other.stat_val[swap_values] = save_elem;
            }
        } else {
            for(std::size_t swap_values = 0; swap_values < other.stat_val.size(); ++swap_values) {
                auto save_elem = stat_val[swap_values];
                stat_val[swap_values] = other.stat_val[swap_values];
                other.stat_val[swap_values] = save_elem;
            }
        }
    }
    static_valarray operator-(const static_valarray& other) {
        if(this->stat_val.size() != other.stat_val.size()) {
            for(std::size_t plus_vals = 0; plus_vals < this->stat_val.size(); ++plus_vals) {
                if(plus_vals >= other.stat_val.size()) {break;}
                this->stat_val[plus_vals] -= other.stat_val[plus_vals];
            }
        } else {
            for(std::size_t plus_vals = 0; plus_vals < Size; ++plus_vals) {
                this->stat_val[plus_vals] -= other.stat_val[plus_vals];
            }
        }
        return *this;
    }
    static_valarray operator*(const static_valarray& other) {
        if(this->stat_val.size() != other.stat_val.size()) {
            for(std::size_t plus_vals = 0; plus_vals < this->stat_val.size(); ++plus_vals) {
                if(plus_vals >= other.stat_val.size()) {break;}
                this->stat_val[plus_vals] *= other.stat_val[plus_vals];
            }
        } else {
            for(std::size_t plus_vals = 0; plus_vals < Size; ++plus_vals) {
                this->stat_val[plus_vals] *= other.stat_val[plus_vals];
            }
        }
        return *this;
    }
    static_valarray operator/(const static_valarray& other) {
        if(this->stat_val.size() != other.stat_val.size()) {
            for(std::size_t plus_vals = 0; plus_vals < this->stat_val.size(); ++plus_vals) {
                if(plus_vals >= other.stat_val.size()) {break;}
                if(other.stat_val[plus_vals] == 0) {
                    throw std::runtime_error("Division by zero");
                }
                this->stat_val[plus_vals] /= other.stat_val[plus_vals];
            }
        } else {
            for(std::size_t plus_vals = 0; plus_vals < Size; ++plus_vals) {
                this->stat_val[plus_vals] /= other.stat_val[plus_vals];
            }
        }
        return *this;
    }
    static_valarray operator%(const static_valarray& other) {
        if(this->stat_val.size() != other.stat_val.size()) {
            for(std::size_t div_vals = 0; div_vals < this->stat_val.size(); ++div_vals) {
                if(div_vals >= other.stat_val.size()) {break;}
                if(other.stat_val[div_vals] == 0) {
                    throw std::runtime_error("Division by zero");
                }
                this->stat_val[div_vals] %= other.stat_val[div_vals];
            }
        } else {
            for(std::size_t div_vals = 0; div_vals < Size; ++div_vals) {
                this->stat_val[div_vals] %= other.stat_val[div_vals];
            }
        }
        return *this;
    }
    Type& operator[](std::size_t&& index) {
        if(index < 0 || index > Size) {
            throw std::runtime_error("Out of range exception");
        }
        return stat_val[index];
    }
    std::size_t size() {
        return Size;
    }
    std::size_t real_size() {
        std::size_t fact_size = std::count(flags.begin(),flags.end(),1);
        return fact_size;
    }
}; // STATIC_VALARRAY <std::array + std::valarray> //
template<typename Type,std::size_t Size>
class unique_valarray {
private:
    std::array<bool,Size> flags;
    std::valarray<Type> uniq_val;
    std::set<Type> u_val;
public:
    unique_valarray() : uniq_val(Size) {
        if(!std::is_arithmetic<Type>::value) {
            throw std::runtime_error("Type must be arithmetic for static_valarray");
        } else {
            std::fill(flags.begin(),flags.end(),0);
            std::fill(std::begin(uniq_val),std::end(uniq_val),(Type)0);
        }
    }
    void add(std::size_t index, Type element) {
        if(index < 0 || index >= Size) {throw std::runtime_error("Out of range exception");}
        uniq_val[index] = element;
        flags[index] = 1;
        for(auto& put_to_set : uniq_val) {
            u_val.emplace(put_to_set);
        }
        u_val.erase(0);
    }
    void erase(std::size_t index, Type&& element) {
        if(index < 0 || index >= Size) {throw std::runtime_error("Out of range exception");}
        std::size_t iter_index = 0;
        auto find_and_delete = std::find(u_val.begin(),u_val.end(),element);
        u_val.erase(find_and_delete);
        std::fill(std::begin(uniq_val),std::end(uniq_val),(Type)0);
        for(auto& put_again : u_val) {
            uniq_val[iter_index] = put_again;
            iter_index++;
        }
        flags[index] = 0;
    }
    void for_each() {
        for(std::size_t iterate = 0; iterate < flags.size(); ++iterate) {
            if(flags[iterate] == 1) {
                std::cout << u_val[iterate] << " ";
            }
        }
        std::cout << std::endl;
    }
    std::size_t size() {return Size;}
    std::size_t real_size() {
        std::size_t fact_size = std::count(flags.begin(),flags.end(),1);
        return fact_size;
    }
    void swap(const unique_valarray& other) {
        if(uniq_val.size() == other.uniq_val.size()) {
            for(std::size_t swap_values = 0; swap_values < uniq_val.size(); ++swap_values) {
                auto save_elem = uniq_val[swap_values];
                uniq_val[swap_values] = other.uniq_val[swap_values];
                other.uniq_val[swap_values] = save_elem;
            }
        } else {
            for(std::size_t swap_values = 0; swap_values < other.uniq_val.size(); ++swap_values) {
                auto save_elem = uniq_val[swap_values];
                uniq_val[swap_values] = other.uniq_val[swap_values];
                other.uniq_val[swap_values] = save_elem;
            }
        }
    }
    Type front() {return uniq_val[0];}
    Type back() {return uniq_val[real_size() - 1];}
    auto begin() {return u_val.begin();}
    auto end(){return u_val.end();}
    auto rbegin() {return u_val.rbegin();}
    auto rend() {return u_val.rend();}
    unique_valarray (const unique_valarray& other) {
        this->uniq_val = other.uniq_val;
        this->u_val = other.u_val;
        this->fact_size = other.fact_size;
        this->Size = other.Size;
    }
    unique_valarray operator+(Type&& operand) {
        for(auto& every_element_for_addition : this->uniq_val) {
            every_element_for_addition += operand;
        }
        return *this;
    }
    unique_valarray operator-(Type&& operand) {
        for(auto& every_element_for_subtraction : this->uniq_val) {
            every_element_for_subtraction -= operand;
        }
        return *this;
    }
    unique_valarray operator*(Type&& operand) {
        for(auto& every_element_for_multiplication : this->uniq_val) {
            every_element_for_multiplication *= operand;
        }
        return *this;
    }
    unique_valarray operator/(Type&& operand) {
        if(operand == (Type)0) {throw std::runtime_error("Division by zero");}
        for(auto& every_element_for_division : this->uniq_val) {
            every_element_for_division /= operand;
        }
        return *this;
    }
    unique_valarray operator%(Type&& operand) {
        if(operand == (Type)0) {throw std::runtime_error("Division by zero");}
        for(auto& every_element_for_module_division : this->uniq_val) {
            every_element_for_module_division %= operand;
        }
        return *this;
    }
    unique_valarray operator+(const unique_valarray& other) {
        if(this->uniq_val.size() != other.uniq_val.size()) {
            for(std::size_t plus_vals = 0; plus_vals < this->uniq_val.size(); ++plus_vals) {
                if(plus_vals >= other.uniq_val.size()) {break;}
                this->uniq_val[plus_vals] += other.uniq_val[plus_vals];
            }
        } else {
            for(std::size_t plus_vals = 0; plus_vals < Size; ++plus_vals) {
                this->uniq_val[plus_vals] += other.uniq_val[plus_vals];
            }
        }
        return *this;
    }
    unique_valarray operator-(const unique_valarray& other) {
        if(this->uniqe_val.size() != other.uniq_val.size()) {
            for(std::size_t minus_vals = 0; minus_vals < this->uniq_val.size(); ++minus_vals) {
                if(minus_vals >= other.uniq_val.size()) {break;}
                this->uniq_val[minus_vals] -= other.uniq_val[minus_vals];
            }
        } else {
            for(std::size_t minus_vals = 0; minus_vals < Size; ++minus_vals) {
                this->uniq_val[minus_vals] -= other.uniq_val[minus_vals];
            }
        }
        return *this;
    }
    unique_valarray operator*(const unique_valarray& other) {
        if(this->uniq_val.size() != other.uniq_val.size()) {
            for(std::size_t mult_vals = 0; mult_vals < this->uniq_val.size(); ++mult_vals) {
                if(mult_vals >= other.uniq_val.size()) {break;}
                this->uniq_val[mult_vals] *= other.uniq_val[mult_vals];
            }
        } else {
            for(std::size_t mult_vals = 0; mult_vals < Size; ++mult_vals) {
                this->uniq_val[mult_vals] *= other.uniq_val[mult_vals];
            }
        }
        return *this;
    }
    unique_valarray operator/(const unique_valarray& other) {
        if(this->uniq_val.size() != other.uniq_val.size()) {
            for(std::size_t div_vals = 0; div_vals < this->uniq_val.size(); ++div_vals) {
                if(div_vals >= other.uniq_val.size()) {break;}
                if(other.uniq_val[div_vals] == 0) {
                    throw std::runtime_error("Division by zero");
                }
                this->uniq_val[div_vals] /= other.uniq_val[div_vals];
            }
        } else {
            for(std::size_t div_vals = 0; div_vals < Size; ++div_vals) {
                this->uniq_val[div_vals] /= other.uniq_val[div_vals];
            }
        }
        return *this;
    }
    unique_valarray operator%(const unique_valarray& other) {
        if(this->uniq_val.size() != other.uniq_val.size()) {
            for(std::size_t div_vals = 0; div_vals < this->uniq_val.size(); ++div_vals) {
                if(div_vals >= other.uniq_val.size()) {break;}
                if(other.uniq_val[div_vals] == 0) {
                    throw std::runtime_error("Division by zero");
                }
                this->uniq_val[div_vals] %= other.uniq_val[div_vals];
            }
        } else {
            for(std::size_t div_vals = 0; div_vals < Size; ++div_vals) {
                this->uniq_val[div_vals] %= other.uniq_val[div_vals];
            }
        }
        return *this;
    }
    Type operator[](std::size_t index) {
        if(index < 0 || index >= Size) {throw std::out_of_range("Out of range exception");}
        return uniq_val[index];
    }
}; // UNIQUE_VALARRAY <std::set + std::valarray> //
} /* UNTS.H */
