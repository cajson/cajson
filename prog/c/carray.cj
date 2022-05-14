fn mean(a:int*, len:int) {
    s:int=0
    for i:=0 to len-1 s = s+a[i]
    return s/len
}

fn main() {
    a:int* = [1,2,3,4,5]
    printf('mean([1 2 3 4 5])=%d\n', mean(a, 5))
}
 