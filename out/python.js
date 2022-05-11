// source file: prog/python.cj
import '../sys/cj.js'
/* 0  */	import * as p from 'https://deno.land/x/python/mod.ts';
/* 2  */	let python=p.python;
/* 4  */	let np=python.import('numpy');
/* 5  */	let plt=python.import('matplotlib.pyplot');
/* 7  */	let xpoints=np.array([1,8]);
/* 8  */	let ypoints=np.array([3,10]);
/* 10 */	plt.plot(xpoints,ypoints);
/* 11 */	plt.show();
