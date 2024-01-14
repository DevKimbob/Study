Iterator <!-- omit in toc -->
===

**Table of Contents**
- [1. Iterator](#1-iterator)
  - [1.1. IntoIterator](#11-intoiterator)
  - [1.2. 이터레이터 생성](#12-이터레이터-생성)
    - [1.2.1. iter와 iter\_mut](#121-iter와-iter_mut)
    - [1.2.2. IntoIterator 구현](#122-intoiterator-구현)
  - [1.3. 이터레이터 어댑터](#13-이터레이터-어댑터)
    - [1.3.1. map](#131-map)
  - [1.3.2. filter\_map](#132-filter_map)
- [2. Iterator 소비하기](#2-iterator-소비하기)
  - [2.1. count, sum, product, max, min](#21-count-sum-product-max-min)
- [3. 나만의 이터레이터 구현하기](#3-나만의-이터레이터-구현하기)
- [4. Passed](#4-passed)


# 1. Iterator
일련의 값들을 산출하는 값으로, 보통 루프에서 뭔가를 반복 처리하기 위한 용도로 많이 쓰인다. `std::iter::Iterator` 트레이트를 구현하고 있는 모든 값을 이터레이터라고 한다.
```rust
trait Iterator {
    type Item;  // 이터레이터가 산출하는 값의 타입
    fn next(&mut self) -> Option<Self::Item>;
    ...
}
```

## 1.1. IntoIterator
어떤 타입을 반복 처리하는 고유한 방법이 존재한다면, 그 타입은 `std::iter::IntoIterator`를 구현할 수 있다. `IntoIterator`를 구현하고 있는 모든 타입은 요청하면 반복 처리 할 수 있다고 해서 `이터러블`이라고 한다.
```rust
trait IntoIterator where Self::IntoIter: Iterator<Item=Self::Item> {
    type Item;
    type IntoIter: Iterator;  // IntoIter : 이터레이터 값 자체의 타입
    fn into_iter(self) -> Self::IntoIter;
}
```
for 루프는 내부적으로 IntoIterator와 Iterator의 메서드들을 호출하도록 된 축약표기이다.
```rust
let v = vec!["a", "b", "c", "d"];

for element in &v {
    println!("{}", element);
}

let mut iterator = (&v).into_iter();
while let Some(element) = iterator.next() {
    println!("{}", element);
}
```

## 1.2. 이터레이터 생성
### 1.2.1. iter와 iter_mut
대부분의 컬렉션 타입은 그 타입의 고유한 이터레이터를 반환하는 `iter`와 `iter_mut`메서드를 제공한다. 이들 메서드가 반환하는 이터레이터는 각 아이템의 `공유된 레퍼런스`와 `변경할 수 있는 레퍼런스`를 산출한다.
```rust
let v = vec![10, 20, 30];
let mut iterator = v.iter();
println!("{}", iterator.next().unwrap());  // 10
println!("{}", iterator.next().unwrap());  // 20
println!("{}", iterator.next().unwrap());  // 30

let mut v = vec![10, 20, 30];
let mut iter_mut = v.iter_mut();
*iter_mut.next().unwrap() += 1;
*iter_mut.next().unwrap() += 1;
*iter_mut.next().unwrap() += 1;
println!("{}, {}, {}", v[0], v[1], v[2]);  // 11, 21, 31
```

### 1.2.2. IntoIterator 구현
어떤 타입이 `IntoIterator`를 구현하고 있다면 `into_iter`메서드를 호출할 수 있다. 대부분의 컬렉션들은 `IntoIterator`의 구현을 여러 벌 제공하는데, `공유된 레퍼런스(&T)`용, `변경할 수 있는 레퍼런스(&mut T)`용, `이동(T)`용으로 나뉜다.
```rust
for element in &collection { ... }  // &T
for element in &mut collection { ... }  // &mut T
for element in collection { ... }  // T
```

IntoIterator의 변형 중에서 `공유된 레퍼런스`용과 `변경할 수 있는 레퍼런스`용 두 가지는 `iter`와 `iter_mut`를 호출하는 것과 같은데, for 루프를 쓰지 않는 경우에는 `(&variable).into_iter()`보다 `variable.iter()`가 더 명확함을 기억하자.

## 1.3. 이터레이터 어댑터
줄여서 어댑터라고도 부르며, 기존의 이터레이터를 가져다가 유용한 동작을 하는 새로운 이터레이터로 탈바꿈하는 일을 한다.

### 1.3.1. map
이터레이터가 산출하는 아이템에 클로저를 적용한다.
```rust
let text = "hello world".to_string();
// let mut v = text.chars();
let mut v = text.chars().map(|c| c.to_uppercase());  // "hello world"에 문자 단위로 클로저를 적용
for i in v {
    print!("{} ", i);
}  // H E L L O   W O R L D
```

이터레이터와 어댑터에서 주의할 점은 이터레이터를 생성하거나, 어댑터를 이터레이터에 대고 호출한다고 해서 아이템들이 곧바로 소비되는 건 아니다. 이터레이터에 대고 `next`를 호출해야만 실질적인 뭔가가 작동한다.
```rust
let text = "hello world".to_string();
let mut v = text.chars().map(|x| { print!("{} -> ", x); x });
for i in v {  // i: ToUppercase
    println!("{}", i);
}
// h -> H
// e -> E
// l -> L
// l -> L
// o -> O
//   ->  
// w -> W
// o -> O
// r -> R
// l -> L
// d -> D
```

## 1.3.2. filter_map
반복 처리 과정에서 일부 아이템을 삭제하고 싶을 때 사용할 수 있다.
```rust
let text = "hello world".to_string();
let mut v = text.chars().filter_map(|x| {
    match x {
        'h' | 'l' => None,
        _ => Some(x),
    }
});  // 클로저가 None을 반환하면 아이템이 반복 처리 과정에서 제외되고, Some(T)를 반환하면 이터레이터가 산출하는 아이템이 됨
for i in v {
    print!("{}", i);
}  // eo word
```

# 2. Iterator 소비하기
## 2.1. count, sum, product, max, min
이터레이터가 Non을 반환할 때 까지 산출하는 아이템의 개수, 합, 곱, 최대, 최소를 계산한다.
```rust
let a = (1..=10);

let cnt = a.clone().count();  // clone으로 복사를 해야 함에 주의
let sum:i32 = a.clone().sum();
let mul:i32 = a.clone().product();
let max = a.clone().max().unwrap();
let min = a.clone().min().unwrap();

println!("{}, {}, {}, {}, {}", cnt, sum, mul, max, min);
```

# 3. 나만의 이터레이터 구현하기
사용자 정의 타입에 `IntoIterator`와 `Iterator`트레이트를 구현하면 나만의 이터레이터를 구현할 수 있다.
```rust
struct I32Range {
    start: i32,
    end: i32,
}

impl Iterator for I32Range {
    type Item = i32;
    fn next(&mut self) -> Option<i32> {
        if self.start >= self.end {
            return None;
        }
        let result = Some(self.start);
        self.start += 1;
        result
    }
}

for i in (I32Range { start: 2, end: 6 }) {
    println!("{}", i);
} 

let mut iterator = (I32Range { start: 2, end: 6}).into_iter();
while let Some(element) = iterator.next() {
    println!("{}", element);
}
```

```rust
enum BinaryTree<T> {
    Empty,
    NonEmpty(Box<TreeNode<T>>)
}

struct TreeNode<T> {
    element: T,
    left: BinaryTree<T>,
    right: BinaryTree<T>,
}

struct TreeIter<'a, T> {
    unvisited: Vec<&'a TreeNode<T>>
}

impl<T: Ord> BinaryTree<T> {
    fn add(&mut self, value: T) {
        match *self {
            BinaryTree::Empty => {
                *self = BinaryTree::NonEmpty(Box::new(TreeNode {
                    element: value,
                    left: BinaryTree::Empty,
                    right: BinaryTree::Empty,
                }))
            }
            BinaryTree::NonEmpty(ref mut node) => {
                if value <= node.element {
                    node.left.add(value);
                } else {
                    node.right.add(value);
                }
            }
        }
    }
}

impl<'a, T: 'a> TreeIter<'a, T> {
    fn push_left_edge(&mut self, mut tree: &'a BinaryTree<T>) {
        while let BinaryTree::NonEmpty(ref node) = *tree {
            self.unvisited.push(node);
            tree = &node.left
        }
    }
}

impl<T> BinaryTree<T> {
    fn iter(&self) -> TreeIter<T> {
        let mut iter = TreeIter { unvisited: Vec::new() };
        iter.push_left_edge(self);
        iter
    }
}

impl<'a, T: 'a> IntoIterator for &'a BinaryTree<T> {
    type Item = &'a T;
    type IntoIter = TreeIter<'a, T>;
    fn into_iter(self) -> Self::IntoIter {
        self.iter()
    }
}

impl<'a, T> Iterator for TreeIter<'a, T> {
    type Item = &'a T;
    fn next(&mut self) -> Option<&'a T> {
        let node = self.unvisited.pop()?;
        self.push_left_edge(&node.right);
        Some(&node.element)
    }
}

let mut tree = BinaryTree::Empty;
tree.add(30);
tree.add(20);
tree.add(10);
tree.add(40);

let mut iterator = tree.iter();
while let Some(element) = iterator.next() {
    println!("{}", element);
}
for i in &tree {
    println!("{}", i);
}
```

# 4. Passed
from_fn, successors  
drain 메서드  
flat_map  
flatten  
take, take_while  
skip, skip_while  
peekable  
fuse  
rev  
inspect  
chain  
enumerate  
zip  
by_ref  
cloned, copied  
cycle  

max_by, min_by  
max_by_key, min_by_key  
아이템 시퀀스 비교하기  
any, all  
position, rposition, ExactSizeIterator  
fold, rfold  
try_fold, try_rfold  
nth, nth_back  
last  
find, rfind, find_map  

컬렉션 만들기: collect, FromIterator  
Extend  
partition  
for_each, try_for_each  