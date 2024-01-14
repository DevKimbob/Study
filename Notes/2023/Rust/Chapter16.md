Collection <!-- omit in toc -->
===

**Table of Contents**
- [1. Collection](#1-collection)
- [2. Vec\<T\>](#2-vect)
  - [2.1. 연결](#21-연결)
  - [2.2. 분할](#22-분할)
  - [2.3. 교환](#23-교환)
  - [2.4. 채움](#24-채움)
  - [2.5. 정렬](#25-정렬)
  - [2.6. 검색](#26-검색)
  - [2.7. 비교](#27-비교)
  - [2.8. 임의의 요소](#28-임의의-요소)
- [3. VecDeque\<T\>](#3-vecdequet)
- [4. BinaryHeap](#4-binaryheap)
- [5. HashMap\<K, V\>와 BTreeMap\<K, V\>](#5-hashmapk-v와-btreemapk-v)
  - [5.1. 항목(Entry)](#51-항목entry)
- [6. HashSet\<T\>와 BTreeSet\<T\>](#6-hashsett와-btreesett)
- [7. Passed](#7-passed)


# 1. Collection
데이터를 메모리에 저장하기 위한 제네릭 타입으로 다음과 같이 8가지가 있다. 보통은 `Vec<T>`, `HashMap<K, V>`, `HashSet<T>`를 가장 많이 쓴다.
|컬렉션|설명|C++|Java|Python|
|---|---|---|---|---|
|Vec<T>|크기가 늘 수 있는 배열|vector|ArrayList|list|
|VecDeque<T>|양방향 큐(크기가 늘 수 있는 링 버퍼)|deque|ArrayDeque|collections.deque|
|LinkedListT>|양방향 연결 리스트|list|LinkedList|-|
|BinaryHeap<T> whereT: Ord|최대 힙|priority_queue|PriorityQueue|heapq|
|HashMap<K, V> where K: Eq + Hash|키-값 해시 테이블|unordered_map|HashMap|dict|
|BTreeMap<K, V> where K: Ord|정렬된 키-값 테이블|map|TreeMap|-|
|HashSet<T> where T: Eq + Hash|순서 없는 해시 기반 세트|unordered_set|HashSet|set|
|BTreeSet<T> where T: Ord|정렬된 세트|set|TreeSet|-|

# 2. Vec\<T>
힙에 할당되어 크기가 늘 수 있는 T 타입으로 된 값들의 배열이다. 길이와 용량, 그리고 요소들이 저장되는 힙 공간을 가리키는 포인터로 세 개의 필드를 가지고 있다.
```rust
let v = vec![10, 20, 30];  // Vec 생성은 vec! 매크로가 제일 쉬움
let first = &v[0];
let second = v[1];  // Copy
let third = v[2].clone();  // Clone

let v2 = vec![0, 1, 2, 3, 4, 5, 6, 7];
let slice = &v2[1..3];  // [1, 2]
let slice_copy = v2[5..7].to_vec();  // [5, 6]

// 슬라이스 메서드는 모두 배열과 벡터에 쓸 수 있음
let s = vec![0, 1, 2, 3, 4, 5, 6, 7];
println!("{}", s.first().unwrap());  // 0
println!("{}", s.last().unwrap());  // 7
println!("{}", s.get(2).unwrap());  // 2

// 벡터 메소드 예시
vec.push(value);
vec.pop();
vec.insert(index, value);
```

## 2.1. 연결
배열, 슬라이스, 벡터 자체를 요소로 갖는 배열, 슬라이스, 벡터를 뜻하는 배열의 배열에 작용하는 메서드는 두 가지 이다.
```rust
let vv1 = [[1, 2], [3, 4], [5, 6]].concat();  // [1, 2, 3, 4, 5, 6]
let vv2 = [[1, 2], [3, 4], [5, 6]].join(&0);  // [1, 2, 0, 3, 4, 0, 5, 6]
// slices.join(&separator), 슬라이스들 사이에 separator 값의 복사본을 끼워 넣는다.
```

## 2.2. 분할
<!-- 비mut 레퍼런스 여러 개를 한번에 배열, 슬라이스, 벡터로 가져오는 건 쉽다. 그러나 mut 레퍼런스 여러 개를 가져오는 건 쉽지 않다.
```rust
let mut v = vec![0, 1, 2, 3];
let a = &mut v[1];
let b = &mut v[2];  // 컴파일 오류. v를 변경할 수 있게 빌려오는 건 동시에 두 번 이상 할 수 없음

*a = 6;
*b = 7;
``` -->
러스트에는 배열, 슬라이스, 벡터의 일부를 참조하는 mut 레퍼런스 여러 개를 한 번에 빌려올 수 있는 다양한 메서드들이이 있다.
```rust
slice.iter(), slice.iter_mut()
slice.split_at(index), slice.iter_at_mut(index)
slice.split(is_sep)  // is_sep : 함수나 클로저 사용
slice.chunks(n), slice.chunks_mut(n)  // 길이가 n인 서로 겹치지 않는 서브슬라이스들을 반복 처리하는 이터레이터를 반환
```

## 2.3. 교환
```rust
slice.swap(i. j)  // slice[i], slice[j] 요소 교환
slice_a.swap(&mut slice_b)  // slice_a, slice_b의 전체 내용 교환, 서로 길이는 같아야 함
vec.swap_remove(i)  // vec[i]를 빼서 반환하는데, 
// 나머지 요소들을 밀어서 빈틈을 메꾸는게 아니라 vec의 마지막 요소를 빈틈으로 옮긴다.
```

## 2.4. 채움
```rust
slice.fill(value)  // 슬라이스를 value의 복제본으로 채운다
slice.fill_with(function)  // 슬라이스를 주어진 함수를 호출해서 만든 값들로 채운다.
```

## 2.5. 정렬
```rust
slice.sort()  // 요소들을 오름차순으로 정렬. 요소 타입이 Ord를 구현하고 있을 떄만 존재
slice.sort_by_key(key)  // 함수나 클로저 key에 의해 주어지는 정렬 키를 기준으로 요소들을 오름차순으로 정렬. key의 타입은 반드시 K: Ord인 Fn(&T) -> K를 구현하고 있어야 한다.
```
<!-- slice.sort_by(cmp)  // 함수나 클로저 cmp를 써서 요소들을 정렬. cmp는 Fn(&T, &T) -> std::cmp::Ordering을 구현하고 있어야 함 -->

## 2.6. 검색
```rust
slice.binary_search(&value), slice.binary_searcy_by_key(&value, key)  // 정렬된 벡터에 대해 사용
slice.contains(&value)  // 정렬되어 있지 않은 벡터
```

## 2.7. 비교
타입 T가 연산자 `==`와 `!=`를 지원하면 배열 [T; N], 슬라이스 [T], 벡터 Vec\<T>도 이를 지원한다.
```rust
slice.starts_with(other)  // slice가 슬라이스 other의 요소들과 동일한 일련의 값으로 시작하면 true 반환
slice.ends_with(other)
```

## 2.8. 임의의 요소
```rust
slice.choose(&mut rng)  // 슬라이스에서 임의의 요소를 참조하는 레퍼런스를 반환
slice.shuffle(&mut rng)  // 슬라이스의 요소들을 무작위로 섞는다
```
이들은 `rand::Rng` 트레이트의 메서드이므로 호출하려면 난수 생성기 Rng가 필요하다.
```rust
use rand::seq::SliceRandom;
use rand::thread_rng;

my_vec.shuffle(&mut thread_rng());
```

# 3. VecDeque\<T>
```rust
deque.push_front(value)
deque.pop_front()

deque.push_back(value)
deque.pop_back()
```

# 4. BinaryHeap<T>
큰 값이 항상 큐의 맨 앞에 오도록 요소들이 느슨하게 편성된 컬렉션이다.
```rust
heap.push(value)
heap.pop()
heap.peek(), heap.peek_mut()
```

# 5. HashMap\<K, V>와 BTreeMap\<K, V>
맵은 목(entry)이라고 하는 키-값 쌍의 컬렉션이다. 같은 키를 갖는 항목이 둘 이상 존재하지 않으며, 조회 테이블이라고 할 수 있다.
```rust
map.contains_key(&key)
map.get(&key), map.get_mut(&key)
map.insert(key, value)  // 기존 값이 있으면 반환
map.extend(iterable)  // iterable의 (K, V) 아이템들을 반복처리해서 주어진 키-값 쌍을 하나씩 map에 끼워 넣는다
```

## 5.1. 항목(Entry)
HashMap과 BTreeMap은 모두 각자 자신과 대응하는 Entry타입을 가지고 있다. 항목의 핵심은 맵에서 불필요한 조회를 없애는 것이다.
```rust
if !student_map.contains_key(name) {
    student_mep.insert(name.to_string(), Student::new());
}
let record = student_map.get_mut(name).unwrap();

let record = student_map.entry(name.to_string()).or_insert_with(Student::new);
```
```rust
map.entry(key)
// 주어진 key에 대응하는 Entry를 반환한다.
// Entry 타입은 맵 내부에 있는 공간 하나를 참조하는 mut 레퍼런스 역할을 한다.

map.entry(key).or_insert(value)
// key에 대응하는 항목이 없으면 주어진 value를 새로 끼워 넣는다.
map.entry(key).or_default()
map.entry(key).or_insert_with(default_fn)
map.entry(key).and_modify(closure)
```

# 6. HashSet\<T>와 BTreeSet\<T>
세트는 집합에 속하는지 아닌지를 빠르게 알아볼 수 있도록 편성된 값의 컬렉션이다. 사실상 키-값 쌍이 아니라 키만 가지고 있는 맵과 같다. 실제로 러스트의 두 가지 세트 타입인 `HashSet<T>`와 `BTreeSet<T>`는 `HashMap<T, ()`와 `BTreeMap<T, ()>`를 가지고 구현한 얇은 래퍼다.
```rust
iter.collect()
set.contains(&value)
set.insert(value)
set.remove(&value)

set.intersection(&set2)  // same as &set1 & &set2
set.union(&set2)  // same as &set1 | &set2
```

# 7. Passed
Hashing  
