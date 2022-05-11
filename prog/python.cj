import 'https://deno.land/x/python/mod.ts' as p

python := p.python

np := python.import('numpy')
plt := python.import('matplotlib.pyplot')

xpoints := np.array([1, 8])
ypoints := np.array([3, 10])

plt.plot(xpoints, ypoints)
plt.show()
