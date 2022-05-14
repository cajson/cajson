fn sum(n:int) {
    s:int=0
    for i:=1 to n s=s+i
    return s
}

fn main() {
    printf('sum(10)=%d\n', sum(10))
}
