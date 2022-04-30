mean:fn(a) {
    s=0
    i=0
    while (s < a.length) {
        s = s+a[i]
    }
    return s/a.length
}

print(mean([1,2,3,4,5]))
