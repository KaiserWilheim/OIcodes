#[warn(unused_variables)]
use std::io;

static mut A: [i64; 100010] = [0; 100010];
fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let mut s = input.split_whitespace();
    let n: i64 = s.next().unwrap().parse().unwrap();
    let m: i64 = s.next().unwrap().parse().unwrap();
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    unsafe {
        s = input.split_whitespace();
        for i in 1..=n {
            A[i as usize] = s.next().unwrap().parse().unwrap();
        }
    }
    unsafe {
        build(1, 1, n);
    }
    for _i in 0..m {
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        s = input.split_whitespace();
        let op: i64 = s.next().unwrap().parse().unwrap();
        let x: i64 = s.next().unwrap().parse().unwrap();
        let y: i64 = s.next().unwrap().parse().unwrap();
        if op == 1 {
            let k: i64 = s.next().unwrap().parse().unwrap();
            unsafe {
                segadd(1, x, y, k);
            }
        } else if op == 2 {
            let ans: i64 = unsafe { segsum(1, x, y) };
            println!("{}", ans);
        }
    }
}

static mut L: [i64; 800080] = [0; 800080];
static mut R: [i64; 800080] = [0; 800080];
static mut V: [i64; 800080] = [0; 800080];
static mut T: [i64; 800080] = [0; 800080];

unsafe fn pushup(p: usize) {
    V[p] = V[p << 1] + V[p << 1 | 1];
}
unsafe fn pushdown(p: usize) {
    if T[p] != 0 {
        V[p << 1] += (R[p << 1] - L[p << 1] + 1) * T[p];
        V[p << 1 | 1] += (R[p << 1 | 1] - L[p << 1 | 1] + 1) * T[p];
        T[p << 1] += T[p];
        T[p << 1 | 1] += T[p];
        T[p] = 0;
    }
}
unsafe fn build(p: usize, l: i64, r: i64) {
    L[p] = l;
    R[p] = r;
    if l == r {
        V[p] = A[l as usize];
        T[p] = 0;
        return;
    }
    let mid: i64 = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

unsafe fn segadd(p: usize, l: i64, r: i64, k: i64) {
    if L[p] >= l && R[p] <= r {
        V[p] += (R[p] - L[p] + 1) * k;
        T[p] += k;
        return;
    }
    pushdown(p);
    let mid: i64 = (L[p] + R[p]) >> 1;
    if l <= mid {
        segadd(p << 1, l, r, k)
    };
    if r > mid {
        segadd(p << 1 | 1, l, r, k)
    };
    pushup(p);
}
unsafe fn segsum(p: usize, l: i64, r: i64) -> i64 {
    if L[p] >= l && R[p] <= r {
        return V[p];
    };
    pushdown(p);
    let mut res: i64 = 0;
    let mid: i64 = (L[p] + R[p]) >> 1;
    if l <= mid {
        res += segsum(p << 1, l, r)
    };
    if r > mid {
        res += segsum(p << 1 | 1, l, r)
    };
    return res;
}
