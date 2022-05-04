e2c:map{dog:'gou' cat:'mou' a:'one' the:'this' chase:'go' bite:'eat'}

translate:fn(ewords:[]) {
  cwords:[]
  for e in ewords {
    cwords.push(e2c[e])
  }
  return cwords
}

c = translate(['a' 'dog' 'chase' 'a' 'cat'])
print(c)
